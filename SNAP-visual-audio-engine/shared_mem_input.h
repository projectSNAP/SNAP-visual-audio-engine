#pragma once
#include "input_module.h"
class shared_mem_input : public input_module
{
public:
	cv::Mat get_frame();
	~shared_mem_input();
};

