#include <iostream>

using namespace std;

class Parent
{
public:
    virtual void display()
    {
        cout << "Parent" << endl;
    }
};

class Daughter : public Parent
{
 public:   
    void display() {
        cout << "Daughter" << endl;
    }
};

class Son : public Parent 
{
 public:   
    void display() {
        cout << "Son" << endl;
    }
};


int main(int argc, char *argv[])
{
    Parent* p;
    p = new Daughter();

    /*
        类似 "instanceof"，进行类型转换:将一个派生类转换称为基类的对象

        ps: 
            typeid,用于判断对象的类型
    */
    if (Daughter* dau = dynamic_cast<Daughter*>(p))
    {
        cout << "dau dynamic_cast to Daughter Success" << endl;
    } else {
        cout << "Not type Daughter" << endl;
    }

    if (Son* son  = dynamic_cast<Son*>(p))
    {
        cout << "dau dynamic_cast to Son Success" << endl;
    } else {
         cout << "Not type Son" << endl;
    }
    
    return 0;
}

// 在C++的编译器眼里这个class是"trivial"的type
class _A
{
public:
    int foo;
};

/**
 * “default”的作用？
 * 1. 编译器将为显式声明的default函数自动生成函数体
 * 2. 使得方法变成trivial的type，采用更有效率的操作
 * 
 * 什么是“trivial”（无意义）？
 * 告诉系统可以采用更有效率的内存操作，比如malloc、memcpy
 * 
 * “C/C++编程：trivial和non-trivial”：
 * https://blog.csdn.net/zhizhengguan/article/details/115269399
 * 
 * default 的实际影响？使方法称为trivial类型：
 * https://blog.csdn.net/qq_37026934/article/details/124362476
 */
class A
{
public:
    A() = default; // 变成trivial-type
    A(){}; // 给构造函数加上{}后这个class在C++编译器的眼里就变成"User-provided"
    ~A()  = default;
};
