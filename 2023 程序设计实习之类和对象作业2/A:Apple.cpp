#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Apple {
public: //缺省为private
    static int nTotalNumber;
    Apple () //new了四个，所以输出4，肯定用到了构造函数来实现累加
    {
        nTotalNumber ++;
    }
    //delete [] p;后数量减少，肯定自己定义了析构函数
    ~Apple ()
    {
        nTotalNumber --;
    }
    static void PrintTotal() {
        cout << nTotalNumber << endl;
    }

};
int Apple::nTotalNumber = 0;
Apple Fun(const Apple & a) { //这里调用了一次复制构造函数，不是构造函数
    a.PrintTotal();
    return a; //这里隐藏调用了一次析构函数，形参消亡
}
int main()
{
    Apple * p = new Apple[4];
    Fun(p[2]); //这里未调用析构函数。
    Apple p1,p2;
    Apple::PrintTotal (); //所以输出5（=4-1+2）
    delete [] p;
    p1.PrintTotal ();
    return 0;
}
