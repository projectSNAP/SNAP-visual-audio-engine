#include "stdafx.h"
#include "visual_audio_algorithm.h"
#include "openal_module.h"

int visual_audio_algorithm::start(const config_module &config) {
	int width = 180;
	int height = 16;
	float FOV = 180;
	openal_module al(width, height, FOV);
	al.init_sources(height);
	al.init_sine_buffers(height, 44100, 0.2, 220);
	// add buffers to sources
	for (int i = 0; i < height; i++) {
		al.source_set_buffer(i, i);
	}
	al.source_play(0);
	int x = 0;
	while (1) {
		for (x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				al.source_set_pos(x,y);
			}
			al.source_print_position(0);
			Sleep(5);
		}
		for (x; x >= 0; x--) {
			for (int y = 0; y < height; y++) {
				al.source_set_pos(x,y);
			}
			al.source_print_position(0);
			Sleep(5);
		}
	}
	return 0;
}

//float get_grid_intensity(Mat image, int x, int y);