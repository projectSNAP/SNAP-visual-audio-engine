#pragma once
#include <string>

using namespace std;

class config_module
{
private:
	int sourceResolutionVal;
	int fieldOfViewVal;
	float frequencyVal;
	int horizontalStepsVal;
	float freqIncrementVal;
	int stepDelayVal;
	float audioSpreadDegVal;
	float audioVolRollOffVal;
public:
	config_module();
	void load(string filePath);
	int sourceResolution();
	int fieldOfView();
	float frequency();
	int horizontalSteps();
	float freqIncrement();
	int stepDelay();
	float audioSpreadDeg();
	float audioVolRollOff();
};
