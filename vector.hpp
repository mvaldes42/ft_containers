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
			typedef ssize_t size_type;					// size_type				||	an unsigned integral type that can represent any non-negative value of difference_type	||	usually the same as size_t


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
			~vector();								✅
			vector& operator= (const vector& x)		✅
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
			
			// vector (const vector& x) : _size(x._size), _capacity(x._capacity), _array(NULL), _alloc(x._alloc)
			// {
			// 	insert(begin(), x.begin(), x.end());
			// };

			~vector()
			{
				clear();
			};
			vector& operator= (const vector& x)
			{
				clear();
				reserve(x._size);
				for (size_type i = 0; i < x._size; ++i)
					push_back(x._array[i]);
			};

// 		// ** // ITERATORS // ** // ✅ ❌

// 			/*
// 			begin	✅
// 			end		✅
// 			rbegin	❌
// 			rend	❌
// 			*/

			iterator begin() { return (&_array[0]); };
			const_iterator begin() const { return const_iterator(&_array[0]); };

			iterator end() { return (&_array[_size]); };
			const_iterator end() const { return const_iterator(&_array[_size]); };

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
// 			reserve		✅
// 			*/

			size_type size() const { return (_size); };
		
			size_type max_size() const { return (_alloc.max_size()); };
		
			void resize (size_type n, value_type val = value_type())
			{
				if (n < 0 || n > max_size())
					throw std::length_error("error");
				else
				{
					while (n < _size)
						pop_back();
					while (n > _size)
						push_back(val);
				}
			};
		
			size_type capacity() const { return (_capacity); };
		
			bool empty() const { return (_size == 0); };
			
			void reserve (size_type n)
			{
				if (n > max_size() || n < 0)
					throw std::length_error("error");
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
// 			at			✅
// 			front		✅
// 			back		✅
// 			*/

			reference operator[] (size_type n) { return (_array[n]); };
			const_reference operator[] (size_type n) const { return (const_reference((*this)[n])); };

			reference at (size_type n)
			{
				if (n < 0 || n >= _size)
					throw std::out_of_range("Error"); 
				return (_array[n]);
			};
			const_reference at (size_type n) const
			{
				if (n < 0 || n >= _size)
				throw std::out_of_range("Error"); 
				return (_array[n]);
			};

			reference front() { return (*begin()); };
			const_reference front() const { return const_reference(*begin()); };

			reference back() { return *(end() - 1); };
			const_reference back() const { return const_reference(*(end() - 1)); };

// 		// ** // MODIFIERS // ** //

// 			/*
// 			assign		✅ 
// 			push_back	✅ 
// 			pop_back	✅
// 			insert		✅ 🚧  ==> ENABLE IF
// 			erase		✅ 
// 			swap		✅ 
// 			clear		✅ 
// 			*/

// 			/*
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				clear();
				insert(begin(), first, last);
			};
			void assign (size_type n, const value_type& val)
			{
				clear();
				resize(n, val);
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

			void pop_back()
			{
				_alloc.destroy(end() - 1);
				_size -= 1;
			};

			iterator insert (iterator position, const value_type& val)
			{
				insert(position, 1, val);
				return (position);
			};
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n > 0)
				{
					vector tmpVect;
					iterator it = begin();

					tmpVect.reserve(_size + n);
					while (it < position)
						tmpVect.push_back(*(it++));
					while (n-- > 0)
						tmpVect.push_back(val);
					while (it < end())
						tmpVect.push_back(*(it++));
					swap(tmpVect);
				}
			};
			// ENABLE IF
			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last)
			// {
			// 	vector tmpVect;
			// 	iterator it = begin();

			// 	// tmpVect.reserve(_size + n); HOW ??
			// 	while (it < position)
			// 		tmpVect.push_back(*(it++));
			// 	while (first < last)
			// 		tmpVect.push_back(*(first++));
			// 	while (it < end())
			// 		tmpVect.push_back(*(it++));
			// 	swap(tmpVect);	
			// };
			iterator erase (iterator position)
			{
				iterator it = position;
				_alloc.destroy(it);
				for (; it + 1 < end(); ++it)
				{
					_alloc.construct(it, *(it + 1));
					_alloc.destroy(it + 1);
				}
				_alloc.destroy(it);
				_size -= 1;
				return (it);
			};
			iterator erase (iterator first, iterator last)
			{
				size_type n = 0;
				iterator oldFirst = first;
				for (; first < last; first++, n++)
					_alloc.destroy(first);
				iterator oldLast = last;
				for (; oldLast < end(); ++oldLast, ++oldFirst)
				{
					_alloc.construct(oldFirst, *oldLast);
					_alloc.destroy(oldLast);
				}
				_alloc.destroy(oldFirst);
				_size -= n;
				return (last);				
			};

			void swap (vector& x)
			{
				size_type		sizeTemp = x._size;
				size_type		capacityTemp = x._capacity;
				value_type		*arrayTemp = x._array;
				allocator_type	allocTemp = x._alloc;

				x._size = _size;
				x._capacity = _capacity;
				x._array = _array;
				x._alloc = _alloc;

				_size = sizeTemp;
				_capacity = capacityTemp;
				_array = arrayTemp;
				_alloc = allocTemp;
			};

			void clear()
			{
				for (iterator it = begin(); it != end(); ++it)
					_alloc.destroy(it);
				_size = 0;
				_alloc.deallocate(_array, _capacity);
				_capacity = 0;
			};

// 		// ** // ALLOCATOR // ** //

// 			/*
// 			get_allocator	✅ 
// 			*/

			allocator_type get_allocator() const { return (_alloc); };

			friend std::ostream &operator<<(std::ostream &ostr, const vector&vector)
			{
				for (size_type i = 0; i < vector._capacity; ++i)
				{
					if (i == vector._size - 1)
						ostr << vector._array[i] << " | ";
					else
						ostr << vector._array[i] << " ";
				}
				ostr << std::endl;
				return (ostr);
			};

	};
}

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

			// template <class T, class Alloc>
			// void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
			// {

			// };
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

#endif