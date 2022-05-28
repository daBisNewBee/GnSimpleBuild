
# include <iostream>
# include "construct.h"

using namespace std;

/**
 * @brief C++构造函数（详细）
 * 
 * https://blog.csdn.net/qq_45100518/article/details/106722451
 * 
 */
namespace edge_cons {
    class A
    {
    private:
    public:
        int a,b;
        A(){
            cout << "A默认构造函数" << endl;
        };
        /**
         * @brief Construct a new A object
         * 
         * 关键字explicit？ google 建议加上，避免不合时宜的类型转换
         * 
         * 加不加“explicit”的区别？
         * 只需用于类内的单参数构造函数前面；
         * 用于禁止类型转化。
         * 
         * 加了explicit，只能 A a = A(1)
         * 去掉explicit，A a = {1}
         * 
         * @param x 
         */
        A(int x):a(x) {
             cout << "A转换构造函数1" << endl;
        }
        A(int x, int y):a(x),b(y){
            cout << "A转换构造函数2" << endl;
        }
        // 建议使用“const”，保证输入参数安全，不改变被复制对象的值
        A(const A& _A) { // 形参为对象的常引用
            // _A.a = 1;
            a = _A.a;
            b = _A.b;
            cout << "A复制构造函数" << endl;
        }
        ~A(){
            // cout << "析构函数" << endl;
        }
        void print() {
            cout << "a = " << a << ", b = " << b << endl;
        }
        // 想想这里为什么也要“&”？防止拷贝构造函数的低效率！
        A& getSelf() {
            return *this;  // 返回对象本身
        }
    };

    class B
    {
    private:
        /* data */
    public:
        int b;
        A _A;

        B(){
            cout << "B默认构造函数" << endl;
        }
        B(int x):b(x),_A(2*x){
            cout << "B转换构造函数" << endl;
        }
        // 指明成员对象"_A"初始化方式：这里要加"_A(_B._A)"！才会显示调用A的复制构造函数，否则只会调用A的默认构造函数
        B(const B& _B):_A(_B._A) {
            b = _B.b;
        }
        ~B(){}
    };

    class C:public A
    {
    private:
        /* data */
    public:
        int c;
        C() {
            cout << "C默认构造函数" << endl;
        }
        // 指明基类"_A"的初始化方式：这里指定了“A(3)”才会执行A的转换构造，否则只会调用A的默认构造
        C(int x):c(x),A(3) {
             cout << "C转换构造函数" << endl;
        }
    };
    
}

using namespace edge_cons;

/**
 * @brief  
 * 
 * 使用引用参数的主要原因：
 * 1. 方便修改调用函数中的数据对象
 * 2. 高效率！传引用更快！不会存在内存中的临时拷贝现象，有些对象较大，触发的拷贝构造函数很耗时且没必要！
 * 
 * @param _A
 */
void transA(A& _A) { // 需要加“&”，否则会触发“类的复制构造函数”
    cout << "start print." << endl;
    // _A.a = 100; // 确实可以修改原对象！
    _A.print();
    cout << "end print." << endl;
}

/**
 * @brief 复制构造函数
 * 
 */
void copyConstr() {

    cout << "利用复制构造函数初始化对象:" << endl;
    
    A a1 = {1,2};

    cout << "A a2(a1)" << endl;
    A a2(a1);

    cout << "A a3=a1" << endl;
    A a3=a1;

    cout << "函数输入参数，需要是对象的引用:" << endl;
    A a4 = {10};
    transA(a4);

    cout << "函数返回参数，若是类的对象，会触发类的复制构造函数" << endl;
    a4.getSelf();
}

/**
 * @brief 封闭类的复制构造函数
 * 
 * ps: 封闭类：包含成员对象的类
 * 
 */
void encloseCopyContru() {

    cout << "封闭类的复制构造函数:" << endl;

    cout << "B b1(3)" << endl;
    B b1(3);

    cout << "B b2(b1)" << endl;
    B b2(b1);

    cout << b2.b << "," << b2._A.a << endl;
}

void extendCopyContru() {
    cout << "继承类的复制构造函数:" << endl;
    cout << "C c1" << endl;
    C c1;
    cout << c1.c << "," << c1.a << endl; // TODO: 2,3 ?

    cout << "C c2(3)" << endl;
    C c2(3);
    cout << c2.c << "," << c2.a << endl;
}

void edge_cons_entrance() {

    cout << "1. A a" << endl;
    A a; // 默认构造函数

    cout << "2. A a0()" << endl;
    A a0(); // 没有创建对象

    cout << endl;

    /**
     * @brief "转换构造函数"可生成临时对象
     * 
     */
    cout << "3. A a1(1) or A a1={1}" << endl;
    // A a1(1);
    A a1={1};

    cout << "4. A a2(1,2) or A a2={1,2}" << endl;
    // A a2(1,2);
    A a2={1,2}; // 编译器将数字类型转换成了临时对象，然后复制给a1、a2

    cout << endl;

    /**
     * @brief 注意在定义数组时，触发了哪个构造函数?
     * 
     */
    cout << "A array1[2]" << endl;
    A array1[2];

    cout << "A array2[2] = {1,2}" << endl;
    A array2[2] = {{1},{2}};

    cout << "A array3[2] = {{1,2},{3,4}}" << endl;
    A array3[2] = {{1,2},{3,4}};

    cout << "A array4[2] = {{1,2}}" << endl;
    A array4[2] = {{1,2}};

    cout << endl;

    cout << "定义指针时,new了对象才会触发构造函数的调用" << endl;
    A* ptr[3]={new A(1), new A(1,2)};

    cout << endl;

    copyConstr();

    encloseCopyContru();

    extendCopyContru();
}