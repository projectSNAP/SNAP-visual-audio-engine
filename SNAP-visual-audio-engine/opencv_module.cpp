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
	// Get the current frame
	currentFrame = frame;
	// namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
	// imshow( "Display window", *currentFrame);
	// waitKey(2000);
}

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
		Scalar avgPixelIntensity = mean(regionOfInterest);
		// Get the pixel intensity and normalize it to range (0.0-1.0)
		intensity = (float)avgPixelIntensity.val[0] / 255.f;
		// Calculate the normal Rolloff
		intensity = exp(6.908 * intensity) / 1000;
	}
	catch (cv::Exception & e)
	{
		std::cerr << e.msg << std::endl; // output exception message
	}
	return intensity;
}
