#pragma once
#pragma execution_character_set("utf-8")

#include <QMainWindow>
#include "ui_LogIn.h"

class LogIn : public QMainWindow
{
	Q_OBJECT

public:
	LogIn(QWidget *parent = nullptr);
	~LogIn();

private slots:
	void on_ToLogIn_clicked();
	void on_ToRegist_clicked();

private:
	Ui::LogInClass ui;
};
