#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
class imageProcessing
{
public:
	//文字识别预处理部分
	void getImage();		//从特定文件夹读取最新图片？
	Mat preProcessing(Mat &image);		//图像预处理
	Mat getROI(Mat &image);		//返回经过处理和透视变换的ROI图像
};

