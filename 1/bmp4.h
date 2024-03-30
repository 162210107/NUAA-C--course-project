#pragma once
#include"bmp.h"
//基类单位图
class bmp4 :public bmp
{
public:
	bmp4();
	bmp4(const bmp4& obj);//拷贝构造
	virtual void readPic(char fileName[]);
	virtual void writePic(void (*myMethod)(int, int, RGBTriple*), char* outFileName);
	virtual void ShowImage(int i);
	friend ostream& operator<<(ostream& out, bmp& obj);
	~bmp4();
};