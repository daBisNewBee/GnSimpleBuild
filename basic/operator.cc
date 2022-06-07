#include "utils.h"

#include <iostream>

using namespace std;

/**
 * @brief 
 * C++ 符号重载:
 * https://blog.csdn.net/m0_37579906/article/details/82054358
 */
class Complex
{

// 友元函数
friend istream& operator >>(istream& in, Complex& c);
friend ostream& operator <<(ostream& out, Complex& c);

private:
    double x;
    double y;
public:
    Complex(double _x = 0, double _y = 0)
    {
        x = _x;
        y = _y;
    }
    ~Complex(){}

    void print()
    {
        cout << "x = " << this->x << ", y = " << this->y;
    }

    // 符号重载语法: 返回值类型 operator 符号(参数列表);
    Complex operator+(Complex c)
    {
        return Complex(this->x + c.x, this->y + c.y);
    }

    // "()" 符号重载
    double operator()(int a, int b)
    {
        return a + b;
    }
};


istream& operator >>(istream& in, Complex& c)
{
    in >> c.x >> c.y;
    return in;
}

ostream& operator <<(ostream& out, Complex& c)
{
    out << c.x << "+" << c.y << "i" << endl;
    return out;
}

void operatorTest(){
    Complex a,b;
    cin >> a >> b;
    Complex c = a + b;
    cout << c << endl;

    // Complex c1(1,3), c2(3,4);
    // Complex c3 = c1 + c2;
    // c3.print();
    // cout << "operator() result = " << c3(10,20);
}