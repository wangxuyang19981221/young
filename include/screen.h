#pragma once
#include<string>
#include<vector>
#include<iostream>






// ����������ಹ������
class Screen
{
    friend class Screen_mgr;
public:
    typedef std::string::size_type pos;
    // ����
    Screen() = default;
    // ���ܿ�߳�ʼ��һ������Ļ��
    Screen(pos ht,pos wd):height(ht),width(wd),contents(ht*wd,' '){};
	// ���û�������Ļ�ߴ��Լ�������ݵ��Զ���
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht* wd, c) {};
	char get() const // ��ȡ��괦���ַ�,��ʽ����
	{
		return contents[cursor];
	}
	inline char get(pos ht, pos wd)const; // ��ʽ����
    Screen& move(pos wd,pos ht);

    // set�ӿڣ����õ�ǰ���λ�õ��ַ������������λ�õ��ַ�
    Screen& set(char c);
    Screen& set(pos wd,pos ht,char c);

    // display�ӿ�
    const Screen& display()const{
        doprint(std::cout);
        return *this;
    }
    Screen& display(){
        doprint(std::cout);
        return *this;
    }

private:
	pos cursor = 0; // ���λ��
	pos height = 0, width = 0; // ��Ļ�ĳ���
	std::string contents; // ��Ļ����
    // ���ߺ���������������ʾ�Ĺ���
    void doprint(std::ostream& os)const{
        os << contents;
    }

};



// ��Ļ������,���ڹ��������Ļ��
class Screen_mgr
{
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex i);
private:
    std::vector<Screen> screens{Screen(24,80,' ')};
};



// ʹ��inline��Դ�ļ���������ú����Ķ���
inline
Screen& Screen::move(pos wd,pos ht){
     cursor = wd * width + ht;
     return *this;
 }

