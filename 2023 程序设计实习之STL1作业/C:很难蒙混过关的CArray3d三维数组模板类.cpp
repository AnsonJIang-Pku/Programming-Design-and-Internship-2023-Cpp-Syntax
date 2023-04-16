//尽量避免处理指针的指针，及返回值为**的函数，很容易绕晕并出错
//void*指针
/*
operator void* (){
    return arr;
}
*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;
template <class T>
class CArray3D
{
public:
    int dim;
    int row,clm;
    class CArray2D{
    public:
        T *arr; //尽量避免处理指针的指针，及返回值为**的函数，很容易绕晕并出错
        int ro,cl;
            
        CArray2D(int r, int c):ro(r),cl(c) {
            arr = new T[ro * cl]; //尽量避免处理指针的指针，及返回值为**的函数，很容易绕晕并出错
            memset(arr,0,sizeof(arr));
        }
        ~CArray2D() {
            delete [] arr;
        }
        T * operator[](int m){
            return arr + cl * m;
        }
        //处理memset
        operator void* (){
            return arr;
        }
    };
    //先建立一个存储指向CArray2D对象的指针数组
    CArray2D ** array2ds;
    CArray3D(int _dim, int _row, int _clm):dim(_dim),row(_row),clm(_clm) {
        array2ds = new CArray2D * [dim]; //指针数组
        for(int i = 0; i < dim; i++){
            array2ds[i] = new CArray2D(row,clm); //dim个指向CArray2D对象的指针
        }
    }
    //star star
    CArray2D & operator[](int n){ //一开始想返回指针，但会造成a[i][j][k] = No++;失效
        return *array2ds[n]; //返回第n个CArray2D对象
    }
};

CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);
void PrintA()
{
    for(int i = 0;i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for(int j = 0; j < 4; ++j) {
            for(int k = 0; k < 5; ++k)
                cout << a[i][j][k] << "," ;
            cout << endl;
        }
    }
}
void PrintB()
{
    for(int i = 0;i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for(int j = 0; j < 2; ++j) {
            for(int k = 0; k < 2; ++k)
                cout << b[i][j][k] << "," ;
            cout << endl;
        }
    }
}

int main()
{

    int No = 0;
    for( int i = 0; i < 3; ++ i ) {
        //a[i];
        for( int j = 0; j < 4; ++j ) {
            //a[j][i];
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
            //a[j][i][i];
        }
    }
    PrintA();
    memset(a[1],-1 ,20*sizeof(int));
    memset(a[1],-1 ,20*sizeof(int));
    PrintA();
    memset(a[1][1],0 ,5*sizeof(int));
    PrintA();

    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 2; ++j )
            for( int k = 0; k < 2; ++k )
                b[i][j][k] = 10.0/(i+j+k+1);
    PrintB();
    int n = a[0][1][2];
    double f = b[0][1][1];
    cout << "****" << endl;
    cout << n << "," << f << endl;
        
    return 0;
}


    /*
    //先建立一个存储指向CArray2D对象的指针数组
    CArray2D ** array2ds;
    CArray3D(int _dim, int _row, int _clm):dim(_dim),row(_row),clm(_clm) {
        array2ds = new CArray2D * [dim]; //指针数组
        for(int i = 0; i < dim; i++){
            array2ds[i] = new CArray2D; //dim个指向CArray2D对象的指针
        }
    }
    CArray2D * & operator[](int n){
        return array2ds[n]; //返回第n个指向CArray2D的指针
    }
    */
