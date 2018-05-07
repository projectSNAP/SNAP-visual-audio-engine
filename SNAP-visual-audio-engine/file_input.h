#pragma once
#include "input_module.h"

/**
 * A sub-class of the Input Module that simply reads an image from the
 * filesystem, for testing purposes. The image should be in the same directory
 * as the executable.
 */
class file_input : public input_module {
public:
	cv::Mat get_frame();
};

