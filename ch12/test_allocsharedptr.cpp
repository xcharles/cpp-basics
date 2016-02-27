#include <iostream>
#include <memory> //shared_ptr,unique_ptr
#include "foo.h"

using namespace std;

shared_ptr<Foo> factory(int arg) {
	return make_shared<Foo>(arg); //类Foo的构造函数参数形式
}

// void use_factory(int arg) {
// 	auto p = factory(arg);
// 	print(cout, *p);
// 	cout << endl;
// 	//使用p，和内置指针一样的操作
// 	//结束时p变量自动释放,会引发p对象自动调用析构函数
// 	//它会判断p所指的对象引用计数。在这里释放操作会使引用计数减一
// 	//结果计数为0,这个时候会释放指向的Foo对象
// }

shared_ptr<Foo> use_factory(int arg)
{
	shared_ptr<Foo> p = factory(arg);
	print(cout, *p);
	cout << endl;
	// use p
	return p;  // reference count is incremented when we return p
} 

int main() {
	int arg;
	while(cin >> arg) {
		auto p = use_factory(arg);
		cout << endl;
		//cout << p.use_count() << endl;
	}
}