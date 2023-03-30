//这道题真不太会做，总想对已有类继承istream的东西（本质上是不理解istream类是如何写的）
//后面附上了题目中所给的提示
#include <iostream>
#include <string>

using namespace std;
template <class T>
class CMyistream_iterator
{
public:
    istream & is;
    T tmp;
    CMyistream_iterator(istream& iis):is(iis)
    {
        is >> tmp;
    }
    T operator*()
    {
        return tmp;
    }
//后置自增自减运算符重载，要多写一个没用的参数
    CMyistream_iterator operator++(int)
    {
        is >> tmp;
        return *this;
    }
};



int main()  
{ 
	int t;
	cin >> t;
	while( t -- ) {
		 CMyistream_iterator<int> inputInt(cin);
		 int n1,n2,n3;
		 n1 = * inputInt; //读入 n1
		 int tmp = * inputInt;
		 cout << tmp << endl;
		 inputInt ++;   
		 n2 = * inputInt; //读入 n2
		 inputInt ++;
		 n3 = * inputInt; //读入 n3
		 cout << n1 << " " << n2<< " " << n3 << " ";
		 CMyistream_iterator<string> inputStr(cin);
		 string s1,s2;
		 s1 = * inputStr;
		 inputStr ++;
		 s2 = * inputStr;
		 cout << s1 << " " << s2 << endl;
	}
	 return 0;  
}



/* //题目中的提示
C++标准模板库 istream_iterator模版使用说明：

其构造函数执行过程中就会要求输入，然后每次执行++，则读取输入流中的下一个项目，执行 * 则返回上次从输入流中读取的项目。例如，下面程序运行时，就会等待用户输入数据，输入数据后程序才会结束：
#include
#include
using namespace std;
int main() {
istream_iterator inputInt(cin);
return 0;
}

下面程序运行时，如果输入 12 34 程序输出结果是： 12,12
#include
#include
using namespace std;
int main()
{
istream_iterator inputInt(cin);
cout << * inputInt << "," << * inputInt << endl;
return 0;
}

下面程序运行时，如果输入 12 34 56程序输出结果是： 12,56
#include
#include
using namespace std;
int main()
{
istream_iterator inputInt(cin);
cout << * inputInt << "," ;
inputInt ++;
inputInt ++;
cout << * inputInt;
return 0;
}

*/
