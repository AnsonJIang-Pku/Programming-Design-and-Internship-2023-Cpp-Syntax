//这个程序没有精简过，比较容易懂，一半的代码是一样的
//  Created by Anson Jiang on 2023/4/6.
//可以转24位&32位bmp文件；教训：类型强制转换与指针的增加量((char*) bmpinfo)+i != (char*)(bmpinfo + i)，且存在优先级问题，最好加括号
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned char BYTE;
//定义bitmap信息结构体
#pragma pack(push,1) //禁用字节对齐
//bitmap 文件头
struct FileHeader{
    WORD bfType; // 位图文件类型
    DWORD bfSize; // 位图文件大小
    WORD bfReserved1; // 文件保留字
    WORD bfReserved2; // 文件保留字
    DWORD bfOffBits; // 位图数据起始位置
};
//bitmap 信息头
struct InfoHeader{
    DWORD biSize; // 信息头大小
    DWORD biWidth; // 宽度
    DWORD biHeight; // 高度
    WORD biPlanes; // 平面数
    WORD biBitCount;// 单像素位数
    DWORD biCompression; // 压缩类型
    DWORD biSizeImage; // 位图大小，应该会变（填充0的个数不一样）
    DWORD biXPelsPerMeter; // 水平分辨率
    DWORD biYPelsPerMeter; // 垂直分辨率
    DWORD biClrUsed;// 颜色表中颜色数
    DWORD biClrImportant;// 重要的颜色数
};
#pragma pack(pop) //恢复字节对齐
//不存在调色板
//位图数据,24位
struct RGB{
    BYTE blue;
    BYTE green;
    BYTE red;
    
};
//32
struct RGBA{
    BYTE blue;
    BYTE green;
    BYTE red;
    BYTE alpha;
};
//32位的文件还多出来一部分
typedef int FXPT2DOT30;
typedef struct tagCIEXYZ
{
    FXPT2DOT30 ciexyzX ;
    FXPT2DOT30 ciexyzY ;
    FXPT2DOT30 ciexyzZ ;
}
CIEXYZ, * LPCIEXYZ ;

typedef struct tagCIEXYZTRIPLE {
    CIEXYZ ciexyzRed ;
    CIEXYZ ciexyzGreen ;
    CIEXYZ ciexyzBlue ;
}CIEXYZTRIPLE;

struct Plus{
    DWORD        bV5RedMask;
    DWORD        bV5GreenMask;
    DWORD        bV5BlueMask;
    DWORD        bV5AlphaMask;
    DWORD        bV5CSType;
    CIEXYZTRIPLE bV5Endpoints;
    DWORD        bV5GammaRed;
    DWORD        bV5GammaGreen;
    DWORD        bV5GammaBlue;
    DWORD        bV5Intent;
    DWORD        bV5ProfileData;
    DWORD        bV5ProfileSize;
    DWORD        bV5Reserved;
};

//定义全局变量
struct FileHeader file;
struct InfoHeader info;
struct Plus splus;

//计算宽度补零的字节数（如biWidth=7,biBitCount=24,那么每个像素三个字节,一行共21字节,需要补3个字节）
int getDeltaZero(InfoHeader & _info)
{
    DWORD DataSizePerLine = (_info.biWidth * _info.biBitCount + 31)/8; //一个扫描行所占字节数
    DWORD _DataSizeLine = _info.biWidth * _info.biBitCount / 8; //未补零时一行的字节数
    return DataSizePerLine - (DataSizePerLine % 4) - _DataSizeLine; //return补的零的个数
}

