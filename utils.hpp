#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

# define WHAT_TYPE_M(TYPE) template <> struct what_type<TYPE> : public type_struct<true> {};

namespace ft
{

	///// ENABLE_IF /////
	template<bool Cond, class T = void>
	struct enable_if{};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
	/////////////////////

	/// IS_INTEGRAL ////
	template <bool result>
	struct type_struct
	{
		typedef bool value_type;
		static const value_type value = result;
	};

	template <typename>
	struct what_type : public type_struct<false> {};

	WHAT_TYPE_M(bool)
	WHAT_TYPE_M(char)
	WHAT_TYPE_M(char16_t)
	WHAT_TYPE_M(char32_t)
	WHAT_TYPE_M(signed char)
	WHAT_TYPE_M(int)
	WHAT_TYPE_M(short int)
	WHAT_TYPE_M(long int)
	WHAT_TYPE_M(long long int)
	WHAT_TYPE_M(unsigned char)
	WHAT_TYPE_M(unsigned short int)
	WHAT_TYPE_M(unsigned int)
	WHAT_TYPE_M(unsigned long int)
	WHAT_TYPE_M(unsigned long long int)

	template <class T>
	struct is_integral : public what_type<T>{};
	/////////////////////

}

#endif