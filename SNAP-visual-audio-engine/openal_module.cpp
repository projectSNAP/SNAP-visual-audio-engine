#define _USE_MATH_DEFINES
#include <cmath> // Trigonometric functions
#include "stdafx.h"
#include "openal_module.h"
#include <limits.h> // SHRT_MAX

#include <iostream>

using namespace std;

/**
 * @brief      OpenAL specific error handling defines
 */
#define CASE_RETURN(err) case (err): return "##err"
const char* al_err_str(ALenum err) {
	switch (err) {
		CASE_RETURN(AL_NO_ERROR);
		CASE_RETURN(AL_INVALID_NAME);
		CASE_RETURN(AL_INVALID_ENUM);
		CASE_RETURN(AL_INVALID_VALUE);
		CASE_RETURN(AL_INVALID_OPERATION);
		CASE_RETURN(AL_OUT_OF_MEMORY);
	}
	return "unknown";
}
#undef CASE_RETURN
#define __al_check_error(file,line) \
    do { \
        ALenum err = alGetError(); \
        for(; err!=AL_NO_ERROR; err=alGetError()) { \
            std::cerr << "AL Error " << al_err_str(err) << " at " << file << ":" << line << std::endl; \
        } \
    }while(0)
#define al_check_error() \
    __al_check_error(__FILE__, __LINE__)

/**
 * @brief      Constructs the object.
 *
 * @param[in]  count   The number of sources.
 * @param[in]  width   The width of the frame.
 * @param[in]  height  The height of the frame.
 * @param[in]  FOV     The field-of-view of the frame.
 */
openal_module::openal_module(int width, int height, float FOV)
{
	// Set Globals
	sourceCount = 0;
	bufferCount = 0;
	frameWidth = width;
	frameHeight = height;
	horizontalFOV = FOV;
	verticalFOV = 2 * atan(tan(horizontalFOV / 2) * (frameHeight / frameWidth));
	// Initialize pointers
	device = NULL;
	context = NULL;
	sources = NULL;
	buffers = NULL;
	sourceMatCoords = NULL;
	// Create OpenAL device
	const char *defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	device = alcOpenDevice(defname);
	al_check_error();
	// Create Context
	context = alcCreateContext(device, NULL);
	al_check_error();
	alcMakeContextCurrent(context);
	al_check_error();
	// Set default listener orientation is specifiec by an "at" vector and an "up" vector
	// x+ = right, y+ = forward, z+ = up
	// see https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
	// for info on listener orientation section 4.2.1.
	ALfloat listenerOri[] = { 0.f, 1.f, 0.f, 0.f, 0.f, 1.f };
	alListener3f(AL_POSITION, 0, 0, 0);
	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);
}

/**
 * @brief      Destroys the object.
 */
openal_module::~openal_module()
{
	// TODO: also destroy sources and buffers
	alcMakeContextCurrent(NULL);
	al_check_error();
	alcDestroyContext(context);
	al_check_error();
	alcCloseDevice(device);
	al_check_error();
}


// TODO: add the ability to create buffers of varying waveforms

void openal_module::init_sine_buffers(int count, int sampleRate, float amplitude, int frequency) {
	bufferCount = count;
	buffers = new ALuint[bufferCount];
	alGenBuffers(bufferCount, buffers);
	short *samples = new short[sampleRate];
	for (int buffer = 0; buffer < bufferCount; buffer++) {
		for (int i = 0; i < sampleRate; ++i) {
			samples[i] = ((amplitude * SHRT_MAX) * sin(2 * M_PI * i * frequency / sampleRate));
		}
		alBufferData(buffers[buffer], AL_FORMAT_MONO16, samples, sampleRate * sizeof(short), sampleRate);
		al_check_error();
	}
}

/**
 * @brief      Creates sources.
 */
void openal_module::init_sources(int count)
{
	sourceCount = count;
	sources = new ALuint[sourceCount];
	alGenSources(sourceCount, sources);
	sourceMatCoords = new int[sourceCount];
	al_check_error();
	// Set the vertical positions of all the sources.
	for (int i = 0; i < sourceCount; ++i) {
		// Calculate where the sournce would fall on the image matrix
		sourceMatCoords[i] = (frameHeight / (sourceCount * 2)) + (frameHeight / sourceCount) * i;
		// Set the proper flags
		alDistanceModel(AL_INVERSE_DISTANCE);
		al_check_error();
		alSourcef(sources[i], AL_ROLLOFF_FACTOR, 1.f);
		al_check_error();
		alSourcef(sources[i], AL_REFERENCE_DISTANCE, 0.5f);
		al_check_error();
		alSourcei(sources[i], AL_SOURCE_RELATIVE, AL_TRUE);
		al_check_error();
		alSourcei(sources[i], AL_LOOPING, AL_TRUE);
		al_check_error();
		alSource3f(sources[i], AL_POSITION, 10, 0, 0);
		al_check_error();
	}
}

const unsigned int *openal_module::get_sources() {
	return sources;
}

const unsigned int *openal_module::get_buffers() {
	return sources;
}

/**
 * @brief      Adds a buffer to a source.
 *
 * @param[in]  buffer  The buffer
 * @param[in]  source  The source
 */
void openal_module::source_set_buffer(int source, int buffer)
{
	// Add buffers to each source and set properties
	alSourcei(sources[source], AL_BUFFER, buffers[buffer]);
	al_check_error();
}

/**
 * @brief      Tells the source to start playing.
 *
 * @param[in]  source  The source
 */
