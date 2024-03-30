#include "Deal.h"
#include<math.h>
#include <wtypes.h>
#include <wingdi.h>
#include<mmsystem.h>//������ý��ӿ�
#include <string>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

const int WIDTH = 960;
const int HEIGHT = 720;
const double PI = 3.1415926;

using namespace std;
#pragma comment(lib,"winmm.lib")//����ӿ�

extern IMAGE win_image;

//��ť�ؼ�
void Deal::button(int x, int y, int w, int h, TCHAR* text)
{
    setbkmode(TRANSPARENT);
    setfillcolor(YELLOW);
    fillroundrect(x, y, x + w, y + h, 10, 10);
    // ����ַ�����MBCS �ַ�����
    TCHAR s1[] = _TEXT("����");
    settextstyle(30, 0, s1);
    TCHAR s[50] = _TEXT("hello");

    int tx = x + (w - textwidth(text)) / 2;
    int ty = y + (h - textheight(text)) / 2;

    outtextxy(tx, ty, text);
}
//չʾ�˵�
void Deal::showMenu()
{
    initgraph(850, 850);
    HWND a = GetHWnd();
    SetWindowText(a, _TEXT("�����������ֿ�"));
    setbkcolor(WHITE);//����ɫ
    cleardevice();
    settextcolor(BLACK);
    TCHAR s0[] = _TEXT("����");
    settextstyle(30, 0, s0);
    outtextxy(180, 10, _TEXT(" �������ֿ�"));
    TCHAR s[20] = _TEXT("����");
    TCHAR s1[20] = _TEXT("�̻�");
    TCHAR s2[20] = _TEXT("ף��");
    TCHAR s3[20] = _TEXT("��Ա");
    TCHAR s6[10] = _T("�˳�");

    button(775, 160, 75, 20, s);
    button(775, 220, 75, 20, s1);
    button(775, 280, 75, 20, s2);
    button(775, 340, 75, 20, s3);
    button(775, 820, 40, 20, s6);
    ExMessage msg;
    while (true)
    {
        if (peekmessage(&msg, EM_MOUSE))
        {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 160 && msg.y <= 160 + 20)
                {
                    BGM();
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 220 && msg.y <= 220 + 20)
                {
                    FireWork();
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 280 && msg.y <= 280 + 20)
                {
                     Blessing();
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 340 && msg.y <= 340 + 20)
                {
                    ShowMember();
                }
                if (msg.x >= 775 && msg.x <= 775 + 40 && msg.y >= 820 && msg.y <= 820 + 20)
                {
                    close();
                }
                break;
            default:
                break;
            }
        }
    }
    closegraph();
}

void Deal::FireWork()
{
    srand((unsigned)time(nullptr));//�������������Ĵ���

    Fire* fire = new Fire();//��������
    DWORD t1 = timeGetTime(), tt1, t2 = timeGetTime(), tt2;
    //��ȡ��ǰʱ��ڵ�
    DWORD t3 = timeGetTime(), tt3;

    int flag;

    BeginBatchDraw();// ��ʼ��������
    while (!_kbhit())
    //��ȡ��������Ϣ��ֹͣ������������
    {
        tt1 = timeGetTime();
        if (tt1 - t1 > 500)
        {
            //�������500��ô���������̻�����������
            flag = rand() % 10 + 1;
            if (fire->JudgePlay(flag) == true)
                fire->Change(flag);
            t1 = tt1;
        }

        tt2 = timeGetTime();
        if (tt2 - t2 > 20)
        {
            fire->PlayFire();
            t2 = tt2;
        }

        tt3 = timeGetTime();
        if (tt3 - t3 > 50)
        {
            fire->Fire_666();
            t3 = tt3;
        }

        //���汣֤ʱ����,����ʵ

        for (int i = 0; i < 3000; i++)
         //��ȥ�������ŵ��̻���������һ��
        {
            int a = rand() % (WIDTH-200);
            int b = rand() % (HEIGHT-70)+70;
            putpixel(a, b, BLACK);
        }
        EndBatchDraw();
        // �����������ƣ���ִ��ָ��������δ��ɵĻ�������
    }
    delete fire;//�ͷ�ָ��
}

