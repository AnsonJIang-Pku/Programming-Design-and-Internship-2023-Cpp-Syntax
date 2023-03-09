//
//  main.cpp
//
//  Created by Anson Jiang on 2023/2/22.
//

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <algorithm> //min和max函数只能求两个参数的
using namespace std;
//想先实现一个红司令部的输出
bool redstop=0,bluestop=0; //判断是否已经不能制造武士，需要传参

//首先定义武士对象，希望在主程序中定义武士数组，初始化武士的名字和hp
class Warrior{
public:
    char name[10];//武士的名字
    int hp; //生命值
    int num = 0; //已经生成某种武士的数量
    //构造函数
    Warrior () {}
    Warrior(int health, char *str)
    {
        hp = health;
        strcpy(name,str);
    }
    
};


//再定义红司令部对象
class RedHead{
public:
    int hp_ini; //初始生命元
    static int t; //时间变量，为所有函数共有（包括主程序）
    int warriornum = 0; //生成了的武士编号，不等于某种武士存在的数目num
//Warrior数组初始化
    Warrior w_red[5];
    int min_hp;
    //构造函数
    RedHead(int M, int hp[5])
    {
        hp_ini = M;//初始化生命元
        //按照顺序赋予生命值
        w_red[0].hp = hp[2];
        w_red[1].hp = hp[3];
        w_red[2].hp = hp[4];
        w_red[3].hp = hp[1];
        w_red[4].hp = hp[0];
//初始化语句需要写在函数中，否则编译出错
        //为对象名字赋值，方便之后的输出
        //注意红方和蓝方顺序不一样，这里不能按顺序定义
        strcpy(w_red[0].name,"iceman");
        strcpy(w_red[1].name,"lion");
        strcpy(w_red[2].name,"wolf");
        strcpy(w_red[3].name,"ninja");
        strcpy(w_red[4].name,"dragon");
        //求出生命值最小值
        min_hp = min(min(min(min(hp[0],hp[1]),hp[2]),hp[3]),hp[4]);
    }
    //析构函数，不需要
    
    int i = 0; //用来mod5，制造和输出武士
//利用生命元按次序创造武士：只要生命元大于0，就一定可以再创造武士
    int create_warriors()
    {
        //判断这轮是否生成了，没生成值为1
        bool ifmade = 0;
        //在还有生命元的前提下，判断剩余生命元该用于生成哪种武士
            //标准：可以生成的武士满足减去其hp后hp_ini不为负
            if (hp_ini-w_red[i%5].hp >= 0)
            {
                //输出部分
                warriornum ++; //总武士数+1
                w_red[i%5].num ++;//生成该种类的武士数+1
                cout << setw(3) << setfill('0') << t <<' ' << "red " << w_red[i%5].name << ' ' << warriornum << ' ' << "born with strength " << w_red[i%5].hp << ',' << w_red[i%5].num << ' ' << w_red[i%5].name << ' ' << "in red headquarter" << endl;
                hp_ini -= w_red[i%5].hp;
                i++;
                return ifmade;
            }
            else{
                i++;
                ifmade = 1;
                return ifmade;
            }
    }
    
};

//再定义蓝司令部对象
class BlueHead{
public:
    int hp_ini; //初始生命元
    int warriornum = 0; //生成了的武士编号，不等于某种武士存在的数目num
//Warrior数组初始化
    Warrior w_blue[5];
    int min_hp;
    //构造函数
    BlueHead(int M, int hp[5])
    {
        hp_ini = M;//初始化生命元
        //按照顺序赋予生命值
        w_blue[0].hp = hp[3];
        w_blue[1].hp = hp[0];
        w_blue[2].hp = hp[1];
        w_blue[3].hp = hp[2];
        w_blue[4].hp = hp[4];
//初始化语句需要写在函数中，否则编译出错
        //为对象名字赋值，方便之后的输出
        //注意红方和蓝方顺序不一样，这里不能按顺序定义
        strcpy(w_blue[0].name,"lion");
        strcpy(w_blue[1].name,"dragon");
        strcpy(w_blue[2].name,"ninja");
        strcpy(w_blue[3].name,"iceman");
        strcpy(w_blue[4].name,"wolf");
        //求出生命值最小值
        min_hp = min(min(min(min(hp[0],hp[1]),hp[2]),hp[3]),hp[4]);
    }
    //析构函数，不需要
    
    int i = 0; //用来mod5，制造和输出武士

//利用生命元按次序创造武士：只要生命元大于0，就一定可以再创造武士
    int create_warriors()
    {
//判断这轮是否生成了，没生成值为1
        bool ifmade=0;
            //在还有生命元的前提下，判断剩余生命元该用于生成哪种武士
            //标准：可以生成的武士满足减去其hp后hp_ini不为负
            if (hp_ini-w_blue[i%5].hp >= 0)
            {
                //输出部分
                warriornum ++; //总武士数+1
                w_blue[i%5].num ++;//生成该种类的武士数+1
                cout << setw(3) << setfill('0') << RedHead::t <<' ';
                cout << "blue " << w_blue[i%5].name << ' ' << warriornum << ' ' << "born with strength "  << w_blue[i%5].hp << ',' << w_blue[i%5].num << ' ' << w_blue[i%5].name << ' ' << "in blue headquarter" << endl;
                hp_ini -= w_blue[i%5].hp;
                i++;
                return ifmade;
            }
            else{
                i++;
                ifmade = 1;
                return ifmade;
            }
    }
    
};




//静态成员变量必须显式初始化，否则编译错
int RedHead:: t = 0;

int main() {
    int casenum; //需要执行的测试数据组数
    cin >> casenum ;//输入组数
    
//大循环，总共执行的次数
    int totnum = 0;
    while(casenum != 0)
    {
        totnum ++;
        int M; //生命元数量，题目中记为M (1<=M<=10000)

//red 为红司令部，需要初始化
        cin >> M; //输入初始生命元
        int hp[5]; //读取生命值数据
        for(int i=0;i<=4;i++)
        {
            cin >> hp[i];
        }
        //初始化red司令部，赋予生命元和武士生命值
        RedHead red(M, hp);
        //初始化blue司令部
        BlueHead blue(M,hp);
        
//输出
        cout << "Case:"<< totnum <<endl;
        //希望利用RedHead里面的输出函数进行输出
        //red.create_warriors();
        
        //只要有一个没停，就继续输出；停的标准是变为1
        while (redstop == 0 || bluestop == 0)
        {
            //在司令部里生成武士，并输出生成的结果
//利用stop真假判断是否还要继续生成（输出）武士
            if(redstop == 0) //red没停，还有足够的生命元
            {
                //一开始忘记等于号了
                if(red.hp_ini >= red.min_hp)
                {
                    while (red.create_warriors()) { }
                }
                else
                {
                    //输出 red headquarter stops making warriors
                    cout << setw(3) << setfill('0') << RedHead::t <<' ' << "red headquarter stops making warriors" << endl;
                    redstop = 1;
                }
            }
            
            //蓝司令部也没停
            if(bluestop == 0)
            {
                if(blue.hp_ini >= blue.min_hp)
                {
                    while (blue.create_warriors()) { }
                }
                else
                {
                    //输出 blue headquarter stops making warriors
                    cout << setw(3) << setfill('0') << RedHead::t <<' ' << "blue headquarter stops making warriors" << endl;
                    bluestop = 1;
                }
            }
//没考虑的：如果本轮双方都没生成，但都还可以生成武士，t暂时不加
            RedHead::t++;
        }
        
        //出循环
        casenum --;
        redstop=0; bluestop=0;
        RedHead::t=0;
        //cout << "casenum:" << casenum << endl;
    }
    return 0;
}
