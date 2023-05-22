#include "Regist.h"
#include "LogIn.h"
#include "DataBase.h"
#include <qmessagebox.h>

Regist::Regist(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("注册");
}

Regist::~Regist()
{}

void Regist::on_BackToLogIn_clicked() {
	this->close();
	LogIn *w = new LogIn;
	w->show();
}

void Regist::on_ToAddAccount_clicked() {
	QString newAccount = ui.newAccountLine->text();
	if (newAccount.isEmpty()) {
		QMessageBox::information(this, "错误", "请输入账号");
		return;
	}
	QString newPassword = ui.NewPasswordLine->text();
	if (newPassword.isEmpty()) {
		QMessageBox::information(this, "错误", "请输入密码");
		return;
	}
	
	QString PasswordResure = ui.PasswordResure->text();
	if (PasswordResure.isEmpty()) {
		QMessageBox::information(this, "错误", "请输入确认密码");
		return;
	}
	if (QString::compare(newPassword, PasswordResure)) {		//如果两次输入密码不一致
		QMessageBox::information(this, "错误", "两次输入密码不一致");
		return;
	}

	QStringList str;
	str.append(newAccount);
	str.append(newPassword);
	DataBase base1;
	int info = base1.creatAccount(str);
	if (info == -1) {
		QMessageBox::information(this, "错误", "该账号已存在");
		return;
	}
	if (info == 0) {
		QMessageBox::information(this, "错误", "数据库执行出错");
		return;
	}
	if (info == 1) {
		QMessageBox::information(this, "成功", "账号创建成功");
		this->close();
		LogIn *w = new LogIn;
		w->show();
	}
}
