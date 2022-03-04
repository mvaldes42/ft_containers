#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"


namespace ft
{
	template <class iterator>
	class reverse_iterator
	{
		// Member types
		typedef iterator iterator_type;
		typedef typename std::iterator_traits<iterator>::iterator_category iterator_category;
		typedef typename std::iterator_traits<iterator>::value_type value_type;
		typedef typename std::iterator_traits<iterator>::difference_type difference_type;
		typedef typename std::iterator_traits<iterator>::pointer pointer;
		typedef typename std::iterator_traits<iterator>::reference reference;

		// Member object
		protected:
			iterator_type _current; // the underlying iterator of which base() returns a copy

		public:

		// Member functions 🚧
		// (constructor) ✅
		// operator= ✅
		// base ✅
		// operator* ✅
		// operator-> ❌
		// operator[] ❌
		// operator++ ❌
		// operator++(int) ❌
		// operator+= ❌
		// operator+ ❌
		// operator-- ❌
		// operator--(int) ❌
		// operator-= ❌
		// operator- ❌


			reverse_iterator(): _current() {};
			explicit reverse_iterator (iterator_type it) : _current(it) {};
			template <iterator>
			reverse_iterator (const reverse_iterator<iterator>& rev_it) : _current(rev_it._current){};

			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other )
			{
				if (this != other)
					_current = other._current;
				return (*this);
			};

			iterator_type base() const { return _current; };

			//  reverse iterator r constructed from an iterator i => &*r == &*(i-1) //  (as long as r is dereferenceable)
			reference operator*() const
			{
				iterator_type tmp(_current);
				tmp--;
				return (*tmp);
			};

			// pointer operator->() const;

			reference operator[] (difference_type n) const { return (base()[-n-1]); };

			// reverse_iterator& operator++();

			// reverse_iterator  operator++(int);

			// reverse_iterator& operator+= (difference_type n);

			// reverse_iterator operator+ (difference_type n) const;

			// reverse_iterator& operator--();

			// reverse_iterator  operator--(int);

			// reverse_iterator& operator-= (difference_type n);

			// reverse_iterator operator- (difference_type n) const;
	};
}
// Non-member functions 🚧
// compares the underlying iterators (function template) :
// operator== ❌
// operator!= ❌
// operator< ❌
// operator<= ❌
// operator> ❌
// operator>= ❌
// operator+ ❌
// operator- ❌

// template <class Iterator>
// bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
// template <class Iterator>
// bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
// template <class Iterator>
// bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
// template <class Iterator>
// bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
// template <class Iterator>
// bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
// template <class Iterator>
// bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

// template <class Iterator>
// reverse_iterator<Iterator> operator+ (
// 	typename reverse_iterator<Iterator>::difference_type n,
// 	const reverse_iterator<Iterator>& rev_it);

// template <class Iterator>
// typename reverse_iterator<Iterator>::difference_type operator- (
// 	const reverse_iterator<Iterator>& lhs,
//     const reverse_iterator<Iterator>& rhs);


#endif