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

	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
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
		public:
			key_compare		_compare;
			explicit value_compare(key_compare arg) : _compare(arg) {}
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
			ret->_left = nullptr;
			ret->_right = nullptr;
			ret->_color = color;
			ret->_data = _alloc.allocate(1);
			_alloc.construct(ret->_data, val);
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
			if (left)
				left->_parent = parent;
		};

		void 					_linkRight(_t_map* parent, _t_map* right) {
			parent->_right = right;
			if (right)
				right->_parent = parent;
		};

		bool 					_isRedNode(_t_map* node) {
			if (!node)
				return black;
			return node->_color == red;
		}

		_t_map*					_rotateLeft(_t_map* node) {
			_t_map* tmp = node->_right;

			tmp->_parent = nullptr;
			if (node->_parent) {
				if (node->_parent->_left == node)
					_linkLeft(node->_parent, tmp);
				else
					_linkRight(node->_parent, tmp);
			} else
				tmp->_parent = node->_parent;

			_linkRight(node, tmp->_left);
			_linkLeft(tmp, node);
			if (node == _root)
				_root = tmp;

			tmp->_color = node->_color;
			node->_color = red;
			return tmp;
		}

		_t_map*					_rotateRight(_t_map* node) {
			_t_map* tmp = node->_left;

			tmp->_parent = nullptr;
			if (node->_parent) {
				if (node->_parent->_left == node)
					_linkLeft(node->_parent, tmp);
				else
					_linkRight(node->_parent, tmp);
			} else
				tmp->_parent = node->_parent;

			_linkLeft(node, tmp->_right);
			_linkRight(tmp, node);
			if (node == _root)
				_root = tmp;

			tmp->_color = node->_color;
			node->_color = red;
			return tmp;
		}

		void 						_flipColors(_t_map* node) {
			if (node->_left && node->_left != _begin)
				node->_left->_color = !node->_left->_color;
			if (node->_right && node->_right != _end)
				node->_right->_color = !node->_right->_color;
			if (node && node != _root)
				node->_color = !node->_color;
		}

		_t_map*						_balance(_t_map* node) {
			if (_isRedNode(node->_right))
				node = _rotateLeft(node);
			if (_isRedNode(node->_left) && _isRedNode(node->_left->_left))
				node = _rotateRight(node);
			if (_isRedNode(node->_left) && _isRedNode(node->_right))
				_flipColors(node);
			return node;
		}

		inline void 				_insertLeft(_t_map* toInsert, _t_map* parent) {
			if (parent->_left == _begin) {
				toInsert->_left = _begin;
				_begin->_parent = toInsert;
			}
			parent->_left = toInsert;
		}

		inline void 				_insertRight(_t_map* toInsert, _t_map* parent) {
			if (parent->_right == _end)
				_linkRight(toInsert, _end);
			parent->_right = toInsert;
		}

		std::pair<iterator, bool>	_insertNode(_t_map* node, const_reference val) {
			int comp = _compare(val.first, node->_data->first) + _compare(node->_data->first, val.first) * 2;
			if (comp == 0)
				return std::make_pair(iterator(node), false);
			else if (comp == 1 && node->_left && node->_left != _begin)
				return _insertNode(node->_left, val);
			else if (comp == 2 && node->_right && node->_right != _end)
				return _insertNode(node->_right, val);

			_t_map* newNode = _createNode(node, val, red);
			(comp == 1) ? _insertLeft(newNode, node) : _insertRight(newNode, node);
			_balance(node);
			return std::make_pair(iterator(newNode), true);
		}

		/* ERASE SHIT */
		_t_map*						_findMinNode(_t_map* node) {
			if (node->_left)
				return _findMinNode(node->_left);
			return node;
		}

		_t_map*					_moveRedLeft(_t_map* node) {
			_flipColors(node);
			if (node->_right && _isRedNode(node->_right->_left)) {
				node->_right = _rotateRight(node->_right);
				node = _rotateLeft(node);
				_flipColors(node);
			}
			return node;
		}

		_t_map*					_moveRedRight(_t_map* node) {
			_flipColors(node);
			if (node->_left && _isRedNode(node->_left->_left)) {
				node = _rotateRight(node);
				_flipColors(node);
			}
			return node;
		}

		_t_map*					_eraseNode(_t_map* nodeToErase, const key_type& k) {
			if (!nodeToErase)
				return nodeToErase;
			int cmp = _compare(k, nodeToErase->_data->first) + _compare(nodeToErase->_data->first, k) * 2;
			if (cmp == 1) {
				if (!_isRedNode(nodeToErase->_left) && !_isRedNode(nodeToErase->_left->_left)) {
					nodeToErase = _moveRedLeft(nodeToErase);
				}
				_linkLeft(nodeToErase, _eraseNode(nodeToErase->_left, k));
			} else {
				if (_isRedNode(nodeToErase->_left)) {
					nodeToErase = _rotateRight(nodeToErase);
					_linkRight(nodeToErase, _eraseNode(nodeToErase->_right, k));
					return _balance(nodeToErase);
				}
				if (cmp != 2 && (nodeToErase->_right == _end || nodeToErase->_right == nullptr)) {
					_t_map *tmp = (!nodeToErase->_left && nodeToErase->_right == _end) ? nodeToErase->_right : nodeToErase->_left;
					_destroyNode(nodeToErase);
					return tmp;
				}
				if (!_isRedNode(nodeToErase->_right) && nodeToErase->_right && !_isRedNode(nodeToErase->_right->_left)) {
					nodeToErase = _moveRedRight(nodeToErase);
				}
				if (!_compare(nodeToErase->_data->first, k)) {
					_t_map *min = _findMinNode(nodeToErase->_right);
					if (nodeToErase == _root)
						_root = min;
					if (min->_parent != nodeToErase) {
						_linkLeft(min->_parent, min->_right);
						_linkRight(min, nodeToErase->_right);
					}
					if (nodeToErase->_left == _begin) {
						nodeToErase->_left->_parent = min;
						min->_left = nodeToErase->_left;
					} else
						_linkLeft(min, nodeToErase->_left);
					min->_parent = nullptr;
					if (nodeToErase->_parent) {
						if (nodeToErase->_parent->_left == nodeToErase)
							_linkLeft(nodeToErase->_parent, min);
						else
							_linkRight(nodeToErase->_parent, min);
					}
					_destroyNode(nodeToErase);
					nodeToErase = min;
				} else
					_linkRight(nodeToErase, _eraseNode(nodeToErase->_right, k));
			}
			return _balance(nodeToErase);
		}

	public:
		/* Constructors */
		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : _root(nullptr), _alloc(alloc), _size(0), _compare(comp) { _createBeginEnd(); }
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type(),
			 typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) : _root(nullptr), _alloc(alloc), _size(0), _compare(comp) {
			_createBeginEnd();
			insert(first, last);
		}
		map (const map& x) : _root(nullptr), _alloc_rebind(x._alloc_rebind), _alloc(x._alloc), _size(0), _compare(x._compare) {
			_createBeginEnd();
			*this = x;
		}

		/* Destructor */
		~map() {
//			clear();
			_alloc_rebind.deallocate(_begin, 1);
			_alloc_rebind.deallocate(_end, 1);
		}

		/* Operator = */
		map&					operator= (const map& x) {
			clear();
			insert(x.begin(), x.end());
			return *this;
		}

		/* Iterators */
		class iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
		private:
			_t_map*			_ptr;
		public:
			explicit iterator(_t_map* it = nullptr): _ptr(it) {}
			iterator(const iterator &it) : _ptr(it._ptr) {}
			~iterator() {}
			iterator&				operator= (const iterator &it) {
				_ptr = it._ptr;
				return *this;
			}
			bool 					operator==(const iterator &it) const { return _ptr == it._ptr; }
			bool 					operator!=(const iterator &it) const { return _ptr != it._ptr; }
			bool 					operator==(const const_iterator &it) const { return _ptr == it.getPointer(); }
			bool 					operator!=(const const_iterator &it) const { return _ptr != it.getPointer(); }
			iterator&				operator++() {
				_ptr = _nextNode(_ptr);
				return *this;
			}
			iterator&				operator--() {
				_ptr = _prevNode(_ptr);
				return *this;
			}
			iterator				operator++(int) {
				iterator tmp(_ptr);
				operator++();
				return tmp;
			}
			iterator				operator--(int) {
				iterator tmp(_ptr);
				operator--();
				return tmp;
			}
			reference				operator* () const { return *(_ptr->_data); }
			pointer 				operator->() const { return _ptr->_data; }
			_t_map*					getPointer() const { return _ptr; }
		private:
			_t_map*					_findLower(_t_map* node) {
				if (node->_left)
					return _findLower(node->_left);
				return node;
			}
			_t_map*					_findHigher(_t_map* node) {
				if (node->_right)
					return _findHigher(node->_right);
				return node;
			}
			_t_map*					_nextNode(_t_map* node) {
				if (node->_right)
					return _findLower(node->_right);
				else if (node->_parent && node->_parent->_left == node)
					return node->_parent;
				else if (node->_parent->_right == node)
					node = node->_parent;
				_t_map* tmp = node;
				while (tmp->_parent->_right == tmp)
					if (!(tmp = tmp->_parent))
						return node->_right;
				return tmp->_parent;
			}
			_t_map*					_prevNode(_t_map* node) {
				if (node->_left)
					return _findHigher(node->_left);
				else if (node->_parent && node->_parent->_right == node)
					return node->_parent;
				_t_map* tmp = node;
				while (tmp->_parent->_left == tmp)
					if (!(tmp = tmp->_parent))
						return node->_left;
				return tmp->_parent;
			}
		};
		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
		private:
			_t_map*		_ptr;
		public:
			explicit const_iterator(_t_map* it = nullptr): _ptr(it) {}
			const_iterator(const const_iterator &it) : _ptr(it._ptr) {}
			const_iterator(const iterator &it) : _ptr(it.getPointer()) {}
			~const_iterator() {}
			const_iterator&			operator= (const const_iterator &it) {
				_ptr = it._ptr;
				return *this;
			}
			const_iterator&			operator= (const iterator &it) {
				_ptr = it.getPointer();
				return *this;
			}
			bool 					operator==(const iterator &it) const { return _ptr == it.getPointer(); }
			bool 					operator!=(const iterator &it) const { return _ptr != it.getPointer(); }
			bool 					operator==(const const_iterator &it) const { return _ptr == it._ptr; }
			bool 					operator!=(const const_iterator &it) const { return _ptr != it._ptr; }
			const_iterator&			operator++() {
				_ptr = _nextNode(_ptr);
				return *this;
			}
			const_iterator&			operator--() {
				_ptr = _prevNode(_ptr);
				return *this;
			}
			const_iterator			operator++(int) {
				const_iterator tmp(_ptr);
				operator++();
				return tmp;
			}
			const_iterator			operator--(int) {
				const_iterator tmp(_ptr);
				operator--();
				return tmp;
			}
			const_reference			operator* () const { return *(_ptr->_data); }
			const_pointer			operator->() const { return _ptr->_data; }
			_t_map*					getPointer() const { return _ptr; }
		private:
			_t_map*					_findLower(_t_map* node) {
				if (node->_left)
					return _findLower(node->_left);
				return node;
			}
			_t_map*					_findHigher(_t_map* node) {
				if (node->_right)
					return _findHigher(node->_right);
				return node;
			}
			_t_map*					_nextNode(_t_map* node) {
				if (node->_right)
					return _findLower(node->_right);
				else if (node->_parent && node->_parent->_left == node)
					return node->_parent;
				else if (node->_parent->_right == node)
					node = node->_parent;
				_t_map* tmp = node;
				while (tmp->_parent->_right == tmp)
					if (!(tmp = tmp->_parent))
						return node->_right;
				return tmp->_parent;
			}
			_t_map*					_prevNode(_t_map* node) {
				if (node->_left)
					return _findHigher(node->_left);
				else if (node->_parent && node->_parent->_right == node)
					return node->_parent;
				_t_map* tmp = node;
				while (tmp->_parent->_left == tmp)
					if (!(tmp = tmp->_parent))
						return node->_left;
				return tmp->_parent;
			}
		};
		class reverse_iterator : public std::reverse_iterator<iterator> {
		private:
			_t_map*					_ptr;
		public:
			explicit reverse_iterator(_t_map* ptr = nullptr) : _ptr(ptr) {}
			reverse_iterator(const reverse_iterator &it) : _ptr(it._ptr) {}
			~reverse_iterator() {}
			reverse_iterator&		operator= (const reverse_iterator &it) {
				_ptr = it._ptr;
				return *this;
			}
			bool 					operator==(const reverse_iterator &it) { return _ptr == it._ptr; }
			bool 					operator!=(const reverse_iterator &it) { return _ptr != it._ptr; }
			bool 					operator==(const const_reverse_iterator &it) { return _ptr == it.getPointer(); }
			bool 					operator!=(const const_reverse_iterator &it) { return _ptr != it.getPointer(); }
			reverse_iterator&		operator++() {
				_ptr = _prevNode(_ptr);
				return *this;
			}
			reverse_iterator&		operator--() {
				_ptr = _nextNode(_ptr);
				return *this;
			}
			reverse_iterator		operator++(int) {
				reverse_iterator tmp(_ptr);
				operator++();
				return tmp;
			}
			reverse_iterator		operator--(int) {
				reverse_iterator tmp(_ptr);
				operator--();
				return tmp;
			}
			reference				operator* () const { return *(_ptr->_data); }
			pointer					operator->() const { return _ptr->_data; }
			_t_map*					getPointer() const { return _ptr; }
		private:
			_t_map*					_findLower(_t_map* node) {
				if (node->_left)
					return _findLower(node->_left);
				return node;
			}
			_t_map*					_findHigher(_t_map* node) {
				if (node->_right)
					return _findHigher(node->_right);
				return node;
			}
			_t_map*					_nextNode(_t_map* node) {
				if (node->_right)
					return _findLower(node->_right);
				else if (node->_parent && node->_parent->_left == node)
					return node->_parent;
				else if (node->_parent->_right == node)
					node = node->_parent;
				_t_map* tmp = node;
				while (tmp->_parent->_right == tmp)
					if (!(tmp = tmp->_parent))
						return node->_right;
				return tmp->_parent;
			}
			_t_map*					_prevNode(_t_map* node) {
				if (node->_left)
					return _findHigher(node->_left);
				else if (node->_parent && node->_parent->_right == node)
					return node->_parent;
				_t_map* tmp = node;
				while (tmp->_parent->_left == tmp)
					if (!(tmp = tmp->_parent))
						return node->_left;
				return tmp->_parent;
			}
		};
		class const_reverse_iterator : public std::reverse_iterator<iterator> {
		private:
			_t_map*					_ptr;
		public:
			explicit const_reverse_iterator(_t_map* it = nullptr) : _ptr(it) {}
			const_reverse_iterator(const const_reverse_iterator &it) : _ptr(it._ptr) {}
			const_reverse_iterator(const reverse_iterator &it) : _ptr(it.getPointer()) {}
			~const_reverse_iterator() {}
			const_reverse_iterator&	operator= (const const_reverse_iterator &it) {
				_ptr = it._ptr;
				return *this;
			}
			const_reverse_iterator& operator= (const reverse_iterator &it) {
				_ptr = it.getPointer();
				return *this;
			}
			bool 					operator==(const reverse_iterator &it) { return _ptr == it.getPointer(); }
			bool 					operator!=(const reverse_iterator &it) { return _ptr != it.getPointer(); }
			bool 					operator==(const const_reverse_iterator &it) { return _ptr == it._ptr; }
			bool 					operator!=(const const_reverse_iterator &it) { return _ptr != it._ptr; }
			const_reverse_iterator&	operator++() {
				_ptr = _prevNode(_ptr);
				return *this;
			}
			const_reverse_iterator&	operator--() {
				_ptr = _nextNode(_ptr);
				return *this;
			}
			const_reverse_iterator	operator++(int) {
				const_reverse_iterator tmp(_ptr);
				operator++();
				return tmp;
			}
			const_reverse_iterator	operator--(int) {
				const_reverse_iterator tmp(_ptr);
				operator--();
				return tmp;
			}
			const_reference			operator* () const { return *(_ptr->_data); }
			const_pointer			operator->() const { return _ptr->_data; }
			_t_map*					getPointer() const { return _ptr; }
		private:
			_t_map*					_findLower(_t_map* node) {
				if (node->_left)
					return _findLower(node->_left);
				return node;
			}
			_t_map*					_findHigher(_t_map* node) {
				if (node->_right)
					return _findHigher(node->_right);
				return node;
			}
			_t_map*					_nextNode(_t_map* node) {
				if (node->_right)
					return _findLower(node->_right);
				else if (node->_parent && node->_parent->_left == node)
					return node->_parent;
				else if (node->_parent->_right == node)
					node = node->_parent;
				_t_map* tmp = node;
				while (tmp->_parent->_right == tmp) {
					tmp = tmp->_parent;
					if (!tmp)
						return node->_right;
				}
				return tmp->_parent;
			}
			_t_map*					_prevNode(_t_map* node) {
				if (node->_left)
					return _findHigher(node->_left);
				else if (node->_parent && node->_parent->_right == node)
					return node->_parent;
				_t_map* tmp = node;
				while (tmp->_parent->_left == tmp) {
					tmp = tmp->_parent;
					if (!tmp)
						return node->_left;
				}
				return tmp->_parent;
			}
		};
		iterator				begin() { return (!_size) ? iterator(_end) : iterator(_begin->_parent); }
		const_iterator			begin() const { return (!_size) ? const_iterator(_end) : const_iterator(_begin->_parent); }
		iterator				end() { return iterator(_end); }
		const_iterator			end() const { return const_iterator(_end); }
		reverse_iterator		rbegin() { return (!_size) ? reverse_iterator(_begin) : reverse_iterator(_end->_parent); }
		const_reverse_iterator	rbegin() const { return (!_size) ? const_reverse_iterator(_begin) : const_reverse_iterator(_end->_parent); }
		reverse_iterator		rend() { return reverse_iterator(_begin); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(_begin); }

		/* Capacity */
		bool					empty() const { return _size == 0; }
		size_type				size() const { return _size; }
		size_type				max_size() const { return std::numeric_limits<size_type>::max() / sizeof(_t_map); }

		/* Element access */
		mapped_type&			operator[] (const key_type& k) { return insert(std::make_pair(k, mapped_type())).first->second; }

		/* Modifiers */
		std::pair<iterator,bool>	insert (const value_type& val) {
			if (!_size) {
				_root = _createNode(nullptr, val, black);
				_linkRight(_root, _end);
				_linkLeft(_root, _begin);
				return std::make_pair(iterator(_root), true);
			}
			return _insertNode(_root, val);
		}
		iterator				insert(iterator position, const value_type& val) {
			static_cast<void>(position);
			return insert(val).first;
		}
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last,
	   		typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
			for ( ; first != last; ++first)
				insert(*first);
		}
		void					erase(iterator position) {
			(void)position;
			//todo DO IT
		}
		size_type				erase(const key_type& k) {
			(void)k;
			//todo DO IT
			return 0;
		}
		void					erase(iterator first, iterator last) {
			(void)first;
			(void)last;
			//todo DO IT
		}
		void					swap(map& x) {
			_t_map* tmpRoot = _root;
			_root = x._root;
			x._root = tmpRoot;

			_t_map* tmpBegin = _begin;
			_begin = x._begin;
			x._begin = tmpBegin;

			_t_map*	tmpEnd = _end;
			_end = x._end;
			x._end = tmpEnd;

			size_type tmpSize = _size;
			_size = x._size;
			x._size = tmpSize;
		}
		void					clear() {
			while (_size)
				erase(begin());
		}

		/* Observers */
		key_compare				key_comp() const { return _compare; }
		value_compare			value_comp() const { return value_compare(_compare); }

		/* Operations */
		iterator				find(const key_type& k) {
			for (iterator it = begin(); it != end(); ++it)
				if (it->first == k)
					return it;
			return end();
		}
		const_iterator			find(const key_type& k) const {
			for (const_iterator it = begin(); it != end(); ++it)
				if (it->first == k)
					return it;
			return end();
		}
		size_type				count(const key_type& k) const {
			for (const_iterator it = begin(); it != end(); ++it)
				if (it->first == k)
					return 1;
			return 0;
		}
		iterator				lower_bound(const key_type& k) {
			iterator it = begin();
			iterator itEnd = end();
			while (it != itEnd && _compare(it->first, k))
				++it;
			return it;
		}
		const_iterator			lower_bound(const key_type& k) const {
			const_iterator it = begin();
			const_iterator itEnd = end();
			while (it != itEnd && _compare(it->first, k))
				++it;
			return it;
		}
		iterator				upper_bound(const key_type& k) {
			iterator it = lower_bound(k);
			if (it != end() && !_compare(it->first, k) && !_compare(k, it->first))
				++it;
			return it;
		}
		const_iterator			upper_bound(const key_type& k) const {
			const_iterator it = lower_bound(k);
			if (it != end() && !_compare(it->first, k) && !_compare(k, it->first))
				++it;
			return it;
		}
		std::pair<const_iterator,const_iterator>	equal_range (const key_type& k) const {
			return std::make_pair(lower_bound(k), upper_bound(k));
		}
		std::pair<iterator,iterator>				equal_range (const key_type& k) {
			return std::make_pair(lower_bound(k), upper_bound(k));
		}
	};
}

#endif //FT_CONTAINERS_MAP_HPP
