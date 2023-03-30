#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(
T * s, T * e)
{
    T sum = *s;//卡在了初始化，实际上无法初始化就用第一个初始化就ok
    s++;
    for(;s != e; ++s)
    {
        sum += *s;
    }
    return sum;
}
int main() {
	string array[4] = { "Tom","Jack","Mary","John"};
	cout << SumArray(array,array+4) << endl;
	int a[4] = { 1, 2, 3, 4};  //提示：1+2+3+4 = 10
	cout << SumArray(a,a+4) << endl;
	return 0;
}
