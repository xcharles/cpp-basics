#ifndef _QUERY_RESULT_H_
#define _QUERY_RESULT_H_

#include <memory>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <cstddef>

using namespace std;

class QueryResult {
	friend ostream& print(ostream& ,const QueryResult&);
public:
	QueryResult(string s,shared_ptr<set<int>> sp,shared_ptr<vector<string>> sv):
		query_word(s),lines(sp),file(sv) {}

	size_t size() const {  return lines->size(); }

	shared_ptr<vector<string>> get_file() { return file; }

private:
	/*查询的单词*/
	string query_word;
	/*查询单词所在的行号，为了数据共享采用智能指针*/
	shared_ptr<set<int>> lines;
	/*共享输入的文本文件*/
	shared_ptr<vector<string>> file;

};

/*prototype*/
ostream& print(ostream& ,const QueryResult&);

#endif