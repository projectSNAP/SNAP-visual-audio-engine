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
	float x, y, z, rho, theta, phi;
	x = y = z = rho = theta = phi = 0.f;
	al.source_play(0);
	cout << al.rad_to_deg(atan(7.071068 / -7.071068)) << endl;
	while (1) {
		al.source_move(0, al.deg_to_rad(5), 0.f);
		Sleep(500);
	}
}