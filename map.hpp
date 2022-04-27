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
			short					balanceFactor;
			size_t					height;
			//	holds difference in heights between the right and left subtrees.
			//	In a balanced tree, this difference must be -1, 0, or 1. 
			//	0 means that both subtrees have the same height.
			//	-1 means that the left tree is higher (by 1)
			//	1 means that the right tree is higher.

			node() : dataPair(), parent(NULL), left(NULL), right(NULL){};
			node(ft::pair<const Key, T> pair) :  node(), dataPair(pair) {};
			node(const node &other) : dataPair(other.dataPair), parent(other.parent), left(other.left), right(other.right) {};
			~node()
			{
				parent = NULL;
				left = NULL;
				right = NULL;
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

			typedef	typename ft::mapIterator<Key, T, key_compare, node_type, false>	iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef	typename ft::mapIterator<Key, T, key_compare, node_type, false>	const_iterator;
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
				// std::cout << "node destroyed is: " << &node->dataPair << std::endl;
				// _allocPair.destroy(&node->dataPair); /// CHECK ??
				// std::cout << "node destroyed is: " << node<< std::endl;
				_allocNode.destroy(node);
				_allocNode.deallocate(node, 1);
				// node = NULL;
			};

			// FIND NODE
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

			// INSERT NODE
			node_type *insertNode(node_type *toInsert)
			{ return insertNode(toInsert, _racine); };
			node_type *insertNode(node_type *toInsert, node_type *subTree) 
			{
				if (isTreeEmpty(subTree) && _nbNodes == 0)	/*	first insertion into tree	*/
				{
					_racine = toInsert;
					if (toInsert != _endNode)
						_nbNodes++;
					setEndNodeLast(_racine);
					setEndNodeFirst(_racine);
					subTree = _racine;
				}
				else if (_comp(toInsert->dataPair.first, subTree->dataPair.first))	/*	insert < current => go to left	*/
				{
					if (isTreeEmpty(subTree->left) || isEndNode(subTree->left))	/*	reached a leaf	*/
					{
						node_type *oldLeft = subTree->left;
						toInsert->parent = subTree;
						subTree->left = toInsert;
						_nbNodes++;
						if (isEndNode(oldLeft))	/*	reached a leaf that was endNode	*/
							setEndNodeFirst(subTree->left);
						subTree = subTree->left;
					}
					else
						return insertNode(toInsert, subTree->left);
				}
				else if (_comp(subTree->dataPair.first, toInsert->dataPair.first)) 	//*	insert > current => go to right	*/
				{
					if (isTreeEmpty(subTree->right) || isEndNode(subTree->right))	/*	reached a leaf	*/
					{
						node_type *oldRight = subTree->right;
						toInsert->parent = subTree;
						subTree->right = toInsert;
						_nbNodes++;
						if (isEndNode(oldRight))	/*	reached a leaf that was endNode	*/
							setEndNodeLast(subTree->right);
						subTree = subTree->right;
					}
					else
						return insertNode(toInsert, subTree->right);
				}
				setHeight(subTree);
				balanceTree(subTree);
				return subTree;
			}

			// DELETE NODE
			void removeNode(node_type* position, key_type key)
			{
				printBT();
				node_type*	target = findNode(key, position);
				
				if (!target)
					return;
				
				//confusedNode is the node to balance from once the target is deleted
				//this is usually the parent, unless we delete _racine then it is 0 to make balanceTree useless
				node_type*	confusedNode = 0;
				
				/* DELETING THE PARENTLESS ROOT	*/
				if (!target->parent)
				{
					//case 1 : only one node in the tree
					if (target->right == _endNode && target->left == _endNode)
					{
						_racine = _endNode;
						_endNode->right = _endNode;
						_endNode->left = _endNode;
					}
					//case 2 : root only has one left or right child
					else if (target->left && target->right == _endNode)
					{
						confusedNode = target->parent;	//set as 0
						_racine = target->left;			//root becomes left child
						target->left->parent = 0;		//cuts the link between target and new root
						_racine->right = _endNode;
						_endNode->left = _racine;			//setting the right side of the one node tree _endNode elem
					}
					else if (target->right && target->left == _endNode)
					{
						confusedNode = target->parent;	//set as 0
						_racine = target->right;			//root becomes right child
						target->right->parent = 0;		//cuts the link between target and new root
						_racine->left = _endNode;
						_endNode->right = _racine;			//setting the left side of the one node tree _endNode elem
					}
					//case 3 : root has 2 children -> set the 'inorder predecessor' one as root
					else
					{
						node_type*	leftSubtreeHighest = searchMaxNode(target->left);

						_allocPair.destroy(&target->dataPair);
						_allocPair.construct(&target->dataPair, leftSubtreeHighest->dataPair);	//copy highestNode to root
						//in the left subtree, delete the highest that was moved to root
						return (removeNode(target->left, leftSubtreeHighest->dataPair.first));	
					}
				}
				/*	DELETING A NODE	*/
				//case 1 : target is a leaf
				else if ((!target->left || target->left == _endNode) && (!target->right || target->right == _endNode))
				{
					confusedNode = target->parent;

					if (target->left == _endNode)									//min leaf node (left)
					{
						_endNode->right = target->parent;
						target->parent->left = _endNode;
					}
					else if (target->right == _endNode)							//max leaf node (right)
					{
						_endNode->left = target->parent;
						target->parent->right = _endNode;
					}
					else if (target->dataPair.first <= target->parent->dataPair.first)	//regular leaf	(left)
					{
						target->parent->left = 0;
					}
					else														//regular leaf	(right)
					{
						target->parent->right = 0;
					}
				}
				//case 2 : target has a child
				else if ((target->left && target->left != _endNode) && (!target->right || target->right == _endNode))	//has a left child
				{
					confusedNode = target->parent;
		
					if (target->dataPair.first <= target->parent->dataPair.first)		//target is a left child
						target->parent->left = target->left;
					else														//target is a right child
						target->parent->right = target->left;
					target->left->parent = target->parent;
					
					if (target->right == _endNode)									//target is max node
					{
						target->left->right = _endNode;
						_endNode->left = target->left;
					}
				}
				else if ((target->right && target->right != _endNode) && (!target->left || target->left == _endNode))	//has a right child
				{
					std::cout << "here" << std::endl; 
					confusedNode = target->parent;

					if (target->dataPair.first <= target->parent->dataPair.first)		//target is a left child
						target->parent->left = target->right;
					else														//target is a right child
						target->parent->right = target->right;
					target->right->parent = target->parent;
					
					if (target->left == _endNode)									//target is max node
					{
						target->right->left = _endNode;
						_endNode->right = target->right;
					}
				}
				//case 3 : target has 2 children : same logic as root -> set the 'inorder predecessor' one as root
				else
				{
					node_type*	leftSubtreeHighest = searchMaxNode(target->left);

					_allocPair.destroy(&target->dataPair);
					_allocPair.construct(&target->dataPair, leftSubtreeHighest->dataPair);	//copy highestNode to root

					//in the left subtree, delete the highest that was moved to root
					return (removeNode(target->left, leftSubtreeHighest->dataPair.first));					
				}
				printBT();
				setHeight(confusedNode);			
				balanceTree(confusedNode);

				destroyNode(target);

				_nbNodes--;
				printBT();
				return;
			};

			/*		BALANCING TREE SPEC OPERATIONS		*/
			/*	https://www.programiz.com/dsa/avl-tree	*/

			size_type max(int a, int b) { return (a > b) ? a : b; };

			size_type getHeight(node_type *node) const
			{
  				if (isTreeEmpty(node) || isEndNode(node))
				  return (0);
  				return node->height;
			};

			void setHeight(node_type *node)
			{
				// std::cout << "node: " << node->dataPair.first << std::endl;
				if (isTreeEmpty(node) || isEndNode(node))
					return ;
				node->height = 1 + max(getHeight(node->left), getHeight(node->right));
			};

			int getBalanceFactor(node_type *node) const
			{
				if (isTreeEmpty(node) || isEndNode(node))
					return (0);
				return (getHeight(node->left) - getHeight(node->right));
			};

			void balanceTree(node_type *node)
			{
				while (node)
				{
					int	bf;
					setHeight(node);
					bf = getBalanceFactor(node);

					if (bf > 1 && getBalanceFactor(node->left) > 0)			//ll
						rightRotate(node);
					else if (bf > 1 && getBalanceFactor(node->left) <= 0)		//lr
					{
						leftRotate(node->left);
						rightRotate(node);
					}
					else if (bf < -1 && getBalanceFactor(node->right) >= 0)	//rl
					{
						rightRotate(node->right);
						leftRotate(node);
					}
					else if (bf < -1 && getBalanceFactor(node->right) < 0)		//rr
						leftRotate(node);
					node = node->parent;
				}
				return ;
			};

			void rightRotate(node_type *futureBottom)
			{
				node_type *futureTop = futureBottom->left;

				// std::cout << ">> rightRotate node: " << futureBottom->dataPair.first << " with " << futureTop->dataPair.first << std::endl;
				// printBT();
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
				// printBT();
			}

			void leftRotate(node_type *futureBottom)
			{
				node_type *futureTop = futureBottom->right;

				// std::cout << ">> leftRotate node: " << futureBottom->dataPair.first << " with " << futureTop->dataPair.first << std::endl;
				// printBT();
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
				// printBT();
			}

			bool isTreeEmpty(node_type *tree) const { return (tree == NULL); };

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
			node_type *getFirst() const
			{
				iterator it(NULL, _endNode, _comp);
				while (it++ != _endNode)
					;
				return (it.getNode());
			};
			node_type *getLast() const
			{
				iterator it(NULL, _endNode, _comp);
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
				insertNode(_endNode);
			};
			/*✅*/
			template <class InputIterator>
 			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _racine(NULL), _nbNodes(0), _allocPair(alloc), _comp(comp)
			{
				_endNode = createNode();
				insertNode(_endNode);
				for (; first != last; first++)
		 			insert(*first);
			};
			/*✅*/
			map (const map& x) : _racine(NULL), _nbNodes(0), _allocPair(x._allocPair), _comp(x._comp)
			{
				_endNode = createNode();
				insertNode(_endNode);
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
				return (iterator(_endNode->right, _endNode, _comp));
			};
			/*✅*/
			const_iterator begin() const
			{
				return (const_iterator(_endNode->right, _endNode, _comp));
			};
			/*✅*/
			iterator end()
			{
				return (iterator(_endNode, _endNode, _comp));
			};
			/*✅*/
			const_iterator end() const
			{
				return (const_iterator(_endNode, _endNode, _comp));
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

			/// MODIFIERS
			/*✅*/
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				node_type *foundNode = findNode(val.first);	
				if (foundNode)
					return (ft::pair<iterator, bool>(iterator(foundNode, _endNode, _comp), false));
				node_type *insertedNode;
				if (_nbNodes == 0 && _racine == _endNode)
				{
					insertedNode = insertNode(createNode(val), NULL);
				}
				else
					insertedNode = insertNode(createNode(val));
				return (ft::pair<iterator, bool>(iterator(foundNode, _endNode, _comp), true));
			};
			/*✅*/
			iterator insert (iterator position, const value_type& val)
			{
				node_type *foundNode = findNode(val.first);
				if (foundNode)
					return (iterator(foundNode, _endNode, _comp));
				node_type *insertedNode;
				if (position.getNode() == _racine && _racine == _endNode)
				{
					insertedNode = insertNode(createNode(val), NULL);
					return (iterator(insertedNode, _endNode, _comp));
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
				return (iterator(insertedNode, _endNode, _comp));
			};
			/*✅*/
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				for (; first != last; first++)
					insert(*first);
			};
			/*✅*/
			void erase (iterator position) { removeNode(position.getNode(), position.getNode()->dataPair.first); };
			/*✅*/
			size_type erase (const key_type& k)
			{
				node_type *foundNode = findNode(k);
				if (foundNode == NULL)
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
					return (iterator(foundNode, _endNode, _comp));
				return (end());
			};
			/*✅*/
			const_iterator find (const key_type& k) const
			{
				node_type *foundNode = findNode(k, _racine);
				if (foundNode)
					return (const_iterator(foundNode, _endNode, _comp));
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
			{
				const_iterator it = begin();
				const_iterator itEnd = end();
				for (; it != itEnd && (key_comp())(it.getNode()->dataPair.first, k) == true; it++);
				return (it);
			};
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
			{
				const_iterator it = begin();
				const_iterator itEnd = end();
				for (; it != itEnd && (key_comp())(k, it.getNode()->dataPair.first) == false; it++);
				return (it);				
			};
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


			// void printBT(node_type *root, std::string indent, bool last)
			// {
			// 	if (root != NULL && root != _endNode) {
			// 		std::cout << indent;
			// 		if (last) {
			// 		std::cout << "R----";
			// 		indent += "   ";
			// 		} else {
			// 		std::cout << "L----";
			// 		indent += "|  ";
			// 		}
			// 		std::cout << root->dataPair.first << std::endl;
			// 		printBT(root->left, indent, false);
			// 		printBT(root->right, indent, true);
			// 	}
			// }
			// void printBT() { printBT(_racine, "", true); }

			// PRINT TREE
			void printBT(const std::string& prefix, const node_type *node, bool isLeft)
			{
				if( node && node != NULL && node != _endNode)
				{
					// usleep(90000);
					std::cout << prefix;
					std::cout << (isLeft ? "├─L─" : "└─R─" );
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
		typedef	typename ft::mapIterator<Key, T, Compare, node_type, true> const_iterator;

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