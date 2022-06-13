# Tutorial directory

This directory isn't used by the simple build example by default. It's here to
be used for the example in the [quick start guide](../../../docs/quick_start.md).


# C++

### [vitural 的三种用法](https://blog.csdn.net/weixin_42791450/article/details/104612131)
- 虚函数：为了实现多态。父类声明vitural方法，子类覆写，实例为调用子类实现(否则会父类)

```
virtual  void  display()
{  cout<<"A"<<endl; }


// 纯虚函数：必须在子类实现；当前类无法被实例化
virtual void show()=0;
```

- 虚继承：解决菱形继承问题(由于C++支持多继承，因此存在多“二义性”问题，“类Assistant中会有两份Person的成员name”)

```
虚继承：
class Student:virtual public Person

原理：借助内存窗口观察；

“虚基表”的概念

```
[详解C++中单继承与多继承的使用](https://www.jb51.net/article/245775.htm)


- 虚析构：在基类的析构函数前面加上virtual，使其变成虚析构，保证子类的析构函数正常调用

```
virtual  ~Person()  
{ delete []name;cout<<"Person析构"<<endl; }
```