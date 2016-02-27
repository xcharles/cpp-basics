#ifndef _STR_BLOB_H_
#define _STR_BLOB_H_
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>

using namespace std;

/**
 * 使用动态内存的情形:
 * 程序不知道自己需要使用多少对象(容器类内部封装了对象并管理了动态对象的生存期)
 *
 *　程序不知道所需对象的准确类型(具有继承关系的父子类，当派生类对象赋值给基类对象时，
 * 其中派生类部分将被sliced掉，因而容器里无法兼容存储存在继承关系的子类
 * 例如A继承自Base,
 * vector<Base> vc;
 * vc.push_back(Base(xxx)); //允许使用Base类
 * vc.push_back(A(xxx)); //派生类的部分信息会被切掉
　* 因而弥补措施就是建议使用基类指针，这些基类指针所指对象的动态类型可能是基类类型，
　* 也可能是派生类别。而原生指针的缺点在为什么使用智能指针中已经提到，它不利于管理对象的生存期
　* 所以最佳实践就是选择智能指针,并用make_shared函数生成智能指针。
　* 如同我们可以将派生类的普通指针赋值给基类指针一样，我们也可以将
　* 一个派生类的智能指针赋值给基类的智能指针,总的来说使用智能指针能有效管理继承体系下类的生存期即
 * vector<shared_ptr<Base>> vc;
 * vc.push_back(make_shared<Base>("0-201-82470-1",50));
 * vc.push_back(make_shared<A>("0-201-54848-8",50,10,0.25));)
 *
 *　程序需要在多个对象间共享数据(这是为了多个对象能够共享相同的底层数据)
 * 例如
 * vector<string> s1;
 * vector<string> s2 = {"a","an","the"};
 * s1 = s2; //vector是值语义的表示，s1和s2的vector是相互独立的
 * 
 * Blob<string> s1;
 * Blob<string> s2 = {...};
 * s1 = s2; //尽管s2被销毁了但是其中的元素不能被销毁，因为s1仍在使用它
 */


/**
 * 多个StrBlob对象共享vector数据
 * vector数据用智能指针来管理，通过shared_ptr成员可以记录
 * 有多少个StrBlob共享相同的vector并在vector的最后一个使用者被销毁时释放vector
 * 注意到StrBlob使用默认版本的拷贝、赋值和析构函数，由于只有一个shared_ptr成员
 * 它也将被拷贝、赋值和销毁。对应的语义则表示将会修改其引用计数，如果引用计数为0
 * 意味者当最后一个StrBlob对象被销毁时，shared_ptr管理的vector数据将会自动销毁
 * 
 */

/*using forward declaration*/
class StrBlobPtr;

class StrBlob {
	friend class StrBlobPtr;
public:
	typedef vector<string>::size_type size_type;

	StrBlob() : data(make_shared<vector<string>>()) {}

	StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

	/*一些常见的方法*/
	size_type size() const {
		return data->size();
	}

	bool empty() const {
		return data->empty();
	}

	/*添加和删除元素*/
	void push_back(const string& ele) {
		data->push_back(ele);
	}

	void pop_back() {
		check(0,"pop on empty StrBlob");
		data->pop_back();
	}

	/*获取元素，并作合法性检查*/
	string& front() {
		check(0,"front on empty StrBlob");
		return data->front();
	}

	string& back() {
		check(0,"back on empty StrBlob");
		return data->back();
	}

