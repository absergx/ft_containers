//
// Created by Meldred Emilio on 11/29/20.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "list.hpp"

namespace ft {
	template <class T, class Container = list<T> >
	class stack {
	public:
		typedef	T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;

		/* Member functions */
		explicit stack(const container_type& ctnr = container_type()) : _vault(ctnr) {}
		bool				empty() const { return _vault.empty(); }
		size_type			size() const { return _vault.size(); }
		value_type&			top() { return _vault.back(); }
		const value_type&	top() const { return _vault.back(); }
		void				push(const value_type& val) { _vault.push_back(val); }
		void				pop() { _vault.pop_back(); }

		/* Getter for operators */
		container_type const&	getContainer() const { return _vault; }
	private:
		container_type 		_vault;
	};
	/* Relational operators */
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.getContainer() == rhs.getContainer(); }
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.getContainer() != rhs.getContainer(); }
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.getContainer() < rhs.getContainer(); }
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.getContainer() <= rhs.getContainer(); }
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.getContainer() > rhs.getContainer(); }
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.getContainer() >= rhs.getContainer(); }
}

#endif //FT_CONTAINERS_STACK_HPP
