//
// Created by Meldred Emilio on 11/29/20.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <memory>

namespace ft {
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

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

		pointer			_createVector(const_reference val) {
			pointer arr = _alloc.allocate(_capacity);
			for (size_type count = 0; count < _size; ++count)
				_alloc.construct(arr + count, val);
			return arr;
		}

		void 			_reallocVector(size_type range = 0) {
			_capacity = (_size + range) * 2;
			pointer newArr = _alloc.allocate(_capacity);
			for (size_type count = 0; count < _size; ++count)
				_alloc.construct(newArr + count, *(_arr + count));
			for (size_type count = 0; count < _size; ++count)
				_alloc.destroy(_arr + count);
			if (_capacity)
				_alloc.deallocate(_arr, _capacity);
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
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0);
		vector(const vector& x);

		/* Destructor */
		~vector();

		/* Operator = */
		vector&			operator= (const vector& x);

		/* Iterators */
		class iterator {};
		class const_iterator {};
		class reverse_iterator {};
		class const_reverse_iterator {};
		iterator		begin();
		const_iterator	begin() const;
		iterator		end();
		const_iterator	end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		/* Capacity */
		size_type		size() const;
		size_type		max_size() const;
		void			resize(size_type n, value_type val = value_type());
		size_type		capacity() const;
		bool			empty() const;
		void			reserve(size_type n);

		/* Element access */
		reference		operator[] (size_type n);
		const_reference	operator[] (size_type n) const;
		reference		at (size_type n);
		const_reference	at (size_type n) const;
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		/* Modifiers */
		template <class InputIterator>
		void			assign(InputIterator first, InputIterator last,
			   typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0);
		void			assign(size_type n, const value_type& val);

		void			push_back(const value_type& val);

		void			pop_back();

		iterator		insert(iterator position, const value_type& val);
		void			insert(iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void			insert(iterator position, InputIterator first, InputIterator last,
			   typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0);

		iterator		erase(iterator position);
		iterator		erase(iterator first, iterator last);

		void			swap(vector& x);

		void			clear();

	};
	/* Relational operators */
	template <class T, class Alloc>
	bool		operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool		operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool		operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool		operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool		operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool		operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	/* Swap */
	template <class T, class Alloc>
	void		swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
}

#endif //FT_CONTAINERS_VECTOR_HPP
