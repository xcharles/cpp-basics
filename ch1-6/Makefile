CXX= g++
CCFLAGS= -std=c++11 -Wall -O2
DG= -g

OBJS= avg_price

avg_price: avg_price.cpp sales_item.h
	$(CXX) $(CCFLAGS) -o $@ $^

clean:
	rm -rf *~ *.o *~ $(OBJS)




