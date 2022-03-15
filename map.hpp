#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "reverse_iterator.hpp"
#include "pair.hpp"

namespace ft
{
	template <class Key, class T>
	struct node
	{
		public :
			ft::pair<const Key, T>	data;
			node					*father;
			node					*left;
			node					*right;
			int						distance;

			node() : data(), father(NULL), left(NULL), right(NULL), distance(0) {};
	};
	template < class Key,class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			// types:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const Key, T> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::const_reference const_reference;
			// typedef	typename Alloc::pointer iterator; ==> DO IT YOURSELF
			// typedef	typename Alloc::const_pointer const_iterator; ==> DO IT YOURSELF
			typedef size_t size_type;
			typedef	typename Alloc::difference_type difference_type;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;
			// typedef ft::reverse_iterator<iterator> reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef struct ft::node<Key, T> *tree;
			typedef typename Alloc::template rebind<ft::node<Key, T> >::other allocator_node; // BRACKETS ??

			class value_compare : public std::binary_function<value_type,value_type,bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};

		private:
			tree			_racine;
			size_type		_nbNoeuds;
			allocator_type	_allocTree;
			allocator_node	_allocNode;
			key_compare		_comp;

			tree createNode(value_type pair)
			{
				node<Key, T> hello;
				std::cout << "distance " << hello.distance << std::endl;
				// tree tmp = {NULL};
				tree tmp = _allocNode.allocate(1);
				_allocTree.construct(&tmp->data, pair);
				// memset(tmp, 0, sizeof(*tmp));
				std::cout << "distance " << tmp->distance << std::endl;
				return (tmp);
			};

		public:
			// 23.3.1.1 construct/copy/destroy:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _nbNoeuds(0), _allocTree(alloc), _comp(comp)
			{
				std::cout << "hello" << std::endl;
				_racine = createNode(value_type());
			};	
			template <class InputIterator>
 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
			map (const map& x);
			/**/
			~map(){};
			/**/
			map& operator= (const map& x);
			/// ITERATORS
			// iterator begin();
			// const_iterator begin() const;
			// /**/
			// iterator end();
			// const_iterator end() const;
			/**/
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			/**/
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;
			/// CAPACITY
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			/// ELEMENT ACCESS
			mapped_type& operator[] (const key_type& k);
			/// MODIFIERS
			// ft::pair<iterator,bool> insert (const value_type& val);	
			// iterator insert (iterator position, const value_type& val);
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last);
			/**/
			// void erase (iterator position);
			size_type erase (const key_type& k);
			// void erase (iterator first, iterator last);
			/**/
			void swap (map& x);
			/**/
			void clear();
			/// OBSERVERS
			key_compare key_comp() const;
			value_compare value_comp() const;
			/// OPERATIONS
			// iterator find (const key_type& k);
			// const_iterator find (const key_type& k) const;
			/**/
			size_type count (const key_type& k) const;
			/**/
			// iterator lower_bound (const key_type& k);
			// const_iterator lower_bound (const key_type& k) const;
			/**/
			// iterator upper_bound (const key_type& k);
			// const_iterator upper_bound (const key_type& k) const;
			/**/
			// ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			// ft::pair<iterator,iterator> equal_range (const key_type& k);
			/// ALLOCATOR
			allocator_type get_allocator() const;

		private:
			bool is_empty() const { return (_nbNoeuds == 0); };
			// node getRightSon const
			// {
			// 	if (is_empty())
			// 		return NULL;
			// 	else
			// 		return node.filsd;
			// };
  	};
	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	/**/
	template <class Key, class T, class Compare, class Alloc>
 	void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y);
}

#endif