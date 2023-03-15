//
//  main.cpp
//
//  Created by Anson Jiang on 2023/2/22.
//

#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
    char * p;
public:
    MyString(const char * s) {
        if( s) {
            p = new char[strlen(s) + 1];
            strcpy(p,s);
        }
        else
            p = NULL;
    }
    ~MyString() { if(p) delete [] p; }
    //在这里报错基本就是深浅拷贝的问题吧
    //没写复制构造函数
    MyString (const MyString& mystr)
    {
        if (mystr.p) {
            p = new char[strlen(mystr.p)+1];
            strcpy(p,mystr.p);
        }
        else{
            p = NULL;
        }
    }
    //需要重载operator=和左移运算符<<
    void Copy(char * str)
    {
        if(p) delete []p;
        if(str){
            p = new char[strlen(str)+1];
            strcpy(p,str);
        }
        else{
            p = NULL;
        }
    }
    MyString& operator=(const MyString& mystr)
    {
        if(this == &mystr) return *this;
        if(p) delete []p;
        p = new char[strlen(mystr.p)+1];
        strcpy(p,mystr.p);
        return *this;
    }
    MyString& operator=(const char* str)
    {
        if(p) delete []p;
        p = new char[strlen(str)+1];
        strcpy(p,str);
        return *this;
    }
    //重载强制类型转换运算符，用于输出对象（否则cout应写为全局函数重载）
    operator char*()
    {
        return p;
    }

};
int main()
{
    char w1[200],w2[100];
    while( cin >> w1 >> w2) {
        MyString s1(w1),s2 = s1;
        MyString s3(NULL);
        s3.Copy(w1);
        cout << s1 << "," << s2 << "," << s3 << endl;

        s2 = w2;
        s3 = s2;
        s1 = s3;
        cout << s1 << "," << s2 << "," << s3 << endl;
        
    }
}
