#define _USE_MATH_DEFINES
#include "opencv_module.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
using namespace cv;

opencv_module::opencv_module(int width, int height)
{
	xMax = width;
	yMax = height;
	currentFrame = NULL;
}

void opencv_module::set_current_frame(cv::Mat frame)
{
	currentFrame = frame;
}

/**
 * @brief      Gets the pixel intensity of a certain grid point in the current
 *             frame, this intensity should be used to control the
 *             DistanceIndicator on a sound algorithm.
 *
 * @param[in]  x     x location on the grid.
 * @param[in]  y     y location on the grid.
 *
 * @return     The intensity.
 */
float opencv_module::get_intensity(int x, int y)
{
	float intensity = 0.f;
	// Make sure x and y are within bounds
	if (x >= xMax)
		x = xMax - 1;
	else if (x < 0)
		x = 0;
	if (y >= yMax)
		y = yMax - 1;
	else if (y < 0)
		y = 0;
	// Calculate region of interest dimensions from new frame
	int ROIWidth = currentFrame.cols / xMax;
	int ROIHeight = currentFrame.rows / yMax;
	// Find the intensity at x and y
	try
	{
		Mat regionOfInterest(currentFrame, Rect(ROIWidth * x, ROIHeight * y, ROIWidth, ROIHeight));
		Scalar avgPixelIntensity = cv::mean(regionOfInterest);
		// Get the pixel intensity and normalize it to range (0.0-1.0)
		intensity = (float)avgPixelIntensity.val[0] / 65535.0;
	}
	catch (cv::Exception & e)
	{
		std::cerr << e.msg << std::endl; // output exception message
	}
	return intensity;
}

/**
 * @brief      Rolloff helper functions to be used to modify the pixel
 *             intensity.
 *
 * @param[in]  x     float that you want to apply rolloff to. Should be within
 *                   range of (0-1).
 * @param[in]  base  The base (e.g. e)
 */
float opencv_module::rolloff(float x, float base) {
	return (pow(base, x) - 1.0) / (base - 1.0);
}

/**
 * @brief      Convenience function for logarithmic rolloff. Note: the vast
 *             majority of human perception is on a logarithmic scale, so if you
 *             want sound increase to sound right it must be increasing
 *             logarithmicly.
 */
float opencv_module::logarithmic_rolloff(float x) {
	return rolloff(x, M_E);
}
