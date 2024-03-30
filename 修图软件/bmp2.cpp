#include "bmp2.h"

bmp2::bmp2()
{

}
//拷贝构造
bmp2::bmp2(const bmp2& obj)
{
    fileHeader = obj.fileHeader;
    fileInFoHeader = obj.fileInFoHeader;

    int width = obj.fileInFoHeader.biWidth;
    int height = obj.fileInFoHeader.biHeight;
    surface = new RGBTriple[width * height];
    surface = obj.surface;

    rgbQuad = new RGBQUAD[256];
    rgbQuad = obj.rgbQuad;

    offset = obj.offset;
    success = obj.success;

    mfilename = new char[20];
    mfilename = obj.mfilename;
}
//拷贝构造
void bmp2::readPic(char fileName[])
{
    ifstream ifs;
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
        cout << "Can't open the file." << endl;
        success = 0;
        return;
    }
    ifs.read((char*)&fileHeader, sizeof(BmpFileHeader));
    // 判断文件是否读取成功
    if (ifs.fail())
    {
        cout << "读取文件头错误！" << endl;
        success = 0;//记录失败情况
        return;
    }
    //判断bfType格式是否正确
    if (fileHeader.bfType != BMPTYPE)
    {
        cout << "type error!" << endl;
        success = 0;
        return ;
    }
    ifs.read((char*)&fileInFoHeader, sizeof(BmpFileInFoHeader));
    // 判断文件是否读取成功
    if (ifs.fail())
    {
        cout << "读取信息头错误" << endl;
        success = 0;
        return ;
    }
    //判断是否为8位图
    if (fileInFoHeader.biBitCount != 8) 
    {
        cout << "invalid!不是八位图！" << endl;
        success = 0;
        return ;
    }
    ifs.read((char *)rgbQuad, fileInFoHeader.biClrUsed * sizeof(RGBQUAD));
    unsigned char* c;
    c = (unsigned char*)malloc((fileInFoHeader.biWidth + 3) / 4 * 4);

    surface = new RGBTriple[fileInFoHeader.biHeight * fileInFoHeader.biWidth];
    for (int i = fileInFoHeader.biHeight - 1; i >= 0; i--) //由下到上，由左到右储存像素
    {
        for (int j = 0; j < ((fileInFoHeader.biWidth * 3 + 3) / 4 * 4); j++) 
        {//遍历每行中每个字节的循环
            ifs.read((char*)c + j, 1);//将源图每行的每一个字节读入变量a所指向的内存空间
        }
        for (int j = 0; j < fileInFoHeader.biWidth; j++)
        {
            (surface + (i * fileInFoHeader.biWidth + j))->blue = c[j];
            (surface + (i * fileInFoHeader.biWidth + j))->green = c[j];
            (surface + (i * fileInFoHeader.biWidth + j))->red = c[j];
        }
    }
    ifs.close();
    success = 1;
}
//读取
typedef unsigned char BYTE;
//八位图像保存  将BYTE数据保存成为图像，图像路径是filename
void bmp2::writePic(void (*myMethod)(int, int, RGBTriple*), char* strFileName)
{
    myMethod(fileInFoHeader.biHeight, fileInFoHeader.biWidth, surface);

    FILE* fp;
    int i;

    BYTE p[4];//调色板

    //存储图像数据，每行字节数为4的倍数
    //所以 + 3是怕出现不满足4的倍数这种情况；如果是4的倍数则结果和不 + 3的结果是一样的；如果不是4的倍数则结果进1位
    //  /4*4除以四在乘以四是把数据归为4的倍数。
    offset = (fileInFoHeader.biWidth * 3) % 4;//内存对齐计算偏移，4的倍数
    if (offset != 0)
    {
        offset = 4 - offset;
    }

    // Open File
    if ((fp = fopen(strFileName, "w+b")) == NULL)
    {
        success = 0;
        return;
    }

    if (fwrite((char*)&fileHeader, 1, 14, fp) != 14)
    {
        fclose(fp);
        remove(strFileName);
        success = 0;
        return;
    }
    if (fwrite((char*)&fileInFoHeader, 1, 40, fp) != 40)
    {
        fclose(fp);
        remove(strFileName);
        success = 0;
        return;
    }

    // 写入调色板
    for (i = 0, p[3] = 0; i < 256; i++)
    {
      //下面两句选择保存的图像颜色刚好互补
        p[0] = p[1] = p[2] =i; // blue,green,red;
    
        if (fwrite((char*)p, 1, 4, fp) != 4)
        {
           success = 0;
           return;
        }
    }

    //write data 图像数据 从下到上保存
    for (int i = fileInFoHeader.biHeight - 1; i >= 0; i--)
    {
        for (int j = 0; j < fileInFoHeader.biWidth; j++)
        {
            if (fwrite((char*)(surface + (i * fileInFoHeader.biWidth + j)), 1, sizeof(RGBTriple), fp) != sizeof(RGBTriple))
            {
                fclose(fp);
                remove(strFileName);
                success = 0;
                return;
            }
        }
        if (offset != 0)
        {
            char ign;
            for (int k = 0; k < offset; k++)
            {
                if ((fread(&ign, 1, sizeof(char), fp) != sizeof(char)))
                {
                    // 判断文件是否读取成功
                    cout << "填充字节补齐错误" << endl;
                     success = 0;
                     return;
                }
            }
        }
    }
    fclose(fp);
    success = 1;
}
//存储
void bmp2::ShowImage(int i)
{
    IMAGE mage;
    loadimage(&mage, mfilename);
    putimage(80, 70 + 400 * i, &mage);//输出位置
}
//显示
bmp2::~bmp2()
{
    success = 0;
    offset = 0;
    delete[]rgbQuad;
    delete[]surface;
    delete[]mfilename;
}
//析构函数