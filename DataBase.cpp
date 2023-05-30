#include "main.h"
#include "qresource.h"
#include "DataBase.h"
#include <qsqlquery.h>
#include <qvector.h>
#include <qvariant.h>
#include <QDate>
#include <QVariant> 

DataBase::DataBase(QObject *parent)
	: QObject(parent)
{

}

DataBase::~DataBase()
{}

bool DataBase::ToConnect() {
	//���ݿ����Ӻ���
	QSqlDatabase accounts = QSqlDatabase::addDatabase("QODBC");
	accounts.setHostName("localhost");
	accounts.setDatabaseName("Accounts");
	accounts.setUserName("QtProject");
	accounts.setPassword("12345");

	//����Ƿ����ӳɹ�
	bool check = accounts.open();
	if (check) {
		qDebug() << "���ӳɹ�";
		return 1;
	}
	else {
		qDebug() << "����ʧ��" << accounts.lastError().text();
		return 0;
	}
}

bool DataBase::IsAccountExsist(QString account) {
	QSqlQuery query;
	QString sql1 = QString("select id from Accounts where id = '%1' ").arg(account);
	query.exec(sql1);		//��ѯ�������query��ָ�����������
	if (!query.first())		//.first()����bool���ͣ�������ǰ��ѯ����ǲ��ǿռ������ǿռ��򷵻�true����queryָ���һ����Ч��¼
	{
		return 0;		//����0��ʾ�û�������
	}
	else return 1;
}

int DataBase::check(QList<QString> str) {
	if (!IsAccountExsist(str[0])) {		//����˻�������
		return -1;
	}
	QSqlQuery query;
	QString sql2 = QString("select password from Accounts where id = '%1'").arg(str[0]);
	query.exec(sql2);
	query.next();
	bool passwordCorrect = QString::compare(query.value(0).toString(), str[1]);
	if (!passwordCorrect) return 1;	//����1��ʾ������ȷ��½�ɹ�
	else return 0;		//����0��ʾ�������
}

int DataBase::creatAccount(QList<QString> str) {
	if (IsAccountExsist(str[0])) {	//����˻��Ѿ�����
		return -1;		//����-1��ʾ���˺��Ѵ��ڣ�����ʧ��
	}
	QSqlQuery query;
	QString sql = QString("INSERT INTO Accounts(id, password) VALUES('%1', '%2')").arg(str[0], str[1]);
	bool success = query.exec(sql);
	if (success) {
		return 1;		//����1��ʾ�˻������ɹ�
	}
	return 0;		//����0��ʾ���ݿ�ִ�г���
}

QList<int> DataBase::getDateScores(QString account) {
	QSqlQuery query;
	QString sql = QString(" SELECT score FROM scores WHERE id = '%1'").arg(account);
	query.exec(sql);
	QList<int> scores;
	//if (query.first()) {		//����гɼ�,���������ںͳɼ�����QMap��
	//	int score = query.value(0).toInt();
	//	scores.append(score);
		while (query.next()) {
			int score = query.value(0).toInt();
			qDebug() << "score: " << score << "  ";
			scores.append(score);
		}
	//}
	return scores;
}