#ifndef _FOO_H_
#define _FOO_H_

#include <iostream>
using std::ostream;

struct Foo {
	Foo(int x) : val(x) {}
	int val;
};

ostream& print(ostream& os,const Foo& f) {
	os << f.val;
	return os;
}

#endif