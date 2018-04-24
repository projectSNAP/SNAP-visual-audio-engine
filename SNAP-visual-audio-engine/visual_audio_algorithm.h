#pragma once

#include "input_module.h"
#include "config_types.h"
#include <chrono>

class visual_audio_algorithm
{
public:
	visual_audio_algorithm(input_module *input_module);
	int bilateral(config::config_type config);
private:
	input_module *input;
	void delay(int delayLength, std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::high_resolution_clock::now());
};