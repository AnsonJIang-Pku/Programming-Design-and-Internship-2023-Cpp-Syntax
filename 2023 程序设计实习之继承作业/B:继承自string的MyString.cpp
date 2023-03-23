#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class MyString: public string
{
public:
    MyString():string() {}
    MyString(const char *p):string(p) {}
    string operator() (int n, int m)
    {
        return substr(n,m); //直接调用string类里面的函数
    }
    //还差operator=没解决
    MyString (const string& str):string(str) {}
    //为什么能通过构造函数解决s3 = s1+s3;等号的问题？
    //构造函数何时被调用
    //因为operator+在string类中被重载，其返回值为string(&)，因此表达式s1+s3的返回值是string，在MyString类中没写类型转换构造函数，就会报错。
};


int main()
{
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
    MyString SArray[4] = {"big","me","about","take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3;
    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;
    s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;
        sort(SArray,SArray+4);
    for( int i = 0;i < 4;i ++ )
    cout << SArray[i] << endl;
    //s1的从下标0开始长度为4的子串
    cout << s1(0,4) << endl;
    //s1的从下标5开始长度为10的子串
    cout << s1(5,10) << endl;
    return 0;
}
