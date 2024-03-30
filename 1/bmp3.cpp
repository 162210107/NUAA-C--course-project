#include "bmp3.h"

bmp3::bmp3()
{

}

bmp3::bmp3(const bmp3& obj)
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

    rgb_mask = new char[12];
    rgb_mask = obj.rgb_mask;

    int dst_widsize = ((fileInFoHeader.biWidth * 16 + 31) >> 5) << 2;
    imagebuf = new char[dst_widsize* fileInFoHeader.biHeight];//实际像素
    imagebuf = obj.imagebuf;

    int a = ((fileInFoHeader.biWidth * fileInFoHeader.biBitCount + 31) >> 5) << 2;
    bmpbuf = new char[a];
    bmpbuf = obj.bmpbuf;
}

void bmp3::readPic(char fileName[])
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
        return;
    }
    ifs.read((char*)&fileInFoHeader, sizeof(BmpFileInFoHeader));
    // 判断文件是否读取成功
    if (ifs.fail())
    {
        cout << "读取信息头错误" << endl;
        success = 0;
        return;
    }
    //判断是否为16位图
    if (fileInFoHeader.biBitCount != 16)
    {
        cout << "invalid!不是十六位图！" << endl;
        success = 0;
        return;
    }

    rgb_mask = new char[12];
    ifs.read((char*)rgb_mask, sizeof(char) * 12);
    if (ifs.fail())
    {
        cout << "读取掩饰码错误" << endl;
        success = 0;
        return;
    }

    ifs.seekg((long)fileHeader.bfOffBits, SEEK_SET);

    int src = ((fileInFoHeader.biWidth * fileInFoHeader.biBitCount + 31) >> 5) << 2;
    char* bmpbuf = new char[src];//掩饰码对应的数据
    int dst_widsize = ((fileInFoHeader.biWidth * 16 + 31) >> 5) << 2;
    imagebuf = (char*)malloc(dst_widsize * fileInFoHeader.biHeight);//实际像素

    //存储像素数据的数组
    surface = new RGBTriple[fileInFoHeader.biHeight * fileInFoHeader.biWidth];
    short d;
    for (short k = fileInFoHeader.biHeight-1, n = 0; k >=0; k--)
    {
        //读取图片像素数据
        ifs.read((char*)bmpbuf, sizeof(char)*src);
        for (short q = 0; q < fileInFoHeader.biWidth; q++) 
        {
            //对掩饰码进行处理
            d = ((short)(bmpbuf[3 * q + 2] >> 3) << 11)//R G B
                + ((short)(bmpbuf[3 * q + 1] >> 2) << 5)
                + (short)(bmpbuf[3 * q + 0] >> 3);
            (surface + (fileInFoHeader.biWidth * k + q))->blue = bmpbuf[3 * q + 0] >> 3;
            (surface + (fileInFoHeader.biWidth * k + q))->green = (bmpbuf[3 * q + 1] >> 2) << 5;
            (surface + (fileInFoHeader.biWidth * k + q))->red = (bmpbuf[3 * q + 2] >> 3) << 11;
            imagebuf[n++] = d & 0xff;
            imagebuf[n++] = d >> 8;
        }
        while (n % dst_widsize != 0) 
            imagebuf[n++] = 0x00;
    }
}
//写为24位图
void bmp3::writePic(void (*myMethod)(int, int, RGBTriple*), char* outFileName)
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
    ofs.write((char*)&fileHeader, sizeof(BmpFileHeader));
    // 判断文件是否写入成功
    if (ofs.fail())
    {
        cout << "文件头写入失败！" << endl;
        return;
    }
    ofs.write((char*)&fileInFoHeader, sizeof(BmpFileInFoHeader));
    // 判断文件是否写入成功
    if (ofs.fail())
    {
        cout << "信息头写入失败！" << endl;
        return;
    }
    
    for (int i = fileInFoHeader.biHeight - 1; i >= 0; i--)
    {
        for (int j = 0; j < fileInFoHeader.biWidth; j++)
        {
            ofs.write((char*)(surface + (i * fileInFoHeader.biWidth + j)), sizeof(RGBTriple));
            // 判断文件是否写入成功
            if (ofs.fail())
            {
                cout << "写入数据失败！" << endl;
                return;
            }
        }
        //先读一行，增加每行后面的0补足
        if (offset != 0)
        {
            char ign = 0;
            for (int k = 0; k < offset; k++)
            {
                ofs.write(&ign, sizeof(char));//内存对齐
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
    ofs.close();
}

void bmp3::ShowImage(int i)
{
    IMAGE mage;
    loadimage(&mage, mfilename);
    putimage(80, 70 + 400 * i, &mage);//输出位置
}

bmp3::~bmp3()
{
    success = 0;
    offset = 0;
    delete[]rgb_mask;
    delete[]imagebuf;
    delete[]bmpbuf;
    delete[]surface;
    delete[]mfilename;
}