#pragma once
#include"Point.h"
//继承Point
class Property:public Point	
//烟花的属性
{
public:
	int max_x;	//最高点
	int max_y;

	int x;		//当前位置
	int y;

	bool really;	//是否可以发射
	bool max_really;

	int radius = 30;//半径

	int k = 0;//爱心圈数
};