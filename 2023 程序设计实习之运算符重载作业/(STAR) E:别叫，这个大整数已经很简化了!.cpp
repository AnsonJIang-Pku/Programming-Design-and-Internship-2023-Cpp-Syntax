//最大问题：字符串处理的有问题。
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int MAX = 110;
class CHugeInt {
private:
    char s[210];
public:
    void rev(char *p)
    {
        if (p)
        {
            int i = 0,j = strlen(p) - 1;
            while( i < j )
            {
                swap(p[i],p[j]);
                i++; j--;
            }
        }
    }
    
    //构造函数
    CHugeInt(char *p)
    {
        memset(s,0,sizeof(s));
        strcpy(s,p);
        rev(s);
    }
    CHugeInt(int n)
    {
        memset(s,0,sizeof(s));
        sprintf(s, "%d", n);
        rev(s);
    }
    //Overload operators
    friend ostream& operator<< (ostream& os, const CHugeInt& h)
    {
//这里形参如果加引用，会在 cout << a+b << endl;那行报错
//没问题：CHugeInt h 或者 const CHugeInt& h
        int len = strlen(h.s);
        for(int i = len-1; i>=0;i--)
        {
            os << h.s[i];
        }
        return os;
    }
    CHugeInt operator+(const CHugeInt& h)
    {
        int carry = 0;
        CHugeInt tmp(0);
        for (int i = 0; i <210; i++)
        {
            char c1 = s[i];
            char c2 = h.s[i];
            if(c1==0 && c2==0 && carry==0) break;
            if (c1==0) c1 = '0';
            if (c2==0) c2 = '0';
            int k= c1-'0'+c2-'0' +carry;
            if(k >=10)
            {
                carry = 1;
                tmp.s[i] = k-10+'0';
            }
            else{
                carry = 0;
                tmp.s[i] = k+'0';
            }
            
        }
        return tmp;
    }
    CHugeInt operator+(int n)
    {
        CHugeInt h(n);
        return *this + h;
    }
    friend CHugeInt operator+(int n,CHugeInt h)
    {
        return h + n;
    }
    CHugeInt operator+=(int n)
    {
        *this = *this + n;
        return *this;
    }
    CHugeInt operator++()
    {
        *this = *this + 1;
        return *this;
    }
    CHugeInt operator++(int)
    {
        CHugeInt h(*this);
        *this = *this + 1;
        return h;
    }
};
int  main()
{
    char s[210];
    int n;

    while (cin >> s >> n) {
        CHugeInt a(s);
        CHugeInt b(n);

        cout << a + b << endl;
        cout << n + a << endl;
        cout << a + n << endl;
        b += n;
        cout  << ++ b << endl;
        cout << b++ << endl;
        cout << b << endl;
    }
    return 0;
}



