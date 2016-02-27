#include <iostream>

#include "foo.h"

using namespace std;

/*
 * 返回一个动态分配的Foo对象
 * 原生指针由new分配后，它有一个额外负担
 * 调用者必须记得由delete释放内存
 * 即由原生指针(非智能指针)管理的动态内存在被显式释放前一直都会存在
 */
Foo *factory(int arg) {
 	return new Foo(arg);
 }

/**
 * 最合理的方式是其他代码使用该对象后，再返回这个指向对象的指针，用于后续的操作
 */
Foo *use_factory(int arg) {
 	Foo *p = factory(arg);
 	//使用p
 	return p;
}

 // void use_factory(int arg) {
 // 	Foo *p = factory(arg);
 // 	//使用了p,但未delete它
 // 	//p是局部变量，它会被自动释放，但它指向的内存却并未释放
 // 	//产生内存泄露，这种方式不可取
 // }

int main() {
	int arg;
	while(cin >> arg) {
		auto p = use_factory(arg);
		print(cout,*p);
		cout << endl;
		delete p; //必须记住要显示释放
		cout << "deleting successfull!" << endl;
	}
	return 0;
}