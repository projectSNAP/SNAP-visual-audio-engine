#define _USE_MATH_DEFINES
#include <cmath> // Trigonometric functions
#include "stdafx.h"
#include "openal_module.h"

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
openal_module::openal_module(int count = 16, int width = 1920, int height = 1080, float FOV = 90.0)
{
	// Set Globals
	sourceCount = count;
	frameWidth = width;
	frameHeight = height;
	horizontalFOV = FOV;
	verticalFOV = 2 * atan(tan(horizontalFOV / 2) * (frameHeight / frameWidth));
	// Initialize pointers
	device = NULL;
	context = NULL;
	sources = NULL;
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
	// Set default listener orientation
	// x+ = right, y+ = up, z+ = forward
	// see https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
	// for info on listener orientation
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
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

void openal_module::create_buffers() {
// TODO: add the ability to create buffers of varying waveforms
// such as "more scratchy sounding"
}

/**
 * @brief      Creates sources.
 */
void openal_module::create_sources()
{
	sources = new ALuint[sourceCount];
	sourceMatCoords = new int[sourceCount];
	alGenSources(sourceCount, sources);
	al_check_error();
	// Set the vertical positions of all the sources.
	for (int i = 0; i < sourceCount; ++i) {
		// Calculate where the sournce would fall on the image matrix
		sourceMatCoords[i] = (frameHeight / (sourceCount * 2)) + (frameHeight / sourceCount) * i;
		// Set the proper
		alSourcef(sources[i], AL_REFERENCE_DISTANCE, 1.0f);
		al_check_error();
		alSourcei(sources[i], AL_SOURCE_RELATIVE, AL_TRUE);
		al_check_error();
		alSourcei(sources[i], AL_LOOPING, AL_TRUE);
		al_check_error();
		alSource3f(sources[i], AL_POSITION, -2, 0, 1);
		al_check_error();
	}
}

/**
 * @brief      Adds a buffer to a source.
 *
 * @param[in]  buffer  The buffer
 * @param[in]  source  The source
 */
void openal_module::buffer_source(ALuint buffer, ALuint source)
{
	// Add buffers to each source and set properties
	alSourcei(source, AL_BUFFER, buffer);
	al_check_error();
}

/**
 * @brief      Tells the source to start playing.
 *
 * @param[in]  source  The source
 */
void openal_module::play_source(ALuint source)
{
	alSourcePlay(source);
	al_check_error();
}

/**
 * @brief      Moves a source around within the bounds of the FOV.
 *
 * @param[in]  source     The source
 * @param[in]  latitude   The latitude in radians
 * @param[in]  longitude  The longitude in radians
 */
void openal_module::move_source(ALuint source, float latitude, float longitude)
{
	// normalize latitude and longitude
	latitude = fmod(latitude, float(2 * M_PI));
	longitude = fmod(longitude, float(2 * M_PI));
	// get position of source
	ALfloat *oldX;
	ALfloat *oldY;
	ALfloat *oldZ;
	alGetSource3f(source, AL_POSITION, oldX, oldY, oldZ);
	// calculate new position with MATH :o
	float newLat = calc_latitude(*oldX, *oldY, *oldZ) + latitude;
	float newLon = calc_longitude(*oldX, *oldY, *oldZ) + longitude;
	float newX = cos(newLon) * sin(newLat);
	float newY = sin(newLon) * sin(newLat);
	float newZ = cos(newLat);
	// if new position is outside bounds, set new position to bounds
	// TODO: figure out how to keep latitude and longitude within bounds
	// of field-of-view.
}

float openal_module::calc_longitude(float x, float y, float z)
{
	// TODO
	return float();
}
float openal_module::calc_latitude(float x, float y, float z)
{
	// TODO
	return float();
}
float openal_module::deg_to_rad(float x) {
	return x * M_PI / 180;
}
float openal_module::rad_to_deg(float x) {
	return x * 180 / M_PI;
}
