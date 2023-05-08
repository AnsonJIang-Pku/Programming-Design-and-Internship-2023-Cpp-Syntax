#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset
{
    char a[bitNum/8+1];
    MyBitset() { memset(a,0,sizeof(a));};
    void Set(int i,int v) {
        char & c = a[i/8];
        int bp = i % 8;
        if( v )
            c |= (1 << bp);
        else
            c &= ~(1 << bp);
    }
    // 在此处补充你的代码
    //class MyBit中只存储一个bit位，利用MyBit数组存所有的20位
    bool if_cvt = 0; //利用[]来预置bit[20]数组中的元素，避免重复操作
    class MyBit{
    public:
        int bt;
        MyBit & operator=(int x)
        {
            bt = x;
            return *this;
        }
        operator int(){
            return bt;
        }
        friend ostream & operator<< (ostream& os, MyBit mbt){
            os << mbt.bt;
            return os;
        }
    };
    MyBit bit[20];
    //注意返回值是对象，不是int
    MyBit & operator[](int i)
    {
        if(!if_cvt)
        {
            for(int j = 0; j < bitNum; j++)
            {
                //一开始这里的变量写成了i，注意！！！
                bit[j] = (a[j / 8] >> (j % 8)) & 1;
            }
            if_cvt = 1;
        }
        return bit[i];
    }
    // 在此处补充你的代码

    void Print() {
            for(int i = 0;i < bitNum; ++i)
                cout << (*this) [i];
            cout << endl;
        }

};

int main()
{
    int n;
    int i,j,k,v;
    while( cin >>  n) {
        MyBitset<20> bs;
        for(int i = 0;i < n; ++i) {
            int t;
            cin >> t;
            bs.Set(t,1);
        }
        bs.Print();
        cin >> i >> j >> k >> v;
        bs[k] = v;
        bs[i] = bs[j] = bs[k];
        bs.Print();
        cin >> i >> j >> k >> v;
        bs[k] = v;
        (bs[i] = bs[j]) = bs[k];
        bs.Print();
    }
    return 0;
}
