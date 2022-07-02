#pragma once
#include <type_traits>
#include <utility>

template<typename T1, typename T2, bool = std::is_empty_v<T1> && !std::is_final_v<T1>> struct compressed_pair;

struct one_and_variadic_arg_t { explicit one_and_variadic_arg_t() = default; };
struct zero_and_variadic_arg_t { explicit zero_and_variadic_arg_t() = default; };

// T1 is empty class
template<typename T1, typename T2> struct compressed_pair<T1, T2, false>
{
	T1 first;
	T2 second;

	template<typename A1, typename ...A2>
	compressed_pair(one_and_variadic_arg_t, A1&& arg1, A2&& ...arg2)
		:first(std::forward<A1>(arg1)), second(std::forward<A2>(arg2)...) {}

	template<typename ...A2>
	compressed_pair(zero_and_variadic_arg_t, A2&& ...arg2)
		:first(), second(std::forward<A2>(arg2)...) {}

	T1& getFirst() noexcept { return const_cast<T1&>(getFirst()); }
	T2& getSecond() noexcept { return const_cast<T2&>(getSecond()); }
	const T1& getFirst() const noexcept { return first; }
	const T2& getSecond() const noexcept { return second; }
};

// T1 isn't empty class
template<typename T1, typename T2>
struct compressed_pair <T1, T2, true> : public T1
{
	T2 second;

	template<typename A1, typename ...A2>
	compressed_pair(one_and_variadic_arg_t, A1&& arg1, A2&& ...arg2)
		:T1(std::forward<A1>(arg1)), second(std::forward<A2>(arg2)...) {}

	template<typename ...A2>
	compressed_pair(zero_and_variadic_arg_t, A2&& ...arg2)
		:T1(), second(std::forward<A2>(arg2)...) {}

	T1& getFirst() noexcept { return const_cast<T1&>(getFirst()); }
	T2& getSecond() noexcept { return const_cast<T2&>(getSecond()); }
	const T1& getFirst() const noexcept { return *this; }
	const T2& getSecond() const noexcept { return second; }

};