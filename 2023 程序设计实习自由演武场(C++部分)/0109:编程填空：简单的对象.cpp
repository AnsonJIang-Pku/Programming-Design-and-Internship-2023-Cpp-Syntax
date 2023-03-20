#include <iostream>
using namespace std;
class A
{
	static int num;
public:
	A(){num+=1;}
	void func()
	{
		cout<< num <<endl;
	}
void func() const{
        cout << --num << endl;
    }
    A (A & a){ }
};

int A::num=1;

int main()
{
	A a1;
	const A a2 = a1;
	A & a3 = a1;
	const A & a4 = a1;

	a1.func();
	a2.func();
	a3.func();
	a4.func();

	return 0;
}
