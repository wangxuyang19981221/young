#include"sales_item.h"


Sales_item& Sales_item::operator+=(const Sales_item &s){
     units_sold += s.units_sold;
     revenue += s.revenue;
     return *this;
}

// operator+
Sales_item operator+(const Sales_item& lhs, const Sales_item& rhs){
     Sales_item temp = lhs;
     temp += rhs;
     return temp;
}

// operator<<
std::ostream& operator<<(std::ostream& os,const Sales_item& s){
     os << "ISBN: " << s.bookno << " units_sold: " << s.units_sold
     << " price: "  << s.price << " revenue: "  << s.revenue;
     return os;
}

// opertor>>
std::istream& operator>>(std::istream& in, Sales_item& s){
     in >> s.bookno >> s.units_sold >> s.price;
     s.revenue = s.units_sold * s.price;
     return in;
}