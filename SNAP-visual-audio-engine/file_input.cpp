#include "stdafx.h"
#include "file_input.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

cv::Mat file_input::get_frame() {
	// Get a picture from a file next to the exe called soundtest.jpg
	char* filename = "C:\\Users\\dusti\\Pictures\\diagonal.jpg";
	Mat image;
	Mat *splitImage = NULL;
	image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
	if (! image.data )                             // Check for invalid input
	{
		std::cout <<  "Could not open or find the image" << std::endl ;
		return Mat();
	}
	else {
		int channels = image.channels();
		splitImage = new Mat[channels];
		split(image, splitImage);
		// namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
		// for (int i = 0; i < channels; i++) {
		// 	imshow( "Display window", splitImage[i]);
		// 	waitKey(2000);
		// }
		return splitImage[0];
	}
}
