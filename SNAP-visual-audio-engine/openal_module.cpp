#include "openal_module.h"
#include "stdafx.h"

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

openal_module::openal_module()
{
	device = NULL;
	context = NULL;

	const char *defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	device = alcOpenDevice(defname);
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
}


openal_module::~openal_module()
{
	ALCdevice *device = NULL;
	ALCcontext *context = NULL;
	context = alcGetCurrentContext();
	device = alcGetContextsDevice(context);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void createWaveForm(){
	
}
void createSineWave(){
	
}
void createBuffers(){
	
}
void createSources(){
	
}
void moveSource(){
	
}
void changePitch(){
	
}

