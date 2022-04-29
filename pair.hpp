/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:06:13 by mvaldes           #+#    #+#             */
/*   Updated: 2022/04/29 15:06:14 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

		public:
			first_type  first;
			second_type second;

		public:
			pair() : first(first_type()), second(second_type()) {};

			template<class U, class V>
			pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {};

			pair (const first_type& a, const second_type& b) : first(a), second(b) {};

			~pair(){};

			pair& operator= (const pair& other)
			{
				if (this != &other)
				{
					first = other.first;
					second = other.second;
				}
				return (*this);
			};
	};
	/// RELATIONAL OPERATORS
	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); };
	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (!(lhs == rhs)); };
	template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (lhs.first < rhs.first || (!(lhs.first < rhs.first) && lhs.second < rhs.second)); };
	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (!(rhs < lhs)); };
	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (rhs < lhs); };
	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (!(lhs < rhs)); };
	/**/
	template <class T1,class T2>
	ft::pair<T1,T2> make_pair (T1 x, T2 y)
	{ return ( ft::pair<T1,T2>(x,y) ); }
}

#endif