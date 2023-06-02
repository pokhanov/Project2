#include "LogIn.h"
#include "DataBase.h"
#include "main.h"
#include "getApi.h"
#include "dataProcess.h"
#include "imageProcessing.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <string>
#include<Qtcore/qvector.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	////apiµ˜”√≤‚ ‘
	//getApi api1;
	//api1.getInfo("C:/Users/Pokhanov/Documents/Visual Studio 2017/Projects/QtWidgetsApplication1/QtWidgetsApplication1/image/31ed.jpg");

	dataProcess data1;
	data1.txtChange("D:/ocrTraining/t5/31ed.jpg");

    /*LogIn w;
    w.show();
	w.setWindowTitle("µ«¬º");
	w.setFixedSize(700, 500);
	DataBase base1;
	base1.ToConnect();*/
	

	//Õ∏ ”±‰ªª≤‚ ‘
	/*Mat src = imread("D:/ocrTraining/HandwritingNum_pho/32.jpg");
	imshow("origin", src);
	imageProcessing process1;
	Mat dst = process1.preProcessing(src);
	imshow("dst", dst);
	imwrite("D:/ocrTraining/HandwritingNum_pho/32ed.jpg", dst);*/
	
    return a.exec();
}

