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
			size_type		_nbNodes;
			allocator_type	_allocPair;
			allocator_node	_allocNode;
			key_compare		_comp;
			// node_type		_lastNode;
			// node_type		_firstNode;
			node_type		*_endNode;

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
					// _endNode->right = _racine;
					// _racine->left = _endNode;
					// setEndNode();
					return (_racine);
				}
				else if (isTreeEmpty(subTree))
				{
					_nbNodes++;
					toInsert->parent = parent;
					subTree = toInsert;
					// setEndNode();
					return (subTree);
				}
				else if (_comp(toInsert->dataPair.first, subTree->dataPair.first))   
				{
					if (!getLeftTree(subTree))
					{
						toInsert->parent = subTree;
						subTree->left = toInsert;
						_nbNodes++;
						// if (subTree->left == getFirst())
						// 	setEndNodeFirst();
						return (subTree->left);
					}
					else
						return insertNode(toInsert, subTree->left, subTree);
				}
				else if (_comp(subTree->dataPair.first, toInsert->dataPair.first))
				{
					if (!getRightTree(subTree))
					{
						toInsert->parent = subTree;
						subTree->right = toInsert;
						_nbNodes++;
						// if (subTree->right == getLast())
						// 	setEndNodeLast();
						return (subTree->right);
					}
					else
						return insertNode(toInsert, subTree->right, subTree);
				}
				return subTree;
			}
			// DELETE NODE
			node_type *findMin(node_type *t)
			{
				if( t == nullptr || t == _endNode)
					return nullptr;
				if( t->left == nullptr || t == _endNode)
					return t;
				return findMin( t->left );
			}
			void removeNode(node_type *toRemove)
			{ removeNode(toRemove, _racine); }
			void removeNode(node_type *toRemove, node_type *&subTree)
			{
				if(isTreeEmpty(subTree) || isEndNode(subTree))
					return ;
				if(_comp(toRemove->dataPair.first, subTree->dataPair.first))
					removeNode(toRemove, subTree->left);
				else if(_comp(subTree->dataPair.first, toRemove->dataPair.first))
					removeNode(toRemove, subTree->right); 
				else if(!isTreeEmpty(subTree->left) && subTree->left != _endNode && !isTreeEmpty(subTree->right) && subTree->right != _endNode )
				{
					node_type *tmpNode = findMin(subTree->right);
					node_type *newNode = createNode(tmpNode->dataPair);
					newNode->right = subTree->right;
					newNode->left = subTree->left;
					newNode->parent = subTree->parent;
					newNode->right->parent = newNode;
					newNode->left->parent = newNode;
					destroyNode(subTree);
					if (toRemove == _racine)
						_racine = newNode;
					removeNode(tmpNode, newNode->right);
				}
				else if (subTree != _endNode)
				{
					node_type *oldNode = subTree;
					if (!isTreeEmpty(subTree->left))
					{
						subTree->left->parent = subTree->parent;
						subTree = subTree->left;
						if (toRemove == _racine)
							_racine = subTree;
					}
					else
					{
						if (toRemove == _racine && subTree == _racine)
						{
							if (!isTreeEmpty(subTree->right))
								_racine = subTree->right;
							else
								_racine = nullptr;
						}
						else
							subTree = nullptr;
					}
					destroyNode(oldNode);
					_nbNodes--;
				}
			}
			//ISTREE EMPTY
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
				// std::cout << "it == nullptr " << (it == nullptr) << std::endl;
				while (it++ != nullptr)
				{
					if (it == _endNode)
						break;
					// std::cout << "hey" << std::endl;
				}
				// std::cout << "ici first: " << it.getNode()->dataPair.first << std::endl;
				return (it.getNode());
			};
			node_type *getLast() const
			{
				iterator it(_racine, _endNode);
				while (it-- != nullptr)
					if (it == _endNode)
						break;
				// std::cout << "last: " << it.getNode()->dataPair.first << std::endl;
				return (it.getNode());
			};
			void setEndNodeFirst()
			{
				node_type *first = getFirst();
				_endNode->right = first;
				first->left = _endNode;
			};
			void setEndNodeLast()
			{
				node_type *last = getLast();
				_endNode->left = last;
				last->right = _endNode;
			};
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
			map (const map& x) : _racine(NULL), _nbNodes(0), _allocPair(x.get_allocator()), _comp(x.key_comp()), _endNode(x._endNode)
			{
				_endNode = createNode();
				insert(x.begin(), x.end());
			};
			/*✅*/
			~map()
			{
				if (!empty())
					clear();
				// destroyNode(_endNode);
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
				// std::cout << "first: " << first.getNode()->dataPair.first << ", last: " << last.getNode()->dataPair.first << std::endl;
				while (first != last)
				{
					std::cout << "first: " << first.getNode() << ", last: " << last.getNode() << std::endl;
					erase(first++);
				}
				erase(first);
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
				// std::cout << "first: " << begin().getNode()->dataPair.first << "last: " << end().getNode()->dataPair.first << std::endl;
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
				if(node != nullptr && node != _endNode)
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