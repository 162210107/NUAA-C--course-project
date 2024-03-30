#include"bmp4.h"

bmp4::bmp4()
{

}

bmp4::bmp4(const bmp4& obj)
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

void bmp4::readPic(char fileName[])
{

}

void bmp4::writePic(void (*myMethod)(int, int, RGBTriple*), char* outFileName)
{

}

void bmp4::ShowImage(int i)
{
    IMAGE mage;
    loadimage(&mage, mfilename);
    putimage(80, 70 + 400 * i, &mage);// ‰≥ˆŒª÷√
}

bmp4::~bmp4()
{
    success = 0;
    offset = 0;
    delete[]surface;
    delete[]mfilename;
}