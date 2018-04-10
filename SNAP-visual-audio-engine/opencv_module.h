#pragma once
#include "opencv2/core/core.hpp"

class opencv_module
{
public:
	opencv_module(int width, int height);
	void set_current_frame(cv::Mat *frame);
	float get_intensity(int x, int y);
private:
	//
	const cv::Mat *currentFrame;
	//Bounds for grid
	int xMax;
	int yMax;
};

