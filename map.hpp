#ifndef MAP_HPP
#define MAP_HPP

#include <unistd.h>
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

			node() : dataPair(), father(NULL), left(NULL), right(NULL), depth(0) {};
			node(ft::pair<const Key, T> pair) :  node(), dataPair(pair) {};
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
			size_type		_nbNodes;
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
			void destroyNode(node_type *&node)
			{ 
				_allocPair.destroy(&node->dataPair);
				_allocNode.destroy(node);
				_allocNode.deallocate(node, 1);
				node = nullptr;
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
			// will search node inside tree
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
			void insertNode(node_type *toInsert, node_type *subTree) 
			{
				if (isTreeEmpty(subTree) && _nbNodes == 0)
				{
					_nbNodes++;
					_racine = toInsert;
				}
				else if (isTreeEmpty(subTree))
				{
					_nbNodes++;
					subTree = toInsert;
				}
				else if (_comp(toInsert->dataPair.first, subTree->dataPair.first))   
				{
					if (!getLeftTree(subTree))
					{
						subTree->left = toInsert;
						_nbNodes++;
					}
					else
						insertNode(toInsert, subTree->left);
				}
				else if (_comp(subTree->dataPair.first, toInsert->dataPair.first))
				{
					if (!getRightTree(subTree))
					{
						subTree->right = toInsert;
						_nbNodes++;
					}
					else
						insertNode(toInsert, subTree->right);
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
			void removeNode(node_type *toRemove, node_type *&subTree)
			{
				if(isTreeEmpty(subTree))
					return ;
				// std::cout << "subTree->dataPair.first: " << subTree->dataPair.first << ", to remove: " << toRemove->dataPair.first << ", is leaf ? " << isLeaf(toRemove)<< std::endl;
				if(_comp(toRemove->dataPair.first, subTree->dataPair.first))
					removeNode(toRemove, subTree->left);
				else if(_comp(subTree->dataPair.first, toRemove->dataPair.first))
					removeNode(toRemove, subTree->right); 
				else if(!isTreeEmpty(subTree->left) && !isTreeEmpty(subTree->right) )
				{
					// std::cout << "subTree->left: " << subTree->left << ", subTree->right: " << subTree->right << std::endl;
					node_type *tmpNode = findMin(subTree->right);
					node_type *newNode = createNode(tmpNode->dataPair);
					newNode->right = subTree->right;
					newNode->left = subTree->left;
					// parent dont forget
					subTree = newNode;
					destroyNode(newNode); // ?? sure ??
					removeNode(tmpNode, subTree->right);
				}
				else
				{
					node_type *oldNode = subTree;
					subTree = (!isTreeEmpty(subTree->left)) ? subTree->left : subTree->right;
					destroyNode(oldNode);
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
			size_type treeHeight(node_type *tree)
			{
				if (isTreeEmpty(tree))
					return (0);
				return (1 + max(treeHeight(getLeftTree(tree)), treeHeight(getRightTree(tree))));
			};
			void setTreeHeight() { _treeHeight = treeHeight(_racine); };

			// TYPE DE PARCOURS PREFIXE
			// void prefix(node_type *tree) const
			// {
			// 	if (!isTreeEmpty(tree))
			// 	{
			// 		std::cout << "Key: " << tree->dataPair.first <<  ", Value: " << tree->dataPair.second << std::endl;
			// 		prefix(getLeftTree(tree));
			// 		prefix(getRightTree(tree));
			// 	}
			// }
			
			void printBT(const std::string& prefix, const node_type *node, bool isLeft)
			{
				if( node && node != NULL )
				{
					usleep(125000);
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

		public:
			// 23.3.1.1 construct/copy/destroy:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _nbNodes(0), _allocPair(alloc), _comp(comp)
			{
				// ft::node<key_type, mapped_type> tmp;
				// _racine = &tmp;
				_racine = NULL;
				// node_type tempNode;
				// // node_type *newNode = _allocNode.allocate(1);
				// _allocNode.construct(_racine, tempNode);
				// // _allocPair.construct(&newNode->dataPair, pair);
				// _racine->depth = 0;
				// _racine = createNode();
				// std::cout << "_racine->depth: " << _racine->depth << std::endl;
				// insertNode(_racine, createNode(test));
			};	
			template <class InputIterator>
 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());	
			map (const map& x);
			/**/
			~map()
			{
				destroyTree(_racine);
			};
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

			/* Returns whether the map container is empty (i.e. whether its size is 0). */
			bool empty() const;
			/* Returns the number of elements in the map container. */
			size_type size() const {return (_nbNodes); };
			size_type max_size() const { return (_allocNode.max_size()); }; 
			/// ELEMENT ACCESS
			mapped_type& operator[] (const key_type& k)
			{
				node_type *newNode = findNode(k, _racine);
				if (!isTreeEmpty(newNode))
					return (newNode->dataPair.second);
				newNode = createNode(value_type(k, mapped_type()));
				insertNode(newNode, _racine);
				return (newNode->dataPair.second);
			};
			/// MODIFIERS
			// ft::pair<iterator,bool> insert (const value_type& val);	
			// iterator insert (iterator position, const value_type& val);
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			};
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
			bool is_empty() const { return (_nbNodes == 0); };
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