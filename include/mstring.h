#include<memory>
#include<iostream>


namespace orange{
     class string{
          friend std::istream& operator>>(std::istream& in,string& s);
          public:
               typedef unsigned size_type;
               string():string(""){};
               string(const char*);
               string(const string&);
               string& operator=(const string&);
               ~string();
               // begin()
               char* begin(){return elements;};
               const char* cbegin()const{return elements;};
               // end()
               const char* cend()const{return first_free;};
               char* end(){return first_free;};
               // size
               size_type capacity(){return first_free - elements;};
               // capacity
               size_type size(){return cap - elements;};

          private:
          // 静态数据成员，内存分配器
               static std::allocator<char> alloc;
          // 指向分配内存中的第一个元素位置
               char* elements;
          // 指向分配内存中最后一个元素之后的位置
               char* first_free;
          // 指向已分配内存的下一个位置
               char* cap;
          // 工具函数,重新分配内存
               void reallocate();
          // 工具函数，检查内存是否充足
               void chk_n_alloc();
          //  工具函数,供copy操作使用
               std::pair<char*,char*> alloc_n_copy(const char*,const char*);
          // 工具函数,释放资源
               void free();
     };
     std::ostream& operator<<(std::ostream& os,const string& s);
     std::istream& operator>>(std::istream& in,string& s);
     
}
