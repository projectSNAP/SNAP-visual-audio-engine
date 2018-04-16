#pragma once

#include "input_module.h"
#include "config_module.h"
#include <chrono>

class visual_audio_algorithm
{
public:
	visual_audio_algorithm(input_module *input_module);
	int bilateral(config_module *config);
private:
	input_module *input;

	// Typedefs used for the delay function, for brevity.
	typedef std::chrono::high_resolution_clock high_resolution_clock;
	typedef std::chrono::milliseconds milliseconds;
	typedef std::chrono::duration<double> duration;
	typedef std::chrono::time_point<chrono::steady_clock> time_point;
	void delay(int delayLength, time_point start = high_resolution_clock::now());
};