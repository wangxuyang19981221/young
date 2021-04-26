#pragma once
#include<string>
#include<iostream>



class Sales_item{

     friend Sales_item operator+(const Sales_item& lhs, const Sales_item& rhs);
     friend std::ostream& operator<<(std::ostream& os,const Sales_item& s);
     friend std::istream& operator>>(std::istream& in, Sales_item& s);
     public:
          Sales_item() = default;
          // 构造
          Sales_item(const std::string &s,unsigned n,double p):
               price(p),units_sold(n),bookno(s),revenue(price * units_sold){};
          
          // 外部接口，返回书籍名称
          std::string Isbn(){return bookno;};

          // 重载+=运算符
          Sales_item& operator+=(const Sales_item &s);


     private:
          // 单价
          double price = 0;
          // 销售量
          unsigned units_sold = 0;
          // 书名
          std::string bookno;
          // 销售额
          double revenue;
};

// 类概念上的接口

// operator+
Sales_item operator+(const Sales_item& lhs, const Sales_item& rhs);

// operator<<
std::ostream& operator<<(std::ostream& os,const Sales_item& s);

// opertor>>
std::istream& operator>>(std::istream& in, Sales_item& s);