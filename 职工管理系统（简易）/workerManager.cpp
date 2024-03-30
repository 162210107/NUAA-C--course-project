#include"workerManager.h"

workerManager::workerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�

	//�ļ����������
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		//��ʼ������
		this->m_EmArray = NULL;
		//��ʼ������ָ��
		this->m_FileIsEmpty = true;
		//��ʼ���ļ�Ϊ�ձ�־
		ifs.close();
		return;
	}
	//�ļ����ڣ�����û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->m_EmArray = NULL;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ����Ҽ�¼����
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num<<endl;
	this->m_EmpNum = num;
	//����ְ������������
	this->m_EmArray = new Worker * [this->m_EmpNum];
	init_Emp();//��ʼ��Ա��
}

void workerManager::showMenu()
{
	cout << "1.���" << endl;
	cout << "2.��ʾ" << endl;
	cout << "3.ɾ��" << endl;
	cout << "4.�޸�" << endl;
	cout << "5.����" << endl;
	cout << "6.����" << endl;
	cout << "6.���" << endl;
	cout << "0.�˳�ͨѶ¼" << endl;
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
		//��¼����
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
		//��ŵ�������
		this->m_EmArray[index] = worker;
		index++;
	}
}

void workerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void workerManager::Add_Emp()
{
	cout << "����������ְ��������" << endl;

	int addNum = 0;//�����û�����
	cin >> addNum;

	if (addNum > 0)
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ�ռ�ŵ��¿ռ�
		if (this->m_EmArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmArray[i];
			}
		}

		//����������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;

			int ret = this->IsExist(id);
			if (ret!= -1)
			{
				cout << "�Ѵ��ڣ�����������" << endl;
				i--;
			}
			else
			{
				cout << "�������" << i + 1 << "����ְ��������" << endl;
				cin >> name;

				cout << "��ѡ���ְ����λ��" << endl;
				cout << "1.��ְͨ��" << endl;
				cout << "2.����" << endl;
				cout << "3.�ϰ�" << endl;
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
		//�ͷ�ԭ�пռ�
		delete[]this->m_EmArray;

		//�����¿ռ��ָ��
		this->m_EmArray = newSpace;

		//�����µĸ���
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;

		cout << "�ɹ����" << addNum << "����Ա��" << endl;

		//���浽�ļ���
		this->save();
    }
	else
		cout << "����" << endl;
	//��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

void workerManager::ShowEmp()
{
	if (this->m_FileIsEmpty)
		cout << "�ļ�Ϊ��" << endl;
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ýӿ�
			this->m_EmArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void workerManager::FindEmp()
{
	if (this->m_FileIsEmpty)
		cout << "�ļ�Ϊ��" << endl;
	else
	{
		cout << "1.����Ų���" << endl;
		cout << "2.����������" << endl;
		int select;
		cin >> select;

		if (select == 1)
		{
			cout << "������";
			int f;
			cin >> f;
			int ret = this->IsExist(f);
			if (ret == -1)
				cout << "������"<<endl;
			else
			{
				cout << "���ڣ�";
			this->m_EmArray[ret]->showInfo();
			}
		}
		else
		{
			string name;
			cout << "����������";
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmArray[i]->m_Name == name)
				{
					cout << "�ɹ������Ϊ��" << m_EmArray[i]->m_Id << endl;
					this->m_EmArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
				cout << "���޴���";
		}
	}
	system("pause");
	system("cls");
}

void workerManager::SortEmp()
{
	if (this->m_FileIsEmpty)
		cout << "�ļ�Ϊ��";
	else
	{
		cout << "1.����" << endl;
		cout << "2.����" << endl;

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
		cout << "�ɹ�" << endl;
		this->save();
		this->ShowEmp();
	}
}

void workerManager::CleanFile()
{
	ofstream ofs(FILENAME, ios::trunc);//������ڣ�ɾ���ļ������´���
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
	cout << "�ɹ�";
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
		cout << "�ļ�������" << endl;
	else
	{
		int m = 0;
		cout << "������Ҫɾ��ְ���ı��" << endl;
		cin >> m;
		int a = this->IsExist(m);
		if (a == -1)
			cout << "������" << endl;
		else
		{
			cout << "����" << endl;
			for (int j = a; j < this->m_EmpNum - 1; j++)
			{
				this->m_EmArray[j] = this->m_EmArray[j + 1];
			}
			this->m_EmpNum--;
			//ͬ������
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
	}
	system("pause");
	system("cls");
}

void workerManager::ModEmp()
{
	if (this->m_FileIsEmpty)
		cout << "�ļ�������" << endl;
	else
	{
		int id;
		cout << "����ְ�����" << endl;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret == -1)
			cout << "�����ڴ�ְ��" << endl;
		else
		{
			delete[]this->m_EmArray[ret];

			int newid = 0;
			string newname = "";
			int dSelect = 0;

			cout << "��ְ����ţ�";
			cin >> newid;
			int m = this->IsExist(newid);
			while(m != -1)
			{
				cout << "�Ѵ��ڴ˱��" << endl;
				cin >> newid;
				m = this->IsExist(newid);
			}
			cout << "��ְ��������";
			cin >> newname;
			cout << "��ְ����λ��";
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
	ofs.open(FILENAME, ios::out);//������ķ�ʽ���ļ�  --д�ļ�

	//��ÿ������д��ȥ
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