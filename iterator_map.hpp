#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include <iostream>

namespace ft
{
	//boolean is true is const
	template <bool isConst, typename falseConst, typename trueConst>
	struct chooseConst {};

	//sets 2nd parameter as ref and pointer
	template <typename falseConst, typename trueConst>
	struct chooseConst<false, falseConst, trueConst>
	{ typedef falseConst type; };

	//sets 2nd parameter as (const) ref and pointer
	template <typename falseConst, typename trueConst>
	struct chooseConst<true, falseConst, trueConst>
	{ typedef trueConst type; };

	template < class Key, class T, typename Node, bool isConst = false, class Compare = std::less<Key> >
	class mapIterator
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef Compare key_compare;
			typedef ft::pair<const Key, T> value_type;
			typedef size_t size_type;
			typedef	std::ptrdiff_t difference_type;

			typedef typename std::bidirectional_iterator_tag iterator_category;
			typedef typename chooseConst<isConst, value_type &, const value_type &>::type reference;
			typedef typename chooseConst<isConst, value_type *, const value_type *>::type pointer;

		private:

			Node		*_node;
			Node		*_root;
			Node		*_endNode;
			key_compare	_comp;

		public:
			mapIterator(Node *root = NULL,  Node *endNode = NULL, Node *node = NULL, const key_compare& comp = key_compare()) : _node(node), _root(root), _endNode(endNode),_comp(comp) {};
			mapIterator(const mapIterator &other) : _node(other._node), _endNode(other._endNode), _comp(other._comp) {};
			~mapIterator() {};

			Node *getNode() const { return _node; };

			mapIterator & operator = (const mapIterator &rhs)
			{
				if (*this != rhs)
				{
					_node = rhs._node;
					_root = rhs._root;
					_endNode = rhs._endNode;
					_comp = rhs._comp;
				}
				return (*this);
			};
			bool operator == (const mapIterator & rhs) const { return (_node == rhs._node); };
			bool operator != (const mapIterator & rhs) const { return !(*this == rhs); };
			reference operator *() const { return _node->dataPair; };
			pointer operator ->() const { return &_node->dataPair; };

			// https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
			mapIterator & operator ++()
			{
				Node *currentNode;
				// std::cout << "_node == nullptr: " << (_node == nullptr) << std::endl;
				if (_node != nullptr)
					std::cout << "OPERATOR++ 1: _node iterator: " << _node->dataPair.first << std::endl;
				if (_node == nullptr && _node != _endNode)
				{
					_node = _root;
					if (_node == nullptr)
						return *this;
					while (_node->left != nullptr && _node->left != _endNode)
						_node = _node->left;
				}
				else if (_node->right != nullptr && _node->right != _endNode)
				{
					_node = _node->right;
					while (_node->left != nullptr && _node->left != _endNode)
						_node = _node->left;
				}
				else if (_node->right == nullptr)
				{
					currentNode = _node->parent;
					while (currentNode != nullptr && currentNode != _endNode && currentNode->right != nullptr && currentNode->right != _endNode)
					{
						if (_node == currentNode->right)
						{
							_node = currentNode;
							currentNode = currentNode->parent;
						}
						else
							break;
					}
					_node = currentNode;
				}
				else if (_node->right == _endNode)
				{
					_node = _endNode;
				}
				std::cout << "OPERATOR++ 2: _node iterator: " << _node->dataPair.first << std::endl;
				return *this;
			};
			mapIterator operator ++(int)
			{
				mapIterator temp = *this;
				++(*this);
				return temp;
			};
			mapIterator & operator --()
			{
				Node *currentNode;
				if (_node == nullptr)
				{
					_node = _root;
					if (_node == nullptr)
						return *this;
					while (_node->right != nullptr)
						_node = _node->right;
				}
				else if (_node->left != nullptr && _node->left != _endNode)
				{
					_node = _node->left;
					while (_node->right != nullptr && _node->right != _endNode)
						_node = _node->right;
				}
				else if (_node->left == nullptr)
				{
					currentNode = _node->parent;
					while (currentNode != nullptr && currentNode != _endNode && _node == currentNode->left)
					{
						_node = currentNode;
						currentNode = currentNode->parent;
					}
					_node = currentNode;
				}
				else if (_node->left == _endNode)
					_node = _endNode;
				return *this;			
			};
			mapIterator operator --(int)
			{
				mapIterator temp = *this;
				--(*this);
				return temp;
			};
	};
}

#endif