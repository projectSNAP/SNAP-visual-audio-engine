// This is the main entry point for the application.

#include "stdafx.h"
#include "openal_module.h"
#include "input_module.h"
#include "shared_mem_input.h"
#include <stdlib.h>
#include <cmath>

#include <iostream>

using namespace std;

int main() {
	openal_module al;
	al.init_sources(1);
	al.init_sine_buffers(1, 44100, 0.2, 220);
	al.source_set_buffer(0, 0);
	al.source_play(0);
	float horizontalSteps = 10;
	float horizontalFOV = 180;
	float angleMult = openal_module::deg_to_rad(horizontalFOV / horizontalSteps);
	int direction = 1;
	cout << "angleMult:" << angleMult;
	while (1) {
		if (al.source_get_theta(0) >= openal_module::deg_to_rad(180)) {
			direction = -direction;
		}
		al.source_move(0, (angleMult * direction), 0);
		Sleep(50);
	}
}