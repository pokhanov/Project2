#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include <QtCharts/qtchartsversion.h>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include "ui_QtWidgetsApplication1.h"
using namespace QtCharts;


class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();

public:
	void getChart(QString Account);

private:
    Ui::QtWidgetsApplication1Class ui;
};
