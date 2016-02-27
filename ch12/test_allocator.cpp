#include <iostream>
#include <string>
#include <memory> //allocator
#include <cstddef>
#include <fstream> //ifstream
#include <vector>

using namespace std;

void test_allocator() {
	const size_t n = 100;
	/*定义一个可以为string对象分配内存的allocator对象*/
	allocator<string> alloc;
	/*明确分配大小*/
	auto p = alloc.allocate(n);

	/*构造对象*/
	auto q = p;
	alloc.construct(q++);//创造一个空串
	cout << *(q-1) << endl;

	/**
	 * construct接受一个传递给类型T的构造函数
	 */
	/*第二个字符串采用string的某个构造函数*/
	alloc.construct(q++,10,'c');
	cout << *(q-1) << endl;

	alloc.construct(q++,"hi");
	cout << *(q-1) << endl;

	/*接受正确的string输出运算符*/
	cout << *p << endl;

	/*先析构每个构造的对象元素，以指针为参数*/
	while(q != p) {
		alloc.destroy(--q);
	}

	/*释放我们分配的内存*/
	alloc.deallocate(p,n);
}

/**
 * 比较allocator和直接使用new/delete
 */
void test_alloc1() {
	/*use allocator*/

	const size_t n = 100;
	allocator<string> alloc;
	auto p = alloc.allocate(n);
	auto q = p; //工作指针用于遍历读取字符串
	string s;

	ifstream in("data/allocDataFile");
	while(in >> s && q != p + n) {
		alloc.construct(q++,s);
		cout << *(q-1) << " ";
	}
	cout << endl;

	size_t size = q - p;
	cout << "read " << size << " strings" << endl;
	cout << endl;

	/*析构string对象*/
	while(q != p) {
		alloc.destroy(--q);
	}
	/*注意不是释放size大小的内存,而是我们所有分配的内存*/
	alloc.deallocate(p,n); 
	in.close();

	/*use array*/
	in.open("data/allocDataFile");
	p = new string[n];
	q = p;
	while(in >> s && q != p + n) {
		*q++ = s;
		cout << *(q-1) << " ";
	}
	cout << endl;
	size = q - p;
	cout << "read " << size << " strings" << endl;
	cout << endl;
	/*直接释放内存*/
	delete[] p;
}

/**
 * 拷贝和填充未初始化内存的算法
 * 在未初始化内存中创建对象
 * uninitialized_copy(begin,end,b2): 从迭代器begin和end的范围中拷贝元素
 * 到迭代器b2指向的未构造的原始内存中，b2指向的内存必须足够大
 * uninitialized_copy_n(begin,n,b2)
 * 
 * uninitialized_fill(begin,end,t): 用迭代器begin和end的原始内存范围中创建对象
 * 对象的值均为t的拷贝
 * uninitialized_fill_n(begin,n,t)
 */
void test_alloc2() {
	vector<int> vi{1,2,3,4,5,6,7,8,9};
	allocator<int> alloc;

	auto p = alloc.allocate(vi.size() * 2);
	/*返回的指针是指向最后一个构造元素之后的位置*/
	auto q = uninitialized_copy(vi.begin(),vi.end(),p);
	/*后面剩下的元素用100代替*/
	uninitialized_fill_n(q,vi.size(),100);

	/*输出元素*/
	for(size_t i = 0;i < vi.size();i++) 
		cout << *(p+i) << " ";
	for(size_t i = 0;i < vi.size();i++) 
		cout << *(q+i) << " ";
	cout << endl;

	/*要求与allocate分配内存的大小参数一致*/
	alloc.deallocate(p,vi.size() * 2);
}

int main() {
	test_allocator();
	test_alloc1();
	test_alloc2();
}