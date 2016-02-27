#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm> //STL find算法、set操作算法

using namespace std;

void test_set_operations(){
	int ia[5]={0,1,2,3,4};

    //set的构造函数
	set<int> iset(ia,ia+5); 

	cout << "大小： " << iset.size() << endl;
	cout << "统计3的次数： "<< iset.count(3) << endl;
	cout << endl; //5,1

    
    //插入和删除操作：insert、erase
	iset.insert(3);
	cout << "大小： " << iset.size() << endl;
	cout << "统计3的次数： "<< iset.count(3) << endl;
	cout << endl; //不允许插入相同元素-5,1

	iset.insert(5);
	cout << "大小： " << iset.size()<<endl;
	cout << "统计3的次数： "<< iset.count(3)<<endl;
	cout<<endl;//6,1

	iset.erase(1);
	cout << "大小： " << iset.size()<<endl;
	cout << "统计3的次数： "<< iset.count(3)<<endl;
	cout<<endl;//5,1

	
	//迭代器操作
	set<int>::iterator ite1=iset.begin();
	set<int>::iterator ite2=iset.end();
	for(;ite1!=ite2;++ite1)
		cout<< *ite1 << " ";
	cout<<endl;

    
    /**
     * 查找操作-比较STL的find算法、该容器的find算法
     * STL的find算法有效但不是好办法
     * set容器的find算法更有效率
     */

    ite1=find(iset.begin(),iset.end(),3);
    if(ite1 != iset.end())
    	cout<< "3 found" <<endl;

    ite1=find(iset.begin(),iset.end(),1);
    if(ite1 == iset.end())
    	cout<< "1 not found" <<endl;

    ite1=iset.find(3);
    if(ite1 != iset.end())
    	cout<< "3 found" <<endl;


    ite1=iset.find(1);
    if(ite1 == iset.end())
    	cout<< "1 not found" <<endl;

    //*ite1=9; //试图通过迭代器修改set元素，是不允许的，const-iterator
}

void test_map_operations(){
	map<string,int> simap; //string为键值，int为实值

	//插入操作(赋值)，下标引用(左右值)
	simap[string("jihou")]=1; //第1对内容(jihou,1)
	simap[string("jerry")]=2; //第2对内容(jerry,2)
	simap[string("jason")]=3; //第3对内容(jason,3)
	simap[string("jimmy")]=4; //第4对内容(jimmy,4)
    pair<string,int> val(string("david"),5);
	simap.insert(val); //第5对内容(david,5)

	map<string,int>::iterator iter=simap.begin();
	for(;iter!=simap.end();++iter){
		cout << iter->first << " " << iter->second <<endl;
	}

	int num=simap[string("jihou")];
	cout << num << endl;

	//查找操作,关联式容器的find函数
	iter=simap.find(string("mchen"));
	if(iter==simap.end())
		cout<<"mchen not found"<<endl;

	iter=simap.find(string("jerry"));
	if(iter!=simap.end())
		cout <<"jerry found" << endl;

	iter->second=9; //通过map迭代器修改实值，注不能修改实值
	cout< < simap[string("jerry")] <<endl;
}

void test_unordered_set(){
 	unordered_set<int> iht;

	cout<< iht.size() <<endl;
	cout<< iht.bucket_count() <<endl;
	cout<< iht.max_bucket_count() <<endl;
	//0  11  1152921504606846975

	iht.insert(59);
	iht.insert(63);
	iht.insert(108);
	iht.insert(2);
	iht.insert(53);
	iht.insert(55);

    unordered_set<int>::iterator it1=iht.begin();
	unordered_set<int>::iterator it2=iht.end();
	for(;it1!=it2;++it1){
	 	cout<<*it1<< ' ';
	} //55 2 53 108 63 59 
	cout << endl;
}


int main(){
	test_set_operations();
	test_map_operations();
	test_unordered_set();
	return 0;
}