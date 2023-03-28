//
//  main.cpp
//
//  Created by Anson Jiang on 2023/2/22.
//

#include <iostream>
using namespace std;
class B {
    private:
        int nBVal;
    public:
        void Print()
        { cout << "nBVal="<< nBVal << endl; }
        void Fun()
        {cout << "B::Fun" << endl; }
        B ( int n ) { nBVal = n;}
};

class D : public B{
    int nDVal;
public:
    D (int n):nDVal(n),B(3 * n) {}
    void Fun()
    {cout << "D::Fun" << endl; }
    void Print()
    {
        B *ptb = this;
        ptb->Print(); //基类指针没有声明虚函数，输出的是基类的函数
        cout << "nDVal="<< nDVal << endl;
    }
};

int main() {
    B * pb; D * pd;
    D d(4); d.Fun();
    pb = new B(2); pd = new D(8);
    pb -> Fun(); pd->Fun();
    pb->Print (); pd->Print ();
    pb = & d; pb->Fun();
    pb->Print();
    return 0;
}
