#pragma once
#include"bmp.h"
//基类16位图
class bmp3 :public bmp
{
public:
	char* rgb_mask;
	//掩饰码
	char* imagebuf;//实际像素值
	char* bmpbuf;//掩饰码值

	bmp3();
	bmp3(const bmp3& obj);//拷贝构造
	virtual void readPic(char fileName[]);
	virtual void writePic(void (*myMethod)(int, int, RGBTriple*), char* outFileName);
	virtual void ShowImage(int i);
	friend ostream& operator<<(ostream& out, bmp& obj);
	~bmp3();
};