void Deal::BGM()
{
    mciSendString(_T("open ./music.mp3"), 0, 0, 0);//0��0,0ΪĬ���������̨
    mciSendString(_T("play ./music.mp3"), 0, 0, 0);

}

void Deal::Blessing()
{
    TCHAR text[40] = _T("���տ��֣�");
    lunixy_fade_in(text);
    Sleep(1000);
    lunixy_fade_out(text);
    showMenu();
}

void Deal::ShowMember()
{
    TCHAR text[40] = _T("��ʺ��ɶҲ����");
    lunixy_fade_in(text);
    Sleep(1000);
    lunixy_fade_out(text);
    showMenu();
}

// ���ֵ���
void Deal::lunixy_fade_in(TCHAR text[40])
{
    LOGFONT font;
    gettextstyle(&font);

    COLORREF bk_color = getbkcolor();
    COLORREF text_color = GREEN;
    int bk_color_arr[3] = { GetRValue(bk_color), GetGValue(bk_color), GetBValue(bk_color) };
    int text_color_arr[3] = { GetRValue(text_color), GetGValue(text_color), GetBValue(text_color) };

    int times = 80,
        r_incr = (text_color_arr[0] - bk_color_arr[0]) / times,
        g_incr = (text_color_arr[1] - bk_color_arr[1]) / times,
        b_incr = (text_color_arr[2] - bk_color_arr[2]) / times;

    BeginBatchDraw();
    for (int i = 0; i < times; i++) 
    {
        font.lfHeight = 80;
        settextstyle(&font);
        int text_width = textwidth(text),
            text_height = textheight(text);
        cleardevice();
        putimage(0, 0, &win_image);
        settextcolor(RGB(bk_color_arr[0] + r_incr * i, bk_color_arr[1] + g_incr * i, bk_color_arr[2] + b_incr * i));
        outtextxy((WIN_WIDTH - text_width) / 2, (WIN_HEIGHT - text_height) / 2, text);
        FlushBatchDraw();
        Sleep(15);
    }
    EndBatchDraw();
}

// ���ֵ���
void Deal::lunixy_fade_out(TCHAR text[40])
{
    LOGFONT font;
    gettextstyle(&font);

    COLORREF bk_color = getbkcolor();
    COLORREF text_color = BLUE;
    int bk_color_arr[3] = { GetRValue(bk_color), GetGValue(bk_color), GetBValue(bk_color) };
    int text_color_arr[3] = { GetRValue(text_color), GetGValue(text_color), GetBValue(text_color) };

    int times = 80,
        r_incr = (bk_color_arr[0] - text_color_arr[0]) / times,
        g_incr = (bk_color_arr[1] - text_color_arr[1]) / times,
        b_incr = (bk_color_arr[2] - text_color_arr[2]) / times;

    BeginBatchDraw();
    for (int i = 0; i < times; i++) 
    {
        font.lfHeight = 80;
        settextstyle(&font);
        int text_width = textwidth(text),
            text_height = textheight(text);
        cleardevice();
        putimage(0, 0, &win_image);
        settextcolor(RGB(text_color_arr[0] + r_incr * i, text_color_arr[1] + g_incr * i, text_color_arr[2] + b_incr * i));
        outtextxy((WIN_WIDTH - text_width) / 2, (WIN_HEIGHT - text_height) / 2, text);
        FlushBatchDraw();
        Sleep(15);
    }
    putimage(0, 0, &win_image);
    EndBatchDraw();
}

void Deal::close()
{
    HWND a = GetHWnd();
    int i = MessageBox(a, _T("�Ƿ�ر�"), _T("��Ϣ��"), MB_OKCANCEL);
    if (i == IDOK)
    {
        closegraph();
        cout << "��ӭʹ�ã��´��ټ���";
        exit(0);
    }
}