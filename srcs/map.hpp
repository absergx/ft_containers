//
// Created by Meldred Emilio on 11/29/20.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <iostream>

namespace ft {
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less <Key>,                     // map::key_compare
			class Alloc = std::allocator <std::pair<const Key, T>>    // map::allocator_type
	>
	class map {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		class iterator;
		class const_iterator;
		class reverse_iterator;
		class const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
		protected:
			key_compare		_compare;
			value_compare(key_compare arg) : _compare(arg) {}
		public:
			bool operator()(const_reference lhs, const_reference rhs) const { return _compare(lhs.first, rhs.first); }
		};

	private:
		const static bool black = false;
		const static bool red = true;

		typedef struct		_s_map {
			_s_map*			_left;
			_s_map*			_right;
			_s_map*			_parent;
			bool 			_color;
			pointer			_data;
		}					_t_map;

		typedef typename allocator_type::template rebind<_t_map>::other allocator_rebind_type;

		_t_map*					_root;
		_t_map*					_begin;
		_t_map*					_end;
		allocator_rebind_type	_alloc_rebind;
		allocator_type			_alloc;
		size_type				_size;
		key_compare				_compare;

		void 					_createBeginEnd() {
			_begin = _alloc_rebind.allocate(1);
			_begin->_color = black;
			_begin->_parent = nullptr;
			_begin->_left = nullptr;
			_begin->_right = nullptr;
			_begin->_data = nullptr;

			_end = _alloc_rebind.allocate(1);
			_end->_color = black;
			_end->_parent = nullptr;
			_end->_left = nullptr;
			_end->_right = nullptr;
			_end->_data = nullptr;
		}

		_t_map*					_createNode(_t_map* parent, const_reference val, bool color) {
			_t_map* ret = _alloc_rebind.allocate(1);
			ret->_parent = parent;
			ret->_color = color;
			ret->_data = _alloc.allocate(1);
			_alloc.construct(ret->_data, val);
			ret->_left = nullptr;
			ret->_right = nullptr;
			++_size;
			return ret;
		}

		void 					_destroyNode(_t_map* toDel) {
			_alloc.destroy(toDel->_data);
			_alloc.deallocate(toDel->_data, 1);
			_alloc_rebind.deallocate(toDel, 1);
			--_size;
		}

		void 					_linkLeft(_t_map* parent, _t_map* left) {
			parent->_left = left;
			if (left) {
				left->_left = _begin;
				left->_parent = parent;
			}
		};

		void 					_linkRight(_t_map* parent, _t_map* right) {
			parent->_left = right;
			if (right) {
				right->_right = _end;
				right->_parent = parent;
			}
		};

		bool 					_isRedNode(_t_map* node) {
			if (!node)
				return black;
			return node->_color == red;
		}

		_t_map*					_rotateLeft(_t_map* node) {
			_t_map* tmp = node->_right;

//			if (node->_parent->_right == node)
//				_linkRight(node->_parent, tmp);
//			else
//				_linkLeft(node->_parent, tmp);
//			_linkRight(node, tmp->_left);
//			_linkLeft(tmp, node);

			node->_right = tmp->_left; // todo refactor
			tmp->_left = node; // todo refactor

			tmp->_color = node->_color;
			node->_color = red;
			return tmp;
		}

		_t_map*					_rotateRight(_t_map* node) {
			_t_map* tmp = node->_left;

//			if (node->_parent->_right == node)
//				_linkRight(node->_parent, tmp);
//			else
//				_linkLeft(node->_parent, tmp);
//			_linkRight(node, tmp->_right);
//			_linkLeft(tmp, node);

			node->_left = tmp->_right;
			tmp->_right = node;

			tmp->_color = node->_color;
			node->_color = red;
			return tmp;
		}

		void 					_flipColors(_t_map* node) {
			if (node->_left)
				node->_left->_color = !node->_left->_color;
			if (node->_right)
				node->_right->_color = !node->_right->_color;
			node->_color = !node->_color;
		}

		_t_map*					_balance(_t_map* node) {
			if (_isRedNode(node->_left) && _isRedNode(node->_right))
				_flipColors(node);

			if (_isRedNode(node->_right) && !_isRedNode(node->_left))
				node = _rotateLeft(node);

			if (_isRedNode(node->_left) && _isRedNode(node->_left->_left))
				node = _rotateRight(node);

			return node;
		}

	public:
		/* Constructors */
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type(),
			 typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0);
		map (const map& x);

		/* Destructor */
		~map();

		/* Operator = */
		map&					operator= (const map& x);

		/* Iterators */
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		/* Capacity */
		bool					empty() const { return _size == 0; }
		size_type				size() const { return _size; }
		size_type				max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_t_map); }

		/* Element access */
		mapped_type&			operator[] (const key_type& k);

		/* Modifiers */
		std::pair<iterator,bool>	insert (const value_type& val);
		iterator				insert(iterator position, const value_type& val);
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last,
	   		typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0);
		void					erase(iterator position);
		size_type				erase(const key_type& k);
		void					erase(iterator first, iterator last);
		void					swap(map& x);
		void					clear();

		/* Observers */
		key_compare				key_comp() const;
		value_compare			value_comp() const;

		/* Operations */
		iterator				find(const key_type& k);
		const_iterator			find(const key_type& k) const;
		size_type				count(const key_type& k) const;
		iterator				lower_bound(const key_type& k);
		const_iterator			lower_bound(const key_type& k) const;
		iterator				upper_bound(const key_type& k);
		const_iterator			upper_bound(const key_type& k) const;
		std::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
		std::pair<iterator,iterator>				equal_range (const key_type& k);
	};
}

#endif //FT_CONTAINERS_MAP_HPP
