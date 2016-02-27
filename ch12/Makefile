CXX= g++
CCFLAGS= -std=c++11 -Wall -O2
DG= -g

OBJS= wordquery simplewordquery strblob smarttest \
	rawtest sharedtest  weakuniq allocator


all: $(OBJS)

# 针对含有目标文件的依赖项，不应该使用-c选项
# 生成对象目标文件，就不要使用-o选项
wordquery: query_main.cpp textquery.o 
	$(CXX) $(CCFLAGS) -o $@ $^

simplewordquery: test_simplequery.cpp
	$(CXX) $(CCFLAGS) -o $@ $^

strblob: test_strblob.cpp strblob.h
	$(CXX) $(CCFLAGS) -o $@ $^

smarttest: test_smartptr.cpp
	$(CXX) $(CCFLAGS) -o $@ $^

rawtest: test_allocrawptr.cpp foo.h
	$(CXX) $(CCFLAGS) -o $@ $^

sharedtest: test_allocsharedptr.cpp foo.h
	$(CXX) $(CCFLAGS) -o $@ $^

weakuniq: test_weakuniq.cpp
	$(CXX) $(CCFLAGS) -o $@ $^

allocator: test_allocator.cpp
	$(CXX) $(CCFLAGS) -o $@ $^ 


textquery.o: textquery.cpp textquery.h queryresult.h
	$(CXX) $(CCFLAGS) -c $<

clean:
	rm -rf  $(OBJS) *.o *~ core *.stackdump