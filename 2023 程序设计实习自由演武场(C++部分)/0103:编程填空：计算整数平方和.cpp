#include <iostream>
using namespace std;
class CType{
public:
    int num;
    void setvalue(const int& n)
    {
        num = n;
    }
    CType operator++(int)
    {
        CType tmp(*this);
        num = num*num;
        return tmp;
    }
    operator int() { return num; }
    
};
int main(int argc, char* argv[]) {
	CType obj;
	int   n;		
	cin>>n;
	while ( n ) {
		obj.setvalue(n);
		cout<<obj++<<" "<<obj<<endl;
		cin>>n;
	}
	return 0;
}
