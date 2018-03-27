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
	for(int i = 0; i < 360; i++){
		
	}
		al.source_set_pos(0, 0, 1, 0);
		Sleep(500);
		al.source_set_pos(0, 0, 1.5, 0);
		Sleep(500);
		al.source_set_pos(0, 0, 2, 0);
		Sleep(500);
		al.source_set_pos(0, 0, 2.5, 0);
		Sleep(500);
		al.source_set_pos(0, 0, 3, 0);
		Sleep(500);
		al.source_set_pos(0, 0, 3.5, 0);
		Sleep(500);
	
}