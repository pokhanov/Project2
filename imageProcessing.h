#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
class imageProcessing
{
public:
	//����ʶ��Ԥ������
	void getImage();		//���ض��ļ��ж�ȡ����ͼƬ��
	Mat preProcessing(Mat &image);		//ͼ��Ԥ����
	Mat getROI(Mat &image);		//���ؾ��������͸�ӱ任��ROIͼ��
};

