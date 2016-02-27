#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {

	/**
	 *　保存读取的文本信息，并记录单词和其行号set的映射表
	 * 以备查找单词
	 */
	ifstream in("data/allocDataFile");
	/*以行为单位存储整个文本串*/
	vector<string> file;
	/*存储单词到它出现的行号set的映射表*/
	map<string,set<int>> word_map;
	string text;
	static set<int> nodata;
	while(getline(in,text)) {
		file.push_back(text);
		/*保存当前行号*/
		int line_no = file.size() - 1;
		/*行文本分解为单词,istringstream以空白符作为读取单位*/
		istringstream line(text); 
		string word;
		while(line >> word) {
			/**
			 * 若单词不存在，默认创建空set
			 * 若单词在映射表中，加入新行号
			 */
			word_map[word].insert(line_no); 
		}
	}

	/**
	 * 输入查询字符串，输出查询结果
	 * 一个缺点就是只能读取空格作为单词分隔符的，如果一行中有其他标点符号与单词混在一起就
	 * 判断不出来，所以有效的分词很重要
	 */
	while(true) {
		cout << "enter word to look for ,q to quit: ";
		string query;
		if(!(cin >> query) || query == "q") break;
		auto res = word_map.find(query);
		if(res == word_map.end()) {
			cout << "couldn't find " << query << endl;
		} else {
			auto rs = res->second;
			for(auto idx = rs.begin();idx != rs.end();++idx) {
				cout << "\t(line " << (*idx + 1) << ") "
				     << file[*idx] << endl;
			}
		}
		cout << endl;
	}
	return 0;
}