void openal_module::source_play(int source)
{
	alSourcePlay(sources[source]);
	al_check_error();
}

void openal_module::source_stop(int source)
{
	alSourceStop(sources[source]);
	al_check_error();
}

void openal_module::source_pause(int source)
{
	alSourcePause(sources[source]);
	al_check_error();
}

void openal_module::source_add_pitch(int source, float addPitch) {
	ALfloat currentPitch;
	alGetSourcef(sources[source], AL_PITCH, &currentPitch);
	al_check_error();
	currentPitch += addPitch;
	alSourcef(sources[source], AL_PITCH, currentPitch);
	al_check_error();
}

void openal_module::source_set_pitch(int source, float pitch) {
	alSourcef(sources[source], AL_PITCH, pitch);
	al_check_error();
}

/**
 * @brief      Moves a source around within the bounds of the FOV.
 *
 * @param[in]  source     The source
 * @param[in]  latitude   The latitude in radians
 * @param[in]  longitude  The longitude in radians
 */
void openal_module::source_move(int source, float deltaTheta, float deltaPhi)
{
	// get position of source
	float oldX;
	float oldY;
	float oldZ;
	alGetSource3f(sources[source], AL_POSITION, &oldX, &oldY, &oldZ);
	al_check_error();
	float oldTheta = cartesian_to_spherical_theta(oldX, oldY, oldZ);
	float oldPhi = cartesian_to_spherical_phi(oldX, oldY, oldZ);
	printf("BEFORE MOVE, x:%f, y:%f, z:%f, theta:%f, phi:%f\n", oldX, oldY, oldZ, rad_to_deg(oldTheta), rad_to_deg(oldPhi));
	float newTheta = normalize_angle(oldTheta + deltaTheta);
	float newPhi = normalize_angle(oldPhi + deltaPhi);
	float newX = 0.f;
	float newY = 0.f;
	float newZ = 0.f;
	spherical_to_cartesian(10.f, newTheta, newPhi, &newX, &newY, &newZ);
	printf("AFTER MOVE, x:%f, y:%f, z:%f, theta:%f, phi:%f\n", newX, newY, newZ, rad_to_deg(newTheta), rad_to_deg(newPhi));
	alSource3f(sources[source], AL_POSITION, newX, newY, newZ);
	al_check_error();
	// if new position is outside bounds, set new position to bounds
	// TODO: figure out how to keep latitude and longitude within bounds
	// of field-of-view.
}

void openal_module::source_set_pos(int source, float x, float y, float z) {
	alSource3f(sources[source], AL_POSITION, x, y, z);
	al_check_error();
}

float openal_module::source_get_theta(int source) {
	float x;
	float y;
	float z;
	alGetSource3f(sources[source], AL_POSITION, &x, &y, &z);
	return cartesian_to_spherical_theta(x, y, z);
}

float openal_module::cartesian_to_spherical_rho(float x, float y, float z) {
	x = zero_threshold(x);
	y = zero_threshold(y);
	z = zero_threshold(z);
	if (x != 0.f || y != 0.f || z != 0.f) {
		return zero_threshold(sqrt(pow(x, 2.f) + pow(y, 2.f) + pow(z, 2.f)));
	}
	return 0.f;
}

float openal_module::cartesian_to_spherical_theta(float x, float y, float z) {
	x = zero_threshold(x);
	y = zero_threshold(y);
	z = zero_threshold(z);
	if (x != 0.f || y != 0.f) {
		return normalize_angle(atan2(y, x));
	}
	cout << "3\n";
	return 0.f;
}

float openal_module::cartesian_to_spherical_phi(float x, float y, float z) {
	x = zero_threshold(x);
	y = zero_threshold(y);
	z = zero_threshold(z);
	float phi;
	if (x != 0.f || y != 0.f || z != 0.f) {
		if (z != 0.f) {
			phi = atan(sqrt(pow(x, 2.f) + pow(y, 2.f)) / z);
		} else {
			phi = acos(z / sqrt(pow(x, 2.f) + pow(y, 2.f) + pow(z, 2.f)));
		}
		return normalize_angle(phi);
	}
	return 0.f;
}

void openal_module::cartesian_to_spherical(float x, float y, float z, float *rho, float *theta, float *phi) {
	*rho = cartesian_to_spherical_rho(x, y, z);
	*theta = cartesian_to_spherical_theta(x, y, z);
	*phi = cartesian_to_spherical_phi(x, y, z);
}

void openal_module::spherical_to_cartesian(float rho, float theta, float phi, float *x, float *y, float *z) {
	rho = zero_threshold(rho);
	theta = normalize_angle(theta);
	phi = normalize_angle(phi);
	*x = zero_threshold(rho * sin(phi) * cos(theta));
	*y = zero_threshold(rho * sin(phi) * sin(theta));
	*z = zero_threshold(rho * cos(phi));
}

float openal_module::zero_threshold(float num) {
	if (fabs(num) < 0.000010)
		num = 0.f;
	return num;
}

float openal_module::normalize_angle(float angle) {
	float fullCircle = 2 * M_PI;
	fmod(angle, fullCircle);
	if (angle < 0.f)
		angle = fullCircle + angle;
	return zero_threshold(angle);
}

float openal_module::deg_to_rad(float degrees) {
	return degrees * M_PI / 180.f;
}

float openal_module::rad_to_deg(float radians) {
	return radians * 180.f / M_PI;
}
