#include "pch.h"
#include <iostream>	
#include "stdio.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>

using namespace cv;
using namespace std;

int main()
{
	Mat src_image = imread("./input/3.jpg");
	vector<int>compression_pressure;
	compression_pressure.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_pressure.push_back(12);

	imwrite("./output/3.jpg",src_image,compression_pressure);

	return 0;
}
