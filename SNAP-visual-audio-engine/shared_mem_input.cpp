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
	void* ptrToSharedMemory = ReadSharedMemorySpace(width, height);
	int sizeOfImage = width *height * 4;
	// Delete the previous image if it exists
	if (data) {
		delete(data);
	}
	// Copy the new image from shared memory
	data = new int[sizeOfImage];
	memcpy(data, (char*)ptrToSharedMemory, sizeOfImage);
	image = Mat(height, width, CV_16UC2, data);
	// TODO: is it neccessary to unmap the pointer each time?
	// Possibly store pointer as
	UnmapPointerToSharedMemory((int*)ptrToSharedMemory);
	// Check for invalid input
	if (!image.data)
	{
		// TODO: better error message.
		wcerr << "Could not open or find the image" << std::endl;
	}
	return image;
}

shared_mem_input::~shared_mem_input() {
	if (data) {
		delete(data);
	}
}
