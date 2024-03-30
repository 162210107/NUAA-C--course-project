#include "FireWork.h"
#include <stdlib.h>
#include <graphics.h>
#include <cmath>
const int WIDTH = 960;
const int HEIGHT = 720;
const double PI = 3.1415926;
const  int NUM = 10;

Fire::Fire()
{
	for (int i = 0; i < NUM; i++)
		//��ʼ��ÿ���ڵ�������
	{
		arr[i].max_x = rand() % (WIDTH - 400) + 50;
		arr[i].max_y = rand() % 200 + 200;
		arr[i].x = arr[i].max_x;//�ڵ�����Ϊֱ��
		arr[i].y = rand() % 100 + 620;
		arr[i].really = true;
		//��ʼ�����ʾ���Է���
	}
}
void Fire::CreateFire(int n)
{
	//��������̻�
	arr[n].max_x = rand() % (WIDTH - 400) + 50;
	arr[n].max_y = rand() % 200 + 200;
	arr[n].x = arr[n].max_x;
	arr[n].y = rand() % 100 + 620;
	arr[n].really = true;
	arr[n].radius = 30;
	arr[n].k = 0;
}

bool Fire::JudgePlay(int n)
{
	if (arr[n].really == true)
		return true;
	else
		return false;
}

void Fire::PlayFire()
{
	for (int i = 0; i < NUM; i++)
	{
		setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));//���ú��̻���ɫRGB
		if (JudgePlay(i) == false)
		{
			if (arr[i].y > arr[i].max_y)
				//�ж�Ŀǰλ���Ƿ������ߵ�
			{
				clearellipse(arr[i].x - 5, arr[i].y - 10, arr[i].x + 5, arr[i].y + 10);//�����Բ����
				arr[i].y -= 5;//�������ڸ߶�
				solidellipse(arr[i].x - 5, arr[i].y - 10, arr[i].x + 5, arr[i].y + 10);
				//�ޱ߿������
				putpixel(arr[i].x, arr[i].y + 10, getfillcolor());
				putpixel(arr[i].x - 1, arr[i].y + 10, getfillcolor());
				putpixel(arr[i].x + 1, arr[i].y + 10, getfillcolor());
				//�ڶ�Ӧλ�÷������ص�
			}
			else
			{
				clearellipse(arr[i].x - 5, arr[i].y - 10, arr[i].x + 5, arr[i].y + 10);//�����Բ����

				arr[i].max_really = true;
				//������ɵĵ�ǰ����С����ߵ����б��Ϊ�ɷ���

				fz[i].x = arr[i].max_x;
				fz[i].y = arr[i].max_y;
			}
		}
	}
}

void Fire::Fire_666()
{
	int num = 60;

	//��Ҫ���ĵ��㷨
	for (int n = 0; n < NUM; n++)
	{
		if (arr[n].max_really == true)
		{
			setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			for (int i = 0; i < num; i++)
			{
				double radian = (PI / 180) * (360 / num) * i;
				//��������ĽǶȱ�֤360
				int x = (int)(arr[n].x + cos(radian) * arr[n].radius);
				int y = (int)(arr[n].y - sin(radian) * arr[n].radius);
				//����Ƕȷ������ص�

				for (int j = 0; j < arr[n].radius; j++)
				{
					putpixel(x - j, y - j, getfillcolor());
					putpixel(x + j, y - j, getfillcolor());//�������ص�
				}
			}
			arr[n].k++;//��Ȧ
			arr[n].radius += 15;//Խ��Խ��
			if (arr[n].k == 3)
			{
				//�˴η�������±����̻�״̬
				arr[n].max_really = false;
				CreateFire(n);
			}
		}
	}
}