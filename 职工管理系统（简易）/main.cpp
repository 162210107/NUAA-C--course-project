#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<graphics.h>
#include<math.h>
#include "workerManager.h"
#include"employee.h"
#include"worker.h"
#include"manager.h"
#include<conio.h>//getch()函数的头文件
#include<mmsystem.h>//包含多媒体接口
#include <string>

#pragma comment(lib,"winmm.lib")//处理接口
void BGM()
{
	mciSendString(_T("open ./music.mp3"), 0, 0, 0);//0，0,0为默认输出控制台
	mciSendString(_T("play ./music.mp3"), 0, 0, 0);
}

using namespace std;

bool IsLoggedIn()
{
    string username, password, un, pw;
    cout << "用户名: ";
    cin >> username;
    cout << "密码: ";
    cin >> password;

    ifstream in;
    in.open("data.txt", ios::in);
    while (!in.eof())
    {
        getline(in, un);
        if (un == username)
        {
            getline(in, pw);
            if (pw == password)
            {
                cout << "登录成功！" << endl;
                return true;
            }
            continue;
        }
        getline(in, pw);
    }
    in.close();
    return false;
}

bool IsExist(string username)
{
    string un;
    ifstream in;
    in.open("data.txt", ios::in);
    while (!in.eof())
    {
        getline(in, un);
        if (un == username)
        {
            cout << "已存在该用户名" << endl;
            return FALSE;
        }
    }
    in.close();
    return true;
}

bool IsComp(string password)
{
    if (password.length() < 6)
    {
        cout << endl;
        cout << "密码长度过短，请重新输入" << endl;
        return FALSE;
    }
    else if (password.length() >= 21)
    {
        cout << endl;
        cout << "长度太长，请重新输入" << endl;
        return FALSE;
    }
    char p[22];
    password.copy(p, password.length(), 0);
    *(p + password.length()) = '\0';
    int a[4] = { 0 };
    for (int i = 0; i < password.length(); i++)
    {
        if (p[i] >= 'A' && p[i] <= 'Z')
        {
            a[0] = 1;
        }
        else if (p[i] >= 'a' && p[i] <= 'z')
        {
            a[1] = 1;
        }
        else if (p[i] >= '0' && p[i] <= '9')
        {
            a[2] = 1;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (a[i] == 0)
        {
            cout << endl;
            cout << "太过简单" << endl;
            return FALSE;
        }
    }
    return TRUE;
}

int main()
{
	workerManager vm;

    int choice = 0;

    cout << "1: 注册\n2: 登录\n3: 退出\n选择: ";
    cin >> choice;
    if (choice == 1)
    {
        string username;

        cout << "用户名: ";
        cin >> username;
        bool check1 = IsExist(username);
        while (!check1)
        {
            cout << "用户名: ";
            cin >> username;
            check1 = IsExist(username);
        }

        char password[64], ch;
        int i = 0;
        cout << "请输入密码:";
        while (true)
        {
            ch = _getch();//无回显的输入
            password[i++] = ch;
            if (ch == '\r')//getch()函数如果读到回车符号返回'/r'
            {
                password[i] = '\0';
                break;
            }
            putchar('*');
        }
        bool check2 = IsComp(password);
        while (!check2)
        {
            int i = 0;
            cout << "请输入密码:";
            while (true)
            {
                ch = _getch();//无回显的输入
                password[i++] = ch;
                if (ch == '\r')//getch()函数如果读到回车符号返回'/r'
                {
                    password[i] = '\0';
                    break;
                }
                putchar('*');
            }
            check2 = IsComp(password);
        }
        cout << endl;

        cout << "请再次输入密码：";
        char password2[22] = { 0 };
        while (true)
        {
            ch = _getch();//无回显的输入
            password2[i++] = ch;
            if (ch == '\r')//getch()函数如果读到回车符号返回'/r'
            {
                password2[i] = '\0';
                break;
            }
            putchar('*');
        }
        cout << endl;
        while (strcmp(password, password2))
        {
            cout << "与上次输入不匹配！！" << endl;
            cout << "1.再试一次；2.放弃注册" << endl;
            int chioce;
            cin >> chioce;
            if (chioce == 1)
            {
                cout << "请再次输入密码：";
                cin >> password2;
            }
            else
            {
                cout << "注册失败！！！" << endl;
                system("pause");
                system("cls");
                main();
            }
        }

        ofstream file;
        file.open("data.txt", ios::out | ios::app);

        file << username << endl << password << endl;
        file.close();

        cout << "注册成功！！！" << endl;
        system("pause");
        system("cls");
        main();
    }
    else if (choice == 2)
    {
        bool status = IsLoggedIn();

        if (!status)
        {
            cout << "密码错误！你还有两次机会！否则将自动退出！" << endl;
            for (int i = 0; i < 2; i++)
            {
                status = IsLoggedIn();
                if (status)
                {
                    getchar();
                    cout << "登录成功！！！" << endl;
                    system("pause");
                    //获取句柄
                    HWND hnd = GetHWnd();
                    //弹出窗口
                    int isok = MessageBox(hnd, "是否播放音乐", "提示", MB_OKCANCEL);
                    if (isok == IDOK)
                    {
                        BGM();
                    }
                    int select = 0;

                    while (true)
                    {
                        vm.showMenu();
                        cout << "请输入你的选择" << endl;
                        cin >> select;

                        switch (select)
                        {
                        case 1://1.添加
                            vm.Add_Emp();
                            break;
                        case 2://2.显示
                            vm.ShowEmp();
                            break;
                        case 3://3.删除
                            vm.DelEmp();
                            break;
                        case 4://4.修改
                            vm.ModEmp();
                            break;
                        case 5://5.查找
                            vm.FindEmp();
                            break;
                        case 6://6.排序
                            vm.SortEmp();
                            break;
                        case 7://7.清空文件
                            vm.CleanFile();
                            break;
                        case 0://0.退出
                            vm.exitSystem();
                            break;
                        default:
                            system("cls");
                            break;
                        }
                    }
                    return 0;
                }
                cout << "你还有" << 1 - i << "机会" << endl;
            }
            cout << "bye" << endl;
            system("PAUSE");
            return 0;
        }
        if (status)
        {
            cout << "登录成功！！！" << endl;
            system("pause");
            //获取句柄
            HWND hnd = GetHWnd();
            //弹出窗口
            int isok = MessageBox(hnd, "是否播放音乐", "提示", MB_OKCANCEL);
            if (isok == IDOK)
            {
                BGM();
            }
            int select = 0;

            while (true)
            {
                vm.showMenu();
                cout << "请输入你的选择" << endl;
                cin >> select;

                switch (select)
                {
                case 1://1.添加
                    vm.Add_Emp();
                    break;
                case 2://2.显示
                    vm.ShowEmp();
                    break;
                case 3://3.删除
                    vm.DelEmp();
                    break;
                case 4://4.修改
                    vm.ModEmp();
                    break;
                case 5://5.查找
                    vm.FindEmp();
                    break;
                case 6://6.排序
                    vm.SortEmp();
                    break;
                case 7://7.清空文件
                    vm.CleanFile();
                    break;
                case 0://0.退出
                    vm.exitSystem();
                    break;
                default:
                    system("cls");
                    break;
                }
            }
            return 0;
        }
    }
    else
    {
        cout << "bye" << endl;
        system("pause");
        return 0;
    }
}