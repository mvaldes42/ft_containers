#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include <iostream>


namespace   ft
{

	//boolean is true is const
	template <bool isConst, typename falseConst, typename trueConst>
	struct chooseConst {};

	//sets 2nd parameter as ref and pointer
	template <typename falseConst, typename trueConst>
	struct chooseConst<false, falseConst, trueConst>
	{
		typedef falseConst type;
	};

	//sets 2nd parameter as (const) ref and pointer
	template <typename falseConst, typename trueConst>
	struct chooseConst<true, falseConst, trueConst>
	{
		typedef trueConst type;
	};

	template < class Key,											// map::key_type
			class T,												// map::mapped_type
			class Compare,										// map::key_compare
			typename Node, 										// node struct
			bool Con>											// 1 if const
	class mapIterator
	{
		public :
		
			typedef Key					key_type;
			typedef T					mapped_type;
			typedef	Compare				key_compare;
			typedef size_t				size_type;
			typedef std::ptrdiff_t		difference_type;
			typedef ft::pair<const key_type, mapped_type>								value_type;
			typedef typename std::bidirectional_iterator_tag							iterator_category;;
			typedef typename chooseConst<Con, value_type&, const value_type&>::type		reference;
			typedef typename chooseConst<Con, value_type*, const value_type*>::type		pointer;
				
				
		private :
		
			Node*		_node;		//curent node pointed by iterator
			Node*		_endNode;		//pointer to NULL pointer Type Nil : non-existant leaves, past-the-end element
			key_compare	_comp;		//used way of comparing keys to sort the map, needed to know wich way to iterate

		public :

		/*	CONSTRUCTORS, DESTRUCTOR, OPERATOR=	*/

			//default constructor, creates an iterator to the parameter node
			//if the parameters are not sent, default set to 0
			mapIterator(Node* node = 0, Node* last = 0, const key_compare& comp = key_compare()) :
			_node(node),
			_endNode(last),
			_comp(comp)
			{
				return ;
			}

			//copy const
			mapIterator(const mapIterator<Key, T, Compare, Node, false>& copy)
			{
				_node = copy.getNode();
				_endNode = copy.getLast();
				_comp = copy.getComp();
				return ;
			}

			//nothing is ever allocated inside an iterator, it acts like a pointer
			~mapIterator()
			{
				return ;
			}

			mapIterator& operator=(const mapIterator& rhs)
			{
				if (this != &rhs)
				{
					_node = rhs.getNode();
					_endNode = rhs.getLast();
					_comp = rhs.getComp();		
				}
				return (*this);
			}
		
		/*	GETTERS	*/

			Node*	getNode() const
			{
				return (_node);
			}

			Node*	getLast() const
			{
				return (_endNode);
			}

			key_compare	getComp() const
			{
				return (_comp);
			}
		
		/*	MEMBER FUNCTION : OPERATORS	*/

			reference	operator*() const
			{
				return (_node->dataPair);
			}
			
			pointer		operator->() const
			{
				return (&_node->dataPair);	
			}

			//++ pre-increment operator goes from one key to the immediate superior one
			mapIterator&	operator++()
			{
				Node*	prevNode = _node;
				//iterator is starting on _endNode (rend() or end()), go back to min
				if (_node == _endNode)
				{
					_node = _endNode->right;
					return (*this);
				}
				//until reaching last and while prev >= node, we ++ (see ft::less in utils)
				while (_node != _endNode && !_comp(prevNode->dataPair.first, _node->dataPair.first))
				{
					//right child is last
					if (_node->right && _node->right == _endNode)
					{
						_node = _node->right;
					}
					//there is a right child : immediate higher node is right subtree's min
					else if (_node->right && _comp(prevNode->dataPair.first, _node->right->dataPair.first))
					{
						_node = _node->right;
						_node = lowestNode(_node);
					}
					//go up until I am a left child
					else
					{
						Node*	parentNode = _node->parent;
						while (_node != parentNode->left)
						{
							_node = parentNode;
							parentNode = parentNode->parent;
						}
						_node = parentNode;
						return (*this);
					}
				}
				return (*this);
			}

