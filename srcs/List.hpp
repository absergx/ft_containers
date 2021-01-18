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

//		_t_node*			_begin_node;
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
		 * 1. iterators
		 * 2. modifiers
		 * 		a. push_
		 * 		b. insert
		 * 		c. pop_
		 * 		d. erase
		 * */

	public:
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

	};
}

#endif //FT_CONTAINERS_LIST_HPP
