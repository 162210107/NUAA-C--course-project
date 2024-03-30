#pragma once
using namespace std;//使用标准命名空间
#include"bmp1.h"

bmp1::bmp1()
{

}

bmp1::bmp1(const bmp1& obj)
{
    fileHeader = obj.fileHeader;
    fileInFoHeader = obj.fileInFoHeader;

    int width = obj.fileInFoHeader.biWidth;
    int height = obj.fileInFoHeader.biHeight;
    surface = new RGBTriple[width * height];
    surface = obj.surface;

    offset = obj.offset;
    success = obj.success;

    mfilename = new char[20];
    mfilename = obj.mfilename;
}

void bmp1::readPic(char fileName[])
{
    ifstream ifs;//文件输出流
    cout << fileName<<endl;
    mfilename = new char[20];
    int i = 0;
    while (fileName[i] != '\0')
    {
        *(mfilename + i) = fileName[i];
        i++;
    }
    *(mfilename + i) = '\0';
    //打开文件，二进制方式打开读
    ifs.open(fileName, ios::in | ios::binary);
    //判断文件是否打开成功
    if (!ifs.is_open()) 
    {
        cout <<"Can't open the file." << endl;
        success = 0;//记录失败情况
        return;
    }
    ifs.read((char*)&fileHeader,sizeof(BmpFileHeader));
    // 判断文件是否读取成功
    if (ifs.fail())
    {
        cout << "文件头读取错误" << endl;
        success = 0;
        return;
    }
    //判断bfType格式是否正确
    if (fileHeader.bfType != BMPTYPE) 
    {
        cout <<"type error!" << endl;
        success = 0;
        return;
    }
    ifs.read((char*)&fileInFoHeader,sizeof(BmpFileInFoHeader));
    // 判断文件是否读取成功
    if (ifs.fail())
    {
        cout << "信息头读取错误" << endl;
        success = 0;
        return;
    }
    //判断是否为24位图
    if (fileInFoHeader.biBitCount !=24)
    {
        cout <<"invalid!位图格式错误！" << endl;
        success = 0;
        return;
    }
    //内存对齐计算偏移，4的倍数
    offset = (fileInFoHeader.biWidth *3) %4;
    if (offset !=0) 
    {
        offset =4 - offset;
    }
    //存储像素数据的数组
    surface =new RGBTriple[fileInFoHeader.biHeight * fileInFoHeader.biWidth];
    for (int i = fileInFoHeader.biHeight- 1; i >=0; i--) //由下到上，由左到右储存像素
    {
        for (int j =0; j < fileInFoHeader.biWidth; j++) 
        {
            ifs.read((char*)(surface + (fileInFoHeader.biWidth * i + j)), sizeof(RGBTriple));
        }
        //每行读完后，跳过偏移
        if (offset !=0)
        {
            char ign;
            for (int k =0; k < offset; k++) 
            {
                ifs.read(&ign,sizeof(char));
            }
        }
    }
    ifs.close();
    success = 1;//成功标志
}

void bmp1::writePic(void (*myMethod)(int, int, RGBTriple*), char* outFileName) //函数指针
{ 
    myMethod(fileInFoHeader.biHeight, fileInFoHeader.biWidth, surface);
    //create a new bmp处理后的数据

    ofstream ofs;
    ofs.open(outFileName, ios::out | ios::binary);
    // 判断文件是否打开
    if (!ofs.is_open())
    {
        cout << "file open is error!" << endl;
        return;
    }
    ofs.write((char*)&fileHeader,sizeof(BmpFileHeader));
    // 判断文件是否写入成功
    if (ofs.fail())
    {
        cout << "文件头写入失败！" << endl;
        return;
    }
   
    ofs.write((char*)&fileInFoHeader,sizeof(BmpFileInFoHeader));
    // 判断文件是否写入成功
    if (ofs.fail())
    {
        cout << "信息头写入失败！" << endl;
        return;
    }

    //rewrite
    for (int i = fileInFoHeader.biHeight -1; i >=0; i--) 
    {
        for (int j =0; j < fileInFoHeader.biWidth; j++) 
        {
            ofs.write((char*)(surface + (i * fileInFoHeader.biWidth + j)),sizeof(RGBTriple));
            // 判断文件是否写入成功
            if (ofs.fail())
            {
                cout << "写入数据失败！" << endl;
                return;
            }
        }
        //先读一行，增加每行后面的0补足
        if (offset !=0) 
        {
            char ign = 0;
            for (int k =0; k < offset; k++) 
            {
                ofs. write(&ign,sizeof(char));//内存对齐
                // 判断文件是否写入成功
                if (ofs.fail())
                {
                    cout << "偏移量存储错误！" << endl;
                    return;
                }
            }
        }
    }
    delete[] surface;
    ofs. close();
}

void bmp1::ShowImage(int i)
{
	/*int r, g, b, pix;
	HWND wnd=CreateWindow(EDIT,TEXT("图片")，WS_POPUP|WS_SIZEBOX,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL,NULL,hInstance,NULL);                                 //窗口句柄
	HDC dc;
	wnd = GetForegroundWindow();               //获取窗口句柄
	dc = GetDC(wnd);                           //获取绘图设备
	int x = 10;
	int y = 10;
	
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			b = *p++; g = *p++; r = *p++;
			
			pix = RGB(r, g, b);
			
			int ret=SetPixel(dc, i+x , 150+height-j, pix);
			cout << ret;
			system("pause");//调试台没办法显示，redraw规则
		}
	}*/
	IMAGE mage;
	loadimage(&mage,mfilename);
	putimage(80, 70+400*i, &mage);//输出位置
}

bmp1::~bmp1()
{
    success = 0;
    offset = 0;
    delete[]surface;
    delete[]mfilename;
}