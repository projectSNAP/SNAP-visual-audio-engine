#pragma once
#include "al.h"
#include "alc.h"

class openal_module
{
public:
	openal_module(int sourceCount, int frameWidth, int frameHeight, float fieldOfView);
	~openal_module();
	void create_buffers();
protected:
	int sourceCount;
	int frameWidth;
	int frameHeight;
	float horizontalFOV;
	float verticalFOV;
	float stepSize;

	ALCdevice *device;
	ALCcontext *context;
	ALuint *sources;
	int *sourceMatCoords;
	
	void create_sources();
	void buffer_source(ALuint buffer, ALuint source);
	void play_source(ALuint source);
	void move_source(ALuint source, float latitude, float longitude);
};

