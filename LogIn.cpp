#include "main.h"
#include "LogIn.h"
#include "DataBase.h"
#include "Regist.h"
#include <qmessagebox.h>


LogIn::LogIn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("��¼");
}

LogIn::~LogIn()
{}

void LogIn::on_ToLogIn_clicked() {
	//��������ȡ�˺������ַ�������֤���ʽ��Ч��
	QString account = ui.accountNumber->text();
	if (account.isEmpty()) {
		QMessageBox::information(this, "����", "�������˺�");
		return;
	}
	QString password = ui.passwordLine->text();
	if (password.isEmpty()) {
		QMessageBox::information(this, "����", "����������");
		return;
	}
	//���˺����봫�����ݿ�ģ����֤�˺��Ƿ���ڼ������Ƿ���ȷ
	QList<QString> str;
	str.append(account);
	str.append(password);
	DataBase base1;
	int info = base1.check(str);
	if (info == -1) {
		QMessageBox::warning(this, "����", "�û�������");
		return;
	}
	if (info == 0) {
		QMessageBox::warning(this, "����", "�������");
		return;
	}
	if (info == 1) {
		//��½�ɹ��� ҳ��ת��
		QMessageBox::information(this, "test", "��¼�ɹ�");
	}
	
}

void LogIn::on_ToRegist_clicked() {
	this->close();
	Regist *r = new Regist;
	r->show();
	
}