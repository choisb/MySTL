#pragma once
#include <cstddef>
#include <memory>
#include <initializer_list>
#include <vector> //todo:: 구현 완료후 삭제
#include "coreType.h"
#include "iterator.h"

constexpr int INIT_CAP = 10;
constexpr float RESIZE_FACTOR = 1.5f;

namespace my {

	template<class T, class Allocator = std::allocator<T>>
	class vector
	{
		struct vector_iterator;

		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const reference;
		using pointer = value_type* ;				// Allocator::pointer 에러.. 이유는? 일단 value_type* 로도 의미상 동일하기 때문에 이렇게 구현하자.
		using const_pointer = const pointer;
		using iterator = vector_iterator;
		using const_iterator = const iterator;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;



		class vector_iterator : public base_iterator<random_access_iterator_tag, value_type>
		{
			using super = base_iterator<random_access_iterator_tag, value_type>;

		public:
			explicit vector_iterator(pointer inPtr) : super(inPtr) {}
			vector_iterator& operator++() { super::ptr++; return *this; }
			vector_iterator operator++(int amount) { super::ptr += amount; return *super::ptr; }
			bool operator==(vector_iterator other) const { return super::ptr == other.super::ptr; }
			bool operator!=(vector_iterator other) const { return !(this->operator==(other)); }
			reference operator*() const { return *super::ptr; };

		};
			

	public:
		// Constructor
		vector() // 1
			:_allocator(allocator_type())
		{
			_init_allocate();
		}
		explicit vector(const Allocator& alloc) // 2
			:_allocator(alloc)
		{
			_init_allocate();
		}
		vector(size_type count, const value_type& value, const Allocator& alloc = Allocator())	// 3
			:_allocator(alloc)
		{

			_init_construct(count, value);
		}
		explicit vector(size_type count, const Allocator& alloc = Allocator())// 4
		{
			_init_construct(count, value_type()); 
		}
		//template< class InputIt > // 정수형 매개변수를 전달할 경우에도 자동으로 여기로 들어옴. 어떻게 
		//vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())	// 5
		//{

		//}
		vector(const vector& other);																			// 6
		vector( const vector& other, const Allocator& alloc );													// 7
		vector(vector&& other) noexcept;																		// 8
		vector( vector&& other, const Allocator& alloc );														// 9 
		vector( std::initializer_list<T> init, const Allocator& alloc = Allocator() );							// 10

		// Destructor
		virtual ~vector() {};

		// operator=
		vector& operator=(const vector& other);		// 1
		vector& operator=(const vector&& other);	// 2
		vector& operator=(std::initializer_list<T> ilist); // 3

		// assign()
		void assign(size_type count, const T& value);;	// 1

		// at()
		reference at(size_type pos);				// 1
		const_reference at(size_type pos) const;	// 2

		// operator[]
		reference operator[](size_type pos);				// 1
		const_reference operator[](size_type pos) const;	// 2

		// front()
		reference front();				// 1
		const_reference front() const;	// 2

		// back()
		reference back();				// 1
		const_reference back() const;	// 2

		// data()
		T* data() noexcept;				// 1
		const T* data() const noexcept; // 2

		// Iterators
		// begin, cbegin
		iterator begin() noexcept;				// 1
		const_iterator begin() const noexcept;	// 2
		const_iterator cbegin() const noexcept; // 3

		// end, cend
		iterator end() noexcept;				// 1
		const_iterator end() const noexcept;	// 2
		const_iterator cend() const noexcept;	// 3

		// Capacity
		bool empty() const noexcept;
		size_type size() const noexcept;
		size_type max_size() const noexcept;
		void reserve(size_type new_cap);
		size_type capacity() const noexcept;
		void shrink_to_fit();

		// Modifiers
		void clear() noexcept;
		iterator insert(const_iterator pos, const T& value);					// 1
		iterator insert(const_iterator pos, T&& value);							// 2
		iterator insert(const_iterator pos, size_type count, const T& value);	// 3
		template< class InputIt >
		iterator insert(const_iterator pos,	InputIt first, InputIt last);		// 4
		iterator insert(const_iterator pos, std::initializer_list<T> ilist);	// 5

		template< class... Args >
		iterator emplace(const_iterator pos, Args&&... args);

		iterator erase(const_iterator pos);										// 1
		iterator erase(const_iterator first, const_iterator last);				// 2

		void push_back(const T& value);
		void push_back(T&& value);

		template< class... Args >
		void emplace_back(Args&&... args);

		void pop_back();

		void resize(size_type count);
		void resize(size_type count, const value_type& value);

		void swap(vector& other) noexcept;


	private:
		value_type* _data{};
		allocator_type _allocator{};
		size_type _size{};
		size_type _capacity{};

		void _init_allocate(size_type capacity = INIT_CAP)
		{
			_capacity = capacity;
			_data = _allocator.allocate(_capacity);
		}
		void _init_construct(size_type count, const value_type& value)
		{
			size_type newCapacity = INIT_CAP;
			if (count * RESIZE_FACTOR > INIT_CAP)
			{
				newCapacity = count * RESIZE_FACTOR;
			}
			_init_allocate(newCapacity);

			value_type temp(value);
			size_type size = sizeof(value_type);
			for (size_type i = 0; i < count; ++i)
			{
				memcpy(data + (i * size), &temp, size);
			}
		}

		// 추후 구현해야할 기능들
		
		// assing()
		// template< class InputIt >	void assign(InputIt first, InputIt last);	// 2
		// void assign( std::initializer_list<T> ilist );							// 3

		// get_allocator
		// allocator_type get_allocator() const noexcept;

		// rbegin, rcbegin
		// reverse_iterator rbegin() noexcept;
		// const_reverse_iterator rbegin() const noexcept;
		// const_reverse_iterator crbegin() const noexcept;

		// rend, rcend
		// reverse_iterator rend() noexcept;
		// const_reverse_iterator rend() const noexcept;
		// const_reverse_iterator crend() const noexcept;


	};


	//vector<bool>	space - efficient dynamic bitset

	//template< class T, class Alloc >
	//bool operator==(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs);

	//template< class T, class Alloc >
	//bool operator!=(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs);

	//template< class T, class Alloc >
	//bool operator<(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs);

	//template< class T, class Alloc >
	//bool operator<=(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs);

	//template< class T, class Alloc >
	//bool operator>(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs);

	//template< class T, class Alloc >
	//bool operator>=(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs);

	//template< class T, class Alloc >
	//void swap(std::vector<T, Alloc>& lhs, std::vector<T, Alloc>& rhs);



}

