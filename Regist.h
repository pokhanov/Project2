#pragma once
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include "ui_Regist.h"

class Regist : public QMainWindow
{
	Q_OBJECT

public:
	Regist(QWidget *parent = nullptr);
	~Regist();

private slots:
	void on_BackToLogIn_clicked();
	void on_ToAddAccount_clicked();

private:
	Ui::RegistClass ui;
};
