#pragma once
#include <opencv2/core/core.hpp>

/**
 * @brief      A module that contains all of the functions that utilize openCV.
 *             This module accepts a Mat from an input module and splits it into
 *             a grid based upon the desired width and height of the grid. then
 *             calculates the pixel intensity with the get_intensity function at
 *             each point in the grid. Additionally it has functions for
 *             calculating logarithmic and other rolloff values in a range of
 *             (0-1). These rolloff functions are necessary because humans hear
 *             sound on a logarithmic scale instead of a linear scale.
 */
class opencv_module
{
public:
	opencv_module(int width, int height);
	void set_current_frame(cv::Mat frame);
	float get_intensity(int x, int y);
	static float opencv_module::rolloff(float x, float base);
	static float opencv_module::logarithmic_rolloff(float x);
private:
	//
	cv::Mat currentFrame;
	//Bounds for grid
	int xMax;
	int yMax;
};

