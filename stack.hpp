#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T 			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		private:
			container_type c;
		public:
			// ** // FUNCTIONS // ** // ✅

			/*
				constructor
				=		✅
				empty	✅
				size	✅
				top		✅
				push	✅
				pop		✅
			*/
			explicit stack (const container_type& ctnr = container_type());
			stack( const stack& other );
			~stack();
			stack& operator=( const stack& other )
			{
				c = other.c;
				return (*this);
			};
			bool empty() const { return (c.empty(); )};
			size_type size() const { return (c.size()); };
			value_type& top() { return (c.back()); };
			const value_type& top() const { return (c.back()); };
			void push (const value_type& val) { c.push_back(value); };
			void pop() { c.pop_back(); };
	};
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
}

#endif