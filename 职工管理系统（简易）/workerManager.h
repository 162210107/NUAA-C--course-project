#pragma once//��ֹͷ�ļ��ظ�����
using namespace std;//ʹ�ñ�׼�����ռ�
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

	//���캯��
	workerManager();

	//��ʾ�˵�
	void showMenu();

	//����ְ��
	void Add_Emp();

	//ͳ������
	int get_EmpNum();

	//�����ļ�
	void save();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void ShowEmp();

	//ɾ��ְ��
	void DelEmp();

	//�޸�ְ��
	void ModEmp();

	//����ְ��
	void FindEmp();

	//����ְ��
	void SortEmp();

	//����ļ�
	void CleanFile();

	//ְ���Ƿ����
	int IsExist(int id);

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//�˳�����
	void exitSystem();

	//��������
	~workerManager();

	int m_EmpNum;//���� 

	Worker** m_EmArray;//Ա������ָ��
};