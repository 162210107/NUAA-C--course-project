#pragma once//防止头文件重复包含
using namespace std;//使用标准命名空间
#include<iostream>
#include<fstream>
#include"worker.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#define FILENAME "empFile.txt"

class workerManager
{
public:

	//构造函数
	workerManager();

	//显示菜单
	void showMenu();

	//增加职工
	void Add_Emp();

	//统计人数
	int get_EmpNum();

	//保存文件
	void save();

	//初始化员工
	void init_Emp();

	//显示职工
	void ShowEmp();

	//删除职工
	void DelEmp();

	//修改职工
	void ModEmp();

	//查找职工
	void FindEmp();

	//排序职工
	void SortEmp();

	//清空文件
	void CleanFile();

	//职工是否存在
	int IsExist(int id);

	//标志文件是否为空
	bool m_FileIsEmpty;

	//退出程序
	void exitSystem();

	//析构函数
	~workerManager();

	int m_EmpNum;//人数 

	Worker** m_EmArray;//员工数组指针
};