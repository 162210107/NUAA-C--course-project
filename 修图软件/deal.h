#pragma once
using namespace std;//使用标准命名空间
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<graphics.h>
#include<math.h>

#include"bmp.h"
#include"bmp2.h"
#include"bmp3.h"
#include"bmp1.h"
#include"bmp4.h"
#include"help.h"
#include"sss.h"
class deal
{
	int m_EmpNum;//个数

	bmp** m_EmArray;//图像数组指针
public:
	//构造函数
	deal();

	//显示菜单
	void showMenu();

	//button函数
	void button(int x, int y, int w, int h, TCHAR* text);

	//二值化图像
	void binaryimage();

	//读取图像
	void readimagebox();

	//翻转图像
	void ImageInvert();

	//模糊图像
	void Imagemuhu();
	
	//截取图像
	void Imageintercept();

	//叠加图像
	void ImageOver();

	//缩放图像
	void ImageBig();

	//旋转图像
	void ImageTurn();

	//灰度图片
	void ImageGray();

	//清屏
	void closeImage();

	//填充图像
	void ImageAdd();

	//求解方程的k,b值
	void function_line(double x1, double y1, double x2, double y2, double& k, double& b);

	//返回直线的y
	double solve_y(double k, double b, double x);

	//返回直线的x
	double solve_x(double k, double b, double y);

	//排序----从小到大排序
	void sort_min_to_max(double suitable_x[], int n);

	//输出最大的元素值
	double find_max(double elem[], int N);

	//输出最小的元素值
	double find_min(double elem[], int N);

	//找出扫描线与边界相交的点，并储存在suitable_x[]中，把相交的点数储存在n中
	void Suitable_x(double x[], double y[], int N, double now_y, double suitable_x[], int& n);

	//快速排序
	void quick_sort(double s[], int l, int r);

	//关闭窗口
	void close();

	//展示所有
	void showall();

	//析构函数
	~deal();
};