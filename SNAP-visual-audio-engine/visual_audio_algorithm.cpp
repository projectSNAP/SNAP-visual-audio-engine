#include "stdafx.h"
#include "visual_audio_algorithm.h"
#include "openal_module.h"

int visual_audio_algorithm::start(const config_module &config) {
	openal_module al;
	al.init_sources(16);
	al.init_sine_buffers(16, 44100, 0.2, 220);
	// add buffers to sources
	float sourceDistance = 10.f;
	for (int i = 0; i < 16; i++) {
		al.source_set_buffer(i, i);
		al.source_set_pos(i, sourceDistance, 0.f, openal_module::deg_to_rad(90.f));
	}
	float horizontalSteps = 10;
	float horizontalFOV = 180;
	float angleMult = openal_module::deg_to_rad(horizontalFOV / horizontalSteps);
	int direction = 1;
	int horizontalPosition = 0;
	int verticalPosition = 0;
	while (1) {
		for (int i = 0; i < 16; i++) {
			al.source_move(i, (angleMult * direction), 0);
			Sleep(5);
		}
		// al.source_print_position(0);
		horizontalPosition += direction;
		if (horizontalPosition >= 16)
			direction = -direction;
	}
	return 0;
}

//float get_grid_intensity(Mat image, int x, int y);