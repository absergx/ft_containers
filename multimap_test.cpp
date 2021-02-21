//
// Created by Meldred Emilio on 2/21/21.
//

#include <map>
#include "multimap.hpp"
#include <iostream>

namespace Color {
	enum Code {
		FG_RED      = 31,
		FG_GREEN    = 32,
		FG_BLUE     = 34,
		FG_DEFAULT  = 39,
		BG_RED      = 41,
		BG_GREEN    = 42,
		BG_BLUE     = 44,
		BG_DEFAULT  = 49
	};
	class Modifier {
		Code code;
	public:
		Modifier(Code pCode) : code(pCode) {}
		friend std::ostream&
		operator<<(std::ostream& os, const Modifier& mod) {
			return os << "\033[" << mod.code << "m";
		}
	};
}

void 		printMaps(std::multimap<int, int> &s, ft::multimap<int, int> &f) {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	if (s.size() != f.size()) {
		std::cout << "Error in print maps. Size is not equal." << std::endl;
		return;
	} else if (s.empty() && f.empty())
		return;
	std::multimap<int, int>::iterator sit = s.begin();
	std::multimap<int, int>::iterator site = s.end();
	ft::multimap<int, int>::iterator fit = f.begin();
	ft::multimap<int, int>::iterator fite = f.end();
	while (sit != site && fit != fite) {
		std::cout << blue << sit->first << "-" << sit->second << "\t\t" << green << fit->first << "-" << fit->second << def << std::endl;
		++sit;
		++fit;
	}
}

int main() {
	std::multimap<int, int> s;
	ft::multimap<int, int> f;

	for (int i = 0; i < 2; ++i) {
		for (int k = 0; k < 5; ++k) {
			s.insert(std::pair<int, int>(i, i + k));
			f.insert(std::pair<int, int>(i, i + k));
		}
	}
	printMaps(s, f);
//	s.erase(0);
//	f.erase(0);
//	printMaps(s ,f);
//	s.erase(1);
//	f.erase(1);
//	printMaps(s, f);

	return 0;
}