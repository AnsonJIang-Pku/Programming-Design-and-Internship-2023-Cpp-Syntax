#include <iostream>
#include <set>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
//debug注意：应该从头重新写最好，可以理清思路
/*一开始Prime部分的
 if(n != 1 && n != N)
     cnt++;
 写在了for循环里，导致错误。
*/

int prime(int n)
{
    int cnt = 0;
    int N = n;
    for(int i = 2; i*i <= N; i++)
    {
        if(n % i == 0)
        {
            while(n % i == 0)
                n /= i;
            cnt++;
        }
    }
    if(n != 1 && n != N)
        cnt++;
    return cnt;
}

template <class T>
class Prior_than{
public:
    bool operator() (const T & x, const T & y) const
    {
        int n1 = prime(x), n2 = prime(y);
        if (n1 == n2)
            return x < y;
        else if(n1 > n2)
            return 0;
        else
            return 1;
    }
};


int main()
{
    multiset<int, Prior_than<int> > mset;
    int num;
    cin >> num;
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            int x;
            cin >> x;
            mset.insert(x);
        }
     
        multiset<int, Prior_than<int> >::iterator it = mset.end();
        it--;
        cout << *it << ' ';
        cout << *mset.begin() << endl;
        mset.erase(*it);
        mset.erase(*mset.begin());
      
    }
    
    return 0;
}
