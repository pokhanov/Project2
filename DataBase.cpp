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
	//数据库连接函数
	QSqlDatabase accounts = QSqlDatabase::addDatabase("QODBC");
	accounts.setHostName("localhost");
	accounts.setDatabaseName("Accounts");
	accounts.setUserName("QtProject");
	accounts.setPassword("12345");

	//检查是否连接成功
	bool check = accounts.open();
	if (check) {
		qDebug() << "连接成功";
		return 1;
	}
	else {
		qDebug() << "连接失败" << accounts.lastError().text();
		return 0;
	}
}

bool DataBase::IsAccountExsist(QString account) {
	QSqlQuery query;
	QString sql1 = QString("select id from Accounts where id = '%1' ").arg(account);
	query.exec(sql1);		//查询，查完后query是指向结果集以外的
	if (!query.first())		//.first()返回bool类型，表明当前查询结果是不是空集，不是空集则返回true并把query指向第一条有效记录
	{
		return 0;		//返回0表示用户不存在
	}
	else return 1;
}

int DataBase::check(QList<QString> str) {
	if (!IsAccountExsist(str[0])) {		//如果账户不存在
		return -1;
	}
	QSqlQuery query;
	QString sql2 = QString("select password from Accounts where id = '%1'").arg(str[0]);
	query.exec(sql2);
	query.next();
	bool passwordCorrect = QString::compare(query.value(0).toString(), str[1]);
	if (!passwordCorrect) return 1;	//返回1表示密码正确登陆成功
	else return 0;		//返回0表示密码错误
}

int DataBase::creatAccount(QList<QString> str) {
	if (IsAccountExsist(str[0])) {	//如果账户已经存在
		return -1;		//返回-1表示该账号已存在，创建失败
	}
	QSqlQuery query;
	QString sql = QString("INSERT INTO Accounts(id, password) VALUES('%1', '%2')").arg(str[0], str[1]);
	bool success = query.exec(sql);
	if (success) {
		return 1;		//返回1表示账户创建成功
	}
	return 0;		//返回0表示数据库执行出错
}

QList<int> DataBase::getDateScores(QString account) {
	QSqlQuery query;
	QString sql = QString(" SELECT score FROM scores WHERE id = '%1'").arg(account);
	query.exec(sql);
	QList<int> scores;
	//if (query.first()) {		//如果有成绩,把所有日期和成绩加入QMap中
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