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
	al.init_sine_buffers(1,1,22050,0.1,0.77,130.0,1.3);
	al.source_set_buffer(0,0);
	while(1){
		al.source_play(0);
		Sleep(2000);
		al.source_pause(0);
		Sleep(2000);
	}
}