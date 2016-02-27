#include "textquery.h"

#include <sstream>
#include <cctype>
#include <cstring>
#include <utility>

using namespace std;


TextQuery::TextQuery(ifstream& ifs): file(new vector<string>) {
	string text;
	while(getline(ifs,text)) {
		file->push_back(text);
		int line_no = file->size() - 1;
		istringstream line(text);
		string word;
		while(line >> word) {
			word = cleanup_str(word);
			auto &lines = word_map[word];
			if(!lines) /*重置为空set*/
				lines.reset(new set<int>);
			lines->insert(line_no);
		}
	}
}


QueryResult TextQuery::query(const string& word) {
	/*定义一个局部static对象，一个指向空的行号set的智能指针*/
	static shared_ptr<set<int>> nodata(new set<int>);
	auto loc = word_map.find(word);
	if(loc == word_map.end()) 
		return QueryResult(word,nodata,file);
	else
		return QueryResult(word,loc->second,file);
}


/**
 * 移除单词中的标点符号并转成小写输入
 */
string TextQuery::cleanup_str(const string& word) {
	string res;
	for(auto it : word) {
		if(!ispunct(it)) /*跳过标点符号*/
			res += it;
	}
	return res;
}

void TextQuery::display_map() {
	for(auto iter = word_map.begin();iter != word_map.end();++iter) {
		cout << "word : " << iter->first << " {";

		auto word_lines = iter->second;
		for(auto loc = word_lines->begin();loc != word_lines->end();++loc) {
			cout << *loc << " ";
		}
		cout << " }\n";
	}
	cout << endl;
}


string make_plural(size_t cnt , const string& word,const string& ending) {
	return (cnt > 1)? word + ending : word;
}


ostream& print(ostream& os,const QueryResult& qr) {
	os << qr.query_word << " occurs " << qr.lines->size()
	   << " " << make_plural(qr.lines->size(),"time","s") << endl;

	for(auto num : *(qr.lines)) { //set集合
		os << "\t(line " << num + 1 << ") "
		   << *(qr.file->begin() + num) << endl;
	}
	return os;
}