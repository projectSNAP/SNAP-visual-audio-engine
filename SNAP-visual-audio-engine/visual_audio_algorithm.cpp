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

int visual_audio_algorithm::bilateral(config_type config) {
	int width = 36;
	int height = 16;
	float FOV = 180;
	// openAL
	openal_module al(width, height, FOV);
	al.init_sources(height);
	al.init_sine_buffers(height, 5.f, 0.2, 110.f, 440.f);
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
	int delayLength = 10;
	time_point<steady_clock> start;
	while (1) {
		for (x = 0; x < width; x++) {
			start = high_resolution_clock::now();
			for (int y = 0; y < height; y++) {
				al.source_set_pos(x, y);
				intensity = cv.get_intensity(x, y);
				al.source_set_gain(y, intensity);
			}
			al.source_print_position(0);
			delay(delayLength, start);
		}
		cv.set_current_frame(input->get_frame());
		for (x; x >= 0; x--) {
			start = high_resolution_clock::now();
			for (int y = 0; y < height; y++) {
				al.source_set_pos(x, y);
				intensity = cv.get_intensity(x, y);
				al.source_set_gain(y, intensity);
			}
			al.source_print_position(0);
			delay(delayLength, start);
		}
		cv.set_current_frame(input->get_frame());
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
