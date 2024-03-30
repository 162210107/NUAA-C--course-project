#include"help.h"
//水平翻转
void rowReverse(int height, int width, RGBTriple* image)
{
    int ured = 0, ugreen = 0, ublue = 0;  
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j < k; j++, k--)
        {
            ured = (image + (i * width + j))->red;
            (image + (i * width + j))->red = (image + (i * width + k))->red;
            (image + (i * width + k))->red = ured;
            ugreen = (image + (i * width + j))->green;
            (image + (i * width + j))->green = (image + (i * width + k))->green;
            (image + (i * width + k))->green = ugreen;
            ublue = (image + (i * width + j))->blue;
            (image + (i * width + j))->blue = (image + (i * width + k))->blue;
            (image + (i * width + k))->blue = ublue;
           
        }
        
    }
}
//是3x3网格的中心对准图片每一个像素
//求取其覆盖所有像素点的rgb的平均值
//新的rgb最后复制，否则会造成污染
void makeBlur(int height, int width, RGBTriple* image)
{
    RGBTriple* temp = new RGBTriple[height * width];
    int ured = 0;
    int ugreen = 0;
    int ublue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //计算实际覆盖的像素数量
            int total = 0;
            for (int y = i - 1, myCount = 0; myCount < 3; y++, myCount++)//每个像素点前一个
             //mycout用于记录3*3网格长度，最多取三个
            {
                if (y >= 0 && y < height)//保证3*3网格所覆盖的像素点在图像中
                {
                    for (int x = j - 1, myCount1 = 0; myCount1 < 3; x++, myCount1++)
                    {
                        if (x >= 0 && x < width)
                        {
                            ured += (image + (y * width + x))->red;
                            ugreen += (image + (y * width + x))->green;
                            ublue += (image + (y * width + x))->blue;
                            total++;
                        }
                    }
                }
            }
            (temp + (i * width + j))->red = (ured / total);
            (temp + (i * width + j))->green = (ugreen / total);
            (temp + (i * width + j))->blue = (ublue / total);
            ured = ugreen = ublue = 0;//开始下一轮
        }
    }
   //传递值
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            (image + (i * width + j))->blue = (temp + (i * width + j))->blue;
            (image + (i * width + j))->green = (temp + (i * width + j))->green;
            (image + (i * width + j))->red = (temp + (i * width + j))->red;
        }
    }
    delete[] temp;//释放临时数组
}
void makeGary(int height, int width, RGBTriple* image) 
{
    for (int i =0; i < height; i++) 
    {
        for (int j =0; j < width; j++) 
        {
            int aver = ((image + (i * width + j))->blue + (image + (i * width + j))->green + (image + (i * width + j))->red) / 3;
           (image + (i * width + j))->blue = (image + (i * width + j))->green = (image + (i * width + j))->red = aver;
        }
    }
}