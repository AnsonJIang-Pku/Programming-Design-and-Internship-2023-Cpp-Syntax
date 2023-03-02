#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
private:
    char Name[21];
    int age;
    int num;
    int score_1, score_2, score_3, score_4;
    double avescore;
public:
    void input()
    {
        scanf("%[^,]",Name);//并没有输入逗号进去
        getchar();
        scanf("%d,%d,%d,%d,%d,%d",&age,&num,&score_1,&score_2,&score_3,&score_4);
    }
    void calculate()
    {
        avescore = (score_1 + score_2 + score_3 + score_4)*1.0 /4;
    }
    void output()
    {
        printf("%s,%d,%d,",Name,age,num);
        cout << avescore;
    }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}
