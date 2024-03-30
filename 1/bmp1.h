#pragma once
using namespace std;//使用标准命名空间
#include"bmp.h"
//基类24位图
class bmp1:public bmp
{
public:
	bmp1();
	bmp1(const bmp1& obj);//拷贝构造
	virtual void readPic(char fileName[]);
	virtual void writePic(void (*myMethod)(int, int, RGBTriple*),char* outFileName);
	virtual void ShowImage(int i);
	friend ostream& operator<<(ostream& out, bmp& obj);
	~bmp1();
};
