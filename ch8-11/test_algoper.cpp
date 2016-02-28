#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <list>
#include <initializer_list>

using namespace std;


void print(const vector<string>& words) {
	for_each(words.begin(),words.end(),[](const string& s){
		cout << s << " ";
	});
	cout << endl;
	cout << endl;
} 

bool isShorter(const string& s1,const string& s2) {
	return s1.size() < s2.size();
}

string make_plural(int cnt,const string& word,const string& ending) {
	return (cnt > 1)? word + ending : word;
}

/**
 * 如果想相同长度的元素按字典序排序排列
 * 一般是先按照字典序排列后，再按单词长度大小函数
 *　保持相同长度的单词按字典序排列
 * 然后再输出满足条件的单词
 */
void test_alg(unsigned int sz) {
	vector<string> words;
	string next_wd;
	while(cin >> next_wd) {
		words.push_back(next_wd);
	}
	cout << "原始串: " << endl;
	print(words);

	sort(words.begin(),words.end());
	auto eq = unique(words.begin(),words.end());
	words.erase(eq,words.end());
	cout << "按字典序排序: " << endl;
	print(words);

	/*字典排序后再按长度进行排序*/
	stable_sort(words.begin(),words.end(),isShorter);
	cout << "再按长度排序: " << endl;
	print(words);

	/*获取一个迭代器，指向第一个满足size() >= sz的元素*/
	auto wc = find_if(words.begin(),words.end(),
		[sz](const string& a) {
			return a.size() >= sz;
		});

	/*统计数目，并输出这些满足条件的单词*/
	auto count = words.end() - wc;
	cout << count << " " << make_plural(count,"word","s")
		 << " of length " << sz << " or longer " << endl;
	for_each(wc,words.end(),[](const string& s) {
			cout << s << " ";});
	cout << endl;



	/*计算大于sz的数目*/
	// words = cpy; /*恢复数据*/
	// /*按照输入单词的长度进行排序，由短到长*/
	// sort(words.begin(),words.end(),isShorter);
	// print(words);

	// /*使用bind操作将isShorter函数反转排序*/
	// sort(words.begin(),words.end(),bind(isShorter,_2,_1));
	// print(words);
}

/**
 * C++中关于lambda的定义
 * lambda定义后，C++编译器会生成一个与lambda对应的(未命名)类类型
　* 可以理解成当向函数传递一个lambda时，同时定义了一个新类型和该类型的一个对象
　* 传递的参数实际上就是该编译器生成的类类型的未命名对象
　*
 * 默认情况下，从lambda生成的类都包含一个lambda所捕获的变量的数据成员
 * lambda类的数据成员在对象被创建时被初始化
 *
 * 变量的捕获方式
 * 值捕获，表明捕获列表中的变量都可以被拷贝，与参数不同的是被捕获变量的值是在
 * lambda创建时拷贝，而不是调用时拷贝
　* 一般可能的话，我们应该尽量避免捕获指针或引用。
　*
 * 引用捕获: 当在lambda函数体内使用此变量时，实际上使用的是引用所绑定的对象。
 * 引用捕获和返回引用有相同的问题和限制。因为这里提到的引用捕获的变量是局部变量，它不可能作为
 * 返回值。因为函数结束后局部变量会消失
 *
 * 隐式捕获
 * ＆采取引用捕获方式，=表示采取值捕获方式
 * 混合捕获:要求捕获列表中的第一个元素必须是＆或=(隐式捕获)。如果隐式捕获是引用方式，要求后面必须是显式值捕获,
 * 也就是说不能在其名字前使用&
 * 如果隐式捕获是值方式，后面必须是显式引用捕获，意思是在名字前使用&
 *
 */
void test_fcn_val_ref() {
	/*局部变量*/
	size_t v1 = 42;
	/*将v1拷贝到f的可调用对象里*/
	auto f = [v1] {return v1;};
	v1 = 0;
	cout << f() << endl; //42

	size_t v2 = 42;
	/*对象f1中含有v2的引用*/
	auto f1 = [&v2] {return v2;};
	v2 = 0;
	cout << f1() << endl; //0
}

void test_fcn(vector<string>& words,unsigned int sz,
	ostream &os = cout, char c = ' '
	) {
	/*一个引用捕获*/
	for_each(words.begin(),words.end(),
		[&os,c](const string& s) {
			os << s << c;});

	/*隐式值捕获*/
	auto wc = find_if(words.begin(),words.end(),
		[=](const string& s) { return s.size() >= sz });

	/*混合捕获*/
	
	//for_each(words.begin(),words.end(),[&,c](const string& s) { os << s << c;});
	//for_each(words.begin(),words.end(),[=,&os](const string& s) { os << s << c;});
}

/**
 * lambda必须是单一的return语句，返回一个条件表达式的结果，有两个返回值在lambda表达式中就不可行了
 * 如果要定义返回类型的话就必须使用尾置返回类型
 * 明确lambda的参数，它具体的返回类型
 */
void test_return_lambda() {
	vector<int> vi = {-4,6,7,-2,9,10,-1};
	for_each(vi.begin(),vi.end(),
		[](int i) { cout << i << " ";});
	cout << endl;

	/*拷贝，副本*/
	vector<int> orig = vi;
}


void test_lambda_def() {
	
}





int main() {
	//test_alg(4);
	test_fcn_val_ref();
	return 0;
}