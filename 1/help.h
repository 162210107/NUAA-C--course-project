#pragma once
using namespace std;//使用标准命名空间
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<graphics.h>
#include"bmp.h"
#include"bmp1.h"
#include"sss.h"
//***********不改变大小的功能，只改变像素值**********
//水平翻转
void rowReverse(int height, int width, RGBTriple* image);
//模糊化
void makeBlur(int height, int width, RGBTriple* image); 
//灰度化
void makeGary(int height, int width, RGBTriple* image);