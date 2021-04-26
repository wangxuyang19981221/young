#pragma once
#include<iostream>


struct Sales_data
{
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::ostream& print(std::ostream&, const Sales_data&);
    friend std::istream& read(std::istream&, Sales_data&);
public:
    // 构造函数
    Sales_data() = default;
    Sales_data(const std::string& s,unsigned n,double p):
        bookNo(s),units_sold(n),revenue(n*p){};
    Sales_data(const std::string& s):bookNo(s){std::cout << "单参数string的构造" << std::endl;};
    Sales_data(std::istream &in);
    Sales_data& combine(const Sales_data&); //  更新销售内容,类外实现
    std::string isbn() const
	{
		return this->bookNo;
	}
private:
	// 一些属性
	std::string bookNo; // 书籍isbn编号
	unsigned units_sold = 0; // 书籍销量
	double revenue = 0.0; // 总销量收入
	double avg_price() const; // 返回销售平均价格，类外实现。
};

// Sales_data的非成员接口函数
Sales_data add(const Sales_data&, const Sales_data&); // 实现自定义类型数据相加
std::ostream& print(std::ostream&, const Sales_data&); // 打印自定义数据类型
std::istream& read(std::istream&, Sales_data&); // 读取数据