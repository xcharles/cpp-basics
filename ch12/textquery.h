#ifndef _TEXT_QUERY_H_
#define _TEXT_QUERY_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <memory>
#include <fstream>

#include "queryresult.h"

using namespace std;

/**
 * vector存储输入文本文件,map保存单词到文本行号的映射
 * 为了方便QueryResult共享数据，使用智能指针
 */

/*使用前置声明,这里不建议使用，因为需要实现它的友元方法*/
//class QueryResult;

class TextQuery {

public:
	TextQuery(ifstream& ifs);

	QueryResult query(const string&);

	/*print the map*/
	void display_map();

private:
	shared_ptr<vector<string>> file;
	/*共享的是查询string对应的哪些行*/
	map<string,shared_ptr<set<int>>> word_map;

	/* 移除每个单词中的标点符号和大小写
	 * 由于与私有成员无关，使用static静态成员
	 */
	static string cleanup_str(const string&);
};

/**
 * 计数值大于1返回单词的复数形式，否则返回原形
 */
string make_plural(size_t , const string&,const string&);



#endif