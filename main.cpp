
#include <iostream>
#include "list.hpp"
#include <list>
#include "vector.hpp"
#include <vector>
#include "map.hpp"
#include <map>
#include "stack.hpp"
#include <stack>
#include "queue.hpp"
#include <queue>
#include <string>
#include <ostream>

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

std::string 		boolToString(bool answer) {
	return answer ? "true" : "false";
}

void				testStack() {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::stack<int> s;
	ft::stack<int> f;

	std::cout << blue << "Blue - std " << green << "Green - ft" << def << std::endl;
	std::cout << "Is empty? " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	s.push(10);
	f.push(10);
	std::cout << "On Top: ";
	std::cout << blue << s.top() << " " << green << f.top() << def << std::endl;
	s.push(12);
	f.push(12);
	std::cout << "Is empty? " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << "On Top: ";
	std::cout << blue << s.top() << " " << green << f.top() << def << std::endl;
	s.push(14);
	f.push(14);
	std::cout << "On Top: ";
	std::cout << blue << s.top() << " " << green << f.top() << def << std::endl;
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	s.pop();
	f.pop();
	std::cout << "On Top after .pop(): ";
	std::cout << blue << s.top() << " " << green << f.top() << def << std::endl;
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << "Test operators: " << std::endl;
	ft::stack<int> f1;
	f1.push(10);
	f1.push(12);
	std::cout << "f is 10 12 | f1 is 10 12" << std::endl;
	std::cout << "Size: " << f1.size() << " " << f.size() << std::endl;
	std::cout << "== : " << boolToString(f == f1) << std::endl;
	std::cout << "!= : " << boolToString(f != f1) << std::endl;
	std::cout << "> : " << boolToString(f > f1) << std::endl;
	std::cout << "< : " << boolToString(f < f1) << std::endl;
	f1.push(13);
	std::cout << "after push into f1 == : " << boolToString(f == f1) << std::endl;
	std::cout << "!= : " << boolToString(f != f1) << std::endl;
	std::cout << "> : " << boolToString(f > f1) << std::endl;
	std::cout << "< : " << boolToString(f < f1) << std::endl;
	f.push(14);
	std::cout << "after push into f == : " << boolToString(f == f1) << std::endl;
	std::cout << "!= : " << boolToString(f != f1) << std::endl;
	std::cout << "> : " << boolToString(f > f1) << std::endl;
	std::cout << "< : " << boolToString(f < f1) << std::endl;
}

void		testList() {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::list<int> s;
	ft::list<int> f;

	std::cout << blue << "Blue - std " << green << "Green - ft" << def << std::endl;
	std::cout << "Is empty? " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	std::cout << "Push front. For loop from 0 to 10." << std::endl;
	for (int i = 0; i < 10; ++i) {
		s.push_front(i);
		f.push_front(i);
	}
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << ".front(): " << blue << s.front() << " " << green << f.front() << def << std::endl;
	std::cout << ".back(): " << blue << s.back() << " " << green << f.back() << def << std::endl;
	std::cout << "Insert to begin: " << std::endl;
	s.insert(s.begin(), 3, 777);
	f.insert(f.begin(), 3, 777);
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "after .pop_front()" << std::endl;
	s.pop_front();
	f.pop_front();
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "after .pop_back()" << std::endl;
	s.pop_back();
	f.pop_back();
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "For loop from 0 to 9 .push_back()" << std::endl;
	for (int i = 0; i < 10; ++i) {
		s.push_back(i);
		f.push_back(i);
	}
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::list<int>::iterator itS = s.begin();
	ft::list<int>::iterator itF = f.begin();
	for (int i = 0; i < static_cast<int>(s.size() / 2); ++i) {
		++itF;
		++itS;
	}
	std::cout << "Insert in center from other list 22 33 44 55" << std::endl;
	ft::list<int> tmp;
	tmp.push_back(22);
	tmp.push_back(33);
	tmp.push_back(44);
	tmp.push_back(55);
	s.insert(itS, tmp.begin(), tmp.end());
	f.insert(itF, tmp.begin(), tmp.end());
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "Resize to 10" << std::endl;
	s.resize(10);
	f.resize(10);
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "Resize to 15" << std::endl;
	s.resize(15);
	f.resize(15);
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	tmp.push_front(11);
	std::cout << "Assign from another list" << std::endl;
	s.assign(tmp.begin(), tmp.end());
	f.assign(tmp.begin(), tmp.end());
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "Assign with range" << std::endl;
	s.assign(10, 42);
	f.assign(10, 42);
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "Erase begin" << std::endl;
	s.erase(s.begin());
	f.erase(f.begin());
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "Clear" << std::endl;
	s.clear();
	f.clear();
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << "Lets make new lists to test Operations" << std::endl;
	for (int i = 0; i < 10; ++i) {
		int r = std::rand();
		s.push_back(r);
		f.push_back(r);
	}
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	s.sort();
	f.sort();
	std::cout << "Sort:" << std::endl;
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	ft::list<int> fSplice(10, 42);
	std::list<int> sSplice(10, 42);
	std::cout << "Splice to --end() list from ranged constructor (10, 42)" << std::endl;
	f.splice(--f.end(), fSplice);
	s.splice(--s.end(), sSplice);
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "Unique" << std::endl;
	f.unique();
	s.unique();
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
	std::cout << "Reverse" << std::endl;
	f.reverse();
	s.reverse();
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << blue;
	for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << green;
	for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl << def;
}

void		testVector() {
	std::cout << "Place to tests. Come later. Or not" << std::endl;
}

void 		testMap() {
	std::cout << "Place to tests. Come later. Or not" << std::endl;
}

void 		testQueue() {
	std::cout << "Place to tests. Come later. Or not" << std::endl;
}

int			main()
{
	Color::Modifier red(Color::FG_RED);
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);
	while (true) {
		std::string input;
		std::cout << blue << "Possible commands:\n" << green << "map vector stack list queue exit\n" << blue << "Enter what you want to test:" << std::endl;
		std::getline(std::cin, input);
		if (input == "exit")
			break;
		else if (input == "stack") {
			std::cout << green << "Stack Test:" << def << std::endl;
			testStack();
			std::cout << red << "Test ended! Enjoy results." << std::endl;
		}
		else if (input == "list") {
			std::cout << green << "List Test:" << def << std::endl;
			testList();
			std::cout << red << "Test ended! Enjoy results." << std::endl;
		}
		else if (input == "vector") {
			std::cout << green << "Vector Test:" << def << std::endl;
			testVector();
			std::cout << red << "Test ended! Enjoy results." << std::endl;
		}
		else if (input == "queue") {
			std::cout << green << "Queue Test:" << def << std::endl;
			testQueue();
			std::cout << red << "Test ended! Enjoy results." << std::endl;
		}
		else if (input == "map") {
			std::cout << green << "Map Test:" << def << std::endl;
			testMap();
			std::cout << red << "Test ended! Enjoy results." << std::endl;
		}
		else
			std::cout << red << "Oups, i don't know this command." << std::endl;
	}
	std::cout << red << "Have a nice day! Bye!" << std::endl;
	return 0;
}
