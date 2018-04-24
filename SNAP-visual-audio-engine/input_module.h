#pragma once
#include "opencv2/core/core.hpp"

class input_module
{
public:
	input_module() {};
	virtual cv::Mat get_frame() = 0;
};