	/**
	 * const版本的成员函数，应用于常量对象
	 * const成员函数是在参数列表后附有const关键字，它应用于常量对象
	 * 因为非常量版本的函数对于常量对象是不可用的，我们只能在一个常量对象上
	 * 使用const成员函数。相反非常量对象可以调用常量或者非常量版本的成员函数，但编译器
	 * 优先选用非常量版本的函数
	 *
	 * 重载函数: 名字相同但形参列表不同(可能是个数，可能是类型)
	 * 关于判断const形参的类型是否相同
	 * int lookup(phone);
	 * int lookup(const phone); //顶层const不影响形参的类型，它们无法区分
	 * int lookup(phone *);
	 * int lookup(phone *const); //无法区分
	 *
	 * 若形参是某种类型的指针或引用，通过区分其指向的是常量对象还是非常量对象来实现函数重载，底层const
	 * int lookup(phone *); 
	 * int lookup(const phone *); 
	 * 通过判断实参是否为常量判断调用哪个函数，const对象只能传递给const形参，非const对象可做传递给非常量对象
	 * 或者指向非常量对象的指针，又可以转换为const版本，从而传递给const形参，这时候编译器优先选用非常量版本的函数
	 */
	string& front() const {
		check(0,"front on empty StrBlob");
		return data->front();
	}

	string& back() const {
		check(0,"back on empty StrBlob");
		return data->back();
	}

	/**
	 * StrBlobPtr的接口方法
	 */
	StrBlobPtr begin();
	StrBlobPtr end();

private:
	shared_ptr<vector<string>> data;

	//如果data[i]无效将抛出msg消息
	void check(size_type i,const string& msg) const {
		if(i >= data->size())
			throw out_of_range(msg);
	}
};


class StrBlobPtr {
		/*判断两指针是否指向相同的vector*/
		friend bool eq(const StrBlobPtr& lhs,const StrBlobPtr& rhs);
public:
	/*接受空的weak_ptr*/
	StrBlobPtr(): cur(0) {}

	StrBlobPtr(StrBlob &a,size_t sz = 0):
		wptr(a.data),cur(sz) {}

	/**
	　* 伴随指针类主要用于判断共享的vector是否存在
	　* 解引用当前指针和递增递减当前指针
	 */
	string& deref() const {
		auto sp = check(cur,"deference past end");
		return (*sp)[cur]; //sp是指向vector的智能指针
	}

	/*前缀引用*/
	StrBlobPtr& incr() {
		//如果cur已到容器尾部，就不能递增它
		check(cur,"incrment past end");
		++cur;
		return *this;
	}

	StrBlobPtr& decr() {
		//如果cur减到了0,就不能继续递减它
		--cur;
		check(-1,"decrement past begin of StrBlobPtr");
		return *this;
	}


private:
	/**
	 * 保存一个弱引用指针，指向StrBlob的data成员
	 * 这种弱引用关系不会影响一个给定的StrBlob所指向的vector生存期
	 * 反而它可以防止用户去访问一个不存在的vector的企图
	 * 如果vector被销毁了，lock方法会返回空指针，所有的引用将会失败
	 * 否则检查给定索引是否在合理范围内，若索引值合法，将会返回对应的shared_ptr
	 */
	weak_ptr<vector<string>> wptr;

	/*保存当前元素在vector中的下标，可选索引值*/
	size_t cur;

	shared_ptr<vector<string>> check(size_t i,const string& msg) const;
};

shared_ptr<vector<string>> StrBlobPtr::check(size_t i,const string& msg) const {
	auto sp = wptr.lock(); //vector还存在么
	if(!sp) 
		throw runtime_error("unbound StrBlobPtr");
	if(i >= sp->size())
		throw out_of_range("msg");
	return sp;
}

/*使用StrBlob对象本身，返回开始指针*/
StrBlobPtr StrBlob::begin() {
	return StrBlobPtr(*this); 
}

StrBlobPtr StrBlob::end() {
	return StrBlobPtr(*this,data->size());
}


inline bool eq(const StrBlobPtr& lhs,const StrBlobPtr& rhs) {
	auto lsp = lhs.wptr.lock();
	auto rsp = rhs.wptr.lock();
	if(lsp == rsp) {
		/*both null or point to the same element*/
		return (!lsp || lhs.cur == rhs.cur);
	}
	return false; /*points to the different vectors*/
}

inline bool neq(const StrBlobPtr& lhs,const StrBlobPtr& rhs) {
	return !eq(lhs,rhs);
}


#endif