// This is the main entry point for the application.
#include "stdafx.h"
#include "visual_audio_algorithm.h"
#include "file_input.h"
#include <stdlib.h>
#include <cmath>

#include <iostream>

using namespace std;

int main() {
	file_input *input = new file_input();
	visual_audio_algorithm algorithm(input);
	config_module *config = new config_module();
	algorithm.bilateral(config);
}