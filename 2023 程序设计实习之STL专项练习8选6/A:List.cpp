#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <cstdlib>

using namespace std;
//希望通过类来实现给list编号
//由于所给的id不一定为连续整数，所以有必要这样做（而不是直接用vector）
class MyList{
public:
    int id;
    list<int> lst;
    MyList(int _id):id(_id) { }
};

template<class T>
void PrintList(T s, T e)
{
    for(; s!=e; s++){
        cout << *s << ' ';
    }
    cout << endl;
}

int main()
{
    string cmd;
    int n;
    cin >> n;
    vector<MyList> lst_array;
    for(int i = 0; i < n; i++)
    {
        int tag;
        cin >> cmd;
        
        if(cmd == "new"){
            cin >> tag;
            MyList lst(tag);
            lst_array.push_back(lst);
        }
        
        if(cmd == "add"){
            cin >> tag;
            int j;
            for(j = 0; j < lst_array.size(); j++)
            {
                if(lst_array[j].id == tag) break;
            }
            int integer;
            cin >> integer;
            lst_array[j].lst.push_back(integer);
        }
        
        if(cmd == "merge"){
            int id1,id2;
            cin >> id1 >> id2;
            if(id1 != id2)
            {
                int j,k;
                for(j = 0; j < lst_array.size(); j++)
                {
                    if(lst_array[j].id == id1) break;
                }
                for(k = 0; k < lst_array.size(); k++)
                {
                    if(lst_array[k].id == id2) break;
                }
                lst_array[j].lst.merge(lst_array[k].lst);
            }
        }
        
        if(cmd == "unique"){
            int tag;
            cin >> tag;
            int j;
            for(j = 0; j < lst_array.size(); j++)
            {
                if(lst_array[j].id == tag) break;
            }
            lst_array[j].lst.sort();
            lst_array[j].lst.unique();
        }
        
        if(cmd == "out"){
            int tag;
            cin >> tag;
            int j;
            for(j = 0; j < lst_array.size(); j++)
            {
                if(lst_array[j].id == tag) break;
            }
            lst_array[j].lst.sort();
            list<int>::iterator st,ed;
            st = lst_array[j].lst.begin();
            ed = lst_array[j].lst.end();
            PrintList(st, ed);
        }
    }
    
    return 0;
}


/*
 vector<list<int> > list_array; //下标和list id相差1
 string cmd;
 int n;
 int totnum = 0; //记录已存在的list数
 cin >> n;
 for(int i = 0; i < n; i++)
 {
     cin >> cmd;
     if(cmd == "new"){
         list<int> lst;
         list_array.push_back(lst);
     }
 }

 */
