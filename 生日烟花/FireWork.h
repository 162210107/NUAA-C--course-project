#pragma once
#include"Point.h"
#include"Property.h"

class Fire:public Point
{
private:
	Point fz[10] = { 0 };
	Property arr[10];			//Ĭ��Ϊ10���ڵ�

public:
	Fire();
	void CreateFire(int n);  //�ָ�����
	void PlayFire();		 //�����̻�
	bool JudgePlay(int n);	 //�жϷ���
	void Change(int n) { arr[n].really = false; }
	void Fire_666();			 //�̻�����
};