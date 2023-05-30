#pragma once

#include <QObject>
#include <QSql>
#include <qsqldatabase.h>
#include <qdebug.h>
#include <qsqlerror.h>
#include <qmap.h>

class DataBase  : public QObject
{
	Q_OBJECT

public:
	DataBase(QObject *parent = nullptr);
	~DataBase();
	bool ToConnect();
	bool IsAccountExsist(QString account);	//����˺��Ƿ����
	int check(QList<QString> str);		//��������Ƿ���ȷ
	int creatAccount(QList<QString> str);	//�����˻�
	QList<int> getDateScores(QString account);	//����ĳһ�˺ŵ����гɼ�

private:
	QString currentAccount;
	
};

