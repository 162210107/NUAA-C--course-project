#pragma once
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include "FireWork.h"
class Deal
{
public:
	IMAGE win_image;

	//��ʾ�˵�
	void showMenu();

	//button����
	void button(int x, int y, int w, int h, TCHAR* text);

	//���ֲ���
	void BGM();

	//ף����
	void Blessing();

	// ���ֵ���
	void lunixy_fade_in(TCHAR text[40]);

	// ���ֵ���
	void lunixy_fade_out(TCHAR text[40]);

	//��Ա��ʾ
	void ShowMember();

	//�̻�
	void FireWork();

	//�رմ���
	void close();
};