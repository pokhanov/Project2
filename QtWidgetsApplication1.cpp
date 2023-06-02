#include "QtWidgetsApplication1.h"
#include "DataBase.h"
#include <qdatetimeaxis.h>
#include <qvalueaxis.h>
#include <QDateTime>
#include <qDebug.h>

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	this->setFixedSize(700, 700);
	this->setWindowTitle("学生成绩辅助与管理系统");
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}

void QtWidgetsApplication1::getChart(QString Account) {
	QChart *chart =  new QChart();		//建立chart
	//画折线图
		//从DataBase要数据（返回相应的时间和成绩List）
	DataBase base2;
	QList<int> Scores;
	Scores = base2.getDateScores(Account);
		//绘图（横轴时间，纵轴成绩）
	QLineSeries *series = new QLineSeries();	//创建折线序列
	for (int i = 0; i < Scores.size(); i++) {
		series->append(i, Scores[i]);
		//qDebug() << "score: " << i << endl;
	}
	series->setName("成绩曲线图");
	chart->addSeries(series);
	QValueAxis *axisX = new QValueAxis();		//建立坐标轴
	QValueAxis *axisY = new QValueAxis();
	axisY->setTitleText("成绩");
	axisY->setRange(0, 100);
	chart->setAxisX(axisX, series);		//为折线序列设置坐标轴
	chart->setAxisY(axisY, series);
	
	ui.graphicsView->setChart(chart);	//把折线图放进主窗口里
}