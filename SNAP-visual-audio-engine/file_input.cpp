#include "stdafx.h"
#include "file_input.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

cv::Mat file_input::get_frame() {
	// Get a picture from a file next to the exe called soundtest.jpg
	char* filename = "C:\\Users\\dusti\\Pictures\\test.jpg";
	Mat image;
	Mat *splitImage = NULL;
	image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
	if (! image.data )                             // Check for invalid input
	{
		std::cout <<  "Could not open or find the image" << std::endl ;
		return Mat();
	}
	else {
		Mat inverted;
		bitwise_not(image, inverted);
		return inverted;
	}
}
