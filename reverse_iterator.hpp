#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iostream>

namespace ft
{
	template< class Iter >
	class reverse_iterator
	{
		// Member types
		typedef Iter iterator_type;
		typedef typename std::iterator_traits<Iter>::iterator_category iterator_category;
		std::iterator_traits<Iter>::value_type value_type
		std::iterator_traits<Iter>::difference_type difference_type
		std::iterator_traits<Iter>::pointer pointer
		std::iterator_traits<Iter>::reference reference

		// Member object
		protected:
		iterator_type current // the underlying iterator of which base() returns a copy

		public:
		// Member functions
		// (constructor) constructs a new iterator adaptor
		reverse_iterator();
		explicit reverse_iterator (iterator_type it);
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it);
		// operator=
		// base accesses the underlying iterator
		// operator* accesses the pointed-to element
		// operator-> accesses the pointed-to element
		// operator[]
		// operator++
		// operator++(int)
		// operator+=
		// operator+
		// operator--
		// operator--(int)
		// operator-=
		// operator-
	};
}
// Non-member functions
// compares the underlying iterators (function template) :
// operator==
// operator!=
// operator<
// operator<=
// operator>
// operator>=

// operator+
// operator-

#endif