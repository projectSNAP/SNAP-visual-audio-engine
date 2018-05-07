#define _USE_MATH_DEFINES
#include <cmath> // Trigonometric functions
#include <limits.h> // SHRT_MAX
#include <iostream>

#include "openal_module.h"

#define SAMPLE_RATE 44100.f

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
 * @param[in]  FOV     The field-of-view of the frame in degrees.
 */
openal_module::openal_module(int width, int height, float FOV)
{
	// TODO: set limit on height to 16 and throw error otherwise.
	// Set Globals
	horizontalFOV = normalize_angle(deg_to_rad(FOV));
	xMax = width;
	yMax = height;
	// Initialize pointers
	device = NULL;
	context = NULL;
	sources = NULL;
	buffers = NULL;
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
	// +y = right, -x = forward, +z = up
	// see https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
	// for info on listener orientation section 4.2.1.
	ALfloat listenerOri[] = { -1.f, 0.f, 0.f, 0.f, 0.f, 1.f };
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


/**
 * @brief      Create an array of buffers that contain a sine wave, each of
 *             increasing frequency.
 *
 * @param[in]  count         The number of buffers to create.
 * @param[in]  length        The length of each buffer in seconds.
 * @param[in]  frequencyMin  The low end of the frequency range.
 * @param[in]  frequencyMax  The high end of the frequency range.
 */
void openal_module::init_sine_buffers(int count, float length, float frequencyMin, float frequencyMax) {
	// Calculate frequency increment
	float freqInc = (frequencyMax - frequencyMin) / count;
	if (buffers != NULL) {
		free(buffers);
	}
	buffers = new ALuint[count];
	alGenBuffers(count, buffers);
	int sampleSize = SAMPLE_RATE * length;
	short *samples = new short[sampleSize];
	float currFreq = frequencyMax;
	for (int buffer = 0; buffer < count; buffer++) {
		for (int i = 0; i < sampleSize; ++i) {
			samples[i] = ((SHRT_MAX) * sin(2 * M_PI * i * currFreq / SAMPLE_RATE));
		}
		alBufferData(buffers[buffer], AL_FORMAT_MONO16, samples, sampleSize * sizeof(short), SAMPLE_RATE);
		currFreq -= freqInc;
		al_check_error();
	}
}


/**
 * @brief      OpenAL code for creating sources.
 */
void openal_module::init_sources(int count)
{
	sources = new ALuint[count];
	alGenSources(count, sources);
	al_check_error();
	// Set the vertical positions of all the sources.
	for (int i = 0; i < count; ++i) {
		// Set the proper flags
		alDistanceModel(AL_INVERSE_DISTANCE);
		al_check_error();
		alSourcef(sources[i], AL_ROLLOFF_FACTOR, 1.f);
		al_check_error();
		alSourcef(sources[i], AL_REFERENCE_DISTANCE, 1.f);
		al_check_error();
		alSourcei(sources[i], AL_SOURCE_RELATIVE, AL_FALSE);
		al_check_error();
		alSourcei(sources[i], AL_LOOPING, AL_TRUE);
		al_check_error();
		alSource3f(sources[i], AL_POSITION, 10, 0, 0);
		al_check_error();
		// Set initial position
		source_set_pos(0, i);
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
 * @brief      Tells the source to start playing it's assigned buffer.
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

void openal_module::source_set_pitch(int source, float pitch) {
	alSourcef(sources[source], AL_PITCH, pitch);
	al_check_error();
}

void openal_module::source_set_gain(int source, float gain) {
	alSourcef(sources[source], AL_GAIN, gain);
	al_check_error();
}

float openal_module::source_get_gain(int source) {
	float gain = 0.0;
	alGetSourcef(sources[source], AL_GAIN, &gain);
	al_check_error();
	return gain;
}


void openal_module::source_set_pos(int x, int y) {
	// Make sure x and y are within bounds
	if ( x >= xMax)
		x = xMax - 1;
	else if (x < 0)
		x = 0;
	if (y >= yMax)
		y = yMax - 1;
	else if (y < 0)
		y = 0;
	// Find the start angle since theta starts at 0 (-x axis) behind the listener
	// and we want our x axis to start on the left side of the listener
	float startAngle = (horizontalFOV / 2.0) + M_PI;
	// The angle increment is the size (in radians) of each x increment.
	float angleIncrement = horizontalFOV / xMax;
	float theta = startAngle - (angleIncrement / 2.0) - (angleIncrement * x);
	float phi = deg_to_rad(90);
	float rho = 10.f;
	// Get the new coordinates in cartesian
	float newX = 0.f;
	float newY = 0.f;
	float newZ = 0.f;
	spherical_to_cartesian(rho, theta, phi, &newX, &newY, &newZ);
	// Set the source position
	alSource3f(sources[y], AL_POSITION, newX, newY, newZ);
	al_check_error();
}

float openal_module::source_get_theta(int source) {
	float x;
	float y;
	float z;
	alGetSource3f(sources[source], AL_POSITION, &x, &y, &z);
	return cartesian_to_spherical_theta(x, y, z);
}

void openal_module::source_print_position(int source)
{
	float x, y, z, rho, theta, phi;
	alGetSource3f(sources[source], AL_POSITION, &x, &y, &z);
	cartesian_to_spherical(x, y, z, &rho, &theta, &phi);
	printf("SOURCE[%d] POSITION: x:%f, y:%f, z:%f, rho:%f, theta:%f, phi:%f\n", source, x, y, z, rad_to_deg(rho), rad_to_deg(theta), rad_to_deg(phi));
}

float openal_module::cartesian_to_spherical_rho(float x, float y, float z) {
	// TODO: fix or remove rho...this does not calculate the correct rho.
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

/**
 * @brief      Threshold for determining if a float value is essentially 0. If
 *             the number is below the threshold return true 0.0, else return
 *             the number.
 *
 * @param[in]  num   The number
 */
float openal_module::zero_threshold(float num) {
	if (fabs(num) < 0.000010)
		num = 0.f;
	return num;
}

/**
 * @brief      Normalize angle to be within the range of (0.0 to 2*PI). 
 *
 * @param[in]  angle  The angle
 *
 * @return     normalizedAngle The equivalent normalized angle.
 */
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
