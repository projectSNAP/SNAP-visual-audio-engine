#pragma once
#include "al.h"
#include "alc.h"

class openal_module
{
public:
	openal_module(int width = 1920, int height = 1080, float FOV = 90.0);
	~openal_module();
	void init_sine_buffers(int count, int sampleRate, float amplitude, int frequency);
	void init_sources(int count);
	const unsigned int *get_sources();
	const unsigned int *get_buffers();
	void source_set_buffer(int buffer, int source);
	void source_play(int source);
	void source_stop(int source);
	void source_pause(int source);
	void source_move(int source, float latitude, float longitude);
	void source_add_pitch(int source, float addPitch);
	void source_set_pitch(int source, float addPitch);

protected:
	int sourceCount;
	int bufferCount;
	int frameWidth;
	int frameHeight;
	float horizontalFOV;
	float verticalFOV;
	float stepSize;
	ALCdevice *device;
	ALCcontext *context;
	ALuint *sources;
	ALuint *buffers;
	int *sourceMatCoords;
	float calc_longitude(float x, float y, float z);
	float calc_latitude(float x, float y, float z);
	float deg_to_rad(float x);
	float rad_to_deg(float x);
};
