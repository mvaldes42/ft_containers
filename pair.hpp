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

		private:
			first_type  first;
			second_type second;

		public:

		pair() : first(T1()), second(T2()) {};
		template<class U, class V>
		pair (const pair<U,V>& pr);
		pair (const first_type& a, const second_type& b) : first(a), second(b) {};

		// implicitly declared:
		pair& operator= (const pair& pr);
	};
	/// RELATIONAL OPERATORS
	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); };
	// template <class T1b, class T2b>
	// bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs);
	// { return (!(lhs == rhs)); };
	// template <class T1, class T2>
	// bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	// {
	// 	return (lhs.first < rhs.first || (!(lhs.first < rhs.first) && lhs.second < rhs.second));
	// };
	// template <class T1, class T2>
	// bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs);
	// template <class T1, class T2>
	// bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs);
	// template <class T1, class T2>
	// bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs);
}

#endif