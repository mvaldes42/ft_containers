/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:06:26 by mvaldes           #+#    #+#             */
/*   Updated: 2022/04/29 15:06:27 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
// #include <uchar.h>

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
	// WHAT_TYPE_M(char16_t)
	// WHAT_TYPE_M(char32_t)
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


	/// LEXICOGRPHICAL_COMPARE ////
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1<*first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	};

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1!=last1)
		{
			if (first2==last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	};
	/////////////////////
}

#endif