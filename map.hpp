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
			ft::pair<const Key, T>	dataPair;
			node					*father;
			node					*left;
			node					*right;
			size_t					depth;

			node() : dataPair(), father(), left(), right(), depth(0) {};
			node(ft::pair<const Key, T> pair) :  node(), dataPair(pair) { std::cout << "Hello" << std::endl; };
			node(size_t depth) : node(), depth(depth) {};
			node(const node &other) : dataPair(other.dataPair), father(other.father), left(other.left), right(other.right), depth(other.depth) {};
			~node() { depth = 0; }
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
			// typedef struct ft::node<Key, T> *tree;
			typedef typename ft::node<key_type, mapped_type> node_type;
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

		// private:
		public :
			node_type		*_racine;
			size_type		_nbNoeuds;
			allocator_type	_allocPair;
			allocator_node	_allocNode;
			key_compare		_comp;
			size_type		_treeHeight;

			// CREATE NOTE
			node_type *createNode(value_type pair)
			{
				node_type tempNode;
				node_type *newNode = _allocNode.allocate(1);
				_allocNode.construct(newNode, tempNode);
				_allocPair.construct(&newNode->dataPair, pair);
				newNode->depth = 10;
				return (newNode);
			};
			node_type *createNode() { return (createNode(value_type())); };
			node_type *createNode(size_type depth)
			{
				node_type *tmp = createNode();
				tmp->depth = depth;
				return (tmp);
			};

			// DESTROY NODE
			void destroyNode(node_type *node)
			{ 
				_allocPair.destroy(&node->dataPair);
				_allocNode.destroy(node);
				_allocNode.deallocate(node, 1);
			}
			// Find NODE
			// will search node inside tree
			// https://www.cs.odu.edu/~zeil/cs361/latest/Public/bst/index.html
			bool	contains(node_type &subTree, node_type const &needle)
			{
				if (isTreeEmpty(&subTree))
					return false;
				if (_comp(needle.dataPair.first , subTree.dataPair.first))
					return (contains(*subTree.left, needle));
				else if (_comp(subTree.dataPair.first , needle.dataPair.first))
					return contains(*subTree.right, needle);
				else
					return true;
			}
			node_type *findNode (node_type &subTree, node_type const &needle)
			{
				if (isTreeEmpty(&subTree))
					return NULL;
				if (_comp(needle.dataPair.first , subTree.dataPair.first))
					return (findNode(*subTree.left, needle));
				else if (_comp(subTree.dataPair.first , needle.dataPair.first))
					return findNode(*subTree.right, needle);
				else
					return &subTree;
			};

			// https://www.cs.odu.edu/~zeil/cs361/latest/Public/bst/index.html
			// INSERT NODE
			void insertNode(node_type *subTree, node_type *toInsert)
			{
				if (isTreeEmpty(subTree))
				{
					subTree = toInsert;
					std::cout << "toInsert:" << toInsert->dataPair.first << std::endl;
				}
				else if (_comp(toInsert->dataPair.first, subTree->dataPair.first))
					insertNode(subTree->left, toInsert);
				else if (_comp(subTree->dataPair.first, toInsert->dataPair.first))
					insertNode(subTree->right, toInsert);
				else
					;
			}

			// void insertNode(node_type *src, node_type *node)
			// {
			// 	if (isTreeEmpty(src))
			// 		src = node;
			// 	else if (_comp(node->dataPair.first ,src->dataPair.first))
			// 	{
			// 		if (isTreeEmpty(getLeftTree(src)))
			// 			src->left = node;
			// 		else
			// 			insertNode(getLeftTree(src), node);
			// 	}
			// 	else if (!_comp(node->dataPair.first, src->dataPair.first) && node->dataPair.first != src->dataPair.first)
			// 	{
			// 		if (isTreeEmpty(getRightTree(src)))
			// 			src->right = node;
			// 		else
			// 			insertNode(getRightTree(src), node);
			// 	}
			// }
			// DELETE NODE

			//ISTREE EMPTY
			bool isTreeEmpty(node_type *tree) const
			{ return (tree == NULL); };

			node_type *getRightTree(node_type *tree) const
			{
				if (isTreeEmpty(tree))
					return NULL;
				return (tree->right);
			};
			node_type *getLeftTree(node_type *tree) const
			{
				if (isTreeEmpty(tree))
					return NULL;
				return (tree->left);
			};
			bool isLeaf(node_type *node) const
			{
				if (isEmpty(node))
					return false;
				else if (isTreeEmpty(getLeftTree(node)) && isTreeEmpty(getRightTree(node)))
					return true;
				return false;
			}
			bool isInsideNode(node_type *node) const {return (!isLeaf(node)); };

			//TREE HEIGHT
			//- un arbre vide est de hauteur 0
			// - un arbre non vide a pour hauteur 1 + la hauteur maximale entre ses fils.

			size_type max(size_type a, size_type b)
			{
				return (a > b) ? a : b;
			};
			size_type treeHeight(node_type *tree)
			{
				if (isTreeEmpty(tree))
					return (0);
				return (1 + max(treeHeight(getLeftTree(tree)), treeHeight(getRightTree(tree))));
			};
			void setTreeHeight() { _treeHeight = treeHeight(_racine); };

			// TYPE DE PARCOURS PREFIXE
			void prefix(node_type *tree) const
			{
				if (!isTreeEmpty(tree))
				{
					std::cout << "Key: " << tree->dataPair.first <<  ", Value: " << tree->dataPair.second << std::endl;
					prefix(getLeftTree(tree));
					prefix(getRightTree(tree));
				}
			}

		public:
			// 23.3.1.1 construct/copy/destroy:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _nbNoeuds(0), _allocPair(alloc), _comp(comp)
			{
				std::cout << "hello" << std::endl;
				_racine = createNode(0);
				std::cout << "_racine->depth: " << _racine->depth << std::endl;
				// prefix(_racine);
				// value_type test;
				// test.first = 10;
				// insertNode(_racine, createNode(test));
			};	
			template <class InputIterator>
 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
			map (const map& x);
			/**/
			~map(){ destroyNode(_racine); };
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