#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <list>
#include <initializer_list>

using namespace std;

/**
 * 只读算法，不改变元素的话通常最好使用cbegin()和cend()方法
 * 操作在一个序列上
 * find查找操作,accumulate操作要求函数元素实现了加法运算符
 * 例如在const char *上就不可以进行accumulate操作
 * string sum = accumulate(v.cbegin(),v.cend(),"");
 * 因为const char *没有+运算符，会产生编译错误
 * 
 * equal方法比较两个容器中的序列元素，两个容器可以不同，
 * 并且元素类型也不必一样，例如const char *就可以和string进行==比较
 * 两个序列的算法操作，容器可以是不同类型，元素甚至也可以不严格匹配
 * 只要求能够合理比较元素
 * 
 * fill算法要求输入序列是有效的，也就是说如果本身大小不足或者在空容器
 * 调用类似的fill_n算法，结果是未定义的。初学者易犯的错误就是空容器上
 * 使用fill_n算法
 */
void test_primalg() {
	vector<int> vec(10); /*大小为10*/
	fill(vec.begin(),vec.end(),1);

	/*累加操作，第三个参数是初始累加器*/
	int sum = accumulate(vec.begin(),vec.end(),0);
	cout << sum << endl;

	/*设定一定范围内的元素值*/
	fill(vec.begin(),vec.begin() + vec.size()/2,10);
	cout << accumulate(vec.begin(),vec.end(),0) << endl;

	/*重新填充前一半的元素*/
	fill_n(vec.begin(),vec.size()/2,0);
	cout << accumulate(vec.begin(),vec.end(),0) << endl;

	/*插入迭代器，在尾部进行push_back,这时候迭代器起作用，添加元素*/
	fill_n(back_inserter(vec),10,42);
	cout << accumulate(vec.begin(),vec.end(),0) << endl;

	/*字符串的累加操作*/
	vector<string> v = {"rob","john","sansa"};
	string conc = accumulate(v.cbegin(),v.cend(),string(""));
	/*字符串书数组，不可以用累加函数accumulate(begin(v),end(v),"")*/
	cout << conc << endl;

	/*equal算法操作*/
	list<const char *> ros1;
	vector<string> ros2;
	ros1 = {"hello","so long"};
	ros2 = {"hello","so long","tata"};

	/*切记，使用常量迭代器cbegin/cend*/
	auto b = equal(ros1.cbegin(),ros1.cend(),ros2.cbegin());
	if(b)
		cout << "true";
	else
		cout << "false";
	cout << endl;
}

/**
 * copy算法一般返回的是目的迭代器的值。并且这些算法计算新元素的值
 * 但不会将它们放在输入序列的末尾，而是创建一个新的序列来保存结果
 * 
 * replace刚好不同，它意思是将所有等于给定值的元素都改为另外一个值
 * 原序列有所改变，如果要想原序列不变，需要调用replace_copy
 * 第三个参数表示调整后序列的保存位置
 */
void test_copy() {
	vector<int> a1 = {0,1,2,3,4,5,6,7,8,9};
	int a2[a1.size()];
	copy(a1.begin(),a1.end(),a2);
	for(auto i : a2)
		cout << i << " ";
	cout << endl;

	vector<int> a3 = {5,7,8,2,3,2,5,1,2,3,2};
	vector<int> a4;
	replace(a3.begin(),a3.end(),2,10);
	for(auto it = a3.cbegin();it != a3.cend();++it)
		cout << *it << " ";
	cout << endl;

	/*产生一个新序列*/
	replace_copy(a3.begin(),a3.end(),back_inserter(a4),3,9);
	for(auto it = a3.cbegin();it != a3.cend();++it)
		cout << *it << " ";
	cout << endl;
	for(auto it = a4.cbegin();it != a4.cend();++it)
		cout << *it << " ";
	cout << endl;
}

/**
 * 重排容器元素的算法
 *　务必记住标准库算法只对迭代器而不是容器操作，它不会直接添加或删除元素
 * 如果unique算法只会删除重复相邻的元素(要求有序的情况下)，
 * 它只是覆盖相邻的重复元素，使得不重复元素出现在序列开始部分。
 * unique返回的迭代器指向最后一个不重复元素后的位置，但并不确定后面的元素
 * 此时再用容器的操作删除元素,使用erase即使后面没有元素也是安全的
　*
 * vector保存一个多个故事的文本串，我们希望简化这个vector
 * 每个单词只出现一次，而不管单词在任意文档中出现多次
 */

/*输出单词*/
void print(const vector<string>& words) {
	for_each(words.begin(),words.end(),
		[](const string& s) { cout << s << " ";});
	cout << endl;
	cout << endl;
}



/**
 * usage: ./accfill < data/words
 */
void test_rearrange() {
	vector<string> words;
	string next_wd;
	while(cin >> next_wd) {
		words.push_back(next_wd);
	}
	cout << "原始串: " << endl;
	print(words);

	/*默认按字典序排序，并且使用了string的<运算符来实现排序*/
	sort(words.begin(),words.end());
	cout << "按字符串的字典序: " << endl;
	print(words);
	auto end_uniq = unique(words.begin(),words.end());
	words.erase(end_uniq,words.end());
	cout << "删除重复字符串后: " << endl;
	print(words);
}

int main() {
	test_primalg();
	test_copy();
	test_rearrange();
	return 0;
}