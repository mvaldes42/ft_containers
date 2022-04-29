/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:06:21 by mvaldes           #+#    #+#             */
/*   Updated: 2022/04/29 15:06:22 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "vector.hpp"

# define RELA_OPE(OPE) template <class T1, class Container1> friend bool operator OPE (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef Container container_type;

		protected:
			container_type c;
		public:
			explicit stack( const Container& cont = Container() ) : c(cont) {};
			stack( const stack& other ) { c = other.c; };
			~stack(){};
			stack& operator=( const stack& other )
			{
				c = other.c;
				return (*this);
			};
			bool empty() const { return (c.empty()); };
			size_type size() const { return (c.size()); };
			value_type& top() { return (c.back()); };
			const value_type& top() const { return (c.back()); };
			void push (const value_type& val) { c.push_back(val); };
			void pop() { c.pop_back(); };

			RELA_OPE(==)
			RELA_OPE(!=)
			RELA_OPE(<)
			RELA_OPE(>)
			RELA_OPE(>=)
			RELA_OPE(<=)
	};
	template <class T, class Container>
	bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{ return (lhs.c == rhs.c); };

	template <class T, class Container>
	bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{ return (lhs.c != rhs.c); };

	template <class T, class Container>
	bool operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{ return (lhs.c < rhs.c); };
	
	template <class T, class Container>
	bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{ return (lhs.c <= rhs.c); };

	template <class T, class Container>
	bool operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{ return (lhs.c > rhs.c); };

	template <class T, class Container>
	bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{ return (lhs.c >= rhs.c); };
}

#endif