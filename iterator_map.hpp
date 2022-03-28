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
			/*
				1- Is default-constructible, copy-constructible, copy-assignable and destructible (X a; X b(a); b = a;)

				2- Can be compared for equivalence using the equality/inequality operators
				(meaningful when both iterator values iterate over the same underlying sequence). (a == b; a!=b )

				3- Can be dereferenced as an rvalue (if in a dereferenceable state). (*a; a-> b)

				4- For mutable iterators (non-constant iterators):
					Can be dereferenced as an lvalue (if in a dereferenceable state). (*a = t)

				5- Can be incremented (if in a dereferenceable state).
				The result is either also dereferenceable or a past-the-end iterator.
				Two iterators that compare equal, keep comparing equal after being both increased. (++a; a++; *a++)

				6- Can be decremented (if a dereferenceable iterator value precedes it). (--a; a--; *a--)
			*/
			mapIterator(Node *node = NULL, Node *root = NULL, const key_compare& comp = key_compare()) : _node(node), _root(root), _comp(comp)
			{
				if (_node == NULL && _root == NULL)
				{
					_node = Node();
					_root = _node;
				}
			};
			mapIterator(const mapIterator &other) : _node(other._node), _comp(other._comp) {};
			~mapIterator() {};
			mapIterator & operator = (const mapIterator &rhs)
			{
				if (this != rhs)
				{
					_node = rhs._node;
					_comp = rhs._comp;
				}
				return (*this);
			};
			bool operator == (const mapIterator & rhs) const { return (_node == rhs._node); };
			bool operator != (const mapIterator & rhs) const { return !(this == rhs); };
			reference operator *() const { return _node->dataPair; };
			pointer operator ->() const { return &_node->dataPair; };

			mapIterator & operator ++()
			{
				// https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
			// template <class Comparable>
			// typename BinarySearchTree<Comparable>::BstIterator&
			// BinarySearchTree<Comparable>::BstIterator::operator++ ()
			// {
			// BinaryNode<Comparable> *p;
			
			// if (nodePtr == nullptr)
			// 	{
			// 	// ++ from end(). get the root of the tree
			// 	nodePtr = tree->root;
				
			// 	// error! ++ requested for an empty tree
			// 	if (nodePtr == nullptr)
			// 		throw UnderflowException { };
				
			// 	// move to the smallest value in the tree,
			// 	// which is the first node inorder
			// 	while (nodePtr->left != nullptr) {
			// 		nodePtr = nodePtr->left;
			// 	}
			// 	}
			// else
			// 	if (nodePtr->right != nullptr)
			// 	{
			// 		// successor is the farthest left node of
			// 		// right subtree
			// 		nodePtr = nodePtr->right;
					
			// 		while (nodePtr->left != nullptr) {
			// 		nodePtr = nodePtr->left;
			// 		}
			// 	}
			// 	else
			// 	{
			// 		// have already processed the left subtree, and
			// 		// there is no right subtree. move up the tree,
			// 		// looking for a parent for which nodePtr is a left child,
			// 		// stopping if the parent becomes NULL. a non-NULL parent
			// 		// is the successor. if parent is NULL, the original node
			// 		// was the last node inorder, and its successor
			// 		// is the end of the list
			// 		p = nodePtr->parent;
			// 		while (p != nullptr && nodePtr == p->right)
			// 		{
			// 			nodePtr = p;
			// 			p = p->parent;
			// 		}
					
			// 		// if we were previously at the right-most node in
			// 		// the tree, nodePtr = nullptr, and the iterator specifies
			// 		// the end of the list
			// 		nodePtr = p;
			// 	}
			
			// return *this;
			// }

			};
			mapIterator & operator ++(int)
			{

			};

			mapIterator & operator --()
			{

			};
			mapIterator & operator --(int)
			{

			};

		private:

			// mapIterator begin() const
			// {
			// 	return ();
			// }
	};
}

#endif