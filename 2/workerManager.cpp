#include"workerManager.h"

workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件

	//文件不存在情况
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		//初始化人数
		this->m_EmArray = NULL;
		//初始化数组指针
		this->m_FileIsEmpty = true;
		//初始化文件为空标志
		ifs.close();
		return;
	}
	//文件存在，并且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->m_EmArray = NULL;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，并且记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num<<endl;
	this->m_EmpNum = num;
	//根据职工数创建数组
	this->m_EmArray = new Worker * [this->m_EmpNum];
	init_Emp();//初始化员工
}

void workerManager::showMenu()
{
	cout << "1.添加" << endl;
	cout << "2.显示" << endl;
	cout << "3.删除" << endl;
	cout << "4.修改" << endl;
	cout << "5.查找" << endl;
	cout << "6.排序" << endl;
	cout << "6.清空" << endl;
	cout << "0.退出通讯录" << endl;
	cout << endl;
}

int workerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	
	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}

void workerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}
		//存放到数组中
		this->m_EmArray[index] = worker;
		index++;
	}
}

void workerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void workerManager::Add_Emp()
{
	cout << "请输入增加职工数量：" << endl;

	int addNum = 0;//保护用户数量
	cin >> addNum;

	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原空间放到新空间
		if (this->m_EmArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;

			int ret = this->IsExist(id);
			if (ret!= -1)
			{
				cout << "已存在，请重新输入" << endl;
				i--;
			}
			else
			{
				cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
				cin >> name;

				cout << "请选择该职工岗位：" << endl;
				cout << "1.普通职工" << endl;
				cout << "2.经理" << endl;
				cout << "3.老板" << endl;
				cin >> dSelect;

				Worker* worker = NULL;
				switch (dSelect)
				{
				case 1:
					worker = new Employee(id, name, 1);
					break;
				case 2:
					worker = new Manager(id, name, 2);
					break;
				case 3:
					worker = new Boss(id, name, 3);
					break;
				default:
					break;
				}
				newSpace[this->m_EmpNum + i] = worker;
			}
		}
		//释放原有空间
		delete[]this->m_EmArray;

		//更改新空间的指向
		this->m_EmArray = newSpace;

		//更新新的个数
		this->m_EmpNum = newSize;

		//更新职工不为空的标志
		this->m_FileIsEmpty = false;

		cout << "成功添加" << addNum << "名新员工" << endl;

		//保存到文件中
		this->save();
    }
	else
		cout << "错误" << endl;
	//按任意键后，清屏回到上级目录
	system("pause");
	system("cls");
}

void workerManager::ShowEmp()
{
	if (this->m_FileIsEmpty)
		cout << "文件为空" << endl;
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void workerManager::FindEmp()
{
	if (this->m_FileIsEmpty)
		cout << "文件为空" << endl;
	else
	{
		cout << "1.按编号查找" << endl;
		cout << "2.按姓名查找" << endl;
		int select;
		cin >> select;

		if (select == 1)
		{
			cout << "输入编号";
			int f;
			cin >> f;
			int ret = this->IsExist(f);
			if (ret == -1)
				cout << "不存在"<<endl;
			else
			{
				cout << "存在：";
			this->m_EmArray[ret]->showInfo();
			}
		}
		else
		{
			string name;
			cout << "输入姓名：";
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmArray[i]->m_Name == name)
				{
					cout << "成功，编号为：" << m_EmArray[i]->m_Id << endl;
					this->m_EmArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
				cout << "查无此人";
		}
	}
	system("pause");
	system("cls");
}

void workerManager::SortEmp()
{
	if (this->m_FileIsEmpty)
		cout << "文件为空";
	else
	{
		cout << "1.升序" << endl;
		cout << "2.降序" << endl;

		int s = 0;
		cin >> s;

		for (int i = 0; i < m_EmpNum; i++)
		{
			int ret = i;
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (s == 1)
				{
					if (m_EmArray[ret]->m_Id > m_EmArray[j]->m_Id)
						ret = j;
				}
				else
				{
					if (m_EmArray[ret]->m_Id <m_EmArray[j]->m_Id)
						ret = j;
				}
			}
			if (i != ret)
			{
				Worker* temp = m_EmArray[i];
				m_EmArray[i] = m_EmArray[ret];
				m_EmArray[ret] = temp;
			}
		}
		cout << "成功" << endl;
		this->save();
		this->ShowEmp();
	}
}

void workerManager::CleanFile()
{
	ofstream ofs(FILENAME, ios::trunc);//如果存在，删除文件并重新创建
	ofs.close();

	if (this->m_EmArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmArray[i] != NULL)
				delete this->m_EmArray[i];
		}
		this->m_EmpNum = 0;
		delete[] this->m_EmArray;
		this->m_EmArray = NULL;
		this->m_FileIsEmpty = true;
	}
	cout << "成功";
	system("pause");
	system("cls");
}
int workerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (m_EmArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void workerManager::DelEmp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在" << endl;
	else
	{
		int m = 0;
		cout << "请输入要删除职工的编号" << endl;
		cin >> m;
		int a = this->IsExist(m);
		if (a == -1)
			cout << "不存在" << endl;
		else
		{
			cout << "存在" << endl;
			for (int j = a; j < this->m_EmpNum - 1; j++)
			{
				this->m_EmArray[j] = this->m_EmArray[j + 1];
			}
			this->m_EmpNum--;
			//同步更新
			this->save();
			cout << "删除成功" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::ModEmp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在" << endl;
	else
	{
		int id;
		cout << "输入职工编号" << endl;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret == -1)
			cout << "不存在此职工" << endl;
		else
		{
			delete[]this->m_EmArray[ret];

			int newid = 0;
			string newname = "";
			int dSelect = 0;

			cout << "新职工编号：";
			cin >> newid;
			int m = this->IsExist(newid);
			while(m != -1)
			{
				cout << "已存在此编号" << endl;
				cin >> newid;
				m = this->IsExist(newid);
			}
			cout << "新职工姓名：";
			cin >> newname;
			cout << "新职工岗位：";
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newid, newname, 1);
				break;
			case 2:
				worker = new Manager(newid, newname, 2);
				break;
			case 3:
				worker = new Boss(newid, newname, 3);
				break;
			default:
				break;
			}
			this->m_EmArray[ret] = worker;
			this->save();
		}
	}
	system("pause");
	system("cls");
}

void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出的方式打开文件  --写文件

	//将每个数据写进去
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmArray[i]->m_Id << " "
			<< this->m_EmArray[i]->m_Name << " "
			<< this->m_EmArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

workerManager::~workerManager()
{
	if (this->m_EmArray != NULL)
	{
		delete[]this->m_EmArray;
		this->m_EmArray = NULL;
	}
}