#include <iostream>
#include "sales_item.h"
using namespace std;

int main() {
    SalesItem total;
    if(cin >> total) {
        SalesItem trans;
        while(cin >> trans) {
            if(trans.isbn() == total.isbn())
                total += trans;
            else {
                cout << total << endl;
                total = trans;
            }
        }
        cout << total << endl;
    } else {
        cerr << "No Data?!" << endl;
	return -1;
    }
    return 0;
}


