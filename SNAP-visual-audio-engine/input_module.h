#pragma once
#include "opencv2/core/core.hpp"

/**
 * An abstract class that is designed to be the unified way that the Visual
 * Audio Engine accepts depth data as input.
 *
 * In order to allow the Visual Audio Engine to accept input from a new source
 * create a child class of input_module and implement the get_frame function to
 * get depth data from that new source and convert it into a Mat (preferrably a
 * single channel depth image, otherwise behavior is undefined). See
 * shared_mem_input or file_input as an example
 */
class input_module
{
public:
	input_module() {};
	virtual cv::Mat get_frame() = 0;
};

