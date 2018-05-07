#include "file_input.h"
#include "get_exe_directory.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

cv::Mat file_input::get_frame() {
	std::string filename = get_exe_directory() + "test.jpg";
	Mat image;
	Mat *splitImage = NULL;
	image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
	if (! image.data )                             // Check for invalid input
	{
		std::cerr <<  "Could not open or find the image" << std::endl ;
		return Mat();
	}
	else {
		Mat inverted;
		bitwise_not(image, inverted);
		return inverted;
	}
}
