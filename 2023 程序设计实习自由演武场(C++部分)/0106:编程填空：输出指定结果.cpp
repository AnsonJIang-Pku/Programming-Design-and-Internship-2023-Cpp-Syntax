#include <iostream>
using namespace std;

class A {
public:
int num;
    A (int n){
        num = n;
    }
    operator int() {return num;}
    int operator-=(int n)
    {
        num = num - n;
        return num;
    }
    int operator+=(int n)
    {
        num = num + n;
        return num;
    }
    int & getValue()
    {
        return num;
    }
};

int main() {
	int t;
	cin >> t;
	while(t-- ) {
		int m,n,k;
		cin >> m >> n >> k;	
	    A a(m);
	    A b = a;
	    cout << b << endl;
	    cout << (a += b -= n) << endl;
	    cout << a.getValue() << endl;
	    a.getValue() = k;
	    cout << a << endl;
	} 
	return 0;
}
