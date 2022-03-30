#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag

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
			key_compare	_comp;

		public:
			mapIterator(Node *root = NULL, Node *node = NULL, const key_compare& comp = key_compare()) : _node(node), _root(root), _comp(comp) {};
			mapIterator(const mapIterator &other) : _node(other._node), _comp(other._comp) {};
			~mapIterator() {};
			mapIterator & operator = (const mapIterator &rhs)
			{
				if (*this != rhs)
				{
					_node = rhs._node;
					_root = rhs._root;
					_comp = rhs._comp;
				}
				return (*this);
			};
			bool operator == (const mapIterator & rhs) const { return (_node == rhs._node && _root == rhs._root); };
			bool operator != (const mapIterator & rhs) const { return (_node != rhs._node && _root != rhs._root); };
			reference operator *() const { return _node->dataPair; };
			pointer operator ->() const { return &_node->dataPair; };

			// https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
			mapIterator & operator ++()
			{
				Node *currentNode;
				if (_node == nullptr)
				{
					_node = _root;
					if (_node == nullptr)
						std::underflow_error("tree iterator operator++: tree empty");
					while (_node->left != nullptr)
						_node = _node->left;
				}
				else if (_node->right != nullptr)
				{
					_node = _node->right;
					while (_node->left != nullptr)
						_node = _node->left;
				}
				else
				{
					currentNode = _node->parent;
					while (currentNode != nullptr && _node == currentNode->right)
					{
						_node = currentNode;
						currentNode = currentNode->parent;
					}
					_node = currentNode;
				}
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
						throw std::underflow_error("tree iterator operator--: tree empty");
					while (_node->right != nullptr)
						_node = _node->right;
				}
				else if (_node->left != nullptr)
				{
					_node = _node->left;
					while (_node->right != nullptr)
						_node = _node->right;
				}
				else
				{
					currentNode = _node->parent;
					while (currentNode != nullptr && _node == currentNode->left)
					{
						_node = currentNode;
						currentNode = currentNode->parent;
					}
					_node = currentNode;
				}
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