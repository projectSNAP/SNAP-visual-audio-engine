#pragma once
#include "al.h"
#include "alc.h"
class openal_module
{
public:
	openal_module();
	~openal_module();
	void createWaveForm();
	void createSineWave();
	void createBuffers();
	void createSources();
	void moveSource();
	void changePitch();
protected:
	ALCdevice *device;
	ALCcontext *context;
};

