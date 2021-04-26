#pragma once
#include<iostream>


struct Sales_data
{
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::ostream& print(std::ostream&, const Sales_data&);
    friend std::istream& read(std::istream&, Sales_data&);
public:
    // ���캯��
    Sales_data() = default;
    Sales_data(const std::string& s,unsigned n,double p):
        bookNo(s),units_sold(n),revenue(n*p){};
    Sales_data(const std::string& s):bookNo(s){std::cout << "������string�Ĺ���" << std::endl;};
    Sales_data(std::istream &in);
    Sales_data& combine(const Sales_data&); //  ������������,����ʵ��
    std::string isbn() const
	{
		return this->bookNo;
	}
private:
	// һЩ����
	std::string bookNo; // �鼮isbn���
	unsigned units_sold = 0; // �鼮����
	double revenue = 0.0; // ����������
	double avg_price() const; // ��������ƽ���۸�����ʵ�֡�
};

// Sales_data�ķǳ�Ա�ӿں���
Sales_data add(const Sales_data&, const Sales_data&); // ʵ���Զ��������������
std::ostream& print(std::ostream&, const Sales_data&); // ��ӡ�Զ�����������
std::istream& read(std::istream&, Sales_data&); // ��ȡ����