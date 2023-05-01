#include <iostream>
#include <map>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;

multimap<int,int> mmap; // <force,id>，显然应该按照force排序，更方便找到
typedef multimap<int,int> TYPE;

void PrintRace(TYPE::iterator it)
{
    //先判断绝对值之差
    if(it != mmap.begin())
    {
        TYPE::iterator before_it = it;
        before_it--;
        TYPE::iterator after_it = it;
        after_it++;
        if(it->first - before_it->first <= after_it->first - it->first)
            cout << it->second << ' ' << before_it->second << endl;
        else
            cout << it->second << ' ' << after_it->second << endl;
    }
    else
    {
        TYPE::iterator after_it = it;
        after_it++;
        cout << it->second << ' ' << after_it->second << endl;
    }
}

int main()
{
    mmap.insert(make_pair(1000000000,1));
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int id,force;
        cin >> id >> force;
        TYPE::iterator it;
        it = mmap.insert(make_pair(force,id));
        PrintRace(it);
    }
    
    return 0;
}
