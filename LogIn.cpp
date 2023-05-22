#include "main.h"
#include "LogIn.h"
#include "DataBase.h"
#include "Regist.h"
#include <qmessagebox.h>


LogIn::LogIn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("登录");
}

LogIn::~LogIn()
{}

void LogIn::on_ToLogIn_clicked() {
	//从输入框获取账号密码字符串并验证其格式有效性
	QString account = ui.accountNumber->text();
	if (account.isEmpty()) {
		QMessageBox::information(this, "错误", "请输入账号");
		return;
	}
	QString password = ui.passwordLine->text();
	if (password.isEmpty()) {
		QMessageBox::information(this, "错误", "请输入密码");
		return;
	}
	//将账号密码传入数据库模块验证账号是否存在及密码是否正确
	QList<QString> str;
	str.append(account);
	str.append(password);
	DataBase base1;
	int info = base1.check(str);
	if (info == -1) {
		QMessageBox::warning(this, "错误", "用户不存在");
		return;
	}
	if (info == 0) {
		QMessageBox::warning(this, "错误", "密码错误");
		return;
	}
	if (info == 1) {
		//登陆成功， 页面转跳
		QMessageBox::information(this, "test", "登录成功");
	}
	
}

void LogIn::on_ToRegist_clicked() {
	this->close();
	Regist *r = new Regist;
	r->show();
	
}