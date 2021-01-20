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
		size_type			size() const {  }

		/* Getter for operators */
		container_type const&	getContainer() const { return _vault; }
	private:
		container_type 		_vault;
	};
}

#endif //FT_CONTAINERS_STACK_HPP
