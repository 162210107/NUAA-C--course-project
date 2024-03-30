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
		//初始化每个炮弹的属性
	{
		arr[i].max_x = rand() % (WIDTH - 400) + 50;
		arr[i].max_y = rand() % 200 + 200;
		arr[i].x = arr[i].max_x;//炮弹发射为直线
		arr[i].y = rand() % 100 + 620;
		arr[i].really = true;
		//初始化完表示可以发射
	}
}
void Fire::CreateFire(int n)
{
	//随机生成烟花
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
		setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));//设置好烟花颜色RGB
		if (JudgePlay(i) == false)
		{
			if (arr[i].y > arr[i].max_y)
				//判断目前位置是否大于最高点
			{
				clearellipse(arr[i].x - 5, arr[i].y - 10, arr[i].x + 5, arr[i].y + 10);//清空椭圆区域
				arr[i].y -= 5;//降低现在高度
				solidellipse(arr[i].x - 5, arr[i].y - 10, arr[i].x + 5, arr[i].y + 10);
				//无边框有填充
				putpixel(arr[i].x, arr[i].y + 10, getfillcolor());
				putpixel(arr[i].x - 1, arr[i].y + 10, getfillcolor());
				putpixel(arr[i].x + 1, arr[i].y + 10, getfillcolor());
				//在对应位置放置像素点
			}
			else
			{
				clearellipse(arr[i].x - 5, arr[i].y - 10, arr[i].x + 5, arr[i].y + 10);//清空椭圆区域

				arr[i].max_really = true;
				//随机生成的当前坐标小于最高点所有标记为可发射

				fz[i].x = arr[i].max_x;
				fz[i].y = arr[i].max_y;
			}
		}
	}
}

void Fire::Fire_666()
{
	int num = 60;

	//主要画心的算法
	for (int n = 0; n < NUM; n++)
	{
		if (arr[n].max_really == true)
		{
			setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			for (int i = 0; i < num; i++)
			{
				double radian = (PI / 180) * (360 / num) * i;
				//计算所需的角度保证360
				int x = (int)(arr[n].x + cos(radian) * arr[n].radius);
				int y = (int)(arr[n].y - sin(radian) * arr[n].radius);
				//计算角度放置像素点

				for (int j = 0; j < arr[n].radius; j++)
				{
					putpixel(x - j, y - j, getfillcolor());
					putpixel(x + j, y - j, getfillcolor());//放置像素点
				}
			}
			arr[n].k++;//三圈
			arr[n].radius += 15;//越来越大
			if (arr[n].k == 3)
			{
				//此次放完则更新本次烟花状态
				arr[n].max_really = false;
				CreateFire(n);
			}
		}
	}
}