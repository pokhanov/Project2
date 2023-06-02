#pragma once
using namespace std;
class dataProcess
{
public:
	void txtChange(const char * path);
	bool isValid(char curC);
	void imageProcess(int y, int x, int width, int length, bool right, const char * path);
};

