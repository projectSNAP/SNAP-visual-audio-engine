#include "visual_audio_algorithm.h"
#include "config_module.h"
#include "shared_mem_input.h"
#include "get_exe_directory.h"
#include <string>

/**
 * @brief      This is the main entry point for the application.
 */
int main() {
	shared_mem_input *input = new shared_mem_input();
	visual_audio_algorithm algorithm(input);
	config::config_type configs = config::load(get_exe_directory() + "config.json");
	algorithm.lateral(configs);
}
