// This is the main entry point for the application.
#include "visual_audio_algorithm.h"
#include "config_module.h"
#include "shared_mem_input.h"
#include <windows.h>
#include <string>

std::string get_exe_directory();

int main() {
	shared_mem_input *input = new shared_mem_input();
	visual_audio_algorithm algorithm(input);
	config::config_type configs = config::load(get_exe_directory() + "\\config.json");
	algorithm.lateral(configs);
}

std::string get_exe_directory() {
	char path[MAX_PATH];
	// TODO: get the linux version of this to work too.
	GetModuleFileName(NULL, path, MAX_PATH);
	std::string strPath(path);
	return strPath.substr(0, strPath.find_last_of("\\/"));
}