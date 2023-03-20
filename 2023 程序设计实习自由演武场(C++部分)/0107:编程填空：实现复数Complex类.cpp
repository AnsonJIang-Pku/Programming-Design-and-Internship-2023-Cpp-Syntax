#include <iostream>
using namespace std;
class Complex
{
public:
    int real;
    int imag;
    Complex() {}
    Complex(char* p)
    {
        real = p[0] - '0';
        imag = p[2] - '0';
    }
    Complex(int n)
    {
        real = n;
        imag = 0;
    }
    friend ostream& operator<< (ostream& os, const Complex& c)
    {
        if(c.imag == 0)
        {
            os << c.real;
        }
        else{
            if (c.real == 0){
                os << c.imag << "i";
            }
            else{
                os << c.real << "+" << c.imag << "i";
            }
        }
        return os;
    }
    Complex operator+(const Complex& c)
    {
        Complex tmp(*this);
        tmp.real = real + c.real;
        tmp.imag = imag + c.imag;
        return tmp;
    }
    Complex operator-(const Complex& c)
    {
        Complex tmp(*this);
        tmp.real = real - c.real;
        tmp.imag = imag - c.imag;
        return tmp;
    }
    Complex operator*(const Complex& c)
    {
        Complex tmp(*this);
        tmp.real = real * c.real - imag * c.imag;
        tmp.imag = real * c.imag + imag * c.real;
        return tmp;
    }
    Complex& operator+=(const Complex & c)
    {
        real = real + c.real;
        imag = imag + c.imag;
        return *this;
    }
    Complex& operator-=(int n)
    {
        real = real - n;
        return *this;
    }
    Complex& operator*=(Complex& c)
    {
        Complex tmp(*this);
        tmp.real = real * c.real - imag * c.imag;
        tmp.imag = real * c.imag + imag * c.real;
        *this = tmp;
        return *this;
    }
};
int main() {
	Complex c1;
	Complex c2("3+2i"); // 用字符串初始化时，只需考虑"a+bi"的形式，其中a和b都是1位数字
	Complex c3(c2);
	Complex c4(-15);
	cout << c2 << endl;
	cout << c3 << endl;
	cout << c4 << endl;
	cout << c2 + c4 << endl;
	cout << c2 - c3 << endl;
	cout << c2 * c3 << endl;
	c2 += c4;
	cout << c2 << endl;
	c2 -= -12;
	cout << c2 << endl;
	c3 *= c3;
	cout << c3 << endl;
	return 0;
}
