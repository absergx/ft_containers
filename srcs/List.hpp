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
			_alloc_rebind.deallocate(_target, 1);
			_changeSize(-1);
		}

		_t_node*			_createNode(const_reference val) {
			_t_node *ret = _alloc_rebind.allocate(1);
			ret->_data = _alloc.allocate(1);
			_alloc.construct(ret->_data, val);
			_changeSize(1);
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
			_size += (_difference != -1) ? static_cast<size_type>(_difference) : -1;
		}

		/*
		 * TODO :
		 * 1. iterators
		 * 2. modifiers
		 * 		a. push_
		 * 		b. insert
		 * 		c. pop_
		 * 		d. erase
		 * */

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
			bool 						operator==(const const_iterator& rhs) const { return _pointer == rhs._pointer; }
			bool 						operator!=(const iterator& rhs) const { return _pointer != rhs._pointer; }
			bool 						operator!=(const const_iterator& rhs) const { return _pointer != rhs._pointer; }
			iterator&					operator++() {
				_pointer = _pointer->next;
				return *this;
			}
			iterator&					operator++(int) {
				iterator tmp = *this;
				operator++();
				return tmp;
			}
			iterator&					operator--() {
				_pointer = _pointer->_prev;
				return *this;
			}
			iterator&					operator--(int) {
				iterator tmp = *this;
				operator--();
				return tmp;
			}
			value_type&					operator* () const { return _pointer->_data; }
			value_type*					operator->() const { return _pointer->_data; }
		};

		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
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
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}
			bool 						operator==(const iterator& rhs) const { return _pointer == rhs._pointer; }
			bool 						operator==(const const_iterator& rhs) const { return _pointer == rhs._pointer; }
			bool 						operator!=(const iterator& rhs) const { return _pointer != rhs._pointer; }
			bool 						operator!=(const const_iterator& rhs) const { return _pointer != rhs._pointer; }
			const_iterator&				operator++() {
				_pointer = _pointer->next;
				return *this;
			}
			const_iterator&				operator++(int) {
				iterator tmp = *this;
				operator++();
				return tmp;
			}
			const_iterator&				operator--() {
				_pointer = _pointer->_prev;
				return *this;
			}
			const_iterator&				operator--(int) {
				iterator tmp = *this;
				operator--();
				return tmp;
			}
			value_type const&			operator* () const { return _pointer->_data; }
			value_type const*			operator->() const { return _pointer->_data; }
		};

		class reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
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
			bool						operator==(const const_reverse_iterator& rhs) const { return _pointer == rhs._pointer; }
			bool						operator!=(const const_reverse_iterator& rhs) const { return _pointer != rhs._pointer; }
			reverse_iterator&			operator++() {
				_pointer = _pointer->_prev;
				return *this;
			}
			reverse_iterator&			operator++(int) {
				reverse_iterator tmp = *this;
				operator++();
				return tmp;
			}
			reverse_iterator&			operator--() {
				_pointer = _pointer->_next;
				return *this;
			}
			reverse_iterator&			operator--(int) {
				reverse_iterator tmp = *this;
				operator--();
				return tmp;
			}
			value_type&					operator* () const { return _pointer->_data; }
			value_type*					operator->() const { return _pointer->_data; }
		};

		class const_reverse_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
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
				if (this != &rhs)
					_pointer = rhs._pointer;
				return *this;
			}
			bool 						operator==(const reverse_iterator& rhs) const { return _pointer == rhs._pointer; }
			bool 						operator!=(const reverse_iterator& rhs) const { return _pointer != rhs._pointer; }
			bool						operator==(const const_reverse_iterator& rhs) const { return _pointer == rhs._pointer; }
			bool						operator!=(const const_reverse_iterator& rhs) const { return _pointer != rhs._pointer; }
			const_reverse_iterator&		operator++() {
				_pointer = _pointer->_prev;
				return *this;
			}
			const_reverse_iterator&		operator++(int) {
				reverse_iterator tmp = *this;
				operator++();
				return tmp;
			}
			const_reverse_iterator&		operator--() {
				_pointer = _pointer->_next;
				return *this;
			}
			const_reverse_iterator&		operator--(int) {
				reverse_iterator tmp = *this;
				operator--();
				return tmp;
			}
			value_type const&			operator* () const { return _pointer->_data; }
			value_type const*			operator->() const { return _pointer->_data; }
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

			/* empty container constructor (default constructor)
				Constructs an empty container, with no elements. */
		explicit list(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0) { _createEmptyList(); }
			/* fill constructor
				Constructs a container with n elements. Each element is a copy of val. */
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n) {
			_createEmptyList();
			// pushback n values
		}
			/* range constructor
				Constructs a container with as many elements as the range [first,last),
				with each element constructed from its corresponding element in that range, in the same order. */
		template<class InputIterator>
				list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {}
			/* copy constructor
				Constructs a container with a copy of each of the elements in x, in the same order. */
		list(const list &x) {

		}
			/* destructor */
		~list() {
			// call clear
		}
			/* Copies all the elements from x into the container. */
		list& operator=(const list& x) {}

		/* Modifiers */

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {

		}

		void assign (size_type n, const value_type& val) {

		}

		void			push_front(const value_type& val) {
			_t_node *node = _createNode(val);
			_relinkNodes(node, _end_node->_next);
			_relinkNodes(_end_node, node);
		}

		void			pop_front() {
			_t_node *_tmp = _end_node->_next;
			_relinkNodes(_end_node, _end_node->_next->_next);
			_deleteNode(_tmp);
		}

		void			push_back(const value_type& val) {
			_t_node *node = _createNode(val);
			_relinkNodes(_end_node->_prev, node);
			_relinkNodes(node, _end_node);
		}

		void			pop_back() {
			_t_node *_tmp = _end_node->_prev;
			_relinkNodes(_end_node->_prev->_prev, _end_node);
			_deleteNode(_tmp);
		}

		iterator		insert(iterator position, const value_type& val) {
			_t_node *node = _createNode(val);
			_relinkNodes(position->_prev, node);
			_relinkNodes(node, position->_next);
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
			// TODO think
			++position;
			return position;
		}

		iterator		erase(iterator first, iterator last) {}

		void			swap(list& x) {}

		void			resize(size_type n, value_type val = value_type()) {}

		void			clear() {}



	};
}

#endif //FT_CONTAINERS_LIST_HPP
