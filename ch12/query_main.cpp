#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "textquery.h"

using namespace std;

/**
 * 尽管我们可以用vector/set/map等实现一个简单的查询单词方法
 *　但是我们还期望提供一个更为抽象的解决方案
 *　本问题是: 允许用户在一个给定文件中查询单词，查询结果是
 * 单词在文件中出现的次数及所在行的列表
 *
 * 1 如何存储读取的文件，要求必须记住单词的每一行
 * 使用vector来保存输入文件的文本，map来关联每个单词和它的行号set
 * 明确到这个类会有一个用于读取给定输入文件的构造函数和执行查询的操作
 * TextQuery(ifstream& ifs)
 * QueryResult(const string& query) const; 
 * 2　查询的函数难点是确定要返回什么内容，一旦找到了一个单词，我们需要知道它
 * 出现了多少次，它出现的行号及每行的文本。所以建议就是设计一个封装类Query，来保存结果
 * 可以看到这结果依赖于TextQuery的数据成员。简单的办法是我们可以拷贝set，拷贝vector,但效率实在太低
 * 我们只需要打印文件的一小部分而已。第二种办法就是保存一个指向TextQuery对象内部的指针，可以避免操作
 * 但是容易存在一个问题就是如果TextQuery先于QueryResult对象前被销毁，这样就引用了一个不再存在的对象的数据
 *
 * 可以观察到TextQuery和QueryResult对象的生存期是同步的并且两个类共享了必要数据。
 * 可以使用shared_ptr来反映这种共享数据关系。
 * 智能指针一用途是在多个类中共享数据，另外一个用途就是无法明确具体的对象类型，
 * 通过在容器中存储一个基类的智能指针(该指针所指向对象的动态类型可能指向基类类型，也可能是派生类类型)
 * 
 * 设计一个类时，在真正实现具体方法前建议先编写程序使用这个类
 */

void execute_queries(ifstream& ifs) {
	TextQuery tq(ifs);
	while(true) {
		cout << "enter word to look for ,q to quit: ";
		string item;
		if(!(cin >> item) || item == "q") break;
		/*返回一个ostream&的输出流，接受QueryResult对象为参数*/
		print(cout,tq.query(item)) << endl;
	}
}


int main(int argc,char *argv[]) {
	ifstream ifs;
	// open returns void, so we use the comma operator XREF(commaOp) 
	// to check the state of infile after the open
	if(argc < 2 || !(ifs.open(argv[1]),ifs)) {
		cerr << "no input file" << endl;
		exit(1);
	}
	execute_queries(ifs);
	return 0;
}