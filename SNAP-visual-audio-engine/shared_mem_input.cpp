#include "shared_mem_input.h"
#include "BlenderToDepthMapDLL.h"
#include <iostream>

using namespace cv;
using namespace std;

cv::Mat shared_mem_input::get_frame()
{
	// Open the shared memory space for reading.
	void* PointerToBuf = OpenDepthBufMapFileToRead(frameX, frameY);
	int* dst = new int[frameX * frameY];
	memcpy(dst, ReadDepthMapBufFile(PointerToBuf), frameX * frameY * 4);
	Mat image = Mat(frameX, frameY, CV_16UC2, dst);

	if (!image.data) // Check for invalid input
	{
		wcerr << "Could not open or find the image" << std::endl;
	}
	return image;
}
