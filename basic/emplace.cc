#include "utils.h"
#include <string>
#include <iostream>
#include <set>
#include <algorithm> // 用于“for_each”

using namespace std;

class SBook
{
public:
    SBook():bookName(""),price(0)
    {
        std::cout << "default construct: " << bookName << std::endl;
    }

    SBook(std::string _bookName, int _price):bookName(_bookName),price(_price)
    {
         std::cout << "construct: " << bookName << std::endl;
    }

    SBook(const SBook& rhs) : bookName(rhs.bookName),price(rhs.price)
    {
          std::cout << "copy construct: " << bookName << std::endl;
    }

    ~SBook(){
          std::cout << "deconstruct: " << bookName << std::endl;
    }

    bool operator <(const SBook& rhs) const
    {
        return bookName < rhs.bookName;
    }

public:
    std::string bookName;
    int price;
};


void emplaceTest() {
    vector<SBook> books;
    books.reserve(100);

    std::cout << "push_back:" << endl;
    books.push_back(SBook("c++从入门到放弃", 1));
    std::cout << endl;

    /**
     * @brief 验证：“使用emplace比常规的push_back少调用了一次复制构造函数”
     * 
     */
    std::cout << "emplace_back:" << endl;
    books.emplace_back("水浒传", 2);
    // books.emplace_back(SBook("水浒传", 2)); // 结果不一样，想想为什么？
    std::cout << endl;

    std::cout << "emplace_back default:" << endl;
    books.emplace_back();
    auto& book = books.back();
    book.bookName = "红楼梦";
    book.price = 5;
    std::cout << endl;

    std::cout << "emplace:" << endl;
    books.emplace(books.end(), "haha",4); // c.emplace(p,t) 在迭代器p所指向的元素之前创建一个值为t的元素，返回指定新添加元素的迭代器

    auto it = books.emplace(books.end());
    it->bookName = "西游记";
    it->price = 3;
    std::cout << endl;

    std::cout << "print all books :" << endl;
    for_each(books.begin(), books.end(), [](const SBook& book)->void 
    {
        std::cout << book.bookName << endl;
    });
    std::cout << endl;

    /**
     * @brief set 类似vector，用insert会走两次构造，emplace只有一次构造
     * 
     */
    set<SBook> bookSet;

    std::cout << "bookSet insert:" << endl;
    bookSet.insert(SBook("十万个为什么", 1));
    std::cout << endl;

    std::cout << "bookSet emplace:" << endl;
    bookSet.emplace("新华字典", 2);
    // bookSet.emplace(SBook("新华字典", 2)); // 这样和用insert一样了
    std::cout << endl;

    std::cout << "output bookset :" << endl;
    for_each(bookSet.begin(), bookSet.end(), [](const SBook& book)->void 
    {
        std::cout << book.bookName << endl;
    });
    std::cout << endl;
}