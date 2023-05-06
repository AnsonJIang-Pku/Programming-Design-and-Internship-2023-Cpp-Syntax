#include <iostream>

using namespace std;
// 在此处补充你的代码
template <class T1, class T2, class T3>
auto combine(T1 f, T2 g)
{
    auto ff = [=] (T3 x) { return f(f(x)+g(x)); };
    return ff;
}
// 在此处补充你的代码
int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;

    return 0;
}
