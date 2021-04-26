#include"sales_data.h"



// 类外实现成员函数
// 构造函数、
Sales_data::Sales_data(std::istream &in){
    read(in,*this);
}


// 类外实现avg_price
inline
double Sales_data::avg_price()const
{
    return units_sold ? revenue / units_sold : 0;
}
// 函数的返回值类型，函数名，形参列表，对this指针的修饰与否都必须完全匹配。
// 类外实现combine
Sales_data& Sales_data::combine(const Sales_data& s)
{
	this->revenue += s.revenue;
	this->units_sold += s.units_sold;
	return *this;
}


// 定义与类相关的非成员函数
// 从概念上来说，这些函数属于类接口的一部分，在设计上也应该与其他函数一样，将声明与定义分别，为了方便用户使用，应当将函数定义与该类的声明(非定义)写在同一个文件中。
// read函数实现
std::istream& read(std::istream& in, Sales_data& s)
{
	double price;
    in >> s.bookNo >> s.units_sold >> price;
	s.revenue = price * s.units_sold;
	return in;
}

// print函数实现

std::ostream& print(std::ostream& os, const Sales_data& s)
{
	os << "书籍ISBN: " << s.isbn()
		<< " 书籍销售量: " << s.units_sold
		<< " 书籍销售额: " << s.revenue
		<< " 书籍平均价格: " << s.avg_price();
	return os;
}
// 有两点值得注意，1.io对象是不能被copy的，因此只能以引用形式传递，2.print函数不应当打印换行，应当由用户决定是否换行。
Sales_data add(const Sales_data& s1, const Sales_data& s2)
{
	Sales_data s_temp = s1;
	return s_temp.combine(s2);
}
