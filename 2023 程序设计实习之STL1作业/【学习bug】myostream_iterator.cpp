
//  Created by Anson Jiang on 2023/4/9.
//

#include <iostream>
#include <list>
#include <string>
using namespace std;

template <class T1,class T2>
void Copy(T1 s,T1 e, T2 x)
{
    for(; s != e; ++s,++x)
        *x = *s;
}

 
template<class T>
class myostream_iteraotr
{
public:
    ostream& os;
    string s;
    list<T> _lst;
    T tmp;
    typename list<T>::iterator itr = _lst.begin();
    myostream_iteraotr(ostream& _os,const string& str):os(_os),s(str) { }
    void operator++(){
        itr++;
    }
    myostream_iteraotr & operator*(){
        return *itr;
    }
    //在Copy中，先解释*x,之后的等号不会调用下面重载后的=，因此没有输出
    void operator=(const T& x){
        _lst.push_back(x);
        os << x << s;
    }
     
};


int main()
{    const int SIZE = 5;
    int a[SIZE] = {5,21,14,2,3};
    double b[SIZE] = { 1.4, 5.56,3.2,98.3,3.3};
    list<int> lst(a,a+SIZE);
    myostream_iteraotr<int> output(cout,",");
    Copy( lst.begin(),lst.end(),output);
    cout << endl;
    myostream_iteraotr<double> output2(cout,"--");
    Copy(b,b+SIZE,output2);
    return 0;
}
