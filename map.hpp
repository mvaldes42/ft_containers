#ifndef MAP_HPP
#define MAP_HPP

#include <unistd.h>
#include <iostream>
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include "iterator_map.hpp"

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

			node() : dataPair(), parent(NULL), left(NULL), right(NULL){};
			node(ft::pair<const Key, T> pair) :  node(), dataPair(pair) {};
			node(const node &other) : dataPair(other.dataPair), parent(other.parent), left(other.left), right(other.right) {};
			~node()
			{
				parent = nullptr;
				left = nullptr;
				right = nullptr;
			}
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

			typedef	typename ft::mapIterator<Key, T, node_type, false>	iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef	typename ft::mapIterator<Key, T, node_type, true>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>				const_reverse_iterator;

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
			node_type		*_racine;
			node_type		*_endNode;
			size_type		_nbNodes;
			allocator_type	_allocPair;
			allocator_node	_allocNode;
			key_compare		_comp;

			// CREATE NOTE
			node_type *createNode(value_type pair)
			{
				node_type tempNode;
				node_type *newNode = _allocNode.allocate(1);
				_allocNode.construct(newNode, tempNode);
				_allocPair.construct(&newNode->dataPair, pair);
				return (newNode);
			};
			node_type *createNode() { return (createNode(value_type())); };

			// DESTROY NODE
			void destroyNode(node_type *node)
			{
				std::cout << "node destroyed is: " << node->dataPair.first << std::endl;
				_allocPair.destroy(&node->dataPair);
				_allocNode.destroy(node);
				_allocNode.deallocate(node, 1);
				node = nullptr;
			}

			// Find NODE
			bool containsNode( node_type const *needle, node_type *subTree) const
			{ return (containsNode(needle->dataPair.first, subTree)); }
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
			}
			node_type *findNode(key_type const key) const
			{ return (findNode(key, _racine)); };
			node_type *findNode(node_type const *needle, node_type *subTree) const
			{ return (findNode(needle->dataPair.first, subTree)); }
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
			}

			// INSERT NODE
			node_type *insertNode(node_type *toInsert, node_type *subTree)
			{ return insertNode(toInsert, subTree, subTree->parent);}
			node_type *insertNode(node_type *toInsert)
			{
				if (isTreeEmpty(_racine))
					return insertNode(toInsert, _racine, NULL);
				return insertNode(toInsert, _racine, _racine->parent);
			}
			node_type *insertNode(node_type *toInsert, node_type *subTree, node_type *parent) 
			{
				if (isTreeEmpty(subTree) && _nbNodes == 0)
				{
					_nbNodes++;
					_racine = toInsert;
					setEndNodeLast(_racine);
					setEndNodeFirst(_racine);
					return (_racine);
				}
				else if (isTreeEmpty(subTree) || subTree == _endNode)
				{
					_nbNodes++;
					toInsert->parent = parent;
					subTree = toInsert;
					return (subTree);
				}
				else if (_comp(toInsert->dataPair.first, subTree->dataPair.first))   
				{
					if (isTreeEmpty(subTree->left) || subTree->left == _endNode)
					{
						toInsert->parent = subTree;
						subTree->left = toInsert;
						_nbNodes++;
						if (subTree->left == getFirst())
						{
							setEndNodeFirst(subTree->left);
						}
						return (subTree->left);
					}
					else
						return insertNode(toInsert, subTree->left, subTree);
				}
				else if (_comp(subTree->dataPair.first, toInsert->dataPair.first))
				{
					if (isTreeEmpty(subTree->right) || subTree->right == _endNode)
					{
						toInsert->parent = subTree;
						subTree->right = toInsert;
						_nbNodes++;
						if (subTree->right == getLast())
							setEndNodeLast(subTree->right);
						return (subTree->right);
					}
					else
						return insertNode(toInsert, subTree->right, subTree);
				}
				return subTree;
			}

			node_type *findMin(node_type *t)
			{
				if(t == nullptr)
					return nullptr;
				if( t != _endNode && t->left == nullptr)
					return t;
				if (t == _endNode)
					return t->right;
				return findMin(t->left);
			}
			node_type *findMax(node_type *t)
			{
				if(t == nullptr)
					return nullptr;
				if( t != _endNode && t->right == nullptr)
					return t;
				if (t == _endNode)
					return t->left;
				return findMax(t->right);
			}

			// DELETE NODE

			// void removeNode(node_type *toRemove)
			// { removeNode(toRemove, _racine); }

			node_type*	searchMaxNode(node_type* root) const
			{
				if (root->right && root->right != _endNode)
					return (searchMaxNode(root->right));
				return (root);
			}

			node_type*	searchMinNode(node_type* root) const
			{
				if (root->left && root->left != _endNode)
					return (searchMinNode(root->left));
				return (root);
			}
			void removeNode(node_type *toDel)
			{
				// we already searched and found the node to remove and we're already at position.
				std::cout << "> toDel is " << toDel->dataPair.first << std::endl;
				/*	I/ toDel is _root				*/
				if (toDel == _racine)
				{
					/*	A) _root is the only node	*/
					if (_nbNodes == 1)
					{
						std::cout << "	> racine is the only node" << std::endl;
						// OR should we just del _racine ?
						// _racine = _endNode;
						// _endNode->right = _endNode;
						// _endNode->left = _endNode;
					}
					/*	B) _root has only one child	*/
					else if ((_racine->left && _racine->right == _endNode) || (_racine->right && _racine->left == _endNode))
					{
						/*	a) left child			*/
						if (_racine->left && _racine->right == _endNode)
						{
							std::cout << "	> racine has only a left child" << std::endl;
							_racine = _racine->left;
							_racine->parent = nullptr;
							_racine->right = _endNode;
							_endNode->left = _racine;
						}
						/*	b) right child			*/
						else
						{
							std::cout << "	> racine has only a right child" << std::endl;
							_racine = _racine->right;
							_racine->parent = nullptr;
							_racine->left = _endNode;
							_endNode->right = _racine;
						}
					}
					/*	C) _root has two children	*/
					else
					{
						std::cout << "	> racine has two children" << std::endl;
						node_type *maxNode = searchMaxNode(_racine->left);
						_allocPair.destroy(&_racine->dataPair);
						_allocPair.construct(&_racine->dataPair, maxNode->dataPair);
						removeNode(findNode(maxNode->dataPair.first, _racine->left));
						return ;
					}
				}
				/*	II/ toDel is not _root	*/
				else
				{
					/*	A) toDel is a leaf			*/
					if (( isTreeEmpty(toDel->left) || isEndNode(toDel->left) ) && ( isTreeEmpty(toDel->right) || isEndNode(toDel->right) ))
					{
						std::cout << "	> toDel is a leaf" << std::endl;
						if (isEndNode(toDel->left))
						{
							std::cout << "		> min leaf" << std::endl;
							_endNode->right = toDel->parent;
							toDel->parent->left = _endNode;
						}
						else if (isEndNode(toDel->right))
						{
							std::cout << "max leaf" << std::endl;
							_endNode->left = toDel->parent;
							toDel->parent->right = _endNode;
						}
						else if (toDel->dataPair.first <= toDel->parent->dataPair.first)
						{
							std::cout << "left leaf" << std::endl;
							toDel->parent->left = nullptr;
						}
						else
						{
							std::cout << "right leaf" << std::endl;
							toDel->parent->right = nullptr;
						}
					}
					/*	B) toDel has only one child	*/
					else if ((!isTreeEmpty(toDel->left) && isEndNode(toDel->right)) || (!isTreeEmpty(toDel->right) && isEndNode(toDel->left)))
					{
						if ( !isTreeEmpty(toDel->left) && isEndNode(toDel->right) )
							std::cout << "toDel has one left child" << std::endl;
						else
							std::cout << "toDel has one right child" << std::endl;
					}
					/*	C) toDel has two children	*/
					else
					{
						std::cout << "toDel has two children" << std::endl;
					}
				}
				destroyNode(toDel);
				_nbNodes -= 1;
			};

			bool isTreeEmpty(node_type *tree) const { return (tree == nullptr); };

			bool isEndNode(node_type *node) const { return (node == _endNode); };

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
			// bool isLeaf(node_type *&node) const
			// {
			// 	if (isTreeEmpty(node))
			// 		return false;
			// 	else if (isTreeEmpty(node->left) && isTreeEmpty(node->right))
			// 		return true;
			// 	return false;
			// }
			// bool isInsideNode(node_type *node) const { return (!isLeaf(node)); };
			node_type *getFirst() const
			{
				iterator it(_racine, _endNode);
				while (it++ != _endNode)
					;
				return (it.getNode());
			};
			node_type *getLast() const
			{
				iterator it(_racine, _endNode);
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

		public:
		
			/*✅*/
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _racine(NULL), _nbNodes(0), _allocPair(alloc), _comp(comp)
			{
				_endNode = createNode();
			};
			/*✅*/
			template <class InputIterator>
 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _racine(NULL), _nbNodes(0), _allocPair(alloc), _comp(comp)
			{
				_endNode = createNode();
				for (; first != last; first++)
		 			insert(*first);
			};
			/*✅*/
			map (const map& x) : _racine(NULL), _nbNodes(0), _allocPair(x.get_allocator()), _comp(x.key_comp())
			{
				_endNode = createNode();
				insert(x.begin(), x.end());
			};
			/*✅*/
			~map()
			{
				if (!empty())
					clear();
				destroyNode(_endNode);
			};
			/* NO */
			map& operator= (const map& x)
			{
				if (!empty())
					clear();
				insert(x.begin(), x.end());
				return (*this);
			};
			// ITERATORS
			/*✅*/
			iterator begin()
			{
				node_type *first;
				if (!empty())
					first = getFirst();
				else
					first = nullptr;
				return (iterator(_racine, _endNode, first));
			};
			/*✅*/
			const_iterator begin() const
			{
				node_type *first;
				if (!empty())
					first = getFirst();
				else
					first = nullptr;
				return (const_iterator(_racine, _endNode, first));
			};
			/*✅*/
			iterator end()
			{
				node_type *afterEnd;
				if (!empty())
					afterEnd = _endNode;
				else
					return (begin());
				return (iterator(_racine, _endNode, afterEnd));
			};
			/*✅*/
			const_iterator end() const
			{
				node_type *afterEnd;
				if (!empty())
					afterEnd = _endNode;
				else
					return (begin());
				return (const_iterator(_racine, _endNode, afterEnd));
			};
			/*✅*/
			reverse_iterator rbegin() { return reverse_iterator(end()); };
			/*✅*/
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
			/*✅*/
			reverse_iterator rend() { return reverse_iterator(begin()); };
			/*✅*/
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

			/// CAPACITY
			/*✅*/
			bool empty() const { return (_nbNodes == 0); };
			/*✅*/
			size_type size() const {return (_nbNodes); };
			/*✅*/
			size_type max_size() const { return (_allocNode.max_size()); };

			/// ELEMENT ACCESS
			/*✅*/
			mapped_type& operator[] (const key_type& k)
			{
				node_type *newNode = findNode(k, _racine);
				if (!isTreeEmpty(newNode))
					return (newNode->dataPair.second);
				newNode = createNode(value_type(k, mapped_type()));
				insertNode(newNode);
				return (newNode->dataPair.second);
			};

			/// MODIFIERS
			/*✅*/
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				size_type preNbNodes = _nbNodes;
				node_type *toInsert = createNode(val);
				node_type *insertedNode = insertNode(toInsert);
				bool isInserted = true;
				if (preNbNodes == _nbNodes)
				{
					destroyNode(toInsert);
					isInserted = false;
				}
				return (ft::pair<iterator, bool>(iterator(_racine, _endNode, insertedNode), isInserted));
			};
			/*✅*/
			iterator insert (iterator position, const value_type& val)
			{
				node_type *foundNode = findNode(val.first);
				if (foundNode)
					return (iterator(_racine, _endNode, foundNode));
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
				node_type *insertedNode = insertNode(createNode(val), position.getNode());
				return (iterator(_racine, _endNode, insertedNode));
			};
			/*✅*/
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			};
			/*✅*/
			void erase (iterator position) { removeNode(position.getNode()); };
			/*✅*/
			size_type erase (const key_type& k)
			{
				node_type *foundNode = findNode(k);
				if (foundNode == nullptr)
					return 0;
				removeNode(foundNode);
				return 1;
			};
			/*✅*/
			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					std::cout << "ERASE: first: " << first.getNode()->dataPair.first << std::endl;
					erase(first++);
				}
				// erase(first);
			};
			/*✅*/
			void swap (map& x)
			{
				node_type		*_racineTemp = x._racine;
				size_type		_nbNodesTemp = x._nbNodes;
				allocator_type	_allocPairTemp = x._allocPair;
				allocator_node	_allocNodeTemp = x._allocNode;
				key_compare		_compTemp = x._comp;

				x._racine = _racine;
				x._nbNodes = _nbNodes;
				x._allocPair = _allocPair;
				x._allocNode = _allocNode;
				x._comp = _comp;

				_racine = _racineTemp;
				_nbNodes = _nbNodesTemp;
				_allocPair = _allocPairTemp;
				_allocNode = _allocNodeTemp;
				_comp = _compTemp;
			};
			/*✅*/
			void clear()
			{
				erase(begin(), end());
			};

			/// OBSERVERS
			/*✅*/
			key_compare key_comp() const { return (_comp); };
			/*✅*/
			value_compare value_comp() const { return (value_compare(_comp)); };

			/// OPERATIONS
			/*✅*/
			iterator find (const key_type& k)
			{
				node_type *foundNode = findNode(k, _racine);
				if (foundNode)
					return (iterator(_racine, _endNode, foundNode));
				return (end());
			};
			/*✅*/
			const_iterator find (const key_type& k) const
			{
				node_type *foundNode = findNode(k, _racine);
				if (foundNode)
					return (const_iterator(_racine, _endNode, foundNode));
				return (const_iterator(end()));
			};
			/*✅*/
			size_type count (const key_type& k) const
			{
				if (containsNode(k, _racine))
					return (1);
				return (0);
			};
			/*✅*/
			iterator lower_bound (const key_type& k)
			{
				iterator it = begin();
				iterator itEnd = end();
				for (; it != itEnd && (key_comp())(it.getNode()->dataPair.first, k) == true; it++);
				return (it);
			};
			/*✅*/
			const_iterator lower_bound (const key_type& k) const
			{ return const_iterator(lower_bound(k)); };
			/*✅*/
			iterator upper_bound (const key_type& k)
			{
				iterator it = begin();
				iterator itEnd = end();
				for (; it != itEnd && (key_comp())(k, it.getNode()->dataPair.first) == false; it++);
				return (it);				
			};
			/*✅*/
			const_iterator upper_bound (const key_type& k) const
			{ return const_iterator(upper_bound(k)); };
			/*✅*/
			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				ft::pair<const_iterator, const_iterator> result(lower_bound(k), upper_bound(k));
				return (result);
			};
			/*✅*/
			ft::pair<iterator,iterator> equal_range (const key_type& k)
			{
				ft::pair<iterator, iterator> result(lower_bound(k), upper_bound(k));
				return (result);
			};

			/// ALLOCATOR
			/*✅*/
			allocator_type get_allocator() const { return (_allocNode); };

			//PRINT TREE
			void printBT(const std::string& prefix, const node_type *node, bool isLeft)
			{
				if( node && node != NULL && node != _endNode)
				{
					// usleep(90000);
					std::cout << prefix;
					std::cout << (isLeft ? "├──" : "└──" );
					// print the value of the node
					std::cout << node->dataPair.first << std::endl;
					// enter the next tree level - left and right branch
					printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
					printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
				}
			}
			void printBT() { printBT("", _racine, false); }
			//////////////////////////////////////////////////////////////////////////////////

  	};
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typedef typename ft::node<Key, T> node_type;
		typedef	typename ft::mapIterator<Key, T, node_type, true> const_iterator;

		if (lhs.size() != rhs.size())
			return false;
		const_iterator startLeft = lhs.begin();
		const_iterator startRight = rhs.begin();
		const_iterator endRight = rhs.end();
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
	/**/
	template <class Key, class T, class Compare, class Alloc>
 	void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y) { x.swap(y); };
}

#endif