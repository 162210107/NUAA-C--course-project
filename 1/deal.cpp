#include"deal.h"
//用于使图像宽度所占字节数为4byte的倍数
#define   WIDTHBYTES(bits) (((bits)+31)/32*4)
//定义PI
#define PI 3.14
//构造函数
deal::deal()
{
    this->m_EmpNum = 0;
    //初始化个数
    this->m_EmArray = NULL;
    //初始化数组指针
}
//按钮控件
void deal:: button(int x, int y, int w, int h, TCHAR* text)
{
    setbkmode(TRANSPARENT);
    setfillcolor(YELLOW);
    fillroundrect(x, y, x + w, y + h, 10, 10);
    // 输出字符串（MBCS 字符集）
    TCHAR s1[] = "黑体";
    settextstyle(30, 0, s1);
    TCHAR s[50] = "hello";

    int tx = x + (w - textwidth(text)) / 2;
    int ty = y + (h - textheight(text)) / 2;

    outtextxy(tx, ty, text);

}
//展示菜单
void deal::showMenu()          
{
	initgraph(850, 850);
    HWND a = GetHWnd();
    SetWindowText(a, "小菜的修图软件");
	setbkcolor(WHITE);//背景色
	cleardevice();
    settextcolor(BLACK);
    TCHAR s0[] = "黑体";
    settextstyle(30, 0, s0);
    outtextxy(140, 30, _TEXT(" ！！小菜的修图软件！！"));
    TCHAR s[20] = "翻转";
    TCHAR s1[20] = "填充";
    TCHAR s2[20] = "叠加";
    TCHAR s3[20] = "模糊";
    TCHAR s4[20] = "截取";
    TCHAR s5[20] = "读取";
    TCHAR s8[20] = "缩放";
    TCHAR s6[10] = "退出";
    TCHAR s7[10] = "清屏";
    TCHAR s9[20] = "旋转";
    TCHAR s10[20] = "已读";
    TCHAR s11[20] = "灰度";
    TCHAR s12[20] = "二值";
    button(775, 100, 75, 20, s5);
    button(775, 160, 75, 20, s1);
    button(775, 220, 75, 20, s2);
    button(775, 280, 75, 20, s);
    button(775, 340, 75, 20, s4);
    button(775, 400, 75, 20, s3);
    button(775, 460, 75, 20, s8);
    button(775, 520, 75, 20, s9);
    button(700, 820, 40, 20, s7);
    button(775, 640, 75, 20, s11);
    button(775, 700, 75, 20, s12);
    button(775, 820, 40, 20, s6);
    button(775, 580, 75, 20, s10);
    ExMessage msg;
    while (true) 
    {
        if (peekmessage(&msg, EM_MOUSE)) 
        {

            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 100 && msg.y <= 100 + 20)
                {
                    cout << s5;
                    readimagebox();
                    //outtextxy(2, 2, s5); //写了一个展示文字的效果，相当于是测试,实际使用时可以删除
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 160 && msg.y <= 160 + 20)
                {
                    cout << s1;
                    //outtextxy(2, 20, s1);
                    //区域填充算法-非递归形式（扫描线优化）
                    ImageAdd();
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 220 && msg.y <= 220 + 20)
                {
                    cout << s2;
                    //outtextxy(2, 200, s2);
                    ImageOver();
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 280 && msg.y <= 280 + 20)
                {
                    cout << s;
                    ImageInvert();
                    //outtextxy(2, 300, s);
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 340 && msg.y <= 340 + 20)
                {
                    cout << s4;
                    //outtextxy(2, 400, s4);
                    Imageintercept();
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 400 && msg.y <= 400 + 20)
                {
                    cout << s3;
                    //outtextxy(2, 500, s3);
                    Imagemuhu();
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 460 && msg.y <= 460 + 20)
                {
                    cout << s8;
                    //双线性插值算法
                    ImageBig();
                }
                if (msg.x >= 775 && msg.x <= 775 + 75 && msg.y >= 520 && msg.y <= 520 + 20)
                {
                    cout << s9;
                    //双线性插值算法+旋转
                    ImageTurn();
                }
                if (msg.x >= 775 && msg.x <= 775 + 40 && msg.y >= 580 && msg.y <=580 + 20)
                {
                    cout << s10;
                    //展示所有读取过的图像
                    showall();
                }
                if (msg.x >= 775 && msg.x <= 775 + 40 && msg.y >= 640 && msg.y <= 640 + 20)
                {
                    cout << s11;
                    //灰度化
                    ImageGray();
                }
                if (msg.x >= 775 && msg.x <= 775 + 40 && msg.y >= 700 && msg.y <= 700 + 20)
                {
                    cout << s12;
                    //二值
                    binaryimage();
                }
                if (msg.x >= 700 && msg.x <= 700 + 75 && msg.y >= 820 && msg.y <= 820 + 20)
                {
                    cout << s7<<endl;
                    //outtextxy(2, 500, s3);
                    closeImage();
                }
                if (msg.x >= 775 && msg.x <= 775+ 40 && msg.y >= 820 && msg.y <=   820   + 20)
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
//读取
void deal::readimagebox()
{
    char filename[20];
    cout << "读取图像名称:";
    cin >> filename;

    cout << "1.单位图；2.8位图；3.24位图；4.16位图"<<endl;
    int am=0;//选项
    cin >> am;
    
    switch (am)
    {
    case 1:
    {
        bmp* a1 = new bmp4;
        a1->readPic(filename);
        if (a1->success == 1)
        {
            a1->ShowImage(m_EmpNum);

            bmp** newspace1 = new bmp * [m_EmpNum + 1];
            if (this->m_EmArray != NULL)
            {
                for (int i = 0; i < this->m_EmpNum; i++)
                {
                    newspace1[i] = this->m_EmArray[i];
                }
            }
            newspace1[this->m_EmpNum] = a1;
            m_EmpNum++;
            //释放原有空间
            delete[]this->m_EmArray;

            //更改新空间的指向
            this->m_EmArray = newspace1;
        }
        else
        {
            cout << "重新选择右侧功能" << endl;
        }
        break;
    }
    case 2:
    {
        bmp* a2 = new bmp2;
        a2->readPic(filename);
        if (a2->success == 1)
        {
            a2->ShowImage(m_EmpNum);

            bmp** newspace2 = new bmp * [m_EmpNum + 1];
            if (this->m_EmArray != NULL)
            {
                for (int i = 0; i < this->m_EmpNum; i++)
                {
                    newspace2[i] = this->m_EmArray[i];
                }
            }
            newspace2[this->m_EmpNum] = a2;
            m_EmpNum++;
            //释放原有空间
            delete[]this->m_EmArray;

            //更改新空间的指向
            this->m_EmArray = newspace2;
        }
        else
        {
            cout << "重新选择右侧功能"<<endl;
        }
        break;
    }
    case 3:
    {
        bmp * a3 = new bmp1;
        a3->readPic(filename);
        if (a3->success == 1)
        {
            a3->ShowImage(m_EmpNum);

            bmp** newspace3 = new bmp * [m_EmpNum + 1];
            if (this->m_EmArray != NULL)
            {
                for (int i = 0; i < this->m_EmpNum; i++)
                {
                    newspace3[i] = this->m_EmArray[i];
                }
            }
            newspace3[this->m_EmpNum] = a3;
            m_EmpNum++;
            //释放原有空间
            delete[]this->m_EmArray;

            //更改新空间的指向
            this->m_EmArray = newspace3;
        }
        else
        {
            cout << "重新选择功能" << endl;
        }
        break;
    }
    case 4:
    {
        bmp* a4 = new bmp3;
        a4->readPic(filename);
        if (a4->success == 1)
        {
            a4->ShowImage(m_EmpNum);

            bmp** newspace4 = new bmp * [m_EmpNum + 1];
            if (this->m_EmArray != NULL)
            {
                for (int i = 0; i < this->m_EmpNum; i++)
                {
                    newspace4[i] = this->m_EmArray[i];
                }
            }
            newspace4[this->m_EmpNum] = a4;
            m_EmpNum++;
            //释放原有空间
            delete[]this->m_EmArray;

            //更改新空间的指向
            this->m_EmArray = newspace4;
        }
        else
        {
            cout << "重新选择功能" << endl;
        }
        break;
    }
    default:
    {
        cout << "选择错误，重选功能"<<endl;
        break;
    }
    }
}
//翻转
void deal::ImageInvert()
{
    //找到最新一次处理的图像
    bmp* a = this->m_EmArray[m_EmpNum-1];

    cout << endl;
    char name[100]={0};//新建成的bmp名称
    cout << "新图片名称:";
    cin>>name;

    a->writePic(rowReverse, name);
    bmp* a1 = NULL;
    //根据图片几位图进行储存
    if (a->fileInFoHeader.biBitCount == 8)
    {
        a1 = new bmp2;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 24)
    {
        a1 = new bmp1;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 16)
    {
        a1 = new bmp3;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 1)
    {
        a1 = new bmp4;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else
    {
        cout << "不属于此项目所能读取的图片格式，请重新选择图片格式！！" << endl;
        return;
    }

   bmp** newspace = new bmp * [m_EmpNum + 1];
   if (this->m_EmArray != NULL)
   {
       for (int i = 0; i < this->m_EmpNum; i++)
       {
           newspace[i] = this->m_EmArray[i];
       }
   }
   newspace[this->m_EmpNum] = a1;
   m_EmpNum++;
   //释放原有空间
   delete[]this->m_EmArray;

   //更改新空间的指向
   this->m_EmArray = newspace;

}
//模糊
void deal::Imagemuhu() 
{
    bmp* a = this->m_EmArray[m_EmpNum-1];

    cout << endl;
    cout << "新图片名称：";
    char name[100]={0};//bmp名称
    cin>>name;

    a->writePic(makeBlur, name);

    bmp* a1 = NULL;
    if (a->fileInFoHeader.biBitCount == 8)
    {
        a1 = new bmp2;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 24)
    {
        a1 = new bmp1;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 16)
    {
        a1 = new bmp3;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 1)
    {
        a1 = new bmp4;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else
    {
        cout << "不属于此项目所能读取的图片格式，请重新选择图片格式！！" << endl;
        return;
    }

    bmp** newspace = new bmp * [m_EmpNum + 1];
    if (this->m_EmArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            newspace[i] = this->m_EmArray[i];
        }
    }
    newspace[this->m_EmpNum] = a1;
    m_EmpNum++;
    //释放原有空间
    delete[]this->m_EmArray;

    //更改新空间的指向
    this->m_EmArray = newspace;
}
//截取
void deal::Imageintercept()
{
    bmp* a = this->m_EmArray[m_EmpNum-1];
    cout << endl;
    cout << "新图片名称:";
    char name[100]={0};//bmp名称
    cin>>name;
   
    int newheight1 = 0;
    int newwidth1 = 0;
    int newheight2 = 0;
    int newwidth2 = 0;

    cout << "截取起点:"<<endl;
    cout << "y坐标：";
    cin >> newheight1;
    getchar();
    cout << "x坐标：";
    cin >> newwidth1;
    getchar();

    while (newheight1 < 0 || newwidth1 < 0||newheight1>a->fileInFoHeader.biHeight||newwidth1>a->fileInFoHeader.biWidth)
    {
        cout << "超出图片范围！！！重新输入!!!" << endl;
        cout << "截取起点:"<<endl;
        cout << "y坐标：";
        cin >> newheight1;
        getchar();
        cout << "x坐标：";
        cin >> newwidth1;
        getchar();
    }

    cout << "截取终点:"<<endl;
    cout << "y坐标：";
    cin >> newheight2;
    getchar();
    cout << "x坐标：";
    cin >> newwidth2;
    getchar();

    while (newheight2 >= a->fileInFoHeader.biHeight || newwidth2 >= a->fileInFoHeader.biWidth||newheight2<=newheight1||newwidth2<=newwidth1)
    {
        cout << "超出图片范围！！！重新输入!!!" << endl;
        cout << "截取终点:"<<endl;
        cout << "y坐标：";
        cin >> newheight2;
        getchar();
        cout << "x坐标：";
        cin >> newwidth2;
        getchar();
    }

    int h = newheight2 - newheight1;
    int w = newwidth2 - newwidth1;
    RGBTriple* image = new RGBTriple[h * w];

    FILE* wfile;//输出文件
    wfile = fopen(name, "wb");//打开文件为存储修改后图像做准备
    if (wfile == NULL)
    {
        cout << "打开文件错误";
        return;
    }

    //读取位图文件头信息
    BmpFileHeader wbitHead;
    wbitHead = a->fileHeader;
    //由于截取图像头和源文件头相似，所以先将源文件头数据赋予截取文件头
    //读取位图信息头信息
    BmpFileInFoHeader wbitInfoHead;
    wbitInfoHead = a->fileInFoHeader;//同位图文件头相似

    wbitInfoHead.biHeight = h;//为截取文件重写位图高度
    wbitInfoHead.biWidth = w;//为截取文件重写位图宽度

    int mywritewidth = WIDTHBYTES(wbitInfoHead.biWidth * wbitInfoHead.biBitCount);
    //BMP图像实际位图数据区的宽度为4byte的倍数，在此计算实际数据区宽度
    wbitInfoHead.biSizeImages = mywritewidth * wbitInfoHead.biHeight;//计算位图实际数据区大小

    wbitHead.bfSize = 54 + wbitInfoHead.biSizeImages;//位图文件头大小为位图数据区大小加上54byte

    if (fwrite(&wbitHead, 1, sizeof(BITMAPFILEHEADER), wfile) != 14)
    {
        cout << "错误文件头" << endl;
        return;
    }//写回位图文件头信息到输出文件
    if (fwrite(&wbitInfoHead, 1, sizeof(BITMAPINFOHEADER), wfile) != 40)
    {
        cout << "错误信息头" << endl;
        return;
    }//写回位图信息头信息到输出文件

    int offset = (wbitInfoHead.biWidth * 3) % 4;//内存对齐计算偏移，4的倍数
    if (offset != 0)
    {
        offset = 4 - offset;
    }

    RGBTriple* temp = a->surface;
    int i2 = h - 1;
    for (int i =newheight2; i>=newheight1; i--) //由下到上，由左到右储存像素
    {
        if (i2 >= 0)
        {
            int j2 = 0;
            for (int j = newwidth1; j < a->fileInFoHeader.biWidth - newwidth2; j++)
            {
                if (j2 < w)
                {
                    (image + (i2 * w + j2))->blue = (temp + (i * a->fileInFoHeader.biWidth + j))->blue;
                    (image + (i2 * w + j2))->green = (temp + (i * a->fileInFoHeader.biWidth + j))->green;
                    (image + (i2 * w + j2))->red = (temp + (i * a->fileInFoHeader.biWidth + j))->red;
                    fwrite((char*)(image + (i2 * w + j2)), sizeof(RGBTriple), 1, wfile);
                }
                j2++;
            }
            if (offset != 0)
            {
                char ign;
                for (int k = 0; k < offset; k++)
                {
                    if (fwrite(&ign, sizeof(char), 1, wfile) != 1)
                    {
                        cout << "偏移写入错误" << endl;
                        return;
                    }
                }
            }
        }
        i2--;
    }
    fclose(wfile);
 
    bmp* a1 = NULL;
    if (a->fileInFoHeader.biBitCount == 8)
    {
        a1 = new bmp2;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 24)
    {
        a1 = new bmp1;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 16)
    {
        a1 = new bmp3;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 1)
    {
        a1 = new bmp4;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else
    {
        cout << "不属于此项目所能读取的图片格式，请重新选择图片格式！！" << endl;
        return;
    }

    bmp** newspace = new bmp * [m_EmpNum + 1];
    if (this->m_EmArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            newspace[i] = this->m_EmArray[i];
        }
    }
    newspace[this->m_EmpNum] = a1;
    m_EmpNum++;
    //释放原有空间
    delete[]this->m_EmArray;

    //更改新空间的指向
    this->m_EmArray = newspace;
}
//叠加
void deal::ImageOver()
{
    bmp* a = this->m_EmArray[m_EmpNum-2];
    bmp* b = this->m_EmArray[m_EmpNum-1];
  
    int newheight = 0;
    int newwidth = 0;

    cout << "输入叠加位置："<<endl;
    cout << "y坐标:";
    cin >> newheight;
    getchar();
    cout << "x坐标:";
    cin >> newwidth;
    getchar();

    while (newheight < 0 || newwidth < 0)
    {
        cout << "超出图片范围！！！重新输入" << endl;
        cout << "叠加位置:"<<endl;
        cout << "y坐标:";
        cin >> newheight;
        getchar();
        cout << "x坐标:";
        cin >> newwidth;
        getchar();
    }

    cout << "新图片名称:";
    char name[100]={0};//bmp名称
    cin>>name;

    FILE* wfile;//输出文件
    wfile = fopen(name, "wb");//打开文件为存储修改后图像做准备
    if (wfile == NULL)
    {
        cout << "打开文件错误"<<endl;
        return;
    }

    //读取位图文件头信息
    BmpFileHeader wbitHead;
    wbitHead = a->fileHeader;
    //由于截取图像头和源文件头相似，所以先将源文件头数据赋予截取文件头
    //读取位图信息头信息
    BmpFileInFoHeader wbitInfoHead;
    wbitInfoHead = a->fileInFoHeader;//同位图文件头相似

    if (fwrite(&wbitHead, 1, sizeof(BITMAPFILEHEADER), wfile) != 14)
    {
        cout << "错误文件头" << endl;
        return;
    }//写回位图文件头信息到输出文件
    if (fwrite(&wbitInfoHead, 1, sizeof(BITMAPINFOHEADER), wfile) != 40)
    {
        cout << "错误信息头" << endl;
        return;
    }//写回位图信息头信息到输出文件

    RGBTriple* temp = a->surface;
    RGBTriple* temp1 = b->surface;
    RGBTriple* image = new RGBTriple[wbitInfoHead.biWidth* wbitInfoHead.biHeight];

    int offset = (wbitInfoHead.biWidth * 3) % 4;//内存对齐计算偏移，4的倍数
    if (offset != 0)
    {
        offset = 4 - offset;
    }

    //不在需要改变的高度内
    for (int i = a->fileInFoHeader.biHeight - 1; i >= newheight - 1 + b->fileInFoHeader.biHeight; i--) //由下到上，由左到右储存像素
    {
        for (int j =0; j < a->fileInFoHeader.biWidth; j++ )
        {
            (image + (i * a->fileInFoHeader.biWidth + j))->blue = (temp + (i * a->fileInFoHeader.biWidth + j))->blue;
            (image + (i * a->fileInFoHeader.biWidth+ j))->green = (temp + (i * a->fileInFoHeader.biWidth + j))->green;
            (image + (i *a->fileInFoHeader.biWidth + j))->red = (temp + (i * a->fileInFoHeader.biWidth + j))->red;
            fwrite((char*)(image + (i * a->fileInFoHeader.biWidth + j)), sizeof(RGBTriple), 1, wfile);
        }
        if (offset != 0)
        {
            char ign;
            for (int k = 0; k < offset; k++)
            {
                if (fwrite(&ign, sizeof(char), 1, wfile) != 1)
                {
                    cout << "偏移写入错误" << endl;
                    return;
                }
            }
        }
    }
    //与叠加所在行有联系的行单开来看
    int i2 = b->fileInFoHeader.biHeight - 1;
    for (int i =newheight-1+b->fileInFoHeader.biHeight-1; i >= newheight-1; i--) //由下到上，由左到右储存像素
    {
        if (i2 >= 0)
        {
            //与叠加无关的列
            for (int j = 0; j < newwidth; j++)
            {
                (image + (i * wbitInfoHead.biWidth + j))->blue = (temp + (i * wbitInfoHead.biWidth + j))->blue;
                (image + (i * wbitInfoHead.biWidth + j))->green = (temp + (i * wbitInfoHead.biWidth + j))->green;
                (image + (i * wbitInfoHead.biWidth + j))->red = (temp + (i * wbitInfoHead.biWidth + j))->red;
                fwrite((char*)(image + (i * wbitInfoHead.biWidth + j)), sizeof(RGBTriple), 1, wfile);
            }
            //与叠加有关的列
            for (int j = newwidth; j < newwidth + b->fileInFoHeader.biWidth; j++)
            {
                (image + (i * wbitInfoHead.biWidth + j))->blue = (temp1 + (i2 * b->fileInFoHeader.biWidth + j - newwidth))->blue;
                (image + (i * wbitInfoHead.biWidth + j))->green = (temp1 + (i2 * b->fileInFoHeader.biWidth + j - newwidth))->green;
                (image + (i * wbitInfoHead.biWidth + j))->red = (temp1 + (i2 * b->fileInFoHeader.biWidth + j - newwidth))->red;
                fwrite((char*)(image + (i * wbitInfoHead.biWidth + j)), sizeof(RGBTriple), 1, wfile);
            }
            //与叠加无关的列
            for (int j = newwidth + b->fileInFoHeader.biWidth; j < a->fileInFoHeader.biWidth; j++)
            {
                (image + (i * wbitInfoHead.biWidth + j))->blue = (temp + (i * wbitInfoHead.biWidth + j))->blue;
                (image + (i * wbitInfoHead.biWidth + j))->green = (temp + (i * wbitInfoHead.biWidth + j))->green;
                (image + (i * wbitInfoHead.biWidth + j))->red = (temp + (i * wbitInfoHead.biWidth + j))->red;
                fwrite((char*)(image + (i * wbitInfoHead.biWidth + j)), sizeof(RGBTriple), 1, wfile);
            }
            if (offset != 0)
            {
                char ign;
                for (int k = 0; k < offset; k++)
                {
                    if (fwrite(&ign, sizeof(char), 1, wfile) != 1)
                    {
                        cout << "偏移写入错误" << endl;
                        return;
                    }
                }
            }
        }
        i2--;
    }
    //与偏移无关的行
    for (int i = newheight-2; i >=0; i--) 
    {
        for (int j = 0; j < a->fileInFoHeader.biWidth; j++)
        {
            (image + (i * a->fileInFoHeader.biWidth + j))->blue = (temp + (i * a->fileInFoHeader.biWidth + j))->blue;
            (image + (i * a->fileInFoHeader.biWidth + j))->green = (temp + (i * a->fileInFoHeader.biWidth + j))->green;
            (image + (i * a->fileInFoHeader.biWidth + j))->red = (temp + (i * a->fileInFoHeader.biWidth + j))->red;
            fwrite((char*)(image + (i * a->fileInFoHeader.biWidth + j)), sizeof(RGBTriple), 1, wfile);
        }
        if (offset != 0)
        {
            char ign;
            for (int k = 0; k < offset; k++)
            {
                if (fwrite(&ign, sizeof(char), 1, wfile) != 1)
                {
                    cout << "偏移写入错误" << endl;
                    return;
                }
            }
        }
    }
    fclose(wfile);

    clearrectangle(80, 70, 770, 850);

    bmp* a1 = NULL;
    if (a->fileInFoHeader.biBitCount == 8)
    {
        a1 = new bmp2;
        a1->readPic(name);
        a1->ShowImage(0);
    }
    else if (a->fileInFoHeader.biBitCount == 24)
    {
        a1 = new bmp1;
        a1->readPic(name);
        a1->ShowImage(0);
    }
    else if (a->fileInFoHeader.biBitCount == 16)
    {
        a1 = new bmp3;
        a1->readPic(name);
        a1->ShowImage(0);
    }
    else if (a->fileInFoHeader.biBitCount == 1)
    {
        a1 = new bmp4;
        a1->readPic(name);
        a1->ShowImage(0);
    }
    else
    {
        cout << "不属于此项目所能读取的图片格式，请重新选择图片格式！！" << endl;
        return;
    }

    bmp** newspace = new bmp * [m_EmpNum + 1];
    if (this->m_EmArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            newspace[i] = this->m_EmArray[i];
        }
    }
    newspace[this->m_EmpNum] = a1;
    m_EmpNum++;
    //释放原有空间
    delete[]this->m_EmArray;

    //更改新空间的指向
    this->m_EmArray = newspace;
}
//缩放
void deal::ImageBig()
{
    bmp* a = this->m_EmArray[m_EmpNum-1];
    cout << endl;
    cout << "新图片名称:";
    char name[100]={0};//bmp名称
    cin>>name;

    int newheight = 0;//新图片高度
    int newwidth = 0;//新图片宽度
    cout << "新图片高度:";
    cin >> newheight;
    getchar();
    cout << "新图片宽度:";
    cin >> newwidth;
    getchar();

    while (newheight <= 0 || newwidth <= 0)
    {
        cout << "无法窃取负大小图片，请重新输入！" << endl;
        cout << "新图片高度:";
        cin >> newheight;
        getchar();
        cout << "新图片宽度:";
        cin >> newwidth;
        getchar();
    }

    //读取位图文件头信息
    BmpFileHeader wbitHead;
    wbitHead = a->fileHeader;
    //由于截取图像头和源文件头相似，所以先将源文件头数据赋予截取文件头
    //读取位图信息头信息
    BmpFileInFoHeader wbitInfoHead;
    wbitInfoHead = a->fileInFoHeader;//同位图文件头相似

    FILE* wfile;//输出文件
    wfile = fopen(name, "wb");//打开文件为存储修改后图像做准备
    if (wfile == NULL)
    {
        cout << "打开文件错误"<<endl;
        return;
    }

    wbitInfoHead.biWidth = newwidth;
    wbitInfoHead.biHeight = newheight;
    int mywritewidth = WIDTHBYTES(wbitInfoHead.biWidth * wbitInfoHead.biBitCount);
    //BMP图像实际位图数据区的宽度为4byte的倍数，在此计算实际数据区宽度  
    wbitInfoHead.biSizeImages = mywritewidth * wbitInfoHead.biHeight;//计算位图实际数据区大小
    wbitHead.bfSize = 54 + wbitInfoHead.biSizeImages;//位图文件头大小为位图数据区大小加上54byte

    if (fwrite(&wbitHead, 1, sizeof(BITMAPFILEHEADER), wfile) != 14)
    {
        cout << "错误文件头" << endl;
        return;
    }//写回位图文件头信息到输出文件
    if (fwrite(&wbitInfoHead, 1, sizeof(BITMAPINFOHEADER), wfile) != 40)
    {
        cout << "错误信息头" << endl;
        return;
    }//写回位图信息头信息到输出文件

    //分配内存空间把源图存入内存   
    RGBTriple* image = new RGBTriple[newheight * newwidth];
   
    int offset = (wbitInfoHead.biWidth * 3) % 4;//内存对齐计算偏移，4的倍数
    if (offset != 0)
    {
        offset = 4 - offset;
    }

    /*******************图像处理部分******************/
    /*******************双线性插值******************/
    RGBTriple* temp = a->surface;
    for (int i = newheight - 1; i >= 0; i--)
    {
        for (int j = 0; j < newwidth; j++)
        {
            //对应原图的坐标
            double X = j * a->fileInFoHeader.biWidth / newwidth;
            double Y = i * a->fileInFoHeader.biHeight / newheight;

            int OX = X;//原点的X轴坐标，取整
            int OY = Y;//原点的Y轴坐标，取整

            double distanceX = Y - OY;//距离y方向的距离
            double distanceY = X - OX;//距离x方向的距离

            int BX = OX + 1;
            int BY = OY;
            int CX = OX;
            int CY = OY + 1;
            int DX = OX + 1;
            int DY = OY + 1;

            //处理越界问题
            if (OX + 1 >= a->fileInFoHeader.biWidth)
            {
                BX = OX;
                BY = OY;
                DX = CX;
                DY = CY;
            }
            if (OY + 1 >= a->fileInFoHeader.biHeight)
            {
                CX = OX;
                CY = OY;
                DX = BX;
                DY = BY;
            }

            (image + (i * newwidth + j))->blue = (temp + (OY * a->fileInFoHeader.biWidth + OX))->blue * (1 - distanceX) * (1 - distanceY)
                + (temp + (BY * a->fileInFoHeader.biWidth + BX))->blue * distanceY * (1 - distanceX)
                + (temp + (CY * a->fileInFoHeader.biWidth + CX))->blue * distanceX * (1 - distanceY)
                + (temp + (DY * a->fileInFoHeader.biWidth + DX))->blue * distanceY * distanceX;
            (image + (i * newwidth + j))->green = (temp + (OY * a->fileInFoHeader.biWidth + OX))->green * (1 - distanceX) * (1 - distanceY)
                + (temp + (BY * a->fileInFoHeader.biWidth + BX))->green * distanceY * (1 - distanceX)
                + (temp + (CY * a->fileInFoHeader.biWidth + CX))->green * distanceX * (1 - distanceY)
                + (temp + (DY * a->fileInFoHeader.biWidth + DX))->green * distanceY * distanceX;
            (image + (i * newwidth + j))->red = (temp + (OY * a->fileInFoHeader.biWidth + OX))->red * (1 - distanceX) * (1 - distanceY)
                + (temp + (BY * a->fileInFoHeader.biWidth + BX))->red * distanceY * (1 - distanceX)
                + (temp + (CY * a->fileInFoHeader.biWidth + CX))->red * distanceX * (1 - distanceY)
                + (temp + (DY * a->fileInFoHeader.biWidth + DX))->red * distanceY * distanceX;

            fwrite((char*)(image + (i * newwidth + j)), sizeof(RGBTriple), 1, wfile);
        }
        if (offset != 0)
        {
            char ign;
            for (int k = 0; k < offset; k++)
            {
                if (fwrite(&ign, sizeof(char), 1, wfile) != 1)
                {
                    cout << "偏移写入错误" << endl;
                    return;
                }
            }
        }
    }
    fclose(wfile);

    bmp* a1 = NULL;
    if (a->fileInFoHeader.biBitCount == 8)
    {
        a1 = new bmp2;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 24)
    {
        a1 = new bmp1;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 16)
    {
        a1 = new bmp3;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 1)
    {
        a1 = new bmp4;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else
    {
        cout << "不属于此项目所能读取的图片格式，请重新选择图片格式！！" << endl;
        return;
    }

    bmp** newspace = new bmp * [m_EmpNum + 1];
    if (this->m_EmArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            newspace[i] = this->m_EmArray[i];
        }
    }
    newspace[this->m_EmpNum] = a1;
    m_EmpNum++;
    //释放原有空间
    delete[]this->m_EmArray;

    //更改新空间的指向
    this->m_EmArray = newspace;
}
//旋转
void deal::ImageTurn()
{
    bmp* a = this->m_EmArray[m_EmpNum-1];
    cout << endl;
    cout << "新图片名称:";
    char name[100]={0};//bmp名称
    cin>>name;

    int angle=0;
    cout << "please input the rotate angle : ";
    cin >> angle;
    getchar();
    //角度制转换为弧度制
    double thelta = (double)(1.0*angle * PI / 180);
    auto cosa = (double)cos(thelta);
    auto sina = (double)sin(thelta);

    //读取位图文件头信息
    BmpFileHeader wbitHead;
    wbitHead = a->fileHeader;
    //由于截取图像头和源文件头相似，所以先将源文件头数据赋予截取文件头
    //读取位图信息头信息
    BmpFileInFoHeader wbitInfoHead;
    wbitInfoHead = a->fileInFoHeader;//同位图文件头相似

    FILE* wfile;//输出文件
    wfile = fopen(name, "wb");
    //打开文件为存储修改后图像做准备
    if (wfile == NULL)
    {
        cout << "lose";
        return;
    }

    int width =a->fileInFoHeader.biWidth;
    int height = a->fileInFoHeader.biHeight;

    //计算新图的宽度和高度
    //原图的四个角坐标
    auto SrcX1 = (float)(-0.5 * width);
    auto SrcY1 = (float)(0.5 * height);
    auto SrcX2 = (float)(0.5 * width);
    auto SrcY2 = (float)(0.5 * height);
    auto SrcX3 = (float)(-0.5 * width);
    auto SrcY3 = (float)(-0.5 * height);
    auto SrcX4 = (float)(0.5 * width);
    auto SrcY4 = (float)(-0.5 * height);
    //新图的四个角坐标
    float DstX1 = cosa * SrcX1 + sina * SrcY1;
    float DstY1 = -sina * SrcX1 + cosa * SrcY1;
    float DstX2 = cosa * SrcX2 + sina * SrcY2;
    float DstY2 = -sina * SrcX2 + cosa * SrcY2;
    float DstX3 = cosa * SrcX3 + sina * SrcY3;
    float DstY3 = -sina * SrcX3 + cosa * SrcY3;
    float DstX4 = cosa * SrcX4 + sina * SrcY4;
    float DstY4 = -sina * SrcX4 + cosa * SrcY4;
    //计算新图的宽度和高度
    auto newWidth = (int)(max(fabs(DstX4 - DstX1), fabs(DstX3 - DstX2)) + 0.5);
    auto newHeight = (int)(max(fabs(DstY4 - DstY1), fabs(DstY3 - DstY2)) + 0.5);
    wbitInfoHead.biHeight = newHeight;
    wbitInfoHead.biWidth = newWidth;
    int mywritewidth = WIDTHBYTES(wbitInfoHead.biWidth * wbitInfoHead.biBitCount);
    //BMP图像实际位图数据区的宽度为4byte的倍数，在此计算实际数据区宽度  
    wbitInfoHead.biSizeImages = mywritewidth * wbitInfoHead.biHeight;//计算位图实际数据区大小
    wbitHead.bfSize = 54 + wbitInfoHead.biSizeImages;//位图文件头大小为位图数据区大小加上54byte

    if (fwrite(&wbitHead, 1, sizeof(BITMAPFILEHEADER), wfile) != 14)
    {
        cout << "错误文件头" << endl;
        return;
    }//写回位图文件头信息到输出文件
    if (fwrite(&wbitInfoHead, 1, sizeof(BITMAPINFOHEADER), wfile) != 40)
    {
        cout << "错误信息头" << endl;
        return;
    }//写回位图信息头信息到输出文件

    //原来的旋转中心
    double rotateX = width / 2;
    double rotateY = height / 2;
    //新图的中心
    double write_rotateX = newWidth / 2;
    double write_rotateY = newHeight / 2;

    //分配内存空间把源图存入内存   
    RGBTriple* image = new RGBTriple[newHeight * newWidth];

    int offset = (wbitInfoHead.biWidth * 3) % 4;//内存对齐计算偏移，4的倍数
    if (offset != 0)
    {
        offset = 4 - offset;
    }

    /*for (int i = newHeight - 1; i >= 0; i--)
    {
        for (int j = 0; j < newWidth; j++)
        {
            (image + (i * newWidth + j))->blue = 193;
            (image + (i * newWidth + j))->green = 182;
            (image + (i * newWidth + j))->red = 255;
            fwrite((char*)(image + (i * newWidth + j)), sizeof(RGBTriple), 1, wfile);
        }
        if (offset != 0)
        {
            char ign;
            for (int k = 0; k < offset; k++)
            {
                fwrite(&ign, sizeof(char), 1, wfile);
            }
        }
    }*///测试代码
    RGBTriple* temp = a->surface;
    for (int i = newHeight - 1; i >= 0; i--)
    {
        for (int j = 0; j < newWidth; j++)
        {
            // 利用公式计算这个原来的点的地方
            double oy =(j - write_rotateX) * sina + (i - write_rotateY) * cosa + rotateY;
            double ox =(j - write_rotateX) * cosa - (i - write_rotateY) * sina + rotateX;

            //判断原来的点是否存在，不存在为白色
            if (oy < 0 || oy >= a->fileInFoHeader.biHeight || ox < 0 || ox >= a->fileInFoHeader.biWidth)
            {
                (image + (i * newWidth + j))->blue = 0;
                (image + (i * newWidth + j))->green = 0;
                (image + (i * newWidth + j))->red= 0;
                fwrite((char*)(image + (i * newWidth + j)), sizeof(RGBTriple), 1, wfile);
            }
            else
            {
                //双线性插值
                int OX = ox;//原点的X轴坐标，取整
                int OY = oy;//原点的Y轴坐标，取整

                double distanceX = oy - OY;//距离y方向的距离
                double distanceY = ox - OX;//距离x方向的距离

                int BX = OX + 1;
                int BY = OY;
                int CX = OX;
                int CY = OY + 1;
                int DX = OX + 1;
                int DY = OY + 1;

                //处理越界问题
                if (OX + 1 >= a->fileInFoHeader.biWidth)
                {
                    BX = OX;
                    BY = OY;
                    DX = CX;
                    DY = CY;
                }
                if (OY + 1 >= a->fileInFoHeader.biHeight)
                {
                    CX = OX;
                    CY = OY;
                    DX = BX;
                    DY = BY;
                }

                (image + (i * newWidth + j))->blue = (temp + (OY * a->fileInFoHeader.biWidth + OX))->blue * (1 - distanceX) * (1 - distanceY)
                    + (temp + (BY * a->fileInFoHeader.biWidth + BX))->blue * distanceY * (1 - distanceX)
                    + (temp + (CY * a->fileInFoHeader.biWidth + CX))->blue * distanceX * (1 - distanceY)
                    + (temp + (DY * a->fileInFoHeader.biWidth + DX))->blue * distanceY * distanceX;
                (image + (i * newWidth + j))->green = (temp + (OY * a->fileInFoHeader.biWidth + OX))->green * (1 - distanceX) * (1 - distanceY)
                    + (temp + (BY * a->fileInFoHeader.biWidth + BX))->green * distanceY * (1 - distanceX)
                    + (temp + (CY * a->fileInFoHeader.biWidth + CX))->green * distanceX * (1 - distanceY)
                    + (temp + (DY * a->fileInFoHeader.biWidth + DX))->green * distanceY * distanceX;
                (image + (i * newWidth + j))->red = (temp + (OY * a->fileInFoHeader.biWidth + OX))->red * (1 - distanceX) * (1 - distanceY)
                    + (temp + (BY * a->fileInFoHeader.biWidth + BX))->red * distanceY * (1 - distanceX)
                    + (temp + (CY * a->fileInFoHeader.biWidth + CX))->red * distanceX * (1 - distanceY)
                    + (temp + (DY * a->fileInFoHeader.biWidth + DX))->red * distanceY * distanceX;
                fwrite((char*)(image + (i * newWidth + j)), sizeof(RGBTriple), 1, wfile);
            }
        }
        if (offset != 0)
        {
            char ign;
            for (int k = 0; k < offset; k++)
            {
                if (fwrite(&ign, sizeof(char), 1, wfile) != 1)
                {
                    cout << "偏移写入错误" << endl;
                    return;
                }
            }
        }
    }
    fclose(wfile);

    bmp* a1 = NULL;
    if (a->fileInFoHeader.biBitCount == 8)
    {
        a1 = new bmp2;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 24)
    {
        a1 = new bmp1;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 16)
    {
        a1 = new bmp3;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 1)
    {
        a1 = new bmp4;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else
    {
        cout << "不属于此项目所能读取的图片格式，请重新选择图片格式！！" << endl;
        return;
    }

    bmp** newspace = new bmp * [m_EmpNum + 1];
    if (this->m_EmArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            newspace[i] = this->m_EmArray[i];
        }
    }
    newspace[this->m_EmpNum] = a1;
    m_EmpNum++;
    //释放原有空间
    delete[]this->m_EmArray;

    //更改新空间的指向
    this->m_EmArray = newspace;
}
//灰度
void deal::ImageGray()
{
    cout << endl;
    bmp* a = this->m_EmArray[m_EmpNum - 1];

    cout << "新图片名称:";
    char name[100] = { 0 };//bmp名称
    cin>>name;

    a->writePic(makeGary, name);

    bmp* a1 = NULL;
    if (a->fileInFoHeader.biBitCount == 8)
    {
        a1 = new bmp2;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 24)
    {
        a1 = new bmp1;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 16)
    {
        a1 = new bmp3;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 1)
    {
        a1 = new bmp4;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else
    {
        cout << "不属于此项目所能读取的图片格式，请重新选择图片格式！！" << endl;
        return;
    }

    bmp** newspace = new bmp * [m_EmpNum + 1];
    if (this->m_EmArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            newspace[i] = this->m_EmArray[i];
        }
    }
    newspace[this->m_EmpNum] = a1;
    m_EmpNum++;
    //释放原有空间
    delete[]this->m_EmArray;

    //更改新空间的指向
    this->m_EmArray = newspace;
}
//二值化
void deal::binaryimage()
{
    cout << endl;
    bmp* a = this->m_EmArray[m_EmpNum - 1];

    cout << "新图片名称:";
    char name[100] = { 0 };//bmp名称
    cin>>name;

    RGBQUAD rg[2];

    BmpFileHeader newfile= a->fileHeader;
    BmpFileInFoHeader newfilein = a->fileInFoHeader;

    newfilein.biBitCount = 8;
    newfilein.biClrUsed = 2;//颜色索引表数量，二值图为2
    newfilein.biClrImportant = 0;//重要颜色索引为0，表示都重要
    newfile.bfOffBits= sizeof(BmpFileHeader) + sizeof(BmpFileInFoHeader) + 2 * sizeof(RGBQUAD);
    //数据区偏移量，等于文件头，信息头，索引表的大小之和
    newfile.bfSize = newfile.bfOffBits + newfilein.biSizeImages;//文件大小，等于偏移量加上数据区大小

    rg[0].rgbBlue = rg[0].rgbGreen = rg[0].rgbRed = rg[0].rgbReserved = 0;//调色板颜色为黑色对应的索引为0
    rg[1].rgbBlue = rg[1].rgbGreen = rg[1].rgbRed = 255;//白色对应的索引为1
    rg[1].rgbReserved = 0;

    FILE* wfile;//输出文件
    wfile = fopen(name, "wb");//打开文件为存储修改后图像做准备
    if (wfile == NULL)
    {
        cout << "打开文件错误";
        return;
    }

    if (fwrite(&newfile, 1, sizeof(BITMAPFILEHEADER), wfile) != 14)
    {
        cout << "错误文件头" << endl;
        return;
    }//写回位图文件头信息到输出文件
    if (fwrite(&newfilein, 1, sizeof(BITMAPINFOHEADER), wfile) != 40)
    {
        cout << "错误信息头" << endl;
        return;
    }//写回位图信息头信息到输出文件
    if (fwrite(&rg, 1, 2*sizeof(RGBQUAD), wfile) != 8)
    {
        cout << "错误调色板" << endl;
        return;
    }

    RGBTriple* temp = a->surface;
    unsigned char b;//存储每个像素的灰度值或二值
    unsigned char* c;//存储每行像素的二值

    /*将彩色图转为二值图*/
    c = (unsigned char*)malloc((newfilein.biWidth + 3) / 4 * 4);
    //给变量c申请目标图每行像素所占大小的空间,同样四字节对齐

    for (int i = 0; i < newfilein.biHeight; i++) 
    {//遍历图像每行的循环
        for (int j = 0; j < newfilein.biWidth; j++) 
        {//循环像素宽度次,就不会计算读入四字节填充位
            b = (int)(0.114 * (float)temp->blue + 0.587 * (float)temp->green + 0.299 * (float)temp->red);
            //a中每三个字节分别代表BGR分量，乘上不同权值转化为灰度值
            if (190 <= (int)b) b = 1;//将灰度值转化为二值，这里选取的阈值为190
            else b = 0;
            c[j] = b;//存储每行的二值
         }
         fwrite(c, (newfilein.biWidth + 3) / 4 * 4, 1, wfile);
         //将二值像素四字节填充写入文件,填充位没有初始化,为随机值
    }
    fclose(wfile);
}
//填充
void deal::ImageAdd()
{
    bmp* a = this->m_EmArray[m_EmpNum-1];
    cout << endl;
    cout << "新图片名称:";
    char name[100]={0};//bmp名称
    cin>>name;

    BmpFileHeader wbitHead;
    wbitHead = a->fileHeader;
    //由于截取图像头和源文件头相似，所以先将源文件头数据赋予截取文件头
    //读取位图信息头信息
    BmpFileInFoHeader wbitInfoHead;
    wbitInfoHead = a->fileInFoHeader;//同位图文件头相似

    FILE* wfile;//输出文件
    wfile = fopen(name, "wb");//打开文件为存储修改后图像做准备
    if (wfile == NULL)
    {
        cout << "打开文件错误"<<endl;
        return;
    }

    if (fwrite(&wbitHead, 1, sizeof(BITMAPFILEHEADER), wfile) != 14)
    {
        cout << "错误文件头" << endl;
        return;
    }//写回位图文件头信息到输出文件
    if (fwrite(&wbitInfoHead, 1, sizeof(BITMAPINFOHEADER), wfile) != 40)
    {
        cout << "错误信息头" << endl;
        return;
    }//写回位图信息头信息到输出文件

    int offset = (wbitInfoHead.biWidth * 3) % 4;//内存对齐计算偏移，4的倍数
    if (offset != 0)
    {
        offset = 4 - offset;
    }

    RGBTriple* temp = a->surface;
    //分配内存空间把源图存入内存   
    RGBTriple* image = new RGBTriple[wbitInfoHead.biWidth*wbitInfoHead.biHeight];

    int N=0;//顶点数
    int color=0;
    double x[50]={0}, y[50]={0};
    cout << "输入填充的多边形的顶点数：";
    cin >> N;
    cout << "依次输入地物的顶点坐标："<<endl;
    for (int i = 0; i < N; i++)
    {
        cout << "输入第" << i + 1 << "个顶点的坐标:" << endl;
        cout << "x,y:";
        scanf_s("%lf,%lf", &x[i], &y[i]);
        while (x[i] >= wbitInfoHead.biWidth || y[i] >= wbitInfoHead.biHeight)
        {
            cout << "超出范围，请重输：" << endl;
            cout << "输入第" << i + 1 << "个顶点的坐标:" << endl;
            cout << "x,y:";
            scanf_s("%lf,%lf", &x[i], &y[i]);
        }
    }

    cout << "请选择颜色：1 黑，2 深灰绿色  "<< "3 蓝　4 亮蓝：5 绿"<< "6 青  7   红  8 紫   9 棕"<< "10 黄   11 浅灰\n ";
    cout << "请输入颜色：";
    cin >> color;
    int arr[3]={0};
    //BGR
    switch (color)
    {
    case 1:
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
        break;
    case 2:
        arr[0] = 20;
        arr[1] = 128;
        arr[2] = 48;
        break;
    case 3:
        arr[0] = 255;
        arr[1] = 0;
        arr[2] = 0;
        break;
    case 4:
        arr[0] = 112;
        arr[1] = 25;
        arr[2] = 25;
        break;
    case 5:
        arr[0] = 0;
        arr[1] = 255;
        arr[2] = 0;
        break;
    case 6:
        arr[0] = 255;
        arr[1] = 255;
        arr[2] = 0;
        break;
    case 7:
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 255;
        break;
    case 8:
        arr[0] = 240;
        arr[1] = 32;
        arr[2] = 160;
        break;
    case 9:
        arr[0] = 42;
        arr[1] = 42;
        arr[2] = 128;
        break;
    case 10:
        arr[0] = 0;
        arr[1] = 255;
        arr[2] = 255;
        break;
    case 11:
        arr[0] = 192;
        arr[1] = 192;
        arr[2] = 192;
        break;
    default:
        break;
    }

    double new_y[50] = { 0 };
    int n = 0;//相交的点数
    double suitable_x[50]={0};

    cout << "白线为原图中的大致范围：" << endl;
    for (int i = 0; i < N; i++)
     //逆时针顶点相连构成闭合多边形
    {
        if (i == N - 1)
        {
            line(80+x[i], 70+y[i], 80+x[0], 70+y[0]);
        }
        else
        {
            line(80+x[i], 70+y[i], 80+x[i + 1], 70+y[i + 1]);
        }
    }

    //计算扫描线范围
    double min_y = find_min(y, N);
    cout << min_y << endl;
    double max_y = find_max(y, N);
    cout << max_y << endl;
    //不涉及填充区域的部分
    for (int i = wbitInfoHead.biHeight - 1; i > max_y; i--)
    {
        for (int j = 0; j < wbitInfoHead.biWidth; j++)
        {
            (image + (i * wbitInfoHead.biWidth + j))->blue = (temp + (i * a->fileInFoHeader.biWidth + j))->blue;
            (image + (i * wbitInfoHead.biWidth + j))->green = (temp + (i * a->fileInFoHeader.biWidth + j))->green;
            (image + (i * wbitInfoHead.biWidth + j))->red = (temp + (i * a->fileInFoHeader.biWidth + j))->red;
            fwrite((char*)(image + (i * wbitInfoHead.biWidth + j)), sizeof(RGBTriple), 1, wfile);
        }
        if (offset != 0)
        {
            char ign;
            for (int k = 0; k < offset; k++)
            {
                if (fwrite(&ign, sizeof(char), 1, wfile) != 1)
                {
                    cout << "偏移写入错误" << endl;
                    return;
                }
            }
        }
    }
    //-------------------------像素填充面积-------------------------//
    for (int now_y = max_y; now_y > min_y; now_y--)
    {
        Suitable_x(x, y, N, now_y, suitable_x, n);
        sort_min_to_max(suitable_x, n);  //从小到大排序,实现两两配对
        suitable_x[n] = wbitInfoHead.biWidth;
        //与填充区域无关的最左边先处理
        for (int k = 0; k < suitable_x[0]; k++)
        {
            (image + (now_y * wbitInfoHead.biWidth + k))->blue = (temp + (now_y * a->fileInFoHeader.biWidth + k))->blue;
            (image + (now_y * wbitInfoHead.biWidth + k))->green = (temp + (now_y * a->fileInFoHeader.biWidth + k))->green;
            (image + (now_y * wbitInfoHead.biWidth + k))->red = (temp + (now_y * a->fileInFoHeader.biWidth + k))->red;
            fwrite((char*)(image + (now_y * wbitInfoHead.biWidth + k)), sizeof(RGBTriple), 1, wfile);
        }
        for (int i = 0; i < n; i += 2)
         //两个为一组，进行循环
        {
            for (int now_x = suitable_x[i]; now_x < suitable_x[i + 1]; now_x++)
                //确定在扫描线上，要填充的范围
            {
                (image + (now_y * wbitInfoHead.biWidth + now_x))->blue = arr[0];
                (image + (now_y * wbitInfoHead.biWidth + now_x))->green = arr[1];
                (image + (now_y * wbitInfoHead.biWidth + now_x))->red = arr[2];
                fwrite((char*)(image + (now_y * wbitInfoHead.biWidth + now_x)), sizeof(RGBTriple), 1, wfile);
            }
            for (int now_x = suitable_x[i+1]; now_x < suitable_x[i+2]; now_x++)
                //不在扫描线上，要填充的范围
            {
                (image + (now_y * wbitInfoHead.biWidth + now_x))->blue = (temp + (now_y * a->fileInFoHeader.biWidth + now_x))->blue;
                (image + (now_y * wbitInfoHead.biWidth + now_x))->green = (temp + (now_y * a->fileInFoHeader.biWidth + now_x))->green;
                (image + (now_y * wbitInfoHead.biWidth + now_x))->red = (temp + (now_y * a->fileInFoHeader.biWidth + now_x))->red;
                fwrite((char*)(image + (now_y * wbitInfoHead.biWidth + now_x)), sizeof(RGBTriple), 1, wfile);
            }
        }
        if (offset != 0)
        {
            char ign;
            for (int k = 0; k < offset; k++)
            {
                if (fwrite(&ign, sizeof(char), 1, wfile) != 1)
                {
                    cout << "偏移写入错误" << endl;
                    return;
                }
            }
        }
    }
    //与填充区域无关的行
    for (int i = min_y; i >=0; i--)
    {
        for (int j = 0; j < wbitInfoHead.biWidth; j++)
        {
            (image + (i * wbitInfoHead.biWidth + j))->blue = (temp + (i * a->fileInFoHeader.biWidth + j))->blue;
            (image + (i * wbitInfoHead.biWidth + j))->green = (temp + (i * a->fileInFoHeader.biWidth + j))->green;
            (image + (i * wbitInfoHead.biWidth + j))->red = (temp + (i * a->fileInFoHeader.biWidth + j))->red;
            fwrite((char*)(image + (i * wbitInfoHead.biWidth + j)), sizeof(RGBTriple), 1, wfile);
        }
        if (offset != 0)
        {
            char ign;
            for (int k = 0; k < offset; k++)
            {
                if (fwrite(&ign, sizeof(char), 1, wfile) != 1)
                {
                    cout << "偏移错误" << endl;
                    return;
                }
            }
        }
    }
    fclose(wfile);

    bmp* a1 = NULL;
    if (a->fileInFoHeader.biBitCount == 8)
    {
        a1 = new bmp2;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 24)
    {
        a1 = new bmp1;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 16)
    {
        a1 = new bmp3;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else if (a->fileInFoHeader.biBitCount == 1)
    {
        a1 = new bmp4;
        a1->readPic(name);
        a1->ShowImage(1);
    }
    else
    {
        cout << "不属于此项目所能读取的图片格式，请重新选择图片格式！！" << endl;
        return;
    }

    bmp** newspace = new bmp * [m_EmpNum + 1];
    if (this->m_EmArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            newspace[i] = this->m_EmArray[i];
        }
    }
    newspace[this->m_EmpNum] = a1;
    m_EmpNum++;
    //释放原有空间
    delete[]this->m_EmArray;

    //更改新空间的指向
    this->m_EmArray = newspace;
}
//求解方程的k,b值
void deal::function_line(double x1, double y1, double x2, double y2, double& k, double& b)
{
    if (x2 - x1 == 0)
        //垂直线
    {
        k = -9999;
        //与x轴交点
        b = x1;
        return;
    }
    //计算斜率
    k = (y2 - y1) / (x2 - x1);
    b = y1 - k * x1;
}
//返回直线的y
double deal::solve_y(double k, double b, double x)
{
    return k * x + b;
}
//返回直线的x
double deal::solve_x(double k, double b, double y)
{
    if (k == -9999)
        return b;
    int m = (y - b) / k;
    return m;
}
//找出扫描线与边界相交的点，并储存在suitable_x[]中，把相交的点数储存在n中
void deal::Suitable_x(double x[], double y[], int N, double now_y, double suitable_x[], int& n)
//注意是suitable_x和n的地址
//x[]-----------顶点x坐标
//y[]-----------顶点y坐标
//N-------------顶点的个数
//now_y---------当前的扫描线y
//suitable_x[]--扫描线与边界相交的点的x坐标
//n-------------相交的点数
{
    n = 0;
    int t = 0;
    double k, b;
    //每条边是否与扫描线有交点
    for (int i = 0; i < N; i++)
    {
        if (i == N - 1)
        {
            if ((y[i] < now_y && now_y <= y[0]) ||( y[0] < now_y && now_y <= y[i]))
                //判断直线是否过最后一条直线,两种情况
            {
                function_line(x[0], y[0], x[i], y[i], k, b);
                suitable_x[t++] = solve_x(k, b, now_y);
            }
        }
        else
         //扫描其他边
        {
            if ((y[i] < now_y && now_y <= y[i + 1]) ||( y[i + 1] < now_y && now_y <= y[i]))
             //判断扫描线过哪条直线的范围
            {
                function_line(x[i], y[i], x[i + 1], y[i + 1], k, b);
                suitable_x[t++] = solve_x(k, b, now_y);//把交点的x储存在suitable_x[]中
            }
        }
    }
    n = t;
}
//排序----从小到大排序
void deal::sort_min_to_max(double suitable_x[], int n)
{
    double temp;
    int right = n - 1;
    int left = 0;
    quick_sort(suitable_x, left, right);
    //冒泡排序
    //for (int i = 0; i < n - 1; i++)
    //{
      //  for (int j = i + 1; j < n; j++) 
      // {
      //      if (suitable_x[i] > suitable_x[j]) 
      //     {
      //          double temp = suitable_x[i];
      //          suitable_x[i] = suitable_x[j];
      //          suitable_x[j] = temp;
      //      }
      //  }
   //}
}
//快速排序
void deal::quick_sort(double s[], int l, int r)
{
    if (l < r)
    {
        //Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while (i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;
            if (i < j)
                s[i++] = s[j];

            while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                i++;
            if (i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用 
        quick_sort(s, i + 1, r);
    }
}
//输出最大的元素值
double deal::find_max(double elem[], int N)
{
    double max = elem[0];
    for (int i = 0; i < N; i++)
    {
        if (elem[i] > max)
        {
            max = elem[i];
        }
    }
    return max;
}
//输出最小的元素值
double deal::find_min(double elem[], int N)     
{
    double min = elem[0];
    for (int i = 0; i < N; i++)
    {
        if (elem[i] < min)
        {
            min = elem[i];
        }
    }
    return min;
}
//清屏
void deal::closeImage()
{
    //获取句柄
    HWND hnd = GetHWnd();
    //弹出窗口
    int isok = MessageBox(hnd, "清屏并显示最后一步操作图片", "提示", MB_OKCANCEL);
    if (isok == IDOK&&m_EmpNum!=0)
    {
        clearrectangle(80, 70, 750, 850);
        TCHAR s7[10] = "清屏";
        button(700, 820, 40, 20, s7);
        bmp* a = this->m_EmArray[m_EmpNum - 1];
        a->ShowImage(0);
        getchar();
    }
    else
    {
        cout << "go on!";
    }
}
//关闭窗口
void deal::close()
{
    HWND a = GetHWnd();
    int i= MessageBox(a, "是否关闭", "消息框", MB_OKCANCEL);
    if (i == IDOK)
    {
        closegraph();
        cout << "欢迎使用，下次再见！";
        exit(0);
    }
}
//显示全部
void deal::showall()
{
    cout << endl;
    bmp* a = NULL;
    int i;
    for (i = 0; i < m_EmpNum; i++)
    {
        a = this->m_EmArray[i];
        cout << *a;
        getchar();
    }
}
//析构函数
deal::~deal()
{
    if (this->m_EmArray != NULL)
    {
        delete[]this->m_EmArray;
        this->m_EmArray = NULL;
        m_EmpNum = 0;
    }
}