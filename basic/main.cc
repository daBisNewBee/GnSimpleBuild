// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include "construct.h"
#include "template.h"
#include "utils.h"

using namespace std;

namespace edge_basic{


class A
{
private:
  /* data */
public:
  A(/* args */) {
    std::cout << "A constructor" << std::endl;
  }

  A(const A& lhs) {
    std::cout << "A copy constructor" << std::endl;
  }

  // 移动构造函数
  A(A&& rhs) {
    std::cout << "move constructor" << std::endl;
  }

  virtual ~A() {}
};

}

class MyString : public string {
  
public:
  MyString(const char* str):string(str) {
    std::cout << "MyString constructor 1111 " << str << std::endl;
  }

  MyString(const string& str):string(str) {
     std::cout << "MyString copy constructor 1111 " << str << std::endl;
  }
  
  MyString(): string() {
    std::cout << "MyString constructor 2222 " << std::endl;
  }

  MyString(string str) : string(str){
       std::cout << "MyString constructor 3333 " << str << std::endl;
  }

  // MyString opeator () (int i, int j) {
  //   return substr(i,j);
  // }

};

// 不好，待优化：两次拷贝。形参拷贝到返回值，返回值再拷贝到zyy
const MyString& hello(const MyString& str) {
  return str;
}

MyString&& hello_x(MyString&& str) {
  // 移动的优势在于，移动不开辟额外的内存。通过一定的手段（右值引用），延长了局部变量的生命周期
  return move(str);
}


void moveTest() {
  using namespace edge_basic;

  A a; // 换成 “const A a;”后，std::move 会触发拷贝构造函数，不走移动构造函数
  A b = a;
  // C++11中std::move强制将实参转换成"右值引用"的模板函数
  A c = std::move(a); 

  string lover{"girls"};
  string chaser = std::move(lover);
  cout << "lover: " << lover << endl;
  cout << "chaser: " << chaser << endl;
  if (lover.empty()) 
  {
    // 执行move操作后，string lover被清空了
    cout << "lover is empty." << endl;
  }

  const MyString zyy = hello("great");

  const MyString zyy_x {hello_x("haha")};
}

int main(int argc, char *argv[])
{
  // moveTest();
  // edge_cons_entrance();
  // edge_temlpate_entrance();
  emplaceTest();
  return 0;
}
