#pragma once
#include"Point.h"
#include"Property.h"

class Fire:public Point
{
private:
	Point fz[10] = { 0 };
	Property arr[10];			//默认为10个炮弹

public:
	Fire();
	void CreateFire(int n);  //恢复属性
	void PlayFire();		 //发射烟花
	bool JudgePlay(int n);	 //判断发射
	void Change(int n) { arr[n].really = false; }
	void Fire_666();			 //烟花绽放
};