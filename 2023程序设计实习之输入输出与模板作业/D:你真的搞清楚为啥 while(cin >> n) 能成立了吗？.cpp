#include <iostream>
using namespace std;
class MyCin
{
public:
    int flag;
    MyCin()
    {
        flag = 1;
    }
    MyCin& operator >>(int &n) //这里一定要为n的引用，否则出错（cin是要修改已经创建的变量的）
    {
        cin >> n; //在重载的运算符里面调用cin就好了（stuck）
        if(n == -1) flag = 0;
        return *this;
    }
    operator bool()
    {
        return flag;
    }
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2)
        cout  << n1 << " " << n2 << endl;
    return 0;
}
