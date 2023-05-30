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
	this->setWindowTitle("ѧ���ɼ����������ϵͳ");
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}

void QtWidgetsApplication1::getChart(QString Account) {
	QChart *chart =  new QChart();		//����chart
	//������ͼ
		//��DataBaseҪ���ݣ�������Ӧ��ʱ��ͳɼ�List��
	DataBase base2;
	QList<int> Scores;
	Scores = base2.getDateScores(Account);
		//��ͼ������ʱ�䣬����ɼ���
	QLineSeries *series = new QLineSeries();	//������������
	for (int i = 0; i < Scores.size(); i++) {
		series->append(i, Scores[i]);
		//qDebug() << "score: " << i << endl;
	}
	series->setName("�ɼ�����ͼ");
	chart->addSeries(series);
	QValueAxis *axisX = new QValueAxis();		//����������
	QValueAxis *axisY = new QValueAxis();
	axisY->setTitleText("�ɼ�");
	axisY->setRange(0, 100);
	chart->setAxisX(axisX, series);		//Ϊ������������������
	chart->setAxisY(axisY, series);
	
	ui.graphicsView->setChart(chart);	//������ͼ�Ž���������
}