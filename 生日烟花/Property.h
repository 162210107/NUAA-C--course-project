#pragma once
#include"Point.h"
//�̳�Point
class Property:public Point	
//�̻�������
{
public:
	int max_x;	//��ߵ�
	int max_y;

	int x;		//��ǰλ��
	int y;

	bool really;	//�Ƿ���Է���
	bool max_really;

	int radius = 30;//�뾶

	int k = 0;//����Ȧ��
};