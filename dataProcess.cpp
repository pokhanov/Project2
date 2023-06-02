#include "dataProcess.h"
#include "imageProcessing.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include<fstream>
#include<Qtcore/qvector.h>
//#include <opencv2/opencv.hpp>
#include <opencv.hpp>
using namespace std;

bool dataProcess::isValid(char curC) {
	if ((curC >= '0' && curC <= '9') || curC == '+' || curC == '-'
		|| curC == '=') return true;
	else return false;
}

void dataProcess::imageProcess(int y, int x, int width, int length, bool right, const char * path) {
	Mat src = imread(path);
//imshow("ͼƬ��ʾ����", src);
	Scalar s;
	if (right) s = Scalar(0, 255, 0);
	else s = Scalar(0, 0, 255);
	rectangle(src, Rect(x, y, width, length), s, 3);
	imwrite(path, src);
	imshow("11", src);
}




void dataProcess::txtChange(const char * path) {
	fstream f;
	f.open("data.txt", ios::in);
	string oriStr;
	string newStr;
	while (f >> oriStr) {  //ȫ��һ���Զ����
		for (int i = 0; i < oriStr.size(); i++) {
			char curC = oriStr[i];
			//�����λ����Ϣ����ʽ�ַ��������ַ����м���
			if (isValid(curC)) {
				newStr = newStr + curC;
				//�����ǰΪ��Ч��Ϣ����һ����Ϣ��Ч�����롰 ���ָ�
				if (i + 1 < oriStr.size() && !isValid(oriStr[i + 1])) {
					newStr = newStr + ' ';
				}
			}
		}
	}
	f.close();

	//�ѽ��ת��Ϊvector��ʽ
	QVector<string> res;
	istringstream string_to_vector(newStr);
	string str;
	while (string_to_vector >> str) {
		res.append(str);
	}


	//�ѷ���ʽ��λ����Ϣ�޳�
	//�ҵ��еȺŵĲ��֣�������ǰ�ĸ�������ͨ�������������ַ���
	QVector<QVector<string>> trueRes;
	for (int i = 0; i < res.size(); i++) {
		for (int g = 0; g < res[i].size(); g++) {
			//�ҳ���ʽ���еȺŴ��ڵ�ʽ�ӣ�
			if (res[i][g] == '=') {
				QVector<string> cur;
				//����ʽ����λ����Ϣ����trueRes
				for (int h = 4; h >= 0; h--) {
					cur.append(res[i - h]);
				}
				trueRes.append(cur);
			}
		}
	}

	int numOfRignt = 0;
	for (int i = 0; i < trueRes.size(); i++) {
		string curEquation = trueRes[i][4];
std::cout << curEquation << endl;
		string numStr;
		int j = 0;
		//ת������һ������
		while (curEquation[j] != '+' && curEquation[j] != '-') {
			numStr = numStr + curEquation[j];
			j++;
		}
		int symbol = j;
		int num1 = atoi(numStr.c_str());
		j++;
		numStr = "";
		//ת�����ڶ�������
		while (curEquation[j] != '=') {
			numStr = numStr + curEquation[j];
			j++;
		}
		int num2 = atoi(numStr.c_str());
		j++;
		numStr = "";
		//ת��������������
		while (j < curEquation.size()) {
			numStr = numStr + curEquation[j];
			j++;
		}
		int num3 = atoi(numStr.c_str());
		//������ʽ��ȷ���
		int num;
		if (curEquation[symbol] == '+') num = num1 + num2;
		else num = num1 - num2;
		if (num == num3) numOfRignt++;
			int y = atoi(trueRes[i][0].c_str());
			int x = atoi(trueRes[i][1].c_str());
			int width = atoi(trueRes[i][2].c_str());
			int length = atoi(trueRes[i][3].c_str());
			imageProcess(y, x, width, length, num == num3, path);
	}
	int total = trueRes.size();
std::cout << "�ܹ���ʽ����" << total<<endl;
std::cout << "��ȷ��ʽ����" << numOfRignt << endl;
int core = ((double)numOfRignt / total) * 100;
std::cout << "�÷֣�" << core << endl;
	
}