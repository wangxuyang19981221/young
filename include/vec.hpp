#pragma once
#include<memory>
#include<string>
#include<stdexcept>


template<class value_type>
class Vec {
     friend void test01();
public:
	typedef unsigned size_t;
	// 默认构造
	Vec() :elements(nullptr), first_free(nullptr), cap(nullptr) {};
	// 接受一个initializer_list进行构造
	Vec(std::initializer_list<value_type> il);
	// copy构造
	Vec(const Vec&);
	// 移动构造
	Vec(Vec&&);
	// 析构
	~Vec();
	// push_back
	void push_back(const value_type&);
	// 外部begin接口
	value_type* begin()const { return elements; };
	// 外部end接口
	value_type* end()const { return first_free; };
	// 外部size接口
	size_t size()const { return first_free - elements; };
	// 外部capacity接口
	size_t capacity()const { return cap - elements; };
	const value_type& operator[](size_t)const;
	value_type& operator[](size_t);
	template<class... Args>
	void emplace_back(Args&&... args);


private:
	// 内存分配器
	static std::allocator<value_type> alloc;
	// 工具函数,供析构函数与拷贝赋值使用
	void free();
	// 工具函数,重新分配内存
	void reallocate();
	// 工具函数，检查内存,适当时进行内存重新分配
	void chk_n_alloc();
	// 工具函数,检查索引是否合法
	void check(unsigned, const std::string&)const;
	// 工具函数,供copy操作使用
	std::pair<value_type*,value_type*> alloc_n_copy(const value_type*,const value_type*)const;
	// 首指针
	value_type* elements;
	// 尾后指针
	value_type* first_free;
	// 内存尾指针
	value_type* cap;
};

template<class value_type>
std::allocator<value_type> Vec<value_type>::alloc;

template<class value_type>
void Vec<value_type>::free() {
	if (!elements) {
		auto desk = first_free;
		// 销毁元素
		while (desk != elements)
		{
			alloc.destroy(--desk);
		}
		// 释放内存
		alloc.deallocate(elements, cap - elements);
	}
	elements = first_free = cap = nullptr;
}

template<class value_type>
void Vec<value_type>::chk_n_alloc() {
	if (first_free == cap) {
		reallocate();
	}
}

template<class value_type>
void Vec<value_type>::reallocate() {
	size_t new_size = elements ? capacity() * 2 : 1;
	auto n_ptr = alloc.allocate(new_size);
	// 搬运数据
	auto ret = std::uninitialized_copy(std::make_move_iterator(elements),
		std::make_move_iterator(first_free), n_ptr);
	free();
	elements = n_ptr;
	first_free = ret;
	cap = elements + new_size;
}

template<class value_type>
void Vec<value_type>::push_back(const value_type& ele) {
	chk_n_alloc();
	alloc.construct(first_free++,ele);
}

template<class value_type>
Vec<value_type>::Vec(std::initializer_list<value_type> il):Vec(){
	for (const auto& i : il) {
		push_back(i);
	}
}

template<class value_type>
Vec<value_type>::~Vec() {
	free();
}


template<class value_type>
void Vec<value_type>::check(unsigned index, const std::string& errmsg)const {
	if (index >= size()) {
		throw std::out_of_range(errmsg);
	}
}


template<class value_type>
const value_type& Vec<value_type>::operator[](size_t index)const {
	check(index, "subscript out of range!");
	return elements[index];
}


template<class value_type>
value_type& Vec<value_type>::operator[](size_t index) {
	check(index, "subscript out of range!");
	return elements[index];
}

template<class value_type>
std::pair<value_type*, value_type*> Vec<value_type>::alloc_n_copy(const value_type* beg, const value_type* end)const {
	// 首先肯定是分配空间
	auto p = alloc.allocate(end - beg);
	auto desk = std::uninitialized_copy(beg, end, p);
	return { p,desk };
}


// copy构造
template<class value_type>
Vec<value_type>::Vec(const Vec& v) {
	free();
	auto ret = alloc_n_copy(v.begin(), v.end());
	elements = ret.first;
	cap = first_free = ret.second;
}

template<class value_type>
template<class... Args>
inline
void Vec<value_type>::emplace_back(Args&&... args) {
	chk_n_alloc();
	alloc.construct(first_free++, std::forward<Args>(args)...);
}

// 解释以下调用emplace_place(10,'c')

/*
编译器为我们实例化
emplace_back(unsigned&& a1,char&& a2);

alloc.construct(first_free++, std::forward<unsigned>(a1),std::forward<char>(a2));
*/

template<class value_type>
Vec<value_type>::Vec(Vec&& v) :
	first_free(v.first_free), elements(v.elements), cap(v.cap) {
	v.first_free = v.elements = v.cap = nullptr;
};