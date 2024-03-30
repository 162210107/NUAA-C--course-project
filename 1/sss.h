#pragma once
//结构体内存对齐设定为2字节
#pragma pack(2)
//文件头结构体定义
struct  BmpFileHeader
{
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
};
//信息头结构体定义
struct BmpFileInFoHeader
{
    unsigned int biSize=0;
    int biWidth = 0;
    int biHeight = 0;
    unsigned short biPlanes=0;
    unsigned short biBitCount=0;
    unsigned int biCompression=0, biSizeImages=0;
    int biXPelsPerMeter=0, biYPelsPerMeter=0;
    unsigned int biClrUsed=0, biClrImportant=0;
};
//像素数据
struct RGBTriple
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};