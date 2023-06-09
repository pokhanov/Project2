#pragma once

#include <QObject>
#include <QSql>
#include <qsqldatabase.h>
#include <qdebug.h>
#include <qsqlerror.h>

class DataBase  : public QObject
{
	Q_OBJECT

public:
	DataBase(QObject *parent = nullptr);
	~DataBase();
	bool ToConnect();
	bool IsAccountExsist(QString account);	//检查账号是否存在
	int check(QList<QString> str);		//检查密码是否正确
	int creatAccount(QList<QString> str);	//创建账户
	
};

