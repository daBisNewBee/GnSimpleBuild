#include "utils.h"

using std::cout;
using std::endl;

/**
 * @brief 智能指针
 * 
 * C++ 中有四种智能指针：
 *  1. auto_ptr
 *  2. unique_ptr
 *  3. shared_ptr
 *  4. weak_ptr
 *  其中后三个是 C++11 支持，第一个已经被 C++11 弃用且被 unique_ptr 代替，不推荐使用。
 */

class Vec3
{
public:
    int x, y, z;
    Vec3():x(0),y(0),z(0) {
        cout << "Vec3()\n";
    }
    Vec3(int _x, int _y, int _z):x(_x),y(_y),z(_z) {
        cout << "Vec3() 2\n";
    }
    friend std::ostream& operator<<(std::ostream& os, Vec3& v)
    {
        return os << '{' << "x:" << v.x << " y:" << v.y << " z:" << v.z << '}';
    }
    void show() {
        cout << "show()\n";
    }
    ~Vec3(){
        std::cout << "~Vec3() called.\n";
    }
};

class Socket:public std::enable_shared_from_this<Socket>
{
public:
    Socket(/* args */){
            cout << "Socket() called\n";
    };
    ~Socket(){
            cout << "~Socket() called\n";
    };
    // 关闭资源句柄
    void close(){
        cout << "Socket close() called\n";
    }

    // 在类中返回包裹当前对象（this）的一个 std::shared_ptr 对象给外部使用
    std::shared_ptr<Socket> getSelf() {
        return shared_from_this();
    }
};

/**
 * @brief 
 * 
 * auto_ptr 已被弃用！ 
 * 
 * 缺点：
 * 拷贝构造或者赋值构造后，原来的对象内容会丢失，对其的引用会出错！
 * 
 */
void auto_ptr_test() {
    /*
    // TODO: 没有找到禁用的地方. "warning: 'template<class> class std::auto_ptr' is deprecated [-Wdeprecated-declarations]"
    //初始化方式1
    std::auto_ptr<int> ap1(new int(8));
    //初始化方式2
    std::auto_ptr<int> ap2;
    ap2.reset(new int(8));

     //测试拷贝构造
    std::auto_ptr<int> ap1(new int(8));
    std::auto_ptr<int> ap2(ap1);
    if (ap1.get() != NULL)
    {
        std::cout << "ap1 is not empty." << std::endl;
    }
    else
    {
        std::cout << "ap1 is empty." << std::endl;
    }
    if (ap2.get() != NULL)
    {
        std::cout << "ap2 is not empty." << std::endl;
    }
    else
    {
        std::cout << "ap2 is empty." << std::endl;
    }
    
    //测试赋值构造
    std::auto_ptr<int> ap3(new int(8));
    std::auto_ptr<int> ap4;
    ap4 = ap3;
    if (ap3.get() != NULL)
    {
        std::cout << "ap3 is not empty." << std::endl;
    }
    else
    {
        std::cout << "ap3 is empty." << std::endl;
    }

    if (ap4.get() != NULL)
    {
        std::cout << "ap4 is not empty." << std::endl;
    }
    else
    {
        std::cout << "ap4 is empty." << std::endl;
    }
    // ap1 is empty.
    // ap2 is not empty.
    // ap3 is empty.
    // ap4 is not empty.
    */
}


/**
 * @brief 
 * 作为对 std::auto_ptr 的改进，
 * std::unique_ptr 对其持有的堆内存具有唯一拥有权，
 * 也就是 std::unique_ptr 不可以拷贝或赋值给其他对象，
 * 其拥有的堆内存仅自己独占，std::unique_ptr 对象销毁时会释放其持有的堆内存。
 */
void unique_ptr_test() {
    std::unique_ptr<Vec3> vec(new Vec3);

    // 初始化方式1
    std::unique_ptr<int> up1(new int(123));
    // 初始化方式2
    std::unique_ptr<int> up2;
    up2.reset(new int(123));
    // 推荐：初始化方式3（-std=c++14）
    std::unique_ptr<int> up3 = std::make_unique<int>(123);

    // 如何将一个 std::unique_ptr 对象持有的堆内存转移给另外一个呢? move!
    std::unique_ptr<int> up4(std::move(up1));

    cout << ((up1.get() == nullptr) ? "up1 == null" : "up1 != null") << endl;

    std::unique_ptr<int> up5;
    up5 = std::move(up4);

    cout << ((up4.get() == nullptr) ? "up4 == null" : "up4 != null") << endl;

    // 创建10个int类型的堆对象
    std::unique_ptr<int[]> up_array(std::make_unique<int[]>(10));
    for (size_t i = 0; i < 10; i++)
    {
        up_array[i] = i;
    }
    for (size_t i = 0; i < 10; i++)
    {
        cout << up_array[i] << " ";
    }
    cout << endl;
    
    // 自定义智能指针对象持有的资源的释放函数: 
    // 智能指针对象在析构时只会释放其持有的堆内存（调用 delete 或者 delete[]），但是对象还有其他需要回收的资源（fd等）
    auto deletor = [](Socket *pSocket)
    {
        pSocket -> close();
        delete pSocket;
    };
    /**
     * @brief 自定义 std::unique_ptr 的资源释放函数其规则是：
     *      std::unique_ptr<T, DeletorFuncPtr>
     * @param Socket 要释放的对象类型
     * @return std::unique_ptr<Socket, void(*)(Socket *pSocket)>  是一个自定义函数指针
     */
    std::unique_ptr<Socket, void(*)(Socket *pSocket)> upSocket(new Socket(), deletor);
    std::unique_ptr<Socket, decltype(deletor)> upSocket2(new Socket(), deletor); // 等价上面. "decltype"来自动推导deletor的类型
}

void shared_ptr_test(){
    // 初始化方式三种，和unique_ptr一样
    std::shared_ptr<int> sp = std::make_shared<int>(123);

    std::shared_ptr<Socket> sp1(new Socket());
    assert(sp1.use_count() == 1); // use_count ? 有多少个智能指针对象共享所有权

    std::shared_ptr<Socket> sp2(sp1);
    assert(sp1.use_count() == 2);

    sp2.reset();
    assert(sp1.use_count() == 1);
    {
        std::shared_ptr<Socket> sp3 = sp1;
        assert(sp1.use_count() == 2);
    }
    assert(sp1.use_count() == 1);

    std::shared_ptr<Socket> sp4 = sp1->getSelf();
    assert(sp1.use_count() == 2);

    cout << "1111\n";
    Socket socket;
    std::shared_ptr<Socket> sp5 = socket.getSelf(); // 这里会crash
    cout << "2222";
}

void zhiNengPtrTest()
{
    cout << "start zhiNengPtrTest\n";
    auto_ptr_test();
    unique_ptr_test();
    shared_ptr_test();
    // // Use the default constructor.
    // std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();

    // // Use the constructor that matches these arguments
    // std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0,1,2);

    // // Create a unique_ptr to an array of 5 elements
    // std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);
    // std::cout << " make_unique<Vec3>(): " << *v1 << '\n'
    //           << " make_unique<Vec3>(0,1,2): " << *v2 << '\n'
    //           << " make_unique<Vec3[]>(5): " << '\n';

    // for (size_t i = 0; i < 5; i++)
    // {
    //     std::cout << "  " << v3[i] << '\n';
    // }
    cout << "end zhiNengPtrTest\n";
}