#pragma once

#include "input_module.h"
#include "config_module.h"

class visual_audio_algorithm
{
public:
	visual_audio_algorithm(input_module *input_module)
	{
		input = input_module;
	}
	int start(config_module *config);
private:
	input_module *input;
};