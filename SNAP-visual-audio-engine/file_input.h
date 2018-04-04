#pragma once
#include "input_module.h"

class file_input : public input_module {
public:
	cv::Mat get_frame();
};

