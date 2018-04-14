#include "visual_audio_algorithm.h"
#include "openal_module.h"
#include "opencv_module.h"
#include <opencv2/core/core.hpp>
#include <chrono>

// Typedefs used for the delay function.
typedef std::chrono::high_resolution_clock high_resolution_clock;
typedef std::chrono::milliseconds milliseconds;
typedef std::chrono::duration<double> duration;
typedef std::chrono::time_point<chrono::steady_clock> time_point;

void delay(int delayLength, time_point start = high_resolution_clock::now());

int visual_audio_algorithm::start(config_module *config) {
	int width = 36;
	int height = 16;
	float FOV = 180;
	// openAL
	openal_module al(width, height, FOV);
	al.init_sources(height);
	al.init_sine_buffers(height, 5.f, 44100, 0.2, 110.f, 440.f);
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
	time_point start;
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
void delay(int delayLength, time_point start) {
	time_point now;
	duration elapsedTime;
	do  {
		now = high_resolution_clock::now();
		elapsedTime = now - start;
	} while (chrono::duration_cast<milliseconds>(elapsedTime).count() < delayLength);
}
