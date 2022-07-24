#include "utils.h"

using std::cout;
using std::endl;

/**
 * @brief 智能指针:
 * 1. 管理的目标是“堆对象”
 * 2. 将普通指针封装为“栈对象”，利用“栈对象”自动析构的特性，释放普通指针对象
 * 
 * 
 * C++ 中有四种智能指针：
 *  1. auto_ptr
 *      弃用。容易误用：当复制一个对象后，原对象所持有的堆内存对象也会转移给复制出来的对象，造成原对象指向NULL，引发空指针
 * 
 *  2. unique_ptr
 *     对堆对象有独占权；
 *     实例化：std::make_unique
        如何将一个 std::unique_ptr 对象持有的堆内存转移给另外一个呢? move!
        std::unique_ptr<int> up4(std::move(up1));

 *  3. shared_ptr
       单个资源可以在多个 std::shared_ptr 间共享
       use_count 判断共享数量

 *  4. weak_ptr
       不会控制资源声明周期，弱引用。

 *  其中后三个是 C++11 支持，第一个已经被 C++11 弃用且被 unique_ptr 代替，不推荐使用。
 * 
 * 
 * 前置声明 与 include：
 * 尽量前置声明class xxx，而不是include x.h
 * 类中尽量采用指针或引用方式调用其它类，这样就可以只声明 class xxx 了。并且这也符合资源最优利用，更利于使用多态。
 * 
 * 参考：
 * 深入实践C++11智能指针：
 * https://blog.csdn.net/code_peak/article/details/119722167
 * 
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

    void doSth() {

    }

    // 在类中返回包裹当前对象（this）的一个 std::shared_ptr 对象给外部使用
    std::shared_ptr<Socket> getSelf() {
        return shared_from_this();
    }
};


// weak_ptr 的使用场景
class Subscriber {};

class SubcribeManager {
    public:
        void publish() {
            for (auto &iter : m_subscribers)
            {
                if (!iter.expired())
                {
                    // 给订阅者发消息
                }
                
            }
            
        }
    private:
        std::vector<std::weak_ptr<Subscriber>> m_subscribers;
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
    cout << "unique_ptr_test end.\n";
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
    // std::shared_ptr<Socket> sp5 = socket.getSelf(); // 这里会crash
    /*
    智能指针最初设计的目的就是为了管理堆对象的（即那些不会自动释放的资源）!
    terminate called after throwing an instance of 'std::bad_weak_ptr'
    what():  bad_weak_ptr
    */
    cout << "2222\n";
    cout << "shared_ptr_test end.\n";
}

void weak_ptr_test() {
    // "无论通过何种方式创建 std::weak_ptr 都不会增加资源的引用计数, use_count都是1"
    std::shared_ptr<Socket> sp1(new Socket);
    assert(sp1.use_count() == 1);

    std::weak_ptr<Socket> sp2(sp1);
    assert(sp1.use_count() == 1);

    std::weak_ptr<Socket> sp3 = sp1;
    assert(sp1.use_count() == 1);

    std::weak_ptr<Socket> sp4 = sp2;
    assert(sp1.use_count() == 1);

    if (sp4.expired())
    {
        std::shared_ptr<Socket> spGet = sp4.lock();
        if (spGet)
        {       
            // 操作
        }
    }

    if (sp1)
    {
        sp1->doSth();
        (*sp1).doSth();
    }

    if (!sp1)
    {
        /* code */
    }
    
    /*
    编译错误！没有重写 operator-> 和 operator* 方法
    if (sp2)
    {
        sp2->doSth();
        (*sp2).doSth();
    }

    if (!sp2)
    {
    }
    */
    
    // 使用场景： 订阅者-发布者、Session对Connection的使用。
    // 那些资源如果可能就使用，如果不可使用则不用的场景，它不参与资源的生命周期管理
    cout << "weak_ptr_test end.\n";
}

// std_unique_ptr 的大小总是和原始指针大小一样，std::shared_ptr 和 std::weak_ptr 大小是原始指针的一倍。
void commonTest() {
    std::shared_ptr<int> spInt;
    std::shared_ptr<std::string> spStr;
    spStr.reset(new std::string());

    std::unique_ptr<int> upInt;
    std::weak_ptr<int> wpInt;
    int *p = new int(100);

    cout << "size of shared_ptr<int> " << sizeof(spInt) << endl;
    cout << "size of shared_ptr<string> " << sizeof(spStr) << endl;
    cout << "size of unique_ptr<int> " << sizeof(upInt) << endl;
    cout << "size of weak_ptr<int> " << sizeof(wpInt) << endl;
    cout << "size of normal pointer " << sizeof(p) << endl;
    /**
     * @brief 
     *  size of shared_ptr<int> 8
        size of shared_ptr<string> 8
        size of unique_ptr<int> 4
        size of weak_ptr<int> 8
        size of normal pointer 4
     */
}

void autoTest() {
    string s("Hello world");
    // 自动推断类型发生在“编译期”，所以auto不会影响效率
    for(auto c:s) {
        // 无法修改。创建拷贝
        c='t';
    }
    cout << "use auto c, s = " << s << endl;
    for (auto &c : s)
    {
        // 修改了值
        c='t';
    }
    cout << "use auto &c, s = " << s << endl;
    for (auto &&c : s)
    {
        // 修改了值。一般用这种！为啥？TODO
        c='t';
    }
    cout << "use auto &&c, s = " << s << endl;

    for (const auto &c : s)
    {
        // c='t';  // 只读range中的元素！
    }
    
}

void zhiNengPtrTest()
{
    cout << "start zhiNengPtrTest\n";
    auto_ptr_test();
    unique_ptr_test();
    shared_ptr_test();
    weak_ptr_test();
    commonTest();
    autoTest();
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