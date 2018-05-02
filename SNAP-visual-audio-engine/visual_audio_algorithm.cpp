#include "visual_audio_algorithm.h"
#include "openal_module.h"
#include "opencv_module.h"

using namespace std::chrono;
using namespace config;
// Typedefs used for the delay function, for brevity.

visual_audio_algorithm::visual_audio_algorithm(input_module *input_module)
{
	input = input_module;
}

int visual_audio_algorithm::lateral(config_type config) {
	// openAL
	openal_module al(
	    config.horizontalResolution,
	    config.verticalResolution,
	    config.fieldOfView
	);
	al.init_sources(config.verticalResolution);
	al.init_sine_buffers(
	    config.verticalResolution,
	    config.sampleLength,
	    config.frequencyMin,
	    config.frequencyMax
	);
	// add buffers to sources
	for (int i = 0; i < config.verticalResolution; i++) {
		al.source_set_buffer(i, i);
		al.source_set_gain(i, 0.f);
		al.source_play(i);
	}
	// openCV
	opencv_module cv(config.horizontalResolution, config.verticalResolution);
	// create needed variables
	float intensity = 0.f;
	int delayLength = config.cycleLength / config.horizontalResolution;
	time_point<steady_clock> start;
	int x = 0;
	// Lateral right or lateral left?
	int xStart;
	int direction;
	switch (config.scanType) {
		case config::LATERAL_LEFT: {
			direction = -1;
			xStart = config.horizontalResolution;
		}
		break;
		case config::LATERAL_RIGHT:
		default: {
			direction = 1;
			xStart = 0;
		}
	}
	// audio algorithm
	while (1) {
		cv.set_current_frame(input->get_frame());
		for (x = xStart; (x < config.horizontalResolution && x >= 0); x += direction) {
			start = high_resolution_clock::now();
			for (int y = 0; y < config.verticalResolution; y++) {
				intensity = cv.get_intensity(x, y);
				intensity = opencv_module::logarithmic_rolloff(intensity);
				al.source_set_pos(x, y);
				al.source_set_gain(y, intensity);
			}
			delay(delayLength, start);
		}
	}
	return 0;
}

/**
 * @brief      Delay function that waits for delayLength before returning.
 *
 * @param[in]  delayLength  The delay length the length in milliseconds that you would like to delay for.
 * @param[in]  start        (Optional) The start the time_point where you want to delay from.
 */
void visual_audio_algorithm::delay(int delayLength, time_point<steady_clock> start) {
	time_point<steady_clock> now;
	duration<double> elapsedTime;
	do  {
		now = high_resolution_clock::now();
		elapsedTime = now - start;
	} while (duration_cast<milliseconds>(elapsedTime).count() < delayLength);
}