//旋转90度函数
//原来的biWidth含有补零部分，需要在转化为新的biHeight后删掉；原来的biHeight含有补零部分，需要在转化为新的biWidth后加上
void Rotate(ifstream& inFile,ofstream& outFile)
{
    int new_h = info.biWidth, new_w = info.biHeight;
    int size = info.biWidth * info.biHeight;
    int delta = getDeltaZero(info);
    //读入位图像素信息
    if(info.biBitCount == 24){
        RGB* bmpinfo = new RGB[size]; //去掉了struct关键字
        inFile.seekg(file.bfOffBits,ios::beg);
        for(int i = 0; i < info.biHeight; i++)
        {
            for(int j = 0; j < info.biWidth; j++){
                inFile.read( ((char *)bmpinfo) + (i * info.biWidth + j) * 3,sizeof(RGB));
            }
            inFile.seekg(delta,ios::cur); //不读入偏移量
        }
        struct FileHeader new_file = file;
        struct InfoHeader new_info = info;
        //新文件信息头
        new_info.biSize = sizeof(new_info);
        new_info.biWidth = new_w;
        new_info.biHeight = new_h;
        int new_delta = getDeltaZero(new_info);
        new_info.biSizeImage = (DWORD)(new_w * info.biBitCount / 8 + new_delta) * new_h; //之前这句有问题
        //具体写文件操作
        outFile.write((char *) &new_file, sizeof(new_file));
        outFile.write((char *) &new_info, sizeof(new_info));
        //rotate,更改像素信息
        RGB* new_bmpinfo = new RGB[size];
        for(int i = 0; i < new_h; i++){
            for(int j = 0; j < new_w; j++)
            {
                new_bmpinfo[i* new_w + j] = bmpinfo[j * info.biWidth + new_h - i - 1];
            }
        }
        for(int i = 0; i < new_h; i++){
            for(int j = 0; j < new_w; j++)
                outFile.write( ((char *)new_bmpinfo) + (i * new_w + j) * info.biBitCount / 8,sizeof(RGB));
            outFile.seekp(new_delta,ios::cur);
        }
        //删除new空间
        delete [] bmpinfo;
        delete [] new_bmpinfo;
    }
    else{
        RGBA* bmpinfo = new RGBA[size];
        inFile.seekg(file.bfOffBits,ios::beg);
        for(int i = 0; i < info.biHeight; i++)
        {
            for(int j = 0; j < info.biWidth; j++){
                inFile.read( ((char *)bmpinfo) + (i * info.biWidth + j) * 4,sizeof(RGBA));
            }
            inFile.seekg(delta,ios::cur); //不读入偏移量
        }
        struct FileHeader new_file = file;
        struct InfoHeader new_info = info;
        struct Plus new_splus = splus;
        //新文件信息头
        new_info.biSize = sizeof(new_info);
        new_info.biWidth = new_w;
        new_info.biHeight = new_h;
        int new_delta = getDeltaZero(new_info);
        new_info.biSizeImage = (DWORD)(new_w * info.biBitCount / 8 + new_delta) * new_h; //之前这句有问题
        //具体写文件操作
        outFile.write((char *) &new_file, sizeof(new_file));
        outFile.write((char *) &new_info, sizeof(new_info));
        outFile.write((char *) &new_splus, sizeof(new_splus));
        //rotate,更改像素信息
        RGBA* new_bmpinfo = new RGBA[size];
        for(int i = 0; i < new_h; i++){
            for(int j = 0; j < new_w; j++)
            {
                new_bmpinfo[i* new_w + j] = bmpinfo[j * info.biWidth + new_h - i - 1];
            }
        }
        for(int i = 0; i < new_h; i++){
            for(int j = 0; j < new_w; j++)
                outFile.write( ((char *)new_bmpinfo) + (i * new_w + j) * info.biBitCount / 8,sizeof(RGBA));
            outFile.seekp(new_delta,ios::cur);
        }
        //删除new空间
        delete [] bmpinfo;
        delete []new_bmpinfo;
    }
    return;
}

int main(int argc, char* argv[])
{
    if (argc != 3){
        cout << "File Name Missing!" << endl;
        return 0;
    }
    ifstream inFile(argv[1],ios::binary|ios::in);
    if (!inFile){
        cout << "Source File Open Error!" << endl;
        return 0;
    }
    //读文件头
    inFile.read((char *) &file, sizeof(file));
    inFile.read((char *) &info, sizeof(info)); //信息头
    if (info.biBitCount == 32)
        inFile.read((char *) &splus, sizeof(Plus));
    
    ofstream outFile(argv[2],ios::binary|ios::out); //ios::out，如果没有文件就创建文件
    if (!outFile){
        cout << "New File Open Error!" << endl;
        return 0;
    }
    Rotate(inFile,outFile);
    inFile.close();
    outFile.close();
    return 0;
}
