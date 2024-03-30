#pragma once
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include "FireWork.h"
class Deal
{
public:
	IMAGE win_image;

	//显示菜单
	void showMenu();

	//button函数
	void button(int x, int y, int w, int h, TCHAR* text);

	//音乐播放
	void BGM();

	//祝福语
	void Blessing();

	// 文字淡入
	void lunixy_fade_in(TCHAR text[40]);

	// 文字淡出
	void lunixy_fade_out(TCHAR text[40]);

	//成员显示
	void ShowMember();

	//烟花
	void FireWork();

	//关闭窗口
	void close();
};