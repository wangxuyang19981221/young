#include"screen.h"






char Screen::get(pos r, pos c)const{
    pos row = r * width;
    return contents[row + c];
}

// set�ӿڣ����õ�ǰ���λ�õ��ַ������������λ�õ��ַ�
Screen& Screen::set(char c){
    contents[cursor] = c;
    return *this;
}

Screen& Screen::set(pos wd,pos ht,char c){
    contents[wd * width + ht] = c;
    return *this;
}