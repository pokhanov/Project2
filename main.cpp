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
	w.setWindowTitle("��¼");
	w.setFixedSize(700, 500);
	DataBase base1;
	base1.ToConnect();

	//͸�ӱ任����
	Mat src = imread("C:/Users/Pokhanov/Pictures/opencv/3.jpg");
	imshow("ԭͼ", src);
	imageProcessing process1;
	Mat dst = process1.preProcessing(src);
	imshow("Ԥ������", dst);


    return a.exec();
}
