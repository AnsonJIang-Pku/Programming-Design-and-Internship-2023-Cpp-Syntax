#include <iostream>
#include <map>
#include <algorithm>
#include <cstdlib>
using namespace std;

//基本思想: 相同force值，大的id根本不用往里存。
multimap<int,int> mmap;
typedef multimap<int,int>::iterator MIT;

void PrintMap(MIT it)
{
    MIT before_it = it, after_it = it, end_it = mmap.end();
    end_it--;
    if(it == mmap.begin())
    {
        after_it++;
        cout << it->second << ' ' << after_it->second << endl;
    }
    else if(it == end_it)
    {
        before_it--;
        cout << it->second << ' ' << before_it->second << endl;
    }
    else
    {
        before_it--;
        after_it++;
        if(it->first - before_it->first < after_it->first - it->first)
            cout << it->second << ' ' << before_it->second << endl;
        else if(it->first - before_it->first == after_it->first - it->first)
        {
            cout << it->second << ' ' << min(before_it->second,after_it->second) << endl;
        }
        else
            cout << it->second << ' ' << after_it->second << endl;
    }
}

int main()
{
    mmap.insert(make_pair(1000000000,1)); // <force,id>对
    int n;
    cin >> n;
    int id,force;
    MIT it;
    for(int i = 0; i < n; i++)
    {
        cin >> id >> force;
        it = mmap.find(force);
        //原本不存在force的会员
        if(it == mmap.end())
        {
            it = mmap.insert(make_pair(force,id));
            PrintMap(it);
        }
        else //存在force的会员，比较id大小
        {
            if(it->second < id)
                cout << id << ' ' << it->second << endl;
            else
            {
                cout << id << ' ' << it->second << endl;
                mmap.erase(it);
                mmap.insert(make_pair(force,id));
            }
        }
    }
    
    return 0;
}
