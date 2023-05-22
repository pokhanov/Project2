#include "LogIn.h"
#include "DataBase.h"
#include "main.h"
#include "imageProcessing.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogIn w;
    w.show();
	w.setWindowTitle("登录");
	w.setFixedSize(700, 500);
	DataBase base1;
	base1.ToConnect();

	//透视变换测试
	Mat src = imread("C:/Users/Pokhanov/Pictures/opencv/3.jpg");
	imshow("原图", src);
	imageProcessing process1;
	Mat dst = process1.preProcessing(src);
	imshow("预处理结果", dst);


    return a.exec();
}
