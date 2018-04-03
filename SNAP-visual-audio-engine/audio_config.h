#pragma once
#include <string>

using namespace std;

class audio_config
{
public:
	int sourceResolution;
	int fieldOfView;
	float frequency;
	int horizontalSteps;
	float freqIncrement;
	int stepDelay;
	float audioSpreadDeg;
	float audioVolRollOff;
	audio_config();
	void load(string filePath);
};
