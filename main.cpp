#include "LogIn.h"
#include "DataBase.h"
#include "main.h"
#include "getApi.h"
#include "imageProcessing.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	getApi api1;
	api1.getInfo("D:/ocrTraining/t5/31ed.jpg");
	cout << "end";
    /*LogIn w;
    w.show();
	w.setWindowTitle("µÇÂ¼");
	w.setFixedSize(700, 500);
	DataBase base1;
	base1.ToConnect();*/
	

	//Í¸ÊÓ±ä»»²âÊÔ
	/*Mat src = imread("D:/ocrTraining/HandwritingNum_pho/32.jpg");
	imshow("origin", src);
	imageProcessing process1;
	Mat dst = process1.preProcessing(src);
	imshow("dst", dst);
	imwrite("D:/ocrTraining/HandwritingNum_pho/32ed.jpg", dst);*/
	
    return a.exec();
}

