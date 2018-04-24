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
	void* ptrToSharedMemory = ReadSharedMemorySpace(width, height);
	int sizeOfImage = width *height * 4;
	delete(data);
	data = new int[sizeOfImage];
	memcpy(data, (char*)ptrToSharedMemory, sizeOfImage);
	image = Mat(height, width, CV_16UC2, data);
	UnmapPointerToSharedMemory((int*)ptrToSharedMemory);

	if (!image.data) // Check for invalid input
	{
		wcerr << "Could not open or find the image" << std::endl;
	}
	return image;
}

shared_mem_input::~shared_mem_input() {
	delete(data);
}
