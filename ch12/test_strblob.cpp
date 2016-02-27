#include "strblob.h"
#include <iostream>

using namespace std;

int main() {
	/**
	 * 常规使用vector无法产生共享，只会复制一个副本
	 * 两个是相互分离的
	 * 
	 * 若想容器是共享的，一般需要在容器外部套一个智能指针
	 * 让它具有对象语义
	 */
	vector<string> a1;
	vector<string> a2 = {"a","an","the"};
	a1 = a2;
	a2.push_back("about");
	cout << a2.size() << endl;
	cout << a1.size() << endl;

	StrBlob b1;
	StrBlob b2 = {"a","an","the"};
	b1 = b2;
	b2.push_back("about");
	cout << b2.size() << endl;
	cout << b1.size() << endl;

	/*定义了一个StrBlob的迭代器操作，开始、结束和解引用*/
	for(auto it = b1.begin();neq(it,b1.end());it.incr())
		cout << it.deref() << endl;

	return 0;
}