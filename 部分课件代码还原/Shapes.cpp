#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
class CShape
{
public:
    virtual void PrintInfo() = 0;
    virtual double Area() = 0;
};

class CRectangle:public CShape{
public:
    int w, h;
    CRectangle(int _w, int _h):w(_w), h(_h) { }
    virtual double Area(){
        return w*h;
    }
    virtual void PrintInfo(){
        cout << "Rectangle:" << Area() << endl;
    }
};

class CCircle:public CShape{
public:
    int r;
    CCircle(int _r):r(_r) { }
    virtual double Area(){
        return M_PI * r * r;
    }
    virtual void PrintInfo(){
        cout << "Circle:" << Area() << endl;
    }
    
};

class CTriangle:public CShape{
public:
    int a,b,c;
    CTriangle(int _a, int _b, int _c):a(_a),b(_b),c(_c) { }
    virtual double Area(){
        double p = (a+b+c)/2.0;
        return sqrt(p * (p-a) * (p-b) * (p-c));
    }
    virtual void PrintInfo(){
        cout << "Triangle:" << Area() << endl;
    }
};

CShape * pShapes[100];

int MyCompare(const void* p1, const void *p2){
    //pShapes中存储的是CShape*类型的指针,而qsort传入的第一个参数是pShapes,其类型为CShape **
    //因此p1和p2都应该强制转换为CShape**并解引用
    CShape **ps1, **ps2;
    ps1 = (CShape **)p1;
    ps2 = (CShape **)p2;
    //*ps1为pShapes数组中的元素，即CShape*类型; CShape*类型要用->调用属性
    return (int)((*ps1)->Area() - (*ps2)->Area());
}

int main()
{
    int n;
    cin >> n;
    char c;
    CRectangle *pr; CTriangle *pt; CCircle *pc;
    
    for(int i = 0; i < n; i++){
        cin >> c;
        if(c == 'R'){
            int w,h;
            cin >> w >> h;
            pr = new CRectangle(w,h);
            pShapes[i] = pr;
        }
        else if(c == 'C'){
            int r;
            cin >> r;
            pc = new CCircle(r);
            pShapes[i] = pc;
        }
        else{
            int a,b,c;
            cin >> a >> b >> c;
            pt = new CTriangle(a,b,c);
            pShapes[i] = pt;
        }
    }
    
    qsort(pShapes, n, sizeof(CShape *), MyCompare);
    for(int i = 0; i < n; i++){
        pShapes[i]->PrintInfo();
    }
    return 0;
}
