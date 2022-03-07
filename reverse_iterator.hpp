#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iostream>
#include "iterator_traits.hpp"


namespace ft
{
	template <class iterator>
	class reverse_iterator
	{
		typedef iterator iterator_type;
		typedef typename std::iterator_traits<iterator>::iterator_category iterator_category;
		typedef typename std::iterator_traits<iterator>::value_type value_type;
		typedef typename std::iterator_traits<iterator>::difference_type difference_type;
		typedef typename std::iterator_traits<iterator>::pointer pointer;
		typedef typename std::iterator_traits<iterator>::reference reference;

		protected:
			iterator_type _current;

		public:
			// MEMBER FUNCTIONS //
			// (constructor)	✅
			// operator=		✅
			// base				✅
			// operator*		✅
			// operator->		✅
			// operator[]		✅
			// operator++		✅
			// operator++(int)	✅
			// operator+=		✅
			// operator+		✅
			// operator--		✅
			// operator--(int)	✅
			// operator-=		✅
			// operator-		✅

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

			reference operator*() const
			{
				iterator_type tmp(_current);
				tmp--;
				return (*tmp);
			};
 
			pointer operator->() const { return (&(operator*())); };

			reference operator[] (difference_type n) const { return (base()[-n - 1]); };

			reverse_iterator& operator++()
			{
				_current--;
				return (*this);
			};

			reverse_iterator  operator++(int)
			{
				reverse_iterator temp = *this;
				++(*this);
				return temp;
			};

			reverse_iterator& operator+= (difference_type n)
			{
				_current -= n;
				return (*this);
			};

			reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_current - n)); };

			reverse_iterator& operator--()
			{
				_current++;
				return (*this);
			};

			reverse_iterator  operator--(int)
			{
				reverse_iterator temp = *this;
				--(*this);
				return temp;
			};

			reverse_iterator& operator-= (difference_type n)
			{
				_current += n;
				return (*this);
			};

			reverse_iterator operator- (difference_type n) const { return (reverse_iterator(_current + n)); };
	};
	// Non-member functions 🚧
	// compares the underlying iterators (function template) :
	// operator==	✅
	// operator!=	✅
	// operator<	✅
	// operator<=	✅
	// operator>	✅
	// operator>=	✅
	// operator+	✅
	// operator-	✅

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs._current == rhs._current); };

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs._current != rhs._current); };

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs._current > rhs._current); };

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs._current >= rhs._current); };

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs._current < rhs._current); };

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs._current <= rhs._current); };

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{ return (rev_it + n); };

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (rhs.base() - lhs.base()); };
}

#endif