#include "stdafx.h"
#include "visual_audio_algorithm.h"
#include "openal_module.h"
#include "opencv_module.h"
#include <opencv2/core/core.hpp>

int visual_audio_algorithm::start(config_module *config) {
	int width = 180;
	int height = 16;
	float FOV = 180;
	// openAL
	openal_module al(width, height, FOV);
	al.init_sources(height);
	al.init_sine_buffers(height, 44100, 0.2, 110.f, 440.f);
	// add buffers to sources
	for (int i = 0; i < height; i++) {
		al.source_set_buffer(i, i);
		al.source_set_gain(i, 0.f);
		al.source_play(i);
	}
	// openCV
	opencv_module cv(width, height);
	cv.set_current_frame(input->get_frame());
	int x = 0;
	float intensity = 0.f;
	while (1) {
		for (x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				al.source_set_pos(x, y);
				intensity = cv.get_intensity(x, y);
				cout << "intensity: " << intensity << endl;
				al.source_set_gain(y, intensity);
			}
			al.source_print_position(0);
			Sleep(1);
		}
		cv.set_current_frame(input->get_frame());
		for (x; x >= 0; x--) {
			for (int y = 0; y < height; y++) {
				al.source_set_pos(x, y);
				intensity = cv.get_intensity(x, y);
				cout << "intensity: " << intensity << endl;
				al.source_set_gain(y, intensity);
			}
			al.source_print_position(0);
			Sleep(1);
		}
		cv.set_current_frame(input->get_frame());
	}
	return 0;
}

//float get_grid_intensity(Mat image, int x, int y);