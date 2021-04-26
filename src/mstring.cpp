#include"mstring.h"
#include<stdexcept>
#include<cstring>



void orange::string::free(){
     if(elements == nullptr)
          return;
     char* desk = first_free;
     while(desk != elements){
          alloc.destroy(--desk);
     }
     alloc.deallocate(elements,cap - first_free);
     elements = first_free = cap = nullptr;
}


void orange::string::reallocate(){
     size_type new_size = capacity()?capacity()*2:1;
     char* n_ptr = alloc.allocate(new_size);
     auto iter = std::uninitialized_copy(std::make_move_iterator(elements),
          std::make_move_iterator(first_free),n_ptr);
     free();
     elements = n_ptr;
     first_free = iter;
     cap = elements + new_size;  
}


std::pair<char*,char*> orange::string::alloc_n_copy(const char* beg,const char* end){
     char* n_ptr = alloc.allocate(end - beg);
     auto iter = std::uninitialized_copy(beg,end,n_ptr);
     return {n_ptr,iter};
}


void orange::string::chk_n_alloc(){
     if(first_free == cap)
          reallocate();
}


orange::string::string(const char* arr){
     size_type sz = std::strlen(arr);
     auto iter_pair = alloc_n_copy(arr,arr + sz);
     elements = iter_pair.first;
     cap = first_free = iter_pair.second;
}


orange::string::string(const string& s){
     auto iter_pair = alloc_n_copy(s.cbegin(),s.cend());
     elements = iter_pair.first;
     cap = first_free = iter_pair.second;
}

orange::string& orange::string::operator=(const string& s){
     if(this == &s)
          return *this;
     auto iter_pair = alloc_n_copy(s.cbegin(),s.cend());
     free();
     elements = iter_pair.first;
     cap = first_free = iter_pair.second;
     return *this;
}

orange::string::~string(){
     free();
}

std::allocator<char> orange::string::alloc;



 std::ostream& orange::operator<<(std::ostream& os,const string& s){
      for(auto iter = s.cbegin();iter!= s.cend();++iter){
          os << *iter;
      }
      return os;
 }

//  std::istream& orange::operator>>(std::istream& in,string& s){
//       char ch;
//       while(in >> ch){
//            if(ch == '\n'|'\t'|' ')
//            {
//                std::cin.unget();
//                return in;
//            }
//            s.chk_n_alloc();
//            s.alloc.construct(s.first_free++,ch);
//       }
//       return in;
//  }





