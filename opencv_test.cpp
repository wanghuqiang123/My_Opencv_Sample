/*
文件名：opencv_test.cpp
作者：王虎强
日期：2019/2/25
功能：调用电脑摄像头读取视频流，对图像进行运行目标提取，将目标中背景中提取出。


//其他说明：本程序中我把vector容器称之为数组，便于理解
*/

#include "pch.h"
#include <iostream>	
#include "stdio.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>

using namespace std;
using namespace cv;

#define Image_cols 128
#define Image_rows 128

enum {Green,Red,Yellow,White};
int dst_arry[Image_rows][Image_cols];

#define W 640
#define H 640

int out_array[128][128];

int main()
{
	Mat image = imread("./image.png");
	
	Mat hsvimage;

	namedWindow("1", CV_WINDOW_AUTOSIZE);
	//namedWindow("2");

	
	cvtColor(image, hsvimage, CV_RGB2HSV);

	//Mat dst_image(128,128,CV_8UC1);
	//memset(&dst_arry,0,sizeof(dst_arry));

	//IplImage temp = IplImage(hsvimage);
	//IplImage* dst = cvCreateImage(CvSize(128, 128), 8, 1);
	//cvInRangeS(&temp,cvScalar(0,43,255),cvScalar(360,46,255),dst);

	//Mat out_image(128,128,image.type());
	//for (int i = 1; i < 120; i++)
	//{
	//	for (int j = 1; j < 120; j++)
	//	{
	//		dst_arry[j][i] = image_Roi(hsvimage, 21 * j + 3, 72 * i + 3);
	//	}
	//}
	////dst_arry[120][120] = image_Roi(hsvimage, 21 * 120 + 3, 72 * 120 + 3);
	//Mat frame(120, 120, CV_8UC1);
	//for (int i = 0; i < 120; i++)
	//{
	//	for (int j = 0; j < 120; j++)
	//	{
	//		if (dst_arry[i][j] == Green)
	//		{
	//			frame.at<uchar>(i, j) = 255;
	//		}
	//		else
	//		{
	//			frame.at<uchar>(i, j) = 0;
	//		}
	//	}
	//}

	Mat dst_image(hsvimage.rows,hsvimage.cols, CV_8UC1);
	int h;
	int s;
	int v;
	for (int i = 0; i < hsvimage.rows - 1; i++)
	{
		for (int j = 0; j < hsvimage.cols - 1; j++)
		{
			h = (int)hsvimage.at<Vec3b>(i, j)[0];
			s = (int)hsvimage.at<Vec3b>(i, j)[1];
			v = (int)hsvimage.at<Vec3b>(i, j)[2];
			
			if( (h > 52 && h < 74) && (s < 255 && s>43) )
			{
				dst_image.at<uchar>(i, j) = 255;
			}
			else
			{
				dst_image.at<uchar>(i, j) = 0;
			}
		}
	}
	
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(dst_image, dst_image, MORPH_CROSS, element);
	dilate(dst_image, dst_image, element);
	medianBlur(dst_image, dst_image, 7);
	//morphologyEx(dst_image, dst_image, MORPH_OPEN, element);

	Mat dst_zoom(W,H,CV_8UC1);
	resize(dst_image, dst_zoom, Size(W, H), double(W / 9217), double(H / 2617), 2);
	//IplImage temp = IplImage(dst_zoom);
	//cvMorphologyEx(&temp, &temp, 0, 0, CV_MOP_OPEN, 1);			//形态学处理  开运算
	//cvMorphologyEx(&temp, &temp, 0, 0, CV_MOP_CLOSE, 1);			//形态学处理  闭运算
	resize(dst_zoom, dst_zoom, Size(128, 128),0.2,0.2,1);
	

	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			if (dst_zoom.at<uchar>(i, j) == 255)
			{
				out_array[i][j] = 20;
			}
			else
			{
				out_array[i][j] = 0;
			}
		}

	}

	ofstream outfile("C:\\image_data.dat");
	if (outfile.is_open())
	{
		for (int i = 0; i < 128; i++)
		{
			for (int j = 0; j < 128; j++)
			{
				outfile << out_array[i][j] << endl;
			}
		}
	}
	outfile.close();

	while (true)
	{
		if (cvWaitKey(50) == 27)
		{
			break;
		}
		imshow("1", dst_zoom);
		//imshow("2", image);
	}
	cvDestroyAllWindows();

	return 0;
}

//int image_Roi(Mat& mat,int pos_x,int pos_y)
//{
//	vector<int>vec;
//	vec.resize(4);
//	int green = 0;
//	int yellow = 0;
//	int red = 0;
//	int white = 0;
//	short h;
//	short s;
//	short v;
//	for (int i = 0; i < 15; i++)
//	{
//		for (int j = 0; j < 70; j++)
//		{
//			h = mat.at<Vec3b>(pos_x + i, pos_y + j)[0];
//			s = mat.at<Vec3b>(pos_x + i, pos_y + j)[1];
//			v = mat.at<Vec3b>(pos_x + i, pos_y + j)[2];
//
//			if (110 < h&&h < 140)		//判断绿色
//			{
//				green++;
//			}
//			else if(h<70&&h>50)		//黄色
//			{
//				yellow++;
//			}
//			else if ((h < 10 && h >= 0) || (h<360 && h>330))		//红色和白色
//			{
//				if (s < 1.10 && s>0.80)
//				{
//					red++;
//				}
//				else 
//				{
//					white++;
//				}
//			}
//			else
//			{
//				white++;
//			}
//		}
//	}
//	//比较大小
//	vec[Green] = green;
//	vec[Red] = red;
//	vec[White] = white;
//	vec[Yellow] = yellow;
//	int max = 0;
//	int Ret = -1;
//	for (int i = 0; i < 4; i++)
//	{
//		if (max < vec[i])
//		{
//			Ret = i;
//			max = vec[i];
//		}
//	}
//	return Ret;
//}