//
// Created by Meldred Emilio on 11/29/20.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <memory>
#include <type_traits>
#include <stdexcept>

namespace ft {
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template< class T, class Alloc = std::allocator<T> >
	class list {
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
		typedef struct		_s_node
		{
			struct _s_node*	_next;
			struct _s_node*	_prev;
			value_type*		_data;
		}					_t_node;

		_t_node*			_end_node;

		typedef typename	allocator_type::template rebind<_t_node>::other allocator_rebind;
		allocator_rebind	_alloc_rebind;
		allocator_type		_alloc;
		size_type			_size;

		void				_createEmptyList() {
			_end_node = _alloc_rebind.allocate(1);
			_end_node->_data = _alloc.allocate(1);
			_end_node->_next = _end_node;
			_end_node->_prev = _end_node;
		}

		void 				_deleteNode(_t_node* _target) {
			_alloc.destroy(_target->_data);
			_alloc.deallocate(_target->_data, 1);
			_alloc_rebind.deallocate(_target, 1);
			_changeSize(-1);
		}

		_t_node*			_createNode(const_reference val) {
			_t_node *ret = _alloc_rebind.allocate(1);
			ret->_data = _alloc.allocate(1);
			_alloc.construct(ret->_data, val);
			_changeSize(1);
			return ret;
		}

		void 				_insertNode(_t_node* _target, _t_node* _prev, _t_node* _next) {
			_relinkNodes(_prev, _target);
			_relinkNodes(_target, _next);
		}

		void 				_relinkNodes(_t_node* _prev, _t_node* _next) {
			_prev->_next = _next;
			_next->_prev = _prev;
		}

		void 				_changeSize(int _difference) {
			if (_difference == -1)
				_size--;
			else
				_size += static_cast<size_type>(_difference);
		}

//		struct				_equal {
//			bool			operator() (value_type const& lhs, value_type const& rhs) {
//				return lhs == rhs;
//			}
//		};
		inline static bool 	_equal(const value_type &lhs, const value_type &rhs) { return lhs == rhs; }
		inline static bool 	_less(const value_type &lhs, const value_type &rhs) { return lhs < rhs; }
//		struct				_less {
//			bool			operator() (value_type const& lhs, value_type const& rhs) {
//				return lhs < rhs;
//			}
//		};

	public:

		/* Iterators */

		class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
		private:
			_t_node*	_pointer;
		public:
			iterator() : _pointer(nullptr) {}
			iterator(_t_node *pointer) : _pointer(pointer) {}
			iterator(iterator const &iterator) { *this = iterator; }
			~iterator() {}
			iterator&					operator= (const iterator& rhs) {
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}
			bool 						operator==(const iterator& rhs) const { return _pointer == rhs._pointer; }
			bool 						operator==(const const_iterator& rhs) const { return _pointer == rhs.getPointer(); }
			bool 						operator!=(const iterator& rhs) const { return _pointer != rhs._pointer; }
			bool 						operator!=(const const_iterator& rhs) const { return _pointer != rhs._pointer; }
			iterator&					operator++() {
				_pointer = _pointer->_next;
				return *this;
			}
			iterator					operator++(int) {
				iterator tmp = *this;
				operator++();
				return tmp;
			}
			iterator&					operator--() {
				_pointer = _pointer->_prev;
				return *this;
			}
			iterator					operator--(int) {
				iterator tmp = *this;
				operator--();
				return tmp;
			}
			value_type&					operator* () const { return *_pointer->_data; }
			value_type*					operator->() const { return _pointer->_data; }

			_t_node*					getPointer() const { return _pointer; }
		};

		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T> {
		private:
			_t_node*	_pointer;
		public:
			const_iterator() : _pointer(nullptr) {}
			const_iterator(_t_node *pointer) : _pointer(pointer) {}
			const_iterator(iterator const &it) { *this = it; }
			const_iterator(const_iterator const &it) { *this = it; }
			~const_iterator() {}
			const_iterator&				operator= (const const_iterator& rhs) {
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}
			const_iterator&				operator= (const iterator& rhs) {
				_pointer = rhs.getPointer();
				return *this;
			}
			bool 						operator==(const iterator& rhs) const { return _pointer == rhs.getPointer(); }
			bool 						operator==(const const_iterator& rhs) const { return _pointer == rhs._pointer; }
			bool 						operator!=(const iterator& rhs) const { return _pointer != rhs.getPointer(); }
			bool 						operator!=(const const_iterator& rhs) const { return _pointer != rhs._pointer; }
			const_iterator&				operator++() {
				_pointer = _pointer->_next;
				return *this;
			}
			const_iterator				operator++(int) {
				const_iterator tmp(_pointer);
				operator++();
				return tmp;
			}
			const_iterator&				operator--() {
				_pointer = _pointer->_prev;
				return *this;
			}
			const_iterator				operator--(int) {
				const_iterator tmp = *this;
				operator--();
				return tmp;
			}
			value_type &			operator* () const { return *_pointer->_data; }
			value_type *			operator->() const { return _pointer->_data; }
			_t_node*				getPointer() const { return _pointer; }
		};

		class reverse_iterator : public std::reverse_iterator<iterator> {
		private:
			_t_node*	_pointer;
		public:
			reverse_iterator() : _pointer(nullptr) {}
			reverse_iterator(_t_node *pointer) : _pointer(pointer) {}
			reverse_iterator(reverse_iterator const &it) { *this = it; }
			~reverse_iterator() {}
			reverse_iterator&			operator= (const reverse_iterator &rhs) {
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}
			bool 						operator==(const reverse_iterator& rhs) const { return _pointer == rhs._pointer; }
			bool 						operator!=(const reverse_iterator& rhs) const { return _pointer != rhs._pointer; }
			bool						operator==(const const_reverse_iterator& rhs) const { return _pointer == rhs.getPointer(); }
			bool						operator!=(const const_reverse_iterator& rhs) const { return _pointer != rhs.getPointer(); }
			reverse_iterator&			operator++() {
				_pointer = _pointer->_prev;
				return *this;
			}
			reverse_iterator			operator++(int) {
				reverse_iterator tmp = *this;
				operator++();
				return tmp;
			}
			reverse_iterator&			operator--() {
				_pointer = _pointer->_next;
				return *this;
			}
			reverse_iterator			operator--(int) {
				reverse_iterator tmp = *this;
				operator--();
				return tmp;
			}
			value_type&					operator* () const { return *_pointer->_data; }
			value_type*					operator->() const { return _pointer->_data; }
			_t_node*					getPointer() const { return _pointer; }
		};

		class const_reverse_iterator : public std::reverse_iterator<const_iterator> {
		private:
			_t_node*	_pointer;
		public:
			const_reverse_iterator() : _pointer(nullptr) {}
			const_reverse_iterator(_t_node *pointer) : _pointer(pointer) {}
			const_reverse_iterator(reverse_iterator const &it) { *this = it; }
			const_reverse_iterator(const_reverse_iterator const &it) { *this = it; }
			~const_reverse_iterator() {}
			const_reverse_iterator&		operator= (const const_reverse_iterator &rhs) {
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}
			const_reverse_iterator&		operator= (const reverse_iterator &rhs) {
				_pointer = rhs.getPointer();
				return *this;
			}
			bool 						operator==(const reverse_iterator& rhs) const { return _pointer == rhs.getPointer(); }
			bool 						operator!=(const reverse_iterator& rhs) const { return _pointer != rhs.getPointer(); }
			bool						operator==(const const_reverse_iterator& rhs) const { return _pointer == rhs._pointer; }
			bool						operator!=(const const_reverse_iterator& rhs) const { return _pointer != rhs._pointer; }
			const_reverse_iterator&		operator++() {
				_pointer = _pointer->_prev;
				return *this;
			}
			const_reverse_iterator		operator++(int) {
				const_reverse_iterator tmp = *this;
				operator++();
				return tmp;
			}
			const_reverse_iterator&		operator--() {
				_pointer = _pointer->_next;
				return *this;
			}
			const_reverse_iterator		operator--(int) {
				const_reverse_iterator tmp = *this;
				operator--();
				return tmp;
			}
			value_type const&			operator* () const { return *_pointer->_data; }
			value_type const*			operator->() const { return _pointer->_data; }
			_t_node*					getPointer() const { return _pointer; }
		};

		iterator						begin() { return iterator(_end_node->_next); }
		iterator						end() { return iterator(_end_node); }
		const_iterator					begin() const { return const_iterator(_end_node->_next); }
		const_iterator					end() const { return const_iterator(_end_node); }
		reverse_iterator				rbegin() { return reverse_iterator(_end_node->_prev); }
		reverse_iterator				rend() { return reverse_iterator(_end_node); }
		const_reverse_iterator			rbegin() const { return const_reverse_iterator(_end_node->_prev); }
		const_reverse_iterator			rend() const { return const_reverse_iterator(_end_node); }

		/* Constructors and destructor */

		explicit list(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0) { _createEmptyList(); }
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0) {
			_createEmptyList();
			for (; n > 0; n--)
				push_back(val);
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) : _alloc(alloc), _size(0) {
			_createEmptyList();
			for ( ; first != last; first++)
				push_back(*first);
		}
		list(const list &x) : _alloc(x._alloc), _size(0) {
			_createEmptyList();
			*this = x;
		}
		~list() {
			clear();
			_alloc.destroy(_end_node->_data);
			_alloc_rebind.deallocate(_end_node, 1);
		}
		list& operator=(const list& x) {
			if (this == &x)
				return *this;
			clear();
			const_iterator itEnd = x.end();
			for (const_iterator itBegin = x.begin(); itBegin != itEnd; itBegin++)
				push_back(*itBegin);
			return *this;
		}

		/* Modifiers */

		template <class InputIterator>
		void			assign(InputIterator first, InputIterator last,
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			clear();
			for (; first != last; first++)
				push_back(*first);
		}

		void			assign(size_type n, const value_type& val) {
			clear();
			for (; n > 0; n--)
				push_back(val);
		}

		void			push_front(const value_type& val) {
			_t_node *node = _createNode(val);
			_insertNode(node, _end_node, _end_node->_next);
		}

		void			pop_front() {
			_t_node *_tmp = _end_node->_next;
			_relinkNodes(_end_node, _end_node->_next->_next);
			_deleteNode(_tmp);
		}

		void			push_back(const value_type& val) {
			_t_node *node = _createNode(val);
			_insertNode(node, _end_node->_prev,_end_node);
		}

		void			pop_back() {
			_t_node *_tmp = _end_node->_prev;
			_relinkNodes(_end_node->_prev->_prev, _end_node);
			_deleteNode(_tmp);
		}

		iterator		insert(iterator position, const value_type& val) {
			_t_node *node = _createNode(val);
			_insertNode(node, position.getPointer()->_prev, position.getPointer());
			return iterator(node);
		}

		void			insert(iterator position, size_type n, const value_type& val) {
			for (size_type i = 0; i < n; i++)
				insert(position, val);
		}

		template <class InputIterator>
		void			insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			for ( ; first != last; first++)
				insert(position, *first);
		}

		iterator		erase(iterator position) {
			_t_node *toDel = position.getPointer();
			if (toDel == _end_node)
				return position;
			_t_node *ret = toDel->_next;
			_relinkNodes(toDel->_prev, toDel->_next);
			_deleteNode(toDel);
			return iterator(ret);
		}

		iterator		erase(iterator first, iterator last) {
			while (first != last)
				first = erase(first);
			return first;
		}

		void			swap(list& x) {
			_t_node		*tmpNode = _end_node;
			size_type	tmpSize = _size;
			_end_node = x._end_node;
			x._end_node = tmpNode;
			_size = x._size;
			x._size = tmpSize;
		}

		void			resize(size_type n, value_type val = value_type()) {
			while (_size != n) {
				if (_size < n)
					push_back(val);
				else
					erase(iterator(_end_node->_prev));
			}
		}

		void			clear() {
			while (_size != 0) {
				_t_node *tmp = _end_node->_prev;
				_relinkNodes(tmp->_prev, _end_node);
				_deleteNode(tmp);
			}
			_end_node->_next = _end_node;
			_end_node->_prev = _end_node;
		}

		/* Capacity */

		bool			empty() const { return _size == 0; }
		size_type		size() const { return _size; }
		size_type		max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_t_node) / ((sizeof(value_type) == 1) ? 2 : 1); }

		/* Element access */

		reference		front() { return *_end_node->_next->_data; }
		const_reference	front() const { return _end_node->_next->_data; }
		reference		back() { return *_end_node->_prev->_data; }
		const_reference	back() const { return _end_node->_prev->_data; }

		/* Operations */

		void			splice(iterator position, list& x) {
			_t_node *tmp = position.getPointer()->_prev;
			_relinkNodes(tmp, x._end_node->_next);
			_relinkNodes(x._end_node->_prev, position.getPointer());
			_relinkNodes(x._end_node, x._end_node);
			_size += x._size;
			x._size = 0;
		}
		void			splice(iterator position, list& x, iterator i) {
			_t_node *target = i.getPointer();
			_relinkNodes(target->_prev, target->_next);
			_insertNode(target, position.getPointer()->_prev, position.getPointer());
			_changeSize(+1);
			x._size -= 1;
		}
		void			splice(iterator position, list& x, iterator first, iterator last) {
			iterator tmp;
			for (; first != last;) {
				tmp = first++;
				splice(position, x, tmp);
			}
		}

		void			remove(const value_type& val) {
			iterator	_itStart = begin();
			iterator	_itEnd = end();

			while (_itStart != _itEnd) {
				if (*_itStart == val)
					_itStart = erase(_itStart);
				else
					_itStart++;
			}
		}

		template <class Predicate>
		void			remove_if(Predicate pred) {
			iterator	_itStart = begin();
			iterator	_itEnd = end();

			while (_itStart != _itEnd) {
				if (pred(*_itStart))
					_itStart = erase(_itStart);
				else
					_itStart++;
			}
		}

		void			unique() { unique(_equal); }
		template <class BinaryPredicate>
		void			unique(BinaryPredicate binary_pred) {
			iterator	first = begin();
			iterator	second = ++begin();
			iterator	last = end();

			while (second != last) {
				if (binary_pred(*first, *second)) {
					second = erase(second);
				} else {
					++first;
					++second;
				}
			}
		}

		void			merge(list& x) { merge(x, _less); }
		template <class Compare>
		void			merge(list& x, Compare comp) {
			if (this == &x)
				return;
			iterator	currentFirst = begin();
			iterator	currentLast = end();
			iterator	xFirst = x.begin();
			iterator	xLast = x.end();

			for (; xFirst != xLast; xFirst++) {
				for (; currentFirst != currentLast; currentFirst++) {
					if (comp(*xFirst, *currentFirst))
						break;
				}
				splice(currentFirst, x, xFirst);
			}
		}

		void			sort() { sort(_less); }
		template <class Compare>
		void			sort(Compare comp) {
			iterator	first;
			iterator	second;
			iterator	itend = end();
			while (itend != ++begin()) {
				first = begin();
				second = ++begin();
				while (second != itend) {
					if (!comp(*first, *second)) {
//						value_type tmp = *first;
//						*first = *second;
//						*second = tmp;
						_t_node *firstNode = first.getPointer();
						_t_node *secondNode = second.getPointer();
						_t_node *changeBuffer = firstNode->_prev;
						firstNode->_prev = secondNode;
						firstNode->_next = secondNode->_next;
						firstNode->_next->_prev = firstNode;
						secondNode->_prev = changeBuffer;
						secondNode->_next = firstNode;
						secondNode->_prev->_next = secondNode;
						iterator tmp = first;
						first = second;
						second = tmp;
					}
					++first;
					++second;
				}
				itend = first;
			}
		}

		void			reverse() {
			_t_node *start = _end_node->_next;
			for (size_type i = 0; i < _size; ++i) {
				_t_node *tmp = start->_prev;
				_t_node *next = start->_next;
				start->_prev = start->_next;
				start->_next = tmp;
				start = next;
			}
		}

	};

	/* Non-member function overloads */

	template <class T, class Alloc>
	bool	operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		typename ft::list<T, Alloc>::const_iterator	leftIt = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator leftItEnd = lhs.end();
		typename ft::list<T, Alloc>::const_iterator	rightIt = rhs.begin();
		typename ft::list<T, Alloc>::const_iterator rightItEnd = rhs.end();
		for (; leftIt != leftItEnd; leftIt++) {
			if (rightIt == rightItEnd || *leftIt != *rightIt)
				return false;
			rightIt++;
		}
		return true;
	}
	template <class T, class Alloc>
	bool	operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return !(lhs == rhs); }
	template <class T, class Alloc>
	bool	operator< (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		if (lhs.size() < rhs.size())
			return true;
		typename ft::list<T, Alloc>::const_iterator	leftIt = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator leftItEnd = lhs.end();
		typename ft::list<T, Alloc>::const_iterator	rightIt = rhs.begin();
		typename ft::list<T, Alloc>::const_iterator rightItEnd = rhs.end();
		for (; leftIt != leftItEnd; leftIt++) {
			if (rightIt == rightItEnd)
				return false;
			if (*leftIt < *rightIt)
				return true;
			rightIt++;
		}
		return false;
	}
	template <class T, class Alloc>
	bool	operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return !(rhs < lhs); }
	template <class T, class Alloc>
	bool	operator> (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return rhs < lhs; }
	template <class T, class Alloc>
	bool	operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return !(lhs < rhs); }

	template <class T, class Alloc>
	void	swap(list<T,Alloc>& x, list<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif //FT_CONTAINERS_LIST_HPP
