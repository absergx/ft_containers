//
// Created by Meldred Emilio on 11/29/20.
//

#pragma once

#include "list.hpp"

namespace ft {
	template <class T, class Container = list<T> >
	class queue {
	public:
		typedef	T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;

		/* Member functions */
		explicit queue(const container_type& ctnr = container_type()) : _vault(ctnr) {}
		bool				empty() const { return _vault.empty(); }
		size_type			size() const { return _vault.size(); }
		value_type&			front() { return _vault.front(); }
		const value_type&	front() const { return _vault.front(); }
		value_type&			back() { return _vault.back(); }
		const value_type&	back() const { return _vault.back(); }
		void				push(const value_type& val) { _vault.push_back(val); }
		void				pop() { _vault.pop_front(); }

		/* Getter for operators */
		container_type const&	getContainer() const { return _vault; }
	private:
		container_type		_vault;
	};

	/* Non-member function overloads */
	template <class T, class Container>
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs.getContainer() == rhs.getContainer(); }
	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs.getContainer() != rhs.getContainer(); }
	template <class T, class Container>
	bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs.getContainer() < rhs.getContainer(); }
	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs.getContainer() <= rhs.getContainer(); }
	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs.getContainer() > rhs.getContainer(); }
	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) { return lhs.getContainer() >= rhs.getContainer(); }
}
