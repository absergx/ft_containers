//
// Created by Meldred Emilio on 11/29/20.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include <memory>
#include <stdexcept>

namespace ft {
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

	public:
		explicit list(const allocator_type& alloc = allocator_type()) {}
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {}
		template<class InputIterator>
				list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {}
		list(const list &x) {}
		~list();

	};
}

#endif //FT_CONTAINERS_LIST_HPP
