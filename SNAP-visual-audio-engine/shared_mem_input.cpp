#include "shared_mem_input.h"
#include "SharedMemoryDLL.h"
#include <iostream>

using namespace cv;
using namespace std;

cv::Mat shared_mem_input::get_frame()
{
	// Open the shared memory space for reading.
	Mat image;
	int width, height;
	// Get the dimensions of the image
	// TODO: have ReadSharedMemorySpace return null if there is nothing to read,
	// so we know to end the program gracefully instead of a crash.
	void* ptrToSharedMemory = ReadSharedMemorySpace(width, height);
	int sizeOfImage = width * height * 4;
	// Delete the previous image if it exists
	if (data) {
		delete(data);
	}
	// Copy the new image from shared memory
	data = new int[sizeOfImage];
	memcpy(data, (char*)ptrToSharedMemory, sizeOfImage);
	image = Mat(height, width, CV_8UC2, data);
	UnmapPointerToSharedMemory((int*)ptrToSharedMemory);
	// Check for invalid input
	if (!image.data)
	{
		// TODO: better error message.
		wcerr << "Could not open or find the image" << std::endl;
	} else {
		// extract the greyscale image from channel 0.
		Mat channels[2];
		split(image, channels);
		// invert the colors because unity shader creates depth inverted.
		Mat inverted;
		bitwise_not(channels[0], inverted);
		// flip the image because unity shader creates depth flipped.
		Mat flipped;
		flip(inverted, flipped, 0);
		return flipped;
	}
	return image;
}

shared_mem_input::~shared_mem_input() {
	if (data) {
		delete(data);
	}
}
