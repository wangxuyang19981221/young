#pragma once
#include<string>
#include<vector>
#include<iostream>






// 继续给这个类补充内容
class Screen
{
    friend class Screen_mgr;
public:
    typedef std::string::size_type pos;
    // 构造
    Screen() = default;
    // 接受宽高初始化一个空屏幕。
    Screen(pos ht,pos wd):height(ht),width(wd),contents(ht*wd,' '){};
	// 给用户进行屏幕尺寸以及输出内容的自定义
	Screen(pos ht, pos wd, char c) :height(ht), width(wd), contents(ht* wd, c) {};
	char get() const // 读取光标处的字符,隐式内联
	{
		return contents[cursor];
	}
	inline char get(pos ht, pos wd)const; // 显式内联
    Screen& move(pos wd,pos ht);

    // set接口，设置当前光标位置的字符或者任意给定位置的字符
    Screen& set(char c);
    Screen& set(pos wd,pos ht,char c);

    // display接口
    const Screen& display()const{
        doprint(std::cout);
        return *this;
    }
    Screen& display(){
        doprint(std::cout);
        return *this;
    }

private:
	pos cursor = 0; // 鼠标位置
	pos height = 0, width = 0; // 屏幕的长宽
	std::string contents; // 屏幕内容
    // 工具函数，真正负责显示的工作
    void doprint(std::ostream& os)const{
        os << contents;
    }

};



// 屏幕管理器,用于管理多组屏幕。
class Screen_mgr
{
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex i);
private:
    std::vector<Screen> screens{Screen(24,80,' ')};
};



// 使用inline的源文件必须包含该函数的定义
inline
Screen& Screen::move(pos wd,pos ht){
     cursor = wd * width + ht;
     return *this;
 }

