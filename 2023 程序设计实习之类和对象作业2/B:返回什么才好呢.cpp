#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class A {
public:
    int val;
    //类型转换构造函数
    A(int num){
        val = num;
    }
    A ()
    {
        val = 123;
    }
    A &GetObj()//如果没有加&，那么只返回临时变量，会消亡
    {
        return *this;
    }//考点是this指针，问题在于如何返回该对象本身
    //引用作为函数的返回值ppt 1-22
};
int main()
{
    int m,n;
    A a;
    cout << a.val << endl;
    while(cin >> m >> n) {
        a.GetObj() = m;
        cout << a.val << endl;
        a.GetObj() = A(n);
        cout << a.val<< endl;
    }
    return 0;
}
