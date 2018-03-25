// This is the main entry point for the application.

#include "stdafx.h"
#include "openal_module.h"
#include "input_module.h"
#include "shared_mem_input.h"
#include <stdlib.h>

using namespace std;

int main() {
	openal_module al;
	al.init_sources(1);
	al.init_sine_buffers(1, 44100, 0.3, 440);
	al.source_set_buffer(0, 0);
	al.source_play(0);
	while (1) {
	}
}