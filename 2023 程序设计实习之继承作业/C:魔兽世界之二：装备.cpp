//此次在魔兽1的基础上修改，用时不到两小时，不过魔兽3可能会emmm

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
    //某种武士的特点，之后可以用继承和多态重写
    float morale; //dragon的士气，不为dragon时不动
    int loyalty; //lion的忠诚度，不为lion时不动
    
    //构造函数
    Warrior () {}
    Warrior(int health, char *str)
    {
        hp = health;
        strcpy(name,str);
    }
//预期这部分需要在魔兽3里面写开，精确到每种武士
};

//定义武器对象，这里不用详细写
class Weapon
{
public:
    char str[10]; //武器的名字
    int dmg; //武器的攻击力
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
        w_red[0].hp = hp[2]; //w_red[0] 为 iceman
        w_red[1].hp = hp[3]; //为lion
        w_red[2].hp = hp[4]; //为wolf
        w_red[3].hp = hp[1]; //为ninja
        w_red[4].hp = hp[0]; //为dragon
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
    
    int i = 0; //用来mod5，按次序制造和输出武士
//利用生命元创造武士：只要生命元大于=最小生命值，就一定可以再创造武士
    int create_warriors()
    {
        bool ifmade = 0; //判断这轮是否生成了，没生成值为1
        //在还有生命元的前提下，判断剩余生命元该用于生成哪种武士
            //标准：可以生成的武士满足减去其hp后hp_ini不为负
            if (hp_ini-w_red[i%5].hp >= 0)
            {
                //输出部分
                warriornum ++; //总武士数+1
                w_red[i%5].num ++;//生成该种类的武士数+1
                cout << setw(3) << setfill('0') << t <<' ' << "red " << w_red[i%5].name << ' ' << warriornum << ' ' << "born with strength " << w_red[i%5].hp << ',' << w_red[i%5].num << ' ' << w_red[i%5].name << ' ' << "in red headquarter" << endl;
                hp_ini -= w_red[i%5].hp;
    //魔兽2装备的增加部分，分武士类型讨论
            //red iceman
                if (i%5 == 0)
                {
                    cout << "It has a ";
                    if(warriornum % 3 == 0){
                        cout << "sword" << endl;
                    }
                    if(warriornum % 3 == 1){
                        cout << "bomb" << endl;
                    }
                    if(warriornum % 3 == 2){
                        cout << "arrow" << endl;
                    }
                }
            //red lion
                if (i%5 == 1)
                {   //lion没有武器，只有忠诚度(剩余生命元数)
                    cout << "It's loyalty is " << hp_ini << endl;
                }
            //red wolf
                //null，没有特点，没有武器
            //red ninja
                if (i%5 == 3)
                {   //有两把武器
                    cout << "It has a ";
                    if(warriornum % 3 == 0){
                        cout << "sword and a bomb" << endl;
                    }
                    if(warriornum % 3 == 1){
                        cout << "bomb and a arrow" << endl;
                    }
                    if(warriornum % 3 == 2){
                        cout << "arrow and a sword" << endl;
                    }
                }
            //red dragon
                if (i%5 == 4)
                {   //dragon有一个武器和士气
                    cout << "It has a ";
                    if(warriornum % 3 == 0){
                        cout << "sword,";
                    }
                    if(warriornum % 3 == 1){
                        cout << "bomb,";
                    }
                    if(warriornum % 3 == 2){
                        cout << "arrow,";
                    }
            //转换为浮点数除法
                    float temp = (float) hp_ini;
                    w_red[i%5].morale = temp / w_red[i%5].hp ;
                    cout << "and it's morale is ";
            
                    cout << fixed << setprecision(2) << w_red[i%5].morale << endl;
                }
                
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
        //魔兽2装备的增加部分，分武士类型讨论
                //blue lion
                if (i%5 == 0)
                {   //lion没有武器，只有忠诚度(剩余生命元数)
                    cout << "It's loyalty is " << hp_ini << endl;
                }
                //blue dragon
                if (i%5 == 1)
                {   //dragon有一个武器和士气
                    cout << "It has a ";
                    if(warriornum % 3 == 0){
                        cout << "sword,";
                    }
                    if(warriornum % 3 == 1){
                        cout << "bomb,";
                    }
                    if(warriornum % 3 == 2){
                        cout << "arrow,";
                    }
                    float temp = (float) hp_ini;
                    w_blue[i%5].morale = temp / w_blue[i%5].hp ;
                    cout << "and it's morale is ";
                    cout << fixed << setprecision(2) << w_blue[i%5].morale << endl;
                }
                //blue ninja
                if (i%5 == 2)
                {   //有两把武器
                    cout << "It has a ";
                    if(warriornum % 3 == 0){
                        cout << "sword and a bomb" << endl;
                    }
                    if(warriornum % 3 == 1){
                        cout << "bomb and a arrow" << endl;
                    }
                    if(warriornum % 3 == 2){
                        cout << "arrow and a sword" << endl;
                    }
                }
                //blue iceman
                if (i%5 == 3)
                {
                    cout << "It has a ";
                    if(warriornum % 3 == 0){
                        cout << "sword" << endl;
                    }
                    if(warriornum % 3 == 1){
                        cout << "bomb" << endl;
                    }
                    if(warriornum % 3 == 2){
                        cout << "arrow" << endl;
                    }
                }
                //blue wolf
                  //null，wolf没有特点
                
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
    }
    return 0;
}
