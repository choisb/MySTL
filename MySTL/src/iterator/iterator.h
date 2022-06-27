#pragma once
#include <cstddef>

namespace my
{
	// iterator is the base class provided to simplify definitions of the required types for iterators.
	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T* ,
		class Reference = T&
	> struct base_iterator 
	{
		using iterator_category = Category;
		using value_type = T;
		using difference_type = Distance;
		using pointer = Pointer;
		using reference = Reference;
		
		base_iterator() 
			:ptr(nullptr)
		{} // default is nullptr

		base_iterator(pointer inPtr)
			:ptr(inPtr)
		{}
	protected:
		pointer ptr;
	};


	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
}