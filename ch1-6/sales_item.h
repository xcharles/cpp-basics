#ifndef _SALES_ITEM_H_
#define _SALES_ITEM_H_

#include <iostream>
#include <string>
using namespace std;

class SalesItem {
    friend istream& operator>>(istream& in, SalesItem& s);
    friend ostream& operator<<(ostream& out,const SalesItem& s);
    friend bool operator<(const SalesItem& lhs,const SalesItem& rhs);
    friend bool operator==(const SalesItem& lhs,const SalesItem& rhs);

public:
    SalesItem() = default;
    SalesItem(const string& book): m_booknum(book) {}
    SalesItem(istream& is) {
        is >> *this;
    }

public:
    SalesItem& operator+=(const SalesItem& lhs);

    string isbn() const {
        return m_booknum;
    }

    double avg_price() const;

private:
    string m_booknum;
    unsigned m_units_sold = 0;
    double m_profit = 0.0;
};

inline bool compareisbn(const SalesItem& lhs,const SalesItem& rhs) {
    return lhs.isbn() == rhs.isbn();
}

inline bool operator==(const SalesItem& lhs,const SalesItem& rhs) {
    return lhs.m_units_sold == rhs.m_units_sold &&
           lhs.m_profit == rhs.m_profit &&
           lhs.isbn() == rhs.isbn();
}

inline bool operator!=(const SalesItem& lhs,const SalesItem& rhs) {
    return !(lhs == rhs);
}

/*两个对象必须指向同一个ISBN号码*/
SalesItem& SalesItem::operator+=(const SalesItem& lhs) {
    m_units_sold += lhs.m_units_sold;
    m_profit += lhs.m_profit;
    return *this;
}

/*两个对象必须指向同一个ISBN号码*/
SalesItem operator+(const SalesItem& lhs,const SalesItem& rhs) {
    SalesItem ret(lhs);
    ret += rhs;
    return ret;
}

istream& operator>>(istream& in, SalesItem& s) {
    double price;
    in >> s.m_booknum >> s.m_units_sold >> price;
    /*检测输入流的状态*/
    if(in)
        s.m_profit = s.m_units_sold * price;
    else
        s = SalesItem();
    return in;
}

 ostream& operator<<(ostream& out,const SalesItem& s) {
    out << s.isbn() << " " << s.m_units_sold << " "
        << s.m_profit << " " << s.avg_price();
    return out;
 }

  double SalesItem::avg_price() const {
    return (m_units_sold == 0)?0:(m_profit/m_units_sold);
  }

#endif
