#include <cstdio>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;
int main()
{	
	double a[] = {1.2,3.4,9.8,7.3,2.6};
	list<double> lst(a,a+5);
	lst.sort(
[](double x,double y){
                 return x > y;
             }
);
	
	for(list<double>::iterator i  = lst.begin(); i != lst.end(); ++i) 
		cout << * i << "," ;
    return 0;
}
