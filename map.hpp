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
			size_t					depth;

			node() : dataPair(), parent(NULL), left(NULL), right(NULL), depth(0) {};
			node(ft::pair<const Key, T> pair) :  node(), dataPair(pair) {};
			node(size_t depth) : node(), depth(depth) {};
			node(const node &other) : dataPair(other.dataPair), parent(other.parent), left(other.left), right(other.right), depth(other.depth) {};
			~node()
			{
				parent = nullptr;
				left = nullptr;
				right = nullptr;
				depth = 0;
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
			typedef typename Alloc::template rebind<ft::node<Key, T> >::other allocator_node; // BRACKETS ??

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

		// private:
		public :
			node_type		*_racine;
			size_type		_nbNodes;
			allocator_type	_allocPair;
			allocator_node	_allocNode;
			key_compare		_comp;
			// size_type		_treeHeight;

			// CREATE NOTE
			node_type *createNode(value_type pair)
			{
				node_type tempNode;
				node_type *newNode = _allocNode.allocate(1);
				_allocNode.construct(newNode, tempNode);
				_allocPair.construct(&newNode->dataPair, pair);
				newNode->depth = 0;
				// _nbNodes++;
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
				std::cout << "node destroyed is: " << node->dataPair.first << std::endl;
				_allocPair.destroy(&node->dataPair);
				_allocNode.destroy(node);
				_allocNode.deallocate(node, 1);
				// node = nullptr;
			}
			void destroyTree(node_type *&node)
			{
				if (isTreeEmpty(node))
				{
					destroyNode(node);
					_nbNodes--;
					destroyTree(node->left);
					destroyTree(node->right);
				}
			}
			// Find NODE
			// https://www.cs.odu.edu/~zeil/cs361/latest/Public/bst/index.html
			bool contains( node_type const *needle, node_type *subTree) const
			{ return (contains(needle->dataPair.first, subTree)); }
			bool contains( key_type const &key, node_type *subTree) const
			{
				if( isTreeEmpty(subTree))
					return false;
				if (_comp(key , subTree->dataPair.first))
					return contains(key, subTree->left);
				else if (_comp(subTree->dataPair.first , key))
					return contains(key, subTree->right);
				else
					return true;
			}
			node_type *findNode( node_type const *needle, node_type *subTree) const
			{ return (findNode(needle->dataPair.first, subTree)); }
			node_type *findNode(key_type const key, node_type *subTree) const
			{
				if(isTreeEmpty(subTree))
					return NULL;
				if (_comp(key , subTree->dataPair.first))
					return findNode(key, subTree->left);
				else if (_comp(subTree->dataPair.first , key))
					return findNode(key, subTree->right);
				else
					return subTree;
			}
			// https://www.cs.odu.edu/~zeil/cs361/latest/Public/bst/index.html
			// INSERT NODE
			void insertNode(node_type *toInsert)
			{
				if (isTreeEmpty(_racine))
					return insertNode(toInsert, _racine, NULL);
				insertNode(toInsert, _racine, _racine->parent);
			}
			void insertNode(node_type *toInsert, node_type *subTree, node_type *parent) 
			{
				if (isTreeEmpty(subTree) && _nbNodes == 0)
				{
					_nbNodes++;
					_racine = toInsert;
				}
				else if (isTreeEmpty(subTree))
				{
					_nbNodes++;
					toInsert->parent = parent;
					subTree = toInsert;
				}
				else if (_comp(toInsert->dataPair.first, subTree->dataPair.first))   
				{
					if (!getLeftTree(subTree))
					{
						toInsert->parent = subTree;
						subTree->left = toInsert;
						_nbNodes++;
					}
					else
						insertNode(toInsert, subTree->left, subTree);
				}
				else if (_comp(subTree->dataPair.first, toInsert->dataPair.first))
				{
					if (!getRightTree(subTree))
					{
						toInsert->parent = subTree;
						subTree->right = toInsert;
						_nbNodes++;
					}
					else
						insertNode(toInsert, subTree->right, subTree);
				}
			}
			// DELETE NODE
			node_type *findMin(node_type *t)
			{
				if( t == nullptr )
					return nullptr;
				if( t->left == nullptr )
					return t;
				return findMin( t->left );
			}
			void removeNode(node_type *toRemove)
			{ removeNode(toRemove, _racine); }
			void removeNode(node_type *toRemove, node_type *&subTree)
			{
				if(isTreeEmpty(subTree))
					return ;
				if(_comp(toRemove->dataPair.first, subTree->dataPair.first))
					removeNode(toRemove, subTree->left);
				else if(_comp(subTree->dataPair.first, toRemove->dataPair.first))
					removeNode(toRemove, subTree->right); 
				else if(!isTreeEmpty(subTree->left) && !isTreeEmpty(subTree->right) )
				{
					node_type *tmpNode = findMin(subTree->right);
					node_type *newNode = createNode(tmpNode->dataPair);
					newNode->right = subTree->right;
					newNode->left = subTree->left;
					newNode->parent = subTree->parent;
					subTree = newNode;
					destroyNode(newNode); // ?? sure ??
					removeNode(tmpNode, subTree->right);
				}
				else
				{
					node_type *oldNode = subTree;
					if (!isTreeEmpty(subTree->left))
					{
						subTree->left->parent = subTree->parent;
						subTree = subTree->left;
					}
					else
						subTree = NULL;
					destroyNode(oldNode); // sure ??
					_nbNodes--;
				}
			}
			//ISTREE EMPTY
			bool isTreeEmpty(node_type *tree) const { return (tree == NULL); };

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
			bool isLeaf(node_type *&node) const
			{
				if (isTreeEmpty(node))
					return false;
				else if (isTreeEmpty(node->left) && isTreeEmpty(node->right))
					return true;
				return false;
			}
			bool isInsideNode(node_type *node) const { return (!isLeaf(node)); };

			//TREE HEIGHT
			//- un arbre vide est de hauteur 0
			// - un arbre non vide a pour hauteur 1 + la hauteur maximale entre ses fils.
			size_type max(size_type a, size_type b) { return (a > b) ? a : b; };
			// size_type treeHeight(node_type *tree)
			// {
			// 	if (isTreeEmpty(tree))
			// 		return (0);
			// 	return (1 + max(treeHeight(getLeftTree(tree)), treeHeight(getRightTree(tree))));
			// };
			// void setTreeHeight() { _treeHeight = treeHeight(_racine); };

			void printBT(const std::string& prefix, const node_type *node, bool isLeft)
			{
				if( node && node != NULL )
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

			node_type *getFirst()
			{
				iterator it(_racine);
				while (it++ != NULL)
					;
				return (it.getNode());
			};
			node_type *getLast()
			{
				iterator it(_racine);
				while (it-- != NULL)
					;
				return (it.getNode());
			};

		public:
		
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _racine(NULL), _nbNodes(0), _allocPair(alloc), _comp(comp) {};	
			template <class InputIterator>
 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
			map (const map& x);
			/**/
			~map()
			{
				if (_racine)
					destroyTree(_racine);
			};
			/**/
			map& operator= (const map& x);
			/// ITERATORS
			iterator begin()
			{
				node_type *first;
				if (!empty())
				{
					first = getFirst();
				}
				else
					first = nullptr;
				return (iterator(_racine, first));
			};
			const_iterator begin() const
			{
				return (const_iterator(begin()));
			};
			// /**/
			iterator end()
			{
				node_type *end;
				node_type *afterEnd;
				if (!empty())
				{
					end = getLast();
					afterEnd = createNode();
					afterEnd->parent = end; // sure ???
				}
				else
					return (begin());
				return (iterator(_racine, afterEnd));
			};
			const_iterator end() const
			{
				return (const_iterator(end()));
			};
			/**/

			reverse_iterator rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };

			reverse_iterator rend() { return reverse_iterator(begin()); };
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };
			/// CAPACITY

			bool empty() const { return (_nbNodes == 0); };

			size_type size() const {return (_nbNodes); };

			size_type max_size() const { return (_allocNode.max_size()); }; 
			/// ELEMENT ACCESS
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
			ft::pair<iterator,bool> insert (const value_type& val);	
			iterator insert (iterator position, const value_type& val);
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			};
			/**/
			void erase (iterator position)
			{
				removeNode(position.getNode());
			};
			size_type erase (const key_type& k)
			{
				node_type *foundNode = findNode(k);
				if (foundNode == nullptr)
					return 0;
				removeNode(foundNode->getNode());
				return 1;
			};
			void erase (iterator first, iterator last)
			{
				while (first != last)
				{
					if (first != last)
						erase(first++);
				}
			};
			/**/
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
			/**/
			void clear()
			{
				// iterator it = begin();
				// while(it != end())
				// {
				// 	// std::cout << "it: "<<it.getNode()->dataPair.first << std::endl;
				// 	node_type *node = it.getNode();
				// 	// node_type *node = 
				// 	// if (it != begin() && node->parent)
				// 	removeNode(node, _racine);
				// 	++it;
				// }
				erase(begin(), end());
				_nbNodes = 0;
			};
			/// OBSERVERS
			key_compare key_comp() const;
			value_compare value_comp() const; // FRIEND ??
			/// OPERATIONS
			iterator find (const key_type& k);
			const_iterator find (const key_type& k) const;
			/**/
			size_type count (const key_type& k) const;
			/**/
			iterator lower_bound (const key_type& k);
			const_iterator lower_bound (const key_type& k) const;
			/**/
			iterator upper_bound (const key_type& k);
			const_iterator upper_bound (const key_type& k) const;
			/**/
			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			ft::pair<iterator,iterator> equal_range (const key_type& k);
			/// ALLOCATOR
			allocator_type get_allocator() const;

		private:
			bool is_empty() const { return (_nbNodes == 0); };

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