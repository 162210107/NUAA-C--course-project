#pragma once
#include"bmp.h"
#include<fstream>
//基类八位图
class bmp2 :public bmp
{
public:
	RGBQUAD* rgbQuad;

	bmp2();
	bmp2(const bmp2& obj);//拷贝构造
	virtual void readPic(char fileName[]);
	virtual void writePic(void (*myMethod)(int, int, RGBTriple*), char* outFileName);
	virtual void ShowImage(int i);
	friend ostream& operator<<(ostream& out, bmp& obj);
	~bmp2();
};