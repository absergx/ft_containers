//
// Created by Meldred Emilio on 2/12/21.
//

#pragma once

namespace ft {
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };
}
