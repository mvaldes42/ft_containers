#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "reverse_iterator.hpp"

namespace ft
{
	template < class Key,									// map::key_type
			class T											// map::mapped_type
			class Compare = less<Key>,						// map::key_compare
			class Alloc = allocator<pair<const Key,T> >		// map::allocator_type
			>
	class map;
	{
		public:
			// types:
			typedef Key key_type;
			typedef T mapped_type;
			typedef pair<const Key, T> value_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef implementation defined iterator;
			typedef implementation defined const_iterator;
			typedef implementation defined size_type;
			typedef implementation defined difference_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			class value_compare : public binary_function<value_type,value_type,bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};
✅
🚧			// 23.3.1.1 construct/copy/destroy:
❌			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
❌			template <class InputIterator>
❌ 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
❌			map (const map& x);
			/**/
❌			~map();
			/**/
❌			map& operator= (const map& x);
			/// ITERATORS
❌			iterator begin();
❌			const_iterator begin() const;
			/**/
❌			iterator end();
❌			const_iterator end() const;
			/**/
❌			reverse_iterator rbegin();
❌			const_reverse_iterator rbegin() const;
			/**/
❌			reverse_iterator rend();
❌			const_reverse_iterator rend() const;
			/// CAPACITY
❌			bool empty() const;
❌			size_type size() const;
❌			size_type max_size() const;
			/// ELEMENT ACCESS
❌			mapped_type& operator[] (const key_type& k);
			/// MODIFIERS
❌			pair<iterator,bool> insert (const value_type& val);	
❌			iterator insert (iterator position, const value_type& val);
❌			template <class InputIterator>
❌			void insert (InputIterator first, InputIterator last);
			/**/
❌			void erase (iterator position);
❌			size_type erase (const key_type& k);
❌			void erase (iterator first, iterator last);
			/**/
❌			void swap (map& x);
			/**/
❌			void clear();
			/// OBSERVERS
❌			key_compare key_comp() const;
❌			value_compare value_comp() const;
			/// OPERATIONS
❌			iterator find (const key_type& k);
❌			const_iterator find (const key_type& k) const;
			/**/
❌			size_type count (const key_type& k) const;
			/**/
❌			iterator lower_bound (const key_type& k);
❌			const_iterator lower_bound (const key_type& k) const;
			/**/
❌			iterator upper_bound (const key_type& k);
❌			const_iterator upper_bound (const key_type& k) const;
			/**/
❌			pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
❌			pair<iterator,iterator> equal_range (const key_type& k);
			/// ALLOCATOR
❌			allocator_type get_allocator() const;
  	};
❌	template <class Key, class T, class Compare, class Alloc>
❌	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
❌	template <class Key, class T, class Compare, class Alloc>
❌	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
❌	template <class Key, class T, class Compare, class Alloc>
❌	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
❌	template <class Key, class T, class Compare, class Alloc>
❌	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
❌	template <class Key, class T, class Compare, class Alloc>
❌	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
❌	template <class Key, class T, class Compare, class Alloc>
❌	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
	/**/
❌	template <class Key, class T, class Compare, class Alloc>
❌ 	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y);
}

#endif