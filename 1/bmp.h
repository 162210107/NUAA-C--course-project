#pragma once
using namespace std;//使用标准命名空间
#define _CRT_SECURE_NO_WARNINGS
#define BMPTYPE 19778
#include<fstream>
#include<iostream>
#include<conio.h>
#include <wtypes.h>
#include <wingdi.h>
#include <graphics.h>
#include"sss.h"
//虚基类
class bmp 
{
public:
    virtual void readPic(char fileName[]) = 0;//读文件
    virtual void writePic(void (*myMethod)(int, int, RGBTriple*), char* outFileName)=0;
    //基于本类对象进行处理后存储到outfilename这个图像中
    virtual void ShowImage(int i) = 0;
    //指定窗口中显示图像
    friend ostream& operator<<(ostream& out, bmp& obj);
    //输出流重载

    int success=0;
    //记录是否成功读取和存储
    int offset=0;
    //内存偏移量
    RGBTriple* surface;
    //指向储存像素的空间
    BmpFileHeader fileHeader;
    //文件头
    BmpFileInFoHeader fileInFoHeader;
    //信息头
    char* mfilename;
    //图像名称
};