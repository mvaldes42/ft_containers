/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:06:07 by mvaldes           #+#    #+#             */
/*   Updated: 2022/04/29 15:45:58 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <unistd.h>
#include <iostream>
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "iterator_map.hpp"
#include "utils.hpp"

namespace ft
{
	template <class Key, class T>
	struct node
	{
		public :
			ft::pair<const Key, T>	dataPair;
			node					*parent;
			node					*left;
			node					*right;
			size_t					height;

			node() : dataPair(), parent(NULL), left(NULL), right(NULL), height(0) {};
			node(ft::pair<const Key, T> pair) :  node(), dataPair(pair) {};
			node(const node &other)
			: dataPair(other.dataPair), parent(other.parent), left(other.left), right(other.right), height(other.height) {};
			~node() {};
	};
	template < class Key,class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:

			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const Key, T> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef typename Alloc::reference reference;
			typedef typename Alloc::const_reference const_reference;

			typedef size_t size_type;
			typedef	typename Alloc::difference_type difference_type;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;

			typedef typename ft::node<key_type, mapped_type> node_type;
			typedef typename Alloc::template rebind<ft::node<Key, T> >::other allocator_node;

			typedef	typename ft::mapIterator<Key, T, node_type, key_compare, false>	iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef	typename ft::mapIterator<Key, T, node_type, key_compare, true>	const_iterator;
			typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			class value_compare : public std::binary_function<value_type,value_type,bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					bool operator()(const value_type& x, const value_type& y) const
					{ return comp(x.first, y.first); }
			};

		private:

			node_type		*_racine;
			node_type		*_endNode;
			size_type		_nbNodes;
			allocator_type	_allocPair;
			allocator_node	_allocNode;
			key_compare		_comp;

		public:
		
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _racine(NULL), _nbNodes(0), _allocPair(alloc), _comp(comp)
			{
				_endNode = createNode();
				insertNode(_endNode);
			};

			template <class InputIterator>
 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _racine(NULL), _nbNodes(0), _allocPair(alloc), _comp(comp)
			{
				_endNode = createNode();
				insertNode(_endNode);
				for (; first != last; first++)
		 			insert(*first);
			};

			map (const map& x) : _racine(NULL), _nbNodes(0), _allocPair(x._allocPair), _comp(x._comp)
			{
				_endNode = createNode();
				insertNode(_endNode);
				insert(x.begin(), x.end());
			};

			~map()
			{
				if (!empty())
					clear();
				destroyNode(_endNode);
			};

			map& operator= (const map& x)
			{
				if (!empty())
					clear();
				insert(x.begin(), x.end());
				return (*this);
			};

			iterator begin()
			{ return (iterator(_racine, _endNode, _endNode->right, _comp)); };

			const_iterator begin() const
			{ return (const_iterator(_racine, _endNode, _endNode->right, _comp)); };

			iterator end()
			{ return (iterator(_racine, _endNode, _endNode, _comp)); };

			const_iterator end() const
			{ return (const_iterator(_racine, _endNode, _endNode, _comp)); };

			reverse_iterator rbegin() { return reverse_iterator(end()); };

			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };

			reverse_iterator rend() { return reverse_iterator(begin()); };
	
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

			bool empty() const { return (_nbNodes == 0); };

			size_type size() const {return (_nbNodes); };

			size_type max_size() const { return (_allocNode.max_size()); };

			mapped_type& operator[] (const key_type& k)
			{
				node_type *newNode = findNode(k, _racine);
				if (isTreeEmpty(newNode))
				{
					newNode = createNode(value_type(k, mapped_type()));
					if (_nbNodes == 0 && _racine == _endNode)
						insertNode(newNode, NULL);
					else
						insertNode(newNode);
				}
				return (newNode->dataPair.second);
			};

			ft::pair<iterator,bool> insert (const value_type& val)
			{
				node_type *foundNode = findNode(val.first);	
				if (foundNode)
					return (ft::pair<iterator, bool>(iterator(_racine, _endNode, foundNode, _comp), false));
				node_type *insertedNode;
				if (_nbNodes == 0 && _racine == _endNode)
				{
					insertedNode = insertNode(createNode(val), NULL);
				}
				else
					insertedNode = insertNode(createNode(val));
				return (ft::pair<iterator, bool>(iterator(_racine, _endNode, insertedNode, _comp), true));
			};

			iterator insert (iterator position, const value_type& val)
			{
				node_type *foundNode = findNode(val.first);
				if (foundNode)
					return (iterator(_racine, _endNode, foundNode, _comp));
				node_type *insertedNode;
				if (position.getNode() == _racine && _racine == _endNode)
				{
					insertedNode = insertNode(createNode(val), NULL);
					return (iterator(_racine, _endNode, insertedNode, _comp));
				}
				if (_comp(val.first, position.getNode()->dataPair.first))
				{
					for (; position != end() && _comp(val.first, position.getNode()->dataPair.first); position--);
					position++;	
				}
				else if (_comp(position.getNode()->dataPair.first, val.first))
				{
					for (; position != end() && _comp(position.getNode()->dataPair.first, val.first); position++);
					position--;
				}
				insertedNode = insertNode(createNode(val), position.getNode());
				return (iterator(_racine, _endNode, insertedNode));
			};

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			};

			void erase (iterator position) { removeNode(position.getNode()); };

			size_type erase (const key_type& k)
			{
				node_type *foundNode = findNode(k);
				if (foundNode == NULL)
					return 0;
				removeNode(foundNode);
				return 1;
			};

			void erase (iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
			};

			void swap (map& x)
			{
				node_type		*_racineTemp = x._racine;
				node_type		*_endNodeTemp = x._endNode;
				size_type		_nbNodesTemp = x._nbNodes;
				allocator_type	_allocPairTemp = x._allocPair;
				allocator_node	_allocNodeTemp = x._allocNode;
				key_compare		_compTemp = x._comp;

				x._racine = _racine;
				x._endNode = _endNode;
				x._nbNodes = _nbNodes;
				x._allocPair = _allocPair;
				x._allocNode = _allocNode;
				x._comp = _comp;

				_racine = _racineTemp;
				_endNode = _endNodeTemp;
				_nbNodes = _nbNodesTemp;
				_allocPair = _allocPairTemp;
				_allocNode = _allocNodeTemp;
				_comp = _compTemp;
			};

			void clear() { erase(begin(), end()); };

			key_compare key_comp() const { return (_comp); };

			value_compare value_comp() const { return (value_compare(_comp)); };

			iterator find (const key_type& k)
			{
				node_type *foundNode = findNode(k, _racine);
				if (foundNode)
					return (iterator(_racine, _endNode, foundNode, _comp));
				return (end());
			};

			const_iterator find (const key_type& k) const
			{
				node_type *foundNode = findNode(k, _racine);
				if (foundNode)
					return (const_iterator(_racine, _endNode, foundNode, _comp));
				return (const_iterator(end()));
			};

			size_type count (const key_type& k) const
			{
				if (containsNode(k, _racine))
					return (1);
				return (0);
			};

			iterator lower_bound (const key_type& k)
			{
				iterator it = begin();
				iterator itEnd = end();
				for (; it != itEnd && _comp(it.getNode()->dataPair.first, k) == true; it++);
				return (it);
			};

			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator it = begin();
				const_iterator itEnd = end();
				for (; it != itEnd && _comp(it.getNode()->dataPair.first, k) == true; it++);
				return (it);
			};

			iterator upper_bound (const key_type& k)
			{
				iterator it = begin();
				iterator itEnd = end();
				for (; it != itEnd && _comp(k, it.getNode()->dataPair.first) == false; it++);
				return (it);				
			};

			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator it = begin();
				const_iterator itEnd = end();
				for (; it != itEnd && _comp(k, it.getNode()->dataPair.first) == false; it++);
				return (it);				
			};

			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{ return (ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k))); };

			ft::pair<iterator,iterator> equal_range (const key_type& k)
			{ return (ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k))); };

			allocator_type get_allocator() const { return (_allocNode); };

		private:
			/////////////////////////////////
			////	NODE OPERATIONS		////
			///////////////////////////////
			/*		CREATE NODE		*/
			node_type *createNode() { return (createNode(value_type())); };
			node_type *createNode(value_type pair)
			{
				node_type tempNode;
				node_type *newNode = _allocNode.allocate(1);
				_allocNode.construct(newNode, tempNode);
				_allocPair.construct(&newNode->dataPair, pair);
				return (newNode);
			};
			/*		DESTROY NODE		*/
			void destroyNode(node_type *node)
			{
				_allocNode.destroy(node);
				_allocNode.deallocate(node, 1);
				node = NULL;
			};
			/*		FIND NODE		*/
			bool containsNode( node_type const *needle, node_type *subTree) const
			{ return (containsNode(needle->dataPair.first, subTree)); };
			bool containsNode( key_type const &key, node_type *subTree) const
			{
				if(isTreeEmpty(subTree) || isEndNode(subTree))
					return false;
				if (_comp(key , subTree->dataPair.first))
					return containsNode(key, subTree->left);
				else if (_comp(subTree->dataPair.first , key))
					return containsNode(key, subTree->right);
				else
					return true;
			};
			node_type *findNode(key_type const key) const
			{ return (findNode(key, _racine)); };
			node_type *findNode(node_type const *needle, node_type *subTree) const
			{ return (findNode(needle->dataPair.first, subTree)); };
			node_type *findNode(key_type const key, node_type *subTree) const
			{
				if(isTreeEmpty(subTree) || isEndNode(subTree))
					return NULL;
				if (_comp(key , subTree->dataPair.first))
					return findNode(key, subTree->left);
				else if (_comp(subTree->dataPair.first , key))
					return findNode(key, subTree->right);
				else
					return subTree;
			};
			/*		INSERT NODE		*/
			node_type *insertNode(node_type *toInsert)
			{ return insertNode(toInsert, _racine); };
			node_type *insertNode(node_type *toInsert, node_type *subTree) 
			{
				if (isTreeEmpty(subTree) && _nbNodes == 0)
				{
					_racine = toInsert;
					if (toInsert != _endNode)
						_nbNodes++;
					setEndNodeLast(_racine);
					setEndNodeFirst(_racine);
					subTree = _racine;
				}
				else if (_comp(toInsert->dataPair.first, subTree->dataPair.first))
				{
					if (isTreeEmpty(subTree->left) || isEndNode(subTree->left))
					{
						node_type *oldLeft = subTree->left;
						toInsert->parent = subTree;
						subTree->left = toInsert;
						_nbNodes++;
						if (isEndNode(oldLeft))
							setEndNodeFirst(subTree->left);
						subTree = subTree->left;
					}
					else
						return insertNode(toInsert, subTree->left);
				}
				else if (_comp(subTree->dataPair.first, toInsert->dataPair.first))
				{
					if (isTreeEmpty(subTree->right) || isEndNode(subTree->right))
					{
						node_type *oldRight = subTree->right;
						toInsert->parent = subTree;
						subTree->right = toInsert;
						_nbNodes++;
						if (isEndNode(oldRight))
							setEndNodeLast(subTree->right);
						subTree = subTree->right;
					}
					else
						return insertNode(toInsert, subTree->right);
				}
				balanceTree(subTree);
				return subTree;
			};
			/*		DELETE NODE		*/
			void removeNode(node_type *toDel)
			{
				node_type *toBalance;
				if (toDel == _racine)
				{
					toBalance = NULL;
					if (_nbNodes == 1)
					{
						_racine = _endNode;
						_endNode->right = _endNode;
						_endNode->left = _endNode;
					}
					else if (_racine->left && _racine->right == _endNode)
					{
						_racine = toDel->left;
						toDel->left->parent = NULL;
						node_type *maxNode = getMax(toDel->left);
						maxNode->right = _endNode;
						_endNode->left = maxNode;
					}
					else if (_racine->right && _racine->left == _endNode)
					{
						_racine = toDel->right;
						_racine->parent = NULL;
						node_type *minNode = getMin(toDel->right);
						minNode->left = _endNode;
						_endNode->right = minNode;
						}
					else
					{
						node_type *maxNode = getMax(_racine->left);
						_allocPair.destroy(&_racine->dataPair);
						_allocPair.construct(&_racine->dataPair, maxNode->dataPair);
						removeNode(findNode(maxNode->dataPair.first, _racine->left));
						return ;
					}
				}
				else
				{
					if (( isTreeEmpty(toDel->left) || isEndNode(toDel->left) ) && ( isTreeEmpty(toDel->right) || isEndNode(toDel->right) ))
					{
						if (isEndNode(toDel->left))
						{
							_endNode->right = toDel->parent;
							toDel->parent->left = _endNode;
						}
						else if (isEndNode(toDel->right))
						{
							_endNode->left = toDel->parent;
							toDel->parent->right = _endNode;
						}
						else if (toDel->dataPair.first <= toDel->parent->dataPair.first)
							toDel->parent->left = NULL;
						else
							toDel->parent->right = NULL;
					}
					else if ( (!isTreeEmpty(toDel->left) && !isEndNode(toDel->left)) && (isTreeEmpty(toDel->right) || isEndNode(toDel->right)) )
					{
						if (toDel->dataPair.first <= toDel->parent->dataPair.first)
							toDel->parent->left = toDel->left;
						else
							toDel->parent->right = toDel->left;
						toDel->left->parent = toDel->parent;
						if (isEndNode(toDel->right))
						{
							toDel->left->right = _endNode;
							_endNode->left = toDel->left;
						}
					}
					else if ( (!isTreeEmpty(toDel->right) && !isEndNode(toDel->right)) && (isTreeEmpty(toDel->left) || isEndNode(toDel->left)) )
					{
						if (toDel->dataPair.first <= toDel->parent->dataPair.first)
							toDel->parent->left = toDel->right;						
						else
							toDel->parent->right = toDel->right;
						toDel->right->parent = toDel->parent;
						if (isEndNode(toDel->left))
						{
							toDel->right->left = _endNode;
							_endNode->right = toDel->right;
						}
					}
					else
					{
						node_type *maxNode = getMax(toDel->left);
						_allocPair.destroy(&toDel->dataPair);
						_allocPair.construct(&toDel->dataPair, maxNode->dataPair);
						removeNode(findNode(maxNode->dataPair.first, toDel->left));
						return ;
					}
					toBalance = toDel->parent;
				}
				balanceTree(toBalance);
				destroyNode(toDel);
				_nbNodes -= 1;
			};

			/////////////////////////////////
			////	TREE OPERATIONS		////
			///////////////////////////////

			/*	https://www.programiz.com/dsa/avl-tree	*/

			size_type max(int a, int b) { return (a > b) ? a : b; };
			size_type getHeight(node_type *node) const
			{
  				if (isTreeEmpty(node) || isEndNode(node))
				  return (0);
  				return (node->height);
			};
			void setHeight(node_type *node)
			{
				if (isTreeEmpty(node) || isEndNode(node))
					return ;
				node->height = 1 + max(getHeight(node->left), getHeight(node->right));
			};
			/*
				Gets difference in heights between the right and left subtrees.
				In a balanced tree, this difference must be -1, 0, or 1. 
					-	0 means that both subtrees have the same height.
					-	-1 means that the left tree is higher (by 1)
					-	1 means that the right tree is higher.
			*/
			int getBalanceFactor(node_type *node) const
			{
				if (isTreeEmpty(node) || isEndNode(node))
					return (0);
				return (getHeight(node->left) - getHeight(node->right));
			};

			void balanceTree(node_type *node)
			{
				int	factor;

				while (node)
				{
					setHeight(node);
					factor = getBalanceFactor(node);
					if (factor > 1)
					{
						if (getBalanceFactor(node->left) > 0)
							rightRotate(node);
						else if (getBalanceFactor(node->left) <= 0)
						{
							leftRotate(node->left);
							rightRotate(node);
						}
					}
					else if (factor < -1)
					{
						if (getBalanceFactor(node->right) < 0)
							leftRotate(node);
						else if (getBalanceFactor(node->right) >= 0)
						{
							rightRotate(node->right);
							leftRotate(node);
						}
					}
					node = node->parent;
				}
			};

			void rightRotate(node_type *futureBottom)
			{
				node_type *futureTop = futureBottom->left;

				futureBottom->left = futureTop->right;
				if (futureTop->right)
					futureTop->right->parent = futureBottom;
				futureTop->right = futureBottom;
				futureTop->parent = futureBottom->parent;
				if	(futureBottom->parent && futureBottom->parent->left == futureBottom)
					futureBottom->parent->left = futureTop;
				else if (futureBottom->parent)
					futureBottom->parent->right = futureTop;
				futureBottom->parent = futureTop;
				if (isTreeEmpty(futureTop->parent))
					_racine = futureTop;
				futureBottom->height = max(getHeight(futureBottom->left), getHeight(futureBottom->right)) + 1;
				futureTop->height = max(getHeight(futureTop->left), getHeight(futureTop->right)) + 1;
			}

			void leftRotate(node_type *futureBottom)
			{
				node_type *futureTop = futureBottom->right;

				futureBottom->right = futureTop->left;
				if (futureTop->left)
					futureTop->left->parent = futureBottom;
				futureTop->left = futureBottom;
				futureTop->parent = futureBottom->parent;
				if	(futureBottom->parent && futureBottom->parent->left == futureBottom)
					futureBottom->parent->left = futureTop;
				else if (futureBottom->parent)
					futureBottom->parent->right = futureTop;
				futureBottom->parent = futureTop;
				if (isTreeEmpty(futureTop->parent))
					_racine = futureTop;
				futureBottom->height = max(getHeight(futureBottom->left), getHeight(futureBottom->right)) + 1;
				futureTop->height = max(getHeight(futureTop->left), getHeight(futureTop->right)) + 1;
			}

			/////////////////////////////////
			////		UTILS			////
			///////////////////////////////
			bool isTreeEmpty(node_type *tree) const { return (tree == NULL); };

			bool isEndNode(node_type *node) const { return (node == _endNode); };	

			node_type*	getMax(node_type* node) const
			{
				if (!isTreeEmpty(node->right) && !isEndNode(node->right))
					return (getMax(node->right));
				return (node);
			}
			node_type*	getMin(node_type* node) const
			{
				if (!isTreeEmpty(node->left) && !isEndNode(node->left))
					return (getMin(node->left));
				return (node);
			}
			node_type *getFirst() const
			{
				iterator it(_racine, _endNode, NULL, _comp);
				while (it++ != _endNode)
					;
				return (it.getNode());
			};
			node_type *getLast() const
			{
				iterator it(_racine, _endNode, NULL, _comp);
				while (it-- != _endNode)
					;
				return (it.getNode());
			};
			void setEndNodeFirst(node_type *first)
			{
				_endNode->right = first;
				first->left = _endNode;
			};
			void setEndNodeFirst()
			{ setEndNodeFirst(getFirst()); };
			void setEndNodeLast(node_type *last)
			{
				_endNode->left = last;
				last->right = _endNode;
			};
			void setEndNodeLast()
			{ setEndNodeLast(getLast()); };
			void setEndNode()
			{
				setEndNodeFirst();
				setEndNodeLast();
			};

			/*		PRINT TREE		*/
			void printTree() { printTree("", _racine, false); };
			void printTree(const std::string& prefix, const node_type *node, bool isLeft)
			{
				if( node && node != NULL && node != _endNode)
				{
					std::cout << prefix;
					std::cout << (isLeft ? "├─L─" : "└─R─" );
					std::cout << node->dataPair.first << std::endl;
					printTree( prefix + (isLeft ? "│   " : "    "), node->left, true);
					printTree( prefix + (isLeft ? "│   " : "    "), node->right, false);
				}
			};
  	};
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typedef typename ft::node<Key, T> node_type;
		typedef	typename ft::mapIterator<Key, T, node_type, Compare, true> const_iterator;

		if (lhs.size() != rhs.size())
			return false;
		const_iterator startLeft = lhs.begin();
		const_iterator startRight = rhs.begin();
		for (; startLeft != lhs.end(); startLeft++, startRight++)
		{
			if (startLeft.getNode()->dataPair != startRight.getNode()->dataPair)
				return false;
		}
		return true;
	};
	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return !(operator==(lhs, rhs));};
	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); };
	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return (!(rhs<lhs)); };
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return (rhs < lhs); };
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return (!(lhs < rhs)); };

	template <class Key, class T, class Compare, class Alloc>
 	void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y) { x.swap(y); };
}

#endif