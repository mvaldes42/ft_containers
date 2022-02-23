#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

class Vector
{
	private:
		int _size;
		int _capacity;
		int *_array;

	public:

	// ** // CONSTRUCTOR // ** // ✅ ❌

		/*
		explicit vector (const allocator_type& alloc = allocator_type()); 														❌
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());	❌
		template <class InputIterator>
				vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());				❌
		vector (const vector& x) ❌	🚧 
		*/

		Vector() : _size(0), _capacity(0), _array(new int[_capacity]){};
		Vector(const Vector &src) : _size(src._size), _capacity(src._capacity), _array(new int[_capacity])
		{
			for (int i=0; i<_size; ++i)
				_array[i] = src._array[i];
		};
		Vector(int elements, int value = 0) : _size(elements), _capacity(elements), _array(new int[_capacity])
		{
			for (int i=0; i<_size; ++i)
				_array[i] = value;
		};

		~Vector()
		{
			delete [] _array;
		};

		Vector &operator =(const Vector& rhs)
		{
			if (rhs._size > _size)
			{
				delete [] _array;
				_capacity = rhs._capacity;
				_array = new int[_capacity];
			}
			for (int i = 0; i < rhs._size; ++i)
				_array[i] = rhs._array[i];
			_size = rhs._size;
		};

	// ** // ITERATORS // ** // ✅ ❌

		/*
		begin	❌	🚧 
		end		❌	🚧 
		rbegin	❌
		rend	❌
		*/

	    // iterator begin();
		// const_iterator begin() const;

		// iterator end();
		// const_iterator end() const;

		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;

      	// reverse_iterator rend();
		// const_reverse_iterator rend() const;

	// ** // CAPACITY // ** //

		/*
		size		❌	🚧 
		max_size	❌	🚧 
		resize		❌
		capacity	❌
		empty		❌	🚧 
		reserve		❌
		*/

		// size_type size() const;
	
		// size_type max_size() const;
	
		// void resize (size_type n, value_type val = value_type());
	
		// size_type capacity() const;
	
		// bool empty() const;
	     
		// void reserve (size_type n);

	// ** // ELEMENT ACCESS // ** //

		/*
		operator[]	❌	🚧 
		at			❌	🚧 
		front		❌
		back		❌
		*/

		// reference operator[] (size_type n);
		// const_reference operator[] (size_type n) const;

		// reference at (size_type n);
		// const_reference at (size_type n) const;

		// reference front();
		// const_reference front() const;

    	// reference back();
		// const_reference back() const;


	// ** // MODIFIERS // ** //

		/*
		assign		❌
		push_back	❌	🚧 
		pop_back	❌	🚧 
		insert		❌	🚧 
		erase		❌	🚧 
		swap		❌
		clear		❌	🚧 
		*/

		/*
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val);

		void push_back (const value_type& val);

		void pop_back();

		iterator insert (iterator position, const value_type& val);	
		void insert (iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last);

		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);

		void swap (vector& x);

		void clear();
		*/

	// ** // ALLOCATOR // ** //

		/*
		get_allocator	❌
		*/

		// allocator_type get_allocator() const;

	// ** // NON MEMBER FUNCTION OVERLOADS // ** //

		/*
		relational operators :
			==	❌
			!=	❌
			<	❌
			<=	❌
			>	❌
			>=	❌
		swap	❌
		*/

		/*
		template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
		template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

		template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
		*/

		void pushBack(int value)
		{
			if (_size < _capacity)
			{
				_array[_size] = value;
				_size++;
			}
			else
			{
				_capacity *= 2;
				int *newArray = new int[_capacity];
				for (int i = 0; i < _size; ++i)
					newArray[i] = _array[i];
				newArray[_size] = value;
				_size++;
				delete [] _array;
				_array = newArray;
			}

		};

		void popBack()
		{
			if (_size == 0)
				throw std::exception("Pop back on empty vector!");
			--_size;
		};

		bool empty() const { return (_size == 0); };
		int size() const { return (_size); };
		int capacity() const { return (_capacity); };

		bool operator ==(const Vector & rhs) const
		{
			if (size() != rhs.size())
				return false;
			for (int i = 0; i < size(); ++i)
			{
				if (_array[i] != rhs._array[i])
					return false;
			}
			return true;
		};

		bool operator !=(const Vector & rhs) const { return !(*this == rhs); };

		int  &operator[](int index) const { return (_array[index]); };
		int &at(int index)
		{
			if ((index < 0 || index >= _size))
				throw std::exception("Pop back on empty vector!");
			return (_array[index]);
		};
		int &front() const { return _array[0]; };
		int &back() const { return _array[_size - 1]; };

		void insert(int index, int value)
		{

		};
		void erase(int index)
		{
			if (index < 0 || index >= size)
				throw std::exception("Erase - Index out of range!");
			for (int i = index; i < _size; ++i)
				_array[i] = _array[i + 1];
			_size--;
		};
		void clear()
		{
			//clear the memory of pointers if it is pointers
			_size = 0;
		};
};

std::ostream &operator<<(std::ostream &ostr, const Vector&vector)
{
	for (int i = 0; i < vector.size(); ++i)
		ostr << vector._array[i] << " ";
	ostr << std::endl;
	return (ostr);
};

#endif