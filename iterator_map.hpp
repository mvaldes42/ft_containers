#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag

namespace ft
{
	//boolean is true is const
	template <bool isConst, typename falseConst, typename trueConst>
	struct chooseConst {};

	//sets 2nd parameter as ref and pointer
	template <typename falseConst, typename trueConst>
	struct chooseConst<false, falseConst, trueConst>
	{ typedef falseConst type; };

	//sets 2nd parameter as (const) ref and pointer
	template <typename falseConst, typename trueConst>
	struct chooseConst<true, falseConst, trueConst>
	{ typedef trueConst type; };

	template < class Key, class T, typename node, bool isConst = false, class Compare = std::less<Key> >
	class mapIterator
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef Compare key_compare;
			typedef ft::pair<const Key, T> value_type;
			typedef size_t size_type;
			typedef	std::ptrdiff_t difference_type;

			typedef typename std::bidirectional_iterator_tag iterator_category;
			typedef typename chooseConst<isConst, value_type &, const value_type &>::type reference;
			typedef typename chooseConst<isConst, value_type *, const value_type *>::type pointer;

		private:

			node		*_node;
			key_compare	_comp;

		public:
			/*
				1- Is default-constructible, copy-constructible, copy-assignable and destructible (X a; X b(a); b = a;)

				2- Can be compared for equivalence using the equality/inequality operators
				(meaningful when both iterator values iterate over the same underlying sequence). (a == b; a!=b )

				3- Can be dereferenced as an rvalue (if in a dereferenceable state). (*a; a-> b)

				4- For mutable iterators (non-constant iterators):
					Can be dereferenced as an lvalue (if in a dereferenceable state). (*a = t)

				5- Can be incremented (if in a dereferenceable state).
				The result is either also dereferenceable or a past-the-end iterator.
				Two iterators that compare equal, keep comparing equal after being both increased. (++a; a++; *a++)

				6- Can be decremented (if a dereferenceable iterator value precedes it). (--a; a--; *a--)
			*/
			mapIterator() {};
			mapIterator(const mapIterator &src);
			~mapIterator() {};
			mapIterator & operator = (const mapIterator &rhs);

			bool operator == (const mapIterator & rhs) const { return (_node == rhs._node); };
			bool operator != (const mapIterator & rhs) const { return !(this == rhs); };
			reference operator *() const { return _node->dataPair; };
			pointer operator ->() const { return &_node->dataPair; };

			mapIterator & operator ++() {};
			mapIterator & operator ++(int) {};

			mapIterator & operator --() {};
			mapIterator & operator --(int) {};
	};
}

#endif