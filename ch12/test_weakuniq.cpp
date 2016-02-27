#include <iostream>
#include <string>
#include <memory> //unique_ptr,weak_ptr

using namespace std;

/**
 * unique_ptr独占它指向的对象，因而unique_ptr不支持普通的拷贝或赋值
 *　初始化时可以绑定到一个new返回的指针(默认用delete释放对象)或者调用一个删除器对象来代替delete
 * unique_ptr<T,D> u(xxx,d)
 * 重要的方法有两个
 * release方法: unique_ptr放弃对管理对象的控制权，返回指针，并将unique_ptr置为空。注意release返回
 * 的指针通过只是用来初始化另一个智能指针或给另一个智能指针赋值(转移管理内存的责任，不用手动地释放)
 * reset方法: 接受一个可选的指针参数，令unique_ptr指向新的对象，原来对象会被释放否则置为空
 * 最佳实践: 标准库较早版本中包括auto_ptr，但不宜使用(已被丢弃)，建议使用unique_ptr
 */
void test_unique() {
	unique_ptr<string> p1(new string("hello,world"));

	//将对字符串的控制权由p1转至p2,并且p1=nullptr
	unique_ptr<string> p2(p1.release());
	cout << *p2 << endl;

	unique_ptr<string> p3(new string("trex"));
	cout << *p3 << endl;
	//reset方法释放原指向对象的内存，并将trex字符串的控制权由p3转移至p2
	p2.reset(p3.release());
	cout << *p2 << endl;

	if(p1) {
		cout << "p1 not null";
	} else {
		cout << "p1 null";
	}
	cout << endl;
	if(p3) {
		cout << "p3 not null ";
	} else {
		cout << "p3 null";
	}
	cout << endl;
}

/*
 * 它是一种指向一个由shared_ptr管理的对象维持一种弱共享的引用关系、不控制所指对象生存期的智能指针
 * ，利用shared_ptr来初始化weak_ptr
 * 并且不会改变shared_ptr的引用计数，当最后一个shared_ptr被销毁时对象被释放，此时即使
 * weak_ptr指向对象，对象仍可能被释放。
 * 由于对象的不存在，不能使用weak_ptr直接访问对象
 * weak_ptr提供了一个lock方法，检查weak_ptr指向的对象是否存在
 * 如果存在，返回一个指向共享对象的shared_ptr;不存在返回一个空的shared_ptr
 * 通过lock方法可以安全地调用对象
 * weak_ptr的主要用途在于在不影响shared_ptr指向对象的生存期下可以防止用户访问一个不存在的对象，
 * 并且可以避免循环引用(两对象彼此使用shared_ptr来引用对象)
 */
void test_weak() {
	auto p = make_shared<int>(42);
	weak_ptr<int> wp(p);
	p.reset(); //int值被释放
	if(shared_ptr<int> np = wp.lock()) { //如果np存在
		cout << "still have the object" ;
	} else {
		cout << "the object has been released";
	}
	cout << endl;
}

int main() {
	test_unique();
	test_weak();
	return 0;
}
