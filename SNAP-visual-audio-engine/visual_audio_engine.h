#pragma once
#include "stdafx.h"

class visual_audio_engine
{
public:
	visual_audio_engine();
	~visual_audio_engine();
	void al_init();
	void al_exit();
	void read_params();
	void setup_image();
	short *create_sine_waves();
	// Divide the axisSize by the number of sources and place the sources evenly
	// along that axis.
	void set_source_positions(ALuint * sources, int sourceCount, int axisSize);
	void visual_audio_algorithm();

protected:
	int verticalSources;
	float aspectRatio;
	float fieldOfView;
	int debug; 
	int xSize; 
	int ySize;
	// User parameters
	float frequency;
	int horizontalSteps;
	float freqIncrement;
	int stepDelay;
	float audioSpreadDeg;
	float audioVolRollOff;
};

