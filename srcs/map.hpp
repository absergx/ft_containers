//
// Created by Meldred Emilio on 11/29/20.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include <iostream>

namespace ft {

	template<class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less <Key>,                     // map::key_compare
			class Alloc = std::allocator <std::pair<const Key, T>>    // map::allocator_type
	>
	class map {

	};
}

#endif //FT_CONTAINERS_MAP_HPP
