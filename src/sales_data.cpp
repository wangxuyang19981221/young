#include"sales_data.h"



// ����ʵ�ֳ�Ա����
// ���캯����
Sales_data::Sales_data(std::istream &in){
    read(in,*this);
}


// ����ʵ��avg_price
inline
double Sales_data::avg_price()const
{
    return units_sold ? revenue / units_sold : 0;
}
// �����ķ���ֵ���ͣ����������β��б���thisָ���������񶼱�����ȫƥ�䡣
// ����ʵ��combine
Sales_data& Sales_data::combine(const Sales_data& s)
{
	this->revenue += s.revenue;
	this->units_sold += s.units_sold;
	return *this;
}


// ����������صķǳ�Ա����
// �Ӹ�������˵����Щ����������ӿڵ�һ���֣��������ҲӦ������������һ�����������붨��ֱ�Ϊ�˷����û�ʹ�ã�Ӧ����������������������(�Ƕ���)д��ͬһ���ļ��С�
// read����ʵ��
std::istream& read(std::istream& in, Sales_data& s)
{
	double price;
    in >> s.bookNo >> s.units_sold >> price;
	s.revenue = price * s.units_sold;
	return in;
}

// print����ʵ��

std::ostream& print(std::ostream& os, const Sales_data& s)
{
	os << "�鼮ISBN: " << s.isbn()
		<< " �鼮������: " << s.units_sold
		<< " �鼮���۶�: " << s.revenue
		<< " �鼮ƽ���۸�: " << s.avg_price();
	return os;
}
// ������ֵ��ע�⣬1.io�����ǲ��ܱ�copy�ģ����ֻ����������ʽ���ݣ�2.print������Ӧ����ӡ���У�Ӧ�����û������Ƿ��С�
Sales_data add(const Sales_data& s1, const Sales_data& s2)
{
	Sales_data s_temp = s1;
	return s_temp.combine(s2);
}
