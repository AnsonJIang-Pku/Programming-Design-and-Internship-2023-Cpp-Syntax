#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
private:
    int row,clm;
public:
    //(stk0)如何用new创建动态二维数组
    int** arr;
    Array2 (int r=0, int c=0):row(r),clm(c)
    {
        arr = new int*[row];
        for(int i = 0;i < clm; ++i)
        {
            arr[i] = new int[clm];
        }
    };
    ~Array2()
    {
        if(arr) delete []arr;
        row = 0;
        clm = 0;
    }
    //(stk1)一开始返回值类型错了。
    int* & operator[] (int i)
    {
        return arr[i];
    }
    int operator() (int i, int j)
    {
        return arr[i][j];
    }
    //b=a需要深拷贝
    Array2& operator=(const Array2 & a)
    {
        row = a.row;
        clm = a.clm;
        //new
        arr = new int*[row];
        for(int i = 0;i < clm; ++i)
        {
            arr[i] = new int[clm];
        }
        //赋值
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<clm; j++)
            {
                arr[i][j] = a.arr[i][j];
            }
        }
        return *this;
    }
// 在此处补充你的代码
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
