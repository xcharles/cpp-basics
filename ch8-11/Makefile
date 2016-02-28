CXX= g++
CCFLAGS= -std=c++11 -Wall -O2
DG= -g

OBJS= accfill algoper

all: $(OBJS)

accfill: test_accfill.cpp
	$(CXX) $(CCFLAGS) -o $@ $^

algoper: test_algoper.cpp
	$(CXX) $(CCFLAGS) -o $@ $^


clean:
	rm -rf *.o $(OBJS) *~ 


