#include "LogIn.h"
#include "DataBase.h"
#include "main.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogIn w;
    w.show();
	w.setWindowTitle("µÇÂ¼");
	w.setFixedSize(700, 500);
	DataBase base1;
	base1.ToConnect();
    return a.exec();
}
