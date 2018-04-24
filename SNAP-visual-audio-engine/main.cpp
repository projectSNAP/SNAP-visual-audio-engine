// This is the main entry point for the application.
#include "visual_audio_algorithm.h"
#include "config_module.h"
#include "file_input.h"

using namespace std;

int main() {
	file_input *input = new file_input();
	visual_audio_algorithm algorithm(input);
	config::config_type configs = config::load("");
	algorithm.bilateral(configs);
}