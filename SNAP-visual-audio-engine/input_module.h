#pragma once
#include "opencv2/core/core.hpp"

class input_module
{
public:
	input_module();
	~input_module();
	void set_dimensions(int width, int height);
	virtual cv::Mat get_frame() = 0;
protected:
	int frameX;
	int frameY;
};

