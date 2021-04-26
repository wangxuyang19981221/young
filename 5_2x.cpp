#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>

struct PersonInfo
{
    std::string name;
    std::vector<std::string> phones;
};


// ������ʾ��
void record(std::ifstream& ifp,std::vector<PersonInfo>& v){
    std::string lines;
    std::istringstream record;
    while(std::getline(ifp,lines)){
        PersonInfo p;
        std::string word;
        record.rdbuf()->str(lines);
        record >> p.name;
        while(record >> word){
            p.phones.push_back(word);
        }
        // һ�����Ѿ��������
        v.push_back(p);
        record.clear();
    }
}



// �ٶ�����������,���ݲ�ʵ�ֹ���
bool valid(const std::string& s){
    return true;
}

std::string format(std::string s){
    return s;
}



// �����ʾ��
void process(std::vector<PersonInfo> &people){
    // i��PersonInfo����
    for(const auto& i: people){
         std::ostringstream formatted,badNums;
        // jΪstring����
        for(const auto& j : i.phones){
            if(!valid(j))
                badNums << j << " ";
            else
                formatted << format(j) << " ";
        }
        if(badNums.str().empty())
            std::cout << i.name << " " << formatted.str() << std::endl;
        else
            std::cerr << "invalid input!" << badNums.str() << std::endl;
    }
}


void test01(){
    std::vector<PersonInfo> people;
    std::ifstream ifp("iotest.txt");
    record(ifp,people);
    process(people);
}

int main(int argc,char** argv){
    test01();
    system("pause");
}