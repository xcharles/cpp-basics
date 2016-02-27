#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test() {
	vector<int> iv;
	cout << "size := " << iv.size() << " capacity := " << iv.capacity() << endl;

	//添加20个元素
	for(auto ix = 0; ix != 20;ix++) {
		iv.push_back(ix);
		cout << "size := " << iv.size() << " capacity := " << iv.capacity() << endl;
	}

	//严格按照reserve预分配一些额外空间
	iv.reserve(40);
	cout << "size := " << iv.size() << " capacity := " << iv.capacity() << endl;

	//添加元素用光多余容量
	while(iv.size() != iv.capacity()) {
		iv.push_back(0);
		cout << "size := " << iv.size() << " capacity := " << iv.capacity() << endl;
	}

	//再添加一个元素，vector就得重新分配空间了
	iv.push_back(23);
	cout << "size := " << iv.size() << " capacity := " << iv.capacity() << endl;
}

void test1() {
	vector<int> v1;
	cout << v1.size() << v1.capacity() << v1.empty() << endl; // 0 0 1

	v1 = {1,2,3,4,5};
	cout << v1.size() << v1.capacity() << v1.empty() << endl;//5 5 0

	/*测试下使用push_back和resize函数容量大小增长策略*/
	//v1.push_back(2); //6 10 0
	//v1.resize(8); // 8 10 0
	v1.reserve(8); // 5 8 0
	cout << v1.size() << v1.capacity() << v1.empty() << endl;
}

void test2() {
	vector<int> v1;
	for(int i = 1; i <= 6;i++)
		v1.push_back(i); //建议直接用列表初始化，这里是为了演示大小和容量不同时swap的效果
	cout << v1.size() << v1.capacity() << v1.empty() << endl;
	//vector<int> v2;
	//vector<int> v2(v1);
	//swap(v2,v1);
	cout << v1.size() << v1.capacity() << v1.empty() << endl;
}

void test3() {
	vector<int> v1{1,2,4,5,9,6,7};
	//v1.front(); //返回首元素的引用，若v1为空函数行为未定义
	//v1.back();//返回尾元素的引用，若v1为空函数行为未定义
	//v1[2]; //返回下标位置的元素引用，若下标越界函数行为未定义
	//v1.at(2);//返回指定位置的元素引用，但使用at更安全，越界时会抛出异常

	vector<int> v2;
	//cout << v2[0] << endl;
	cout << v2.at(0) << endl;
}

void test4() {
	/**
	 * push_back(val): 在vector尾部添加一个元素,
	 *　insert(iter,val): 在迭代器iter前添加元素val,返回指向该元素的迭代器
	 * insert(iter,num,val): 在迭代器iter前添加num个val，返回第一个添加元素的迭代器
	 * insert(iter,{val-list}): 新特性，在迭代器iter前面添加有花括号包围的元素值列表，返回第一个添加元素的迭代器
	 * insert(iter,start,end): 在迭代器iter前添加[start,end)的所有元素,要求后者不能是前面vector中的元素
	 * 注意新标准下的insert函数都是返回对应元素的迭代器，以前的有返回void有返回迭代器
	 */
	vector<int> v1(3,1);
	v1.push_back(8); //v1: 1 1 1 8
	v1.insert(v1.begin(),100); //v1: 100  1 1 1 8
	v1.insert(v1.end(),2,4); //v1: 100 1 1 1 8 4 4
}

void test5() {
	struct item{
		string name;
		int id;
		double price;
		item(string _name,int _id,double _price = 0.0):
			name(_name),id(_id),price(_price) {}
	} ;
	typedef struct item item_t;
	vector<item_t> v1{{"Fruit",0}}; 
	v1.emplace_back("Apple",1,2.5);
	v1.emplace(v1.begin(),"Banana",3,4.3);
	for(auto iter = v1.begin();iter != v1.end();++iter)
		cout << iter->name <<" " << iter->id << " " << iter->price << endl;
}

void test6() {
	//pop_back(): 删除vector中尾元素。若容器为空函数行为未定义
	//erase(iter): 删除指定位置的元素，返回被删之后的下一个元素的迭代器。若iter指向尾元素返回end();若已是end则函数未定义
	//erase(start,end): 删除区间[start,end)中的所有元素
	//erase函数多结合泛型算法find、remove、remove_if来使用
	vector<int> v1{4,8,7,6,2,3,6,4,5,1};
	v1.pop_back();
	cout << v1.size() << endl;
	
	auto iter = find(v1.begin(),v1.end(),2);
	v1.erase(iter);
	cout << v1.size() << endl;

}

int main() {
	test6();
	return 0;
}