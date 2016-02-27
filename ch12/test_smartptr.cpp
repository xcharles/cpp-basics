#include <iostream>
#include <vector>
#include <string>
#include <memory> //shared_ptr,unique_ptr
#include <new> //nothrow,new throws exceptions rather than NULL
//new(nothrow)

/**
　*　　
 */

using namespace std;

struct ex {
	string data;
};

void test() {
	/*
	　* http://stackoverflow.com/questions/3411815/how-to-use-a-c-string-in-a-structure-when-malloc-ing-the-same-structure
	　* 使用malloc会出现segmentation fault
	 * 不应该使用malloc,因为malloc不会调用任何构造函数，
	 * 使用new运算符才可以调用它成员的构造函数,内部的string成员
	 * 才会被调用
	 */
	ex *p = new ex;
	//ex *p = malloc(sizeof(ex)); 
    p->data = "hello world";
	cout << p->data << endl;
}

void test1() {
	/**
	 * 调用make_shared函数分配对象内存并初始化某个它
	 * 返回指向此对象的shared_ptr
	 * 括号里面传递的参数与给定类型的构造函数形式相匹配
	 * 若不传递任何参数，对象自动进行值初始化
	 */
	auto p1 = make_shared<string>();
	if(p1->empty())
		cout << "空串啦" << endl;

	auto p2 = make_shared<string>("careful with string",7);
	cout << *p2 << " " << p2->size() << endl;

	//指向一个动态分配的空vector<string>()
	auto p3 = make_shared<vector<string>>();
	cout << p3->size() << endl;

	/*
	 * 拷贝一个shared_ptr,会增加对象(资源)的引用计数
	 *　比如用一个shared_ptr初始化另一个shared_ptr,或者
	 *　将它作为函数的参数，或者函数的返回值，
	 * 我们都认为这是拷贝,它关联的对象的引用计数会递增
　　　　　*
	 * 为一个shared_ptr赋新值或者shared_ptr被销毁
	 * (如局部的shared_ptr变量离开其作用域)，其引用计数会递减
	 *
	 * 首先要明确的是shared_ptr是一个模板类，它具有类的特征
	 * 类不再使用时会自动调用析构函数释放对象所分配的资源
	 * 对于shared_ptr这个类的析构函数所做的工作是
	 * 它递减所指向对象的引用计数，如果引用计数为0(指向对象的最后一个shared_ptr被销毁时),它会自动释放对象所占的内存
	 * 这就是共享型(引用计数型)的智能指针特点，它会在适当时候自动释放对象，无需手动释放
	 * 比使用new后必须调用delete操作方便多了
	 * 
	 * 上面谈到了局部的shared_ptr变量，值得注意的是
	 * shared_ptr/unique_ptr/weak_ptr都是值语义，要么是栈上对象(函数节后该变量自动释放)
	 * 要么是其他对象的数据成员，或者是容器例的元素，它肯定不会有如下用法
	　* shared_ptr<Foo> *pFoo = new shared_ptr<Foo>(new Foo); //错误！
	 *
	 * use_count函数仅仅在调试环境中调用，它的执行速度略慢，不建议使用!
	 * 判断共享对象是否还存在可用expired函数或者weak_ptr弱共享判断对象生存期
	 */
	auto p4 = make_shared<int>(42);
	auto q4(p4);
	cout << *q4 << " " << p4.use_count() << endl;
	auto r4 = make_shared<int>(52);
	cout << *r4 << " " << r4.use_count() << endl;
	r4 = p4;
	cout << *r4 << " " << r4.use_count() << " " << p4.use_count() << endl;
}

int main() {
	test1();
	return 0;
}