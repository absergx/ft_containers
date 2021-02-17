//
// Created by Meldred Emilio on 11/29/20.
//

#pragma once
#include "ft.hpp"
#include <memory>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
	private:
		pointer			_arr;
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;

		difference_type	_getIndex(pointer ptr) {
			return end().getPointer() - ptr;
		}

		bool 			_checkFreeSpace(size_type need) {
			return (_capacity - _size) >= need;
		}

		pointer			_createVector(const_reference val) {
			pointer arr = _alloc.allocate(_capacity);
			for (size_type count = 0; count < _size; ++count)
				_alloc.construct(arr + count, val);
			return arr;
		}

		void 			_reallocVector(size_type range = 0) {
			size_type newCapacity = (_size + range) * 2;
			pointer newArr = _alloc.allocate(newCapacity);
			for (size_type count = 0; count < _size; ++count)
				_alloc.construct(newArr + count, *(_arr + count));
			for (size_type count = 0; count < _size; ++count)
				_alloc.destroy(_arr + count);
			if (_capacity)
				_alloc.deallocate(_arr, _capacity);
			_capacity = newCapacity;
			_arr = newArr;
		}

	public:
		/* Constructors */
		explicit vector(const allocator_type& alloc = allocator_type()) : _arr(nullptr), _alloc(alloc), _size(0), _capacity(0) { }
		explicit vector(size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(_size) { _arr = _createVector(val); }
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) : _alloc(alloc), _size(0) {
			_capacity = static_cast<size_type>(last.operator->() - first.operator->());
			_arr = _alloc.allocate(_capacity);
			insert(begin(), first, last);
		}
		vector(const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity) {
			_arr = _alloc.allocate(_size);
			for (size_type count = 0; count < _size; ++count)
				_alloc.construct(_arr + count, *(x._arr + count));
		}

		/* Destructor */
		~vector() {
			clear();
			if (_capacity)
				_alloc.deallocate(_arr, _capacity);
		}

		/* Operator = */
		vector&					operator= (const vector& x) {
			clear();
			insert(begin(), x.begin(), x.end());
			return *this;
		}

		/* Iterators */
		class iterator : public std::iterator<std::random_access_iterator_tag, value_type> {
		private:
			pointer			_pointer;
		public:
			explicit iterator(pointer arg = nullptr) : _pointer(arg) {}
			iterator(iterator const &it) { *this = it; }
			~iterator() {}
			iterator&		operator= (iterator const &rhs) {
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}

			bool 			operator==(iterator const &rhs) const { return _pointer == rhs._pointer; }
			bool 			operator!=(iterator const &rhs) const { return _pointer != rhs._pointer; }
			bool 			operator> (iterator const &rhs) const { return _pointer > rhs._pointer; }
			bool 			operator>=(iterator const &rhs) const { return _pointer >= rhs._pointer; }
			bool 			operator< (iterator const &rhs) const { return _pointer < rhs._pointer; }
			bool 			operator<=(iterator const &rhs) const { return _pointer <= rhs._pointer; }

			bool 			operator==(const_iterator const &rhs) const { return _pointer == rhs.getPointer(); }
			bool 			operator!=(const_iterator const &rhs) const { return _pointer != rhs.getPointer(); }
			bool 			operator> (const_iterator const &rhs) const { return _pointer > rhs.getPointer(); }
			bool 			operator>=(const_iterator const &rhs) const { return _pointer >= rhs.getPointer(); }
			bool 			operator< (const_iterator const &rhs) const { return _pointer < rhs.getPointer(); }
			bool 			operator<=(const_iterator const &rhs) const { return _pointer <= rhs.getPointer(); }

			iterator		operator+ (difference_type const &rhs) const { return iterator(_pointer + rhs); }
			iterator		operator- (difference_type const &rhs) const { return iterator(_pointer - rhs); }
			difference_type	operator- (iterator const &rhs) const { return _pointer - rhs._pointer; }
			iterator&		operator+=(difference_type const &rhs) {
				_pointer += rhs;
				return *this;
			}
			iterator&		operator-=(difference_type const &rhs) {
				_pointer -= rhs;
				return *this;
			}

			iterator&		operator++() {
				_pointer += 1;
				return *this;
			}
			iterator&		operator--() {
				_pointer -= 1;
				return *this;
			}
			iterator		operator++(int) {
				iterator tmp(*this);
				operator++();
				return tmp;
			}
			iterator		operator--(int) {
				iterator tmp(*this);
				operator--();
				return tmp;
			}

			value_type&		operator[](difference_type const &index) { return *(_pointer + index); }
			value_type&		operator* () const { return *_pointer; }
			value_type*		operator->() const { return _pointer; }

			pointer 		getPointer() const { return _pointer; }
		};

		class const_iterator : public std::iterator<std::random_access_iterator_tag, value_type> {
		private:
			pointer			_pointer;
		public:
			explicit const_iterator(pointer arg = nullptr) : _pointer(arg) {}
			const_iterator(const_iterator const &it) { *this = it; }
			const_iterator(iterator const &it) { *this = it; }
			~const_iterator() {}
			const_iterator&	operator= (iterator const& rhs) {
				_pointer = rhs.getPointer();
				return *this;
			}
			const_iterator& operator= (const_iterator const &rhs) {
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}

			bool 			operator==(iterator const &rhs) const { return _pointer == rhs.getPointer(); }
			bool 			operator!=(iterator const &rhs) const { return _pointer != rhs.getPointer(); }
			bool 			operator> (iterator const &rhs) const { return _pointer > rhs.getPointer(); }
			bool 			operator>=(iterator const &rhs) const { return _pointer >= rhs.getPointer(); }
			bool 			operator< (iterator const &rhs) const { return _pointer < rhs.getPointer(); }
			bool 			operator<=(iterator const &rhs) const { return _pointer <= rhs.getPointer(); }

			bool 			operator==(const_iterator const &rhs) const { return _pointer == rhs._pointer; }
			bool 			operator!=(const_iterator const &rhs) const { return _pointer != rhs._pointer; }
			bool 			operator> (const_iterator const &rhs) const { return _pointer > rhs._pointer; }
			bool 			operator>=(const_iterator const &rhs) const { return _pointer >= rhs._pointer; }
			bool 			operator< (const_iterator const &rhs) const { return _pointer < rhs._pointer; }
			bool 			operator<=(const_iterator const &rhs) const { return _pointer <= rhs._pointer; }

			const_iterator	operator+ (difference_type const &rhs) const { return const_iterator(_pointer + rhs); }
			const_iterator	operator- (difference_type const &rhs) const { return const_iterator(_pointer - rhs); }
			difference_type operator- (const_iterator const &rhs) const { return _pointer - rhs._pointer; }
			const_iterator&	operator+=(difference_type const &rhs) {
				_pointer += rhs;
				return *this;
			}
			const_iterator&	operator-=(difference_type const &rhs) {
				_pointer -= rhs;
				return *this;
			}

			const_iterator&	operator++() {
				_pointer += 1;
				return *this;
			}
			const_iterator&	operator--() {
				_pointer -= 1;
				return *this;
			}
			const_iterator	operator++(int) {
				const_iterator tmp(*this);
				operator++();
				return tmp;
			}
			const_iterator	operator--(int) {
				const_iterator tmp(*this);
				operator--();
				return tmp;
			}

			value_type const&	operator[](difference_type const &index) { return *(_pointer + index); }
			value_type const&	operator* () const { return *_pointer; }
			value_type const*	operator->() const { return _pointer; }

			pointer 		getPointer() const { return _pointer; }
		};

		class reverse_iterator : public std::reverse_iterator<vector::iterator> {
		private:
			pointer 		_pointer;
		public:
			explicit reverse_iterator(pointer ptr = nullptr) : _pointer(ptr) {}
			reverse_iterator(reverse_iterator const &it) { *this = it; }
			~reverse_iterator() {}
			reverse_iterator&	operator= (reverse_iterator const& rhs) {
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}

			bool 			operator==(reverse_iterator const &rhs) const { return _pointer == rhs._pointer; }
			bool 			operator!=(reverse_iterator const &rhs) const { return _pointer != rhs._pointer; }
			bool 			operator> (reverse_iterator const &rhs) const { return _pointer < rhs._pointer; }
			bool 			operator>=(reverse_iterator const &rhs) const { return _pointer <= rhs._pointer; }
			bool 			operator< (reverse_iterator const &rhs) const { return _pointer > rhs._pointer; }
			bool 			operator<=(reverse_iterator const &rhs) const { return _pointer >= rhs._pointer; }

			bool 			operator==(const_reverse_iterator const &rhs) const { return _pointer == rhs.getPointer(); }
			bool 			operator!=(const_reverse_iterator const &rhs) const { return _pointer != rhs.getPointer(); }
			bool 			operator> (const_reverse_iterator const &rhs) const { return _pointer < rhs.getPointer(); }
			bool 			operator>=(const_reverse_iterator const &rhs) const { return _pointer <= rhs.getPointer(); }
			bool 			operator< (const_reverse_iterator const &rhs) const { return _pointer > rhs.getPointer(); }
			bool 			operator<=(const_reverse_iterator const &rhs) const { return _pointer >= rhs.getPointer(); }

			reverse_iterator	operator+ (difference_type n) const { return reverse_iterator(_pointer - n); }
			reverse_iterator	operator- (difference_type n) const { return reverse_iterator(_pointer + n); }
			reverse_iterator&	operator+=(difference_type n) {
				_pointer -= n;
				return *this;
			}
			reverse_iterator&	operator-=(difference_type n) {
				_pointer += n;
				return *this;
			}

			reverse_iterator&	operator++() {
				_pointer -= 1;
				return *this;
			}
			reverse_iterator&	operator--() {
				_pointer += 1;
				return *this;
			}
			reverse_iterator	operator++(int) {
				reverse_iterator tmp(*this);
				operator++();
				return tmp;
			}
			reverse_iterator	operator--(int) {
				reverse_iterator tmp(*this);
				operator--();
				return tmp;
			}

			value_type&		operator[](difference_type const &index) { return *(_pointer - index); }
			value_type&		operator* () const { return *_pointer; }
			value_type*		operator->() const { return _pointer; }

			pointer 		getPointer() const { return _pointer; }
		};

		class const_reverse_iterator : public std::reverse_iterator<vector::iterator> {
		private:
			pointer			_pointer;
		public:
			explicit const_reverse_iterator(pointer ptr = nullptr) : _pointer(ptr) {}
			const_reverse_iterator(reverse_iterator const &it) { *this = it; }
			const_reverse_iterator(const_reverse_iterator const &it) { *this = it; }
			~const_reverse_iterator() {}
			const_reverse_iterator&		operator= (const_reverse_iterator const &rhs) {
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}
			const_reverse_iterator&		operator= (reverse_iterator const &rhs) {
				_pointer = rhs.getPointer();
				return *this;
			}

			bool 			operator==(const_reverse_iterator const &rhs) const { return _pointer == rhs._pointer; }
			bool 			operator!=(const_reverse_iterator const &rhs) const { return _pointer != rhs._pointer; }
			bool 			operator> (const_reverse_iterator const &rhs) const { return _pointer < rhs._pointer; }
			bool 			operator>=(const_reverse_iterator const &rhs) const { return _pointer <= rhs._pointer; }
			bool 			operator< (const_reverse_iterator const &rhs) const { return _pointer > rhs._pointer; }
			bool 			operator<=(const_reverse_iterator const &rhs) const { return _pointer >= rhs._pointer; }

			bool 			operator==(reverse_iterator const &rhs) const { return _pointer == rhs.getPointer(); }
			bool 			operator!=(reverse_iterator const &rhs) const { return _pointer != rhs.getPointer(); }
			bool 			operator> (reverse_iterator const &rhs) const { return _pointer < rhs.getPointer(); }
			bool 			operator>=(reverse_iterator const &rhs) const { return _pointer <= rhs.getPointer(); }
			bool 			operator< (reverse_iterator const &rhs) const { return _pointer > rhs.getPointer(); }
			bool 			operator<=(reverse_iterator const &rhs) const { return _pointer >= rhs.getPointer(); }

			const_reverse_iterator	operator+ (difference_type n) const { return const_reverse_iterator(_pointer - n); }
			const_reverse_iterator	operator- (difference_type n) const { return const_reverse_iterator(_pointer + n); }
			const_reverse_iterator&	operator+=(difference_type n) {
				_pointer -= n;
				return *this;
			}
			const_reverse_iterator&	operator-=(difference_type n) {
				_pointer += n;
				return *this;
			}

			const_reverse_iterator&	operator++() {
				_pointer -= 1;
				return *this;
			}
			const_reverse_iterator&	operator--() {
				_pointer += 1;
				return *this;
			}
			const_reverse_iterator	operator++(int) {
				const_reverse_iterator tmp(*this);
				operator++();
				return tmp;
			}
			const_reverse_iterator	operator--(int) {
				const_reverse_iterator tmp(*this);
				operator--();
				return tmp;
			}

			value_type const&		operator[](difference_type const &index) { return *(_pointer - index); }
			value_type const&		operator* () const { return *_pointer; }
			value_type const*		operator->() const { return _pointer; }

			pointer 		getPointer() const { return _pointer; }
		};

		iterator				begin() { return iterator(_arr); }
		const_iterator			begin() const { return const_iterator(_arr); }
		iterator				end() { return iterator(_arr + _size); }
		const_iterator			end() const { return const_iterator(_arr + _size); }
		reverse_iterator		rbegin() { return reverse_iterator(_arr + _size - 1); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(_arr + _size - 1); }
		reverse_iterator		rend() { return reverse_iterator(_arr - 1); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(_arr - 1); }

		/* Capacity */
		size_type		size() const { return _size; }
		size_type		max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type) / ((sizeof(value_type) == 1) ? 2 : 1); }
		void			resize(size_type n, value_type val = value_type()) {
			while (n < _size)
				pop_back();
			while (n > _size)
				push_back(val);
		}
		size_type		capacity() const { return _capacity; }
		bool			empty() const { return _size == 0; }
		void			reserve(size_type n) {
			if (n <= _capacity)
				return;
			pointer newArr = _alloc.allocate(n);
			for (size_type count = 0; count < _size; ++count)
				_alloc.construct(newArr + count, *(_arr + count));
			for (size_type count = 0; count < _size; ++count)
				_alloc.destroy(_arr + count);
			if (_capacity)
				_alloc.deallocate(_arr, _capacity);
			_capacity = n;
			_arr = newArr;
		}

		/* Element access */
		reference		operator[] (size_type n) { return *(_arr + n); }
		const_reference	operator[] (size_type n) const { return *(_arr + n); }
		reference		at (size_type n) {
			if (_size <= n)
				throw std::out_of_range("Index out of range");
			return *(_arr + n);
		}
		const_reference	at (size_type n) const {
			if (_size <= n)
				throw std::out_of_range("Index out of range");
			return *(_arr + n);
		}
		reference		front() { return *_arr; }
		const_reference	front() const { return *_arr; }
		reference		back() { return *(_arr + _size - 1); }
		const_reference	back() const { return *(_arr + _size - 1); }

		/* Modifiers */
		template <class InputIterator>
		void			assign(InputIterator first, InputIterator last,
			   typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			clear();
			insert(begin(), first, last);
		}
		void			assign(size_type n, const value_type& val) {
			clear();
			insert(begin(), n, val);
		}

		void			push_back(const value_type& val) {
			if (_capacity == 0) {
				_capacity = 1;
				_size = 1;
				_arr = _createVector(val);
			} else {
				if (!_checkFreeSpace(1))
					_reallocVector();
				_alloc.construct(_arr + _size, val);
				++_size;
			}
		}

		void			pop_back() {
			_alloc.destroy(_arr + _size - 1);
			--_size;
		}

		iterator		insert(iterator position, const value_type& val) {
			pointer pos = position.getPointer();
			if (!_checkFreeSpace(1)) {
				difference_type index = _getIndex(pos);
				_reallocVector();
				pos = end().getPointer() - index;
			}
			std::memmove(pos + 1, pos, static_cast<size_type>((end().getPointer() - pos)) * sizeof(value_type));
			_alloc.construct(pos, val);
			++_size;
			return iterator(pos);
		}
		void			insert(iterator position, size_type n, const value_type& val) {
			pointer pos = position.getPointer();
			if (!_checkFreeSpace(n)) {
				difference_type index = _getIndex(pos);
				_reallocVector(n);
				pos = end().getPointer() - index;
			}
			std::memmove(pos + n, pos, static_cast<size_type>((end().getPointer() - pos)) * sizeof(value_type));
			for (size_type count = 0; count < n; ++count)
				_alloc.construct(pos + count, val);
			_size += n;
		}
		template <class InputIterator>
		void			insert(iterator position, InputIterator first, InputIterator last,
			   typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			size_type range = static_cast<size_type>(last.operator->() - first.operator->());
			pointer pos = position.getPointer();
			if (!_checkFreeSpace(range)) {
				difference_type index = _getIndex(pos);
				_reallocVector(range);
				pos = end().getPointer() - index;
			}
			std::memmove(pos + range, pos, static_cast<size_type>((end().getPointer() - pos)) * sizeof(value_type));
			for (size_type count = 0; count < range; ++count, ++first)
				_alloc.construct(pos + count, *first);
			_size += range;
		}

		iterator		erase(iterator position) {
			pointer pos = position.getPointer();
			_alloc.destroy(pos);
			std::memmove(pos, pos + 1, static_cast<size_type>((end().getPointer() - pos - 1)) * sizeof(value_type));
			--_size;
			return iterator(pos);
		}
		iterator		erase(iterator first, iterator last) {
			while (first != last) {
				erase(--last);
			}
			return last;
		}

		void			swap(vector& x) {
			pointer			tmpPtr = _arr;
			allocator_type	tmpAlloc = _alloc;
			size_type		tmpSize = _size;
			size_type		tmpCapacity = _capacity;

			_arr = x._arr;
			_alloc = x._alloc;
			_size = x._size;
			_capacity = x._capacity;

			x._arr = tmpPtr;
			x._alloc = tmpAlloc;
			x._size = tmpSize;
			x._capacity = tmpCapacity;
		}

		void			clear() {
			for (size_type count = 0; count < _size; ++count)
				_alloc.destroy(_arr + count);
			_size = 0;
		}

	};
	/* Relational operators */
	template <class T, class Alloc>
	bool		operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		typename ft::vector<T, Alloc>::const_iterator lit = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator rit = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator lite = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator rite = rhs.end();
		for (; lit != lite; ++lit) {
			if (rit == rite || *lit != *rit)
				return false;
			++rit;
		}
		return true;
	}
	template <class T, class Alloc>
	bool		operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs == rhs); }
	template <class T, class Alloc>
	bool		operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() < rhs.size())
			return true;
		typename ft::vector<T, Alloc>::const_iterator lit = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator rit = rhs.begin();
		typename ft::vector<T, Alloc>::const_iterator lite = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator rite = rhs.end();
		for (; lit != lite; ++lit) {
			if (rit == rite)
				return false;
			if (*lit < *rit)
				return true;
			++rit;
		}
		return false;
	}
	template <class T, class Alloc>
	bool		operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(rhs < lhs); }
	template <class T, class Alloc>
	bool		operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return rhs < lhs; }
	template <class T, class Alloc>
	bool		operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs < rhs); }

	/* Swap */
	template <class T, class Alloc>
	void		swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}
