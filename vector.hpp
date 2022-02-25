#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>


namespace ft {
	template<typename T, class Alloc = std::allocator<T> >
	class vector
	{

		public:


			typedef T value_type;													//value_type				||	(T)	
			typedef	Alloc allocator_type;											// allocator_type			||	(Alloc)																					||	defaults to: allocator<value_type>
			typedef	typename allocator_type::reference reference;					// reference				||	allocator_type::reference																||	for the default allocator: value_type&
			typedef	typename allocator_type::const_reference	const_reference;	// const_reference			||	allocator_type::const_reference															||	for the default allocator: const value_type&
			typedef	typename allocator_type::pointer pointer;						// pointer					||	allocator_type::pointer																	||	for the default allocator: value_type*
			typedef	typename allocator_type::const_pointer const_pointer;			// const_pointer			||	allocator_type::const_pointer															||	for the default allocator: const value_type*
			typedef	typename allocator_type::pointer iterator;						// iterator					||	a random access iterator to value_type													||	convertible to const_iterator
			typedef	typename allocator_type::const_pointer const_iterator;			// const_iterator			||	a random access iterator to const value_type											||
			// typedef	ft::reverse_iterator<iterator>	reverse_iterator; 					// reverse_iterator			||	reverse_iterator<iterator>																||
			// typedef	ft::reverse_iterator<const_iterator> const_reverse_iterator;		// const_reverse_iterator	||	reverse_iterator<const_iterator>														||
			typedef	typename allocator_type::difference_type difference_type;		// difference_type			||	a signed integral type, identical to: iterator_traits<iterator>::difference_type		||	usually the same as ptrdiff_t
			typedef typename allocator_type::size_type size_type;					// size_type				||	an unsigned integral type that can represent any non-negative value of difference_type	||	usually the same as size_t


		private:
			size_type		_size;
			size_type		_capacity;
			value_type		*_array;
			allocator_type	_alloc;

		public:
		// ** // CONSTRUCTOR // ** // ✅ ❌

			/*
			explicit vector (const allocator_type& alloc = allocator_type()); 														✅
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());	❌
			template <class InputIterator>
					vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());				🚧 
			vector (const vector& x)				🚧 
			~vector();								❌
			vector& operator= (const vector& x)		🚧 
			*/

			explicit vector(const allocator_type & alloc = allocator_type())
			: _size(0), _capacity(0), _array(NULL), _alloc(alloc) {};

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _size(n), _capacity(n), _array(NULL), _alloc(alloc)
			{
				_array = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; ++i)
					_alloc.construct(&_array[i], val);
			};

			// template <class InputIterator>
			// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			// : _size(0), _capacity(0), _array(NULL), _alloc(alloc)
			// {
			// 	for (InputIterator it = first; it != last; ++it)
			// 		_size++;
			// 	_capacity = _size;
			// 	_array = _alloc.allocate(_size);
			// 	for (size_type i = 0; i < _size; ++i)
			// 		_alloc.construct(&_array[i], (first++));
			// };
			
			// vector (const vector& x) : _size(x._size), _capacity(x._capacity), _array(x._array), _alloc(x._alloc) {}; // insert ?

// 			~Vector() {};

// 			Vector &operator =(const Vector& rhs)
// 			{
// 				if (rhs._size > _size)
// 				{
// 					delete [] _array;
// 					_capacity = rhs._capacity;
// 					_array = new int[_capacity];
// 				}
// 				for (int i = 0; i < rhs._size; ++i)
// 					_array[i] = rhs._array[i];
// 				_size = rhs._size;
// 			};

// 		// ** // ITERATORS // ** // ✅ ❌

// 			/*
// 			begin	✅
// 			end		✅
// 			rbegin	❌
// 			rend	❌
// 			*/

			iterator begin() { return (&_array[0]); };
			const_iterator begin() const { return (const_iterator(begin())); };

			iterator end() { return (&_array[_size]); };
			const_iterator end() const { return (const_iterator(end())); };

// 			// reverse_iterator rbegin();
// 			// const_reverse_iterator rbegin() const;

// 			// reverse_iterator rend();
// 			// const_reverse_iterator rend() const;

// 		// ** // CAPACITY // ** //

// 			/*
// 			size		✅ 
// 			max_size	✅ 
// 			resize		🚧
// 			capacity	✅
// 			empty		✅
// 			reserve		🚧
// 			*/

			size_type size() const { return (_size); };
		
			size_type max_size() const { return (_alloc.max_size()); };
		
			// void resize (size_type n, value_type val = value_type())
			// {
				// resize to contain n elements
				// if n < _size
				// reduce to n & remove + destroy the rest

				// if n > _size
				// insert diff elements at the end to reach n size
				// if val is specified, new elements are copies of val
				// else they are value-initialized

				// if n > _capacity
				// automatic reallocation
			// };
		
			size_type capacity() const { return (_capacity); };
		
			bool empty() const { return (_size == 0); };
			
			void reserve (size_type n)
			{
				// request that _capacity be at least enough for n elements
				// if (n > max_size())
					// throw error // do try catch
				if (n > _capacity)
				{
					size_type oldCapacity = _capacity;
					_capacity = n;
					value_type *newArray = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; ++i)
						_alloc.construct(&newArray[i], _array[i]);
					for (iterator it = begin(); it != end(); ++it)
						_alloc.destroy(it);
					_alloc.deallocate(_array, oldCapacity);
					_array = newArray;
				}
			};

// 		// ** // ELEMENT ACCESS // ** //

// 			/*
// 			operator[]	✅ 
// 			at			🚧 
// 			front		✅
// 			back		✅
// 			*/

			reference operator[] (size_type n) { return (_array[n]); };
			const_reference operator[] (size_type n) const { return ((*this)[n]); };

			reference at (size_type n)
			{
				// if (n < 0 || n >= _size)
					// throwing an out_of_range exception 
				return (_array[n]);
			};
			const_reference at (size_type n) const { return at(n); };

			reference front() { return (*begin()); };
			const_reference front() const { return (const_reference(front())); };

			reference back() { return *(end() - 1); };
			const_reference back() const { return (const_reference(back())); };

// 		// ** // MODIFIERS // ** //

// 			/*
// 			assign		🚧
// 			push_back	🚧 
// 			pop_back	🚧 
// 			insert		🚧 
// 			erase		🚧 
// 			swap		❌
// 			clear		🚧 
// 			*/

// 			/*
// 			template <class InputIterator>
// 			void assign (InputIterator first, InputIterator last);
			void assign (size_type n, const value_type& val)
			{
				size_type oldSize = _size;
				reserve(n);
				for (size_type i = oldSize; i < _size; ++i)
					_alloc.construct(&_array[i], val);
			};

			void push_back (const value_type& val)
			{
				if (_size == _capacity)
				{
					size_type oldCapacity = _capacity;
					_capacity = _size == 0 ? 1 : _capacity * 2;
					value_type *newArray = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; ++i)
						_alloc.construct(&newArray[i], _array[i]);
					for (iterator it = begin(); it != end(); ++it)
						_alloc.destroy(it);
					_alloc.deallocate(_array, oldCapacity);
					_array = newArray;
				}
				_alloc.construct(&_array[_size], val);
				_size++;
			};

// 			void pop_back();

			// iterator insert (iterator position, const value_type& val)
			// {

			// };	
			// void insert (iterator position, size_type n, const value_type& val);
			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position)
			{
				iterator it = position;
				_alloc.destroy(it);
				for (iterator it = position; it + 1 != end(); ++it)
				{
					_alloc.construct(it, *(it + 1));
					// if (it + 1 != end())
					_alloc.destroy(it + 1);
				}
				_size -= 1;
			};
			iterator erase (iterator first, iterator last)
			{
				
			};

// 			void swap (vector& x);

			void clear()
			{
				for (iterator it = begin(); it != end(); ++it)
					_alloc.destroy(it);
				_size = 0;
				_alloc.deallocate(_array, _capacity);
				_capacity = 0;
			};
// 			*/

			// void pushBack(int value)

// 			void popBack()
// 			{
// 				if (_size == 0)
// 					throw std::exception("Pop back on empty vector!");
// 				--_size;
// 			};
// 			void insert(int index, int value)
// 			{

// 			};
// 			void erase(int index)
// 			{
// 				if (index < 0 || index >= size)
// 					throw std::exception("Erase - Index out of range!");
// 				for (int i = index; i < _size; ++i)
// 					_array[i] = _array[i + 1];
// 				_size--;
// 			};
// 		// ** // ALLOCATOR // ** //

// 			/*
// 			get_allocator	❌
// 			*/

// 			// allocator_type get_allocator() const;

// 		// ** // NON MEMBER FUNCTION OVERLOADS // ** //

// 			/*
// 			relational operators :
// 				==	🚧 
// 				!=	🚧 
// 				<	❌
// 				<=	❌
// 				>	❌
// 				>=	❌
// 			swap	❌
// 			*/

// 			/*
// 			template <class T, class Alloc>
// 			bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// 			template <class T, class Alloc>
// 			bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// 			template <class T, class Alloc>
// 			bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// 			template <class T, class Alloc>
// 			bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// 			template <class T, class Alloc>
// 			bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
// 			template <class T, class Alloc>
// 			bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// 			template <class T, class Alloc>
// 			void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
// 			*/

// 			bool operator ==(const Vector & rhs) const
// 			{
// 				if (size() != rhs.size())
// 					return false;
// 				for (int i = 0; i < size(); ++i)
// 				{
// 					if (_array[i] != rhs._array[i])
// 						return false;
// 				}
// 				return true;
// 			};

// 			bool operator !=(const Vector & rhs) const { return !(*this == rhs); };

	};

// 	friend std::ostream &operator<<(std::ostream &ostr, const Vector&vector)
// 	{
// 		for (int i = 0; i < vector.size(); ++i)
// 			ostr << vector._array[i] << " ";
// 		ostr << std::endl;
// 		return (ostr);
// 	};

}

#endif