#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cstring>
#include <cstdlib>
using namespace std;
//由于需要记录某个数字是否曾经存在过，需要结合使用multimap<int,int>加以记录

multimap<int,int> mmap;
typedef multimap<int,int> TYPE;

multiset<int> mset;

void add(){
    int x;
    cin >> x;
    mset.insert(x);
    mmap.insert(make_pair(x,1));
    cout << mset.count(x) << endl;
}

void del(){
    int x;
    cin >> x;
    cout << mset.count(x) << endl;
    mset.erase(x);
}

void ask(){
    int x;
    cin >> x;
    bool flag;
    if(mmap.count(x) == 0)
        flag = 0;
    else
        flag = 1;
    cout << flag << ' ';
    cout << mset.count(x) << endl;
}

int main()
{
    int n;
    cin >> n;
    string cmd;
    for(int i = 0; i < n; i++)
    {
        cin >> cmd;
        if(cmd == "add") add();
        if(cmd == "del") del();
        if(cmd == "ask") ask();
    }
    return 0;
}