			//++ post-increment operator goes from one key to the immediate superior one
			mapIterator	operator++(int)
			{
				mapIterator	ret(*this);
				//iterator is starting on last, go back to min
				if (_node == _endNode)
				{
					_node = _endNode->right;
					return (ret);
				}
				//until reaching last and while prev >= node, we ++ (see ft::less in utils)
				while (_node != _endNode && !_comp(ret->first, _node->dataPair.first))
				{
					//right child is _endNode
					if (_node->right && _node->right == _endNode)
					{
						_node = _node->right;
					}
					//there is a right child : immediate higher node is right subtree's min
					else if (_node->right && _comp(ret->first, _node->right->dataPair.first))
					{
						_node = _node->right;
						_node = lowestNode(_node);
					}
					//go up until I am a left child
					else
					{
						Node*	parentNode = _node->parent;
						while (_node != parentNode->left)
						{
							_node = parentNode;
							parentNode = parentNode->parent;
						}
						_node = parentNode;
						return (ret);
					}
				}
				return (ret);	
			}

			//-- pre-decrement operator goes from one key to the immediate inferior one
			mapIterator&	operator--()
			{
				Node*	prevNode = _node;

				//iterator is starting on _endNode (rend() or end()), go back to max
				if (_node == _endNode)
				{
					_node = _endNode->left;
					return (*this);
				}
				
				//until reaching last and while prev <= node, we -- (see ft::less in utils)
				while (_node != _endNode && !_comp(_node->dataPair.first, prevNode->dataPair.first))
				{
					//left child is _endNode
					if (_node->left && _node->left == _endNode)
					{
						_node = _node->left;
					}
					//there is a left child : immediate lower node is left subtree's max
					else if (_node->left && _comp(_node->left->dataPair.first, prevNode->dataPair.first))
					{
						_node = _node->left;
						_node = highestNode(_node);
					}
					//go up until I am a right child
					else
					{
						Node*	parentNode = _node->parent;
						while (_node != parentNode->right)
						{
							_node = parentNode;
							parentNode = parentNode->parent;
						}
						_node = parentNode;
						return (*this);
					}
				}
				return (*this);
			}

			//-- post-decrement operator goes from one key to the immediate inferior one
			mapIterator	operator--(int)
			{
				mapIterator	ret(*this);

				// iterator is starting on last, go back to root
				if (_node == _endNode)
				{
					_node = _endNode->left;
					return (ret);
				}
				
				//until reaching last and while prev <= node, we -- (see ft::less in utils)
				while (_node != _endNode && !_comp(_node->dataPair.first, ret->first))
				{
					//left child is _endNode
					if (_node->left && _node->left == _endNode)
					{
						_node = _node->left;
					}
					//there is a left child : immediate lower node is left subtree's max
					else if (_node->left && _comp(_node->left->dataPair.first, ret->first))
					{
						_node = _node->left;
						_node = highestNode(_node);
					}
					//no right child, try again from parent
					else
					{
						Node*	parentNode = _node->parent;
						while (_node != parentNode->right)
						{
							_node = parentNode;
							parentNode = parentNode->parent;
						}
						_node = parentNode;
						return (ret);
					}
				}
				return (ret);
			}

			bool	operator==(const mapIterator& rhs) const
			{
				return (rhs._node == _node);
			}

			bool	operator!=(const mapIterator& rhs) const
			{
				return (rhs._node != _node);
			}

		/*	PRIVATE MEMBER FUNCTIONS	*/
		
		private :

			//returns the lowest key node from the root after recursive search
			Node*	lowestNode(Node* root)
			{
				if (root && root != _endNode && root->left && root->left != _endNode)
					return (lowestNode(root->left));
				return (root);
			}
		
			//returns the highest key node from the root after recursive search
			Node*	highestNode(Node* root)
			{
				if (root && root != _endNode && root->right && root->right != _endNode)
					return (highestNode(root->right));
				return (root);
			}
		
	};

};   //namespace end

#endif