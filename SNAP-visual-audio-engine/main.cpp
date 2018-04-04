// This is the main entry point for the application.

#include "stdafx.h"
#include "visual_audio_algorithm.h"
#include "file_input.h"
#include <stdlib.h>
#include <cmath>

#include <iostream>

using namespace std;

int main() {
	file_input input = file_input();
	input.get_frame();
	visual_audio_algorithm algorithm(input);
	config_module config = config_module();
	algorithm.start(config);
}