#include"screen.h"






char Screen::get(pos r, pos c)const{
    pos row = r * width;
    return contents[row + c];
}

// set接口，设置当前光标位置的字符或者任意给定位置的字符
Screen& Screen::set(char c){
    contents[cursor] = c;
    return *this;
}

Screen& Screen::set(pos wd,pos ht,char c){
    contents[wd * width + ht] = c;
    return *this;
}