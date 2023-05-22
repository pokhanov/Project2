#include "Regist.h"
#include "LogIn.h"
#include "DataBase.h"
#include <qmessagebox.h>

Regist::Regist(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("ע��");
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
		QMessageBox::information(this, "����", "�������˺�");
		return;
	}
	QString newPassword = ui.NewPasswordLine->text();
	if (newPassword.isEmpty()) {
		QMessageBox::information(this, "����", "����������");
		return;
	}
	
	QString PasswordResure = ui.PasswordResure->text();
	if (PasswordResure.isEmpty()) {
		QMessageBox::information(this, "����", "������ȷ������");
		return;
	}
	if (QString::compare(newPassword, PasswordResure)) {		//��������������벻һ��
		QMessageBox::information(this, "����", "�����������벻һ��");
		return;
	}

	QStringList str;
	str.append(newAccount);
	str.append(newPassword);
	DataBase base1;
	int info = base1.creatAccount(str);
	if (info == -1) {
		QMessageBox::information(this, "����", "���˺��Ѵ���");
		return;
	}
	if (info == 0) {
		QMessageBox::information(this, "����", "���ݿ�ִ�г���");
		return;
	}
	if (info == 1) {
		QMessageBox::information(this, "�ɹ�", "�˺Ŵ����ɹ�");
		this->close();
		LogIn *w = new LogIn;
		w->show();
	}
}
