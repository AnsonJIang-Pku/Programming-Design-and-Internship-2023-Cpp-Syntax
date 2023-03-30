#include <iostream>
#include <string>
using namespace std;
//函数模版如果返回值类型写错了不会显示报错（Xcode）
template <class T>
void MyForeach(T * s, T * e,void (*fp)(T arg))
{
    T sum = *s;
    s++;
    for(; s!=e; s++)
    {
        sum += *s;
    }
    fp(sum);
}
template <class T>
void MyForeach(T * s, T * e,void (*fp)(T & arg))
{
    for(; s!=e; s++)
    {
        fp(*s);
    }
}
void Print(string s)
{
	cout << s;
}
void Inc(int & n)
{
	++ n;
}
string array[100];
int a[100];
int main() {
	int m,n;
	while(cin >> m >> n) {
		for(int i = 0;i < m; ++i)
			cin >> array[i];
		for(int j = 0; j < n; ++j)
			cin >> a[j];
		MyForeach(array,array+m,Print);		 
		cout << endl;
		MyForeach(a,a+n,Inc);		 
		for(int i = 0;i < n; ++i)
			cout << a[i] << ",";
		cout << endl;
	}
	return 0;
}
