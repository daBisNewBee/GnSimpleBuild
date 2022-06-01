#include "template.h"
#include "iostream"

// C++中 模板Template的使用: 
// https://blog.csdn.net/baidu_16370559/article/details/120224752

using namespace std;

/**
 * @brief 1. 类模板：
 * 
 * template<class  形参名，class 形参名，…>   class 类名
    { ... 
    };
 * 
 * @tparam T 
 */
template <class T>
class Apple {
public:
    T a;
    T b;
    T hy(T c, T &d);
};

// 多个形参
template<class T1, class T2>
class Pear {
public:
    Pear();
    T1 g(T1 a, T2 b);
};

template<class T1, class T2>
Pear<T1, T2>::Pear()
{

}

template<class T1, class T2>
T1 Pear<T1, T2>::g(T1 a, T2 b)
{
    return a + b;
}

// "默认模板参数"需要从右到左依次
template <class T1 = int, int i = 0, class T2 = string>
class ctem
{
public:
    T1 t1;
    void fun1(T2 t2);
};

template <class T1, int i, class T2>
void ctem<T1,i,T2>::fun1(T2 t2) {
    cout << "fun1 called. t2 = " << t2 << endl;
}

/**
 * @brief 2. "函数模板"的格式：
 *        template<parameter-list> function-declaration
 * 
 * 函数模板就像是一种"契约"，任何满足该契约的类型都可以做为模板实参。
 * 而契约就是函数实现中，模板实参需要支持的各种操作。
 * 上面 swap 中 T 需要满足的契约为："支持拷贝构造和赋值"。
 * 
 * @tparam T 
 * @param a 
 * @param b 
 */
template<typename T> void mySwap(T &a, T &b) { //"typename"用来声明 T 是一个模板参数
    T tmp{a};
    a = b;
    b = tmp;
}

template<typename T> void myPrint(const T &r) {
    cout << r << endl;
}

typedef int myInt;  // 旧  新

/**
 * @brief 3. 别名模板(alias template)
 * 
 * C++11引入，与typedef的顺序相反，解决typedef无法使用模板参数的问题
 * 
 */
using myInt2 = int; // 新 = 旧

template<typename T, typename U>
struct A;

// C 为 A<T, int>的别名
template<typename T> using C = A<T, int>;

// TODO： 这里有个历史原因，需要再消化下
template<typename T>
struct B
{
    typedef A<T,int> type;
};

template<typename T> using D = typename B<T>::type;

// 函数模板
template<class T>
constexpr T pi_fn()
{
    return T(3.1415926535897932385);
}

/**
 * @brief 4. 变量模板
 * 
 * C++14新引入,语法功能上它相当于一个没有参数但是有返回值的函数模板
 * 相对于后者，变量模板在语法上更清晰，更能反映编程者的意图
 * 
 * @tparam T 
 */
template<class T>
constexpr T pi = T(3.1415926535897932385); // 有点像lamda？

#include <iomanip>


void edge_temlpate_entrance() {
    int a = 2, b = 3;
    // 调用 swap(a,b)时，发生了隐式实例化
    mySwap(a, b); // 自动推导
    mySwap<int>(a, b); // 显性类型推导
    cout << "a = " << a << ", b = " << b << endl;

    double c = 1.1, d = 2.2;
    mySwap(c, d);
    cout << "c = " << c << ", d = " << d << endl;

    myPrint(1);

    myPrint('c');

    Pear<float, int> ta;
    cout << ta.g(1.1, 2) << endl;

    ctem<> tem;
    tem.fun1("q");

    cout << pi_fn<int>() << pi<int> << endl;
    cout << setprecision(10) << pi<float> << endl;
    cout << setprecision(10) << pi<double> << endl;
}


