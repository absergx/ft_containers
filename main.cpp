
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

struct is_odd {
	bool operator() (const int& value) { return (value%2)==1; }
};

std::string 		boolToString(bool answer) {
	return answer ? "true" : "false";
}

void		printLists(std::list<int> s, ft::list<int> f) {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	if (!s.empty() && !f.empty()) {
		std::cout << blue;
		for (std::list<int>::iterator it = s.begin(); it != s.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << green;
		for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << def;
	}
}

void 		printVectors(std::vector<int> s, ft::vector<int> f) {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	if (!s.empty() && !f.empty()) {
		std::cout << blue;
		for (std::vector<int>::iterator it = s.begin(); it != s.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << green;
		for (ft::vector<int>::iterator it = f.begin(); it != f.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << def;
	}
}

void		testStack() {
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

	std::cout << blue << "Blue - std " << green << "Green - ft" << def << std::endl;

	// Constructors test
	std::cout << "--- Constructors test ---" << std::endl;
	{
		std::cout << "Fill constructor list(12, \"kek\")" << std::endl;
		ft::list<std::string> f(12, "kek");
		std::list<std::string> s(12, "kek");
		std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
		std::cout << blue;
		for (std::list<std::string>::iterator it = s.begin(); it != s.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << green;
		for (ft::list<std::string>::iterator it = f.begin(); it != f.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << def;
	}
	{
		std::cout << "Range Input iterator constructor" << std::endl;
		std::list<int> ex(8, 42);

		ft::list<int> f(ex.begin(), ex.end());
		std::list<int> s(ex.begin(), ex.end());
		printLists(s, f);
	}
	{
		std::cout << "Copy constructor" << std::endl;
		ft::list<int> fA(13, 13);
		std::list<int> sA(13, 13);
		std::cout << "Source to copy:";
		printLists(sA, fA);
		std::cout << "After copy:";
		ft::list<int> f(fA);
		std::list<int> s(sA);
		printLists(s, f);
	}

	std::cout << "Default constructor" << std::endl;
	std::list<int> s;
	ft::list<int> f;

	printLists(s, f);
	std::cout << "Is empty? " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	getchar();

	std::cout << "Operator = " << std::endl;
	{
		std::list<int> s1;
		ft::list<int> f1;
		std::list<int> s2;
		ft::list<int> f2;
		for (int i = 0; i < 10; ++i) {
			s1.push_front(i);
			f1.push_front(i);
		}
		std::cout << "Source:" << std::endl;
		printLists(s1, f1);
		s2 = s1;
		f2 = f1;
		std::cout << "Result:" << std::endl;
		printLists(s2, f2);
	}
	getchar();

	std::cout << "---Modifiers---" << std::endl;
	std::cout << "Push front. For loop from 0 to 10." << std::endl;
	for (int i = 0; i < 10; ++i) {
		s.push_front(i);
		f.push_front(i);
	}
	printLists(s ,f);
	std::cout << "Insert to begin: " << std::endl;
	s.insert(s.begin(), 3, 777);
	f.insert(f.begin(), 3, 777);
	printLists(s ,f);
	std::cout << "after .pop_front()" << std::endl;
	s.pop_front();
	f.pop_front();
	printLists(s ,f);
	std::cout << "after .pop_back()" << std::endl;
	s.pop_back();
	f.pop_back();
	printLists(s ,f);
	std::cout << "For loop from 0 to 9 .push_back()" << std::endl;
	for (int i = 0; i < 10; ++i) {
		s.push_back(i);
		f.push_back(i);
	}
	printLists(s ,f);
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
	printLists(s ,f);
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
	printLists(s ,f);
	getchar();
	std::cout << "Assign from another list" << std::endl;
	tmp.push_front(11);
	s.assign(tmp.begin(), tmp.end());
	f.assign(tmp.begin(), tmp.end());
	printLists(s ,f);
	std::cout << "Assign with range" << std::endl;
	s.assign(10, 42);
	f.assign(10, 42);
	printLists(s ,f);
	std::cout << "Erase begin" << std::endl;
	s.erase(s.begin());
	f.erase(f.begin());
	printLists(s ,f);
	std::cout << "Clear" << std::endl;
	s.clear();
	f.clear();
	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	getchar();

	std::cout << "---Operations---" << std::endl;
	std::cout << "Lets make new lists to test Operations" << std::endl;
	for (int i = 0; i < 10; ++i) {
		int r = std::rand();
		s.push_back(r);
		f.push_back(r);
	}
	printLists(s ,f);
	std::cout << "Sort:" << std::endl;
	s.sort();
	f.sort();
	printLists(s ,f);
	ft::list<int> fSplice(10, 42);
	std::list<int> sSplice(10, 42);
	std::cout << "Splice to --end() list from ranged constructor (10, 42)" << std::endl;
	f.splice(--f.end(), fSplice);
	s.splice(--s.end(), sSplice);
	printLists(s ,f);
	std::cout << "Unique" << std::endl;
	f.unique();
	s.unique();
	printLists(s ,f);
	std::cout << "Reverse" << std::endl;
	f.reverse();
	s.reverse();
	printLists(s ,f);
	getchar();

	// merge
	std::cout << "Merge. First pair of lists:" << std::endl;
	ft::list<int> fMerge(5, 42);
	std::list<int> sMerge(5, 42);
	printLists(sMerge, fMerge);
	std::cout << "Second pair before merge:" << std::endl;
	printLists(s, f);
	s.merge(sMerge);
	f.merge(fMerge);
	std::cout << "After merge:" << std::endl;
	printLists(s, f);
	getchar();

	// remove
	std::cout << "Remove. Lists before:" << std::endl;
	printLists(s, f);
	std::cout << "After .remove(42):" << std::endl;
	s.remove(42);
	f.remove(42);
	printLists(s, f);
	getchar();

	// remove_if
	std::cout << "Remove_if. Lists before:" << std::endl;
	printLists(s, f);
	std::cout << "Remove all odd values. After call:" << std::endl;
	s.remove_if(is_odd());
	f.remove_if(is_odd());
	printLists(s, f);
	getchar();

	std::cout << "---Element access---" << std::endl;
	std::cout << ".front(): " << blue << s.front() << " " << green << f.front() << def << std::endl;
	std::cout << ".back(): " << blue << s.back() << " " << green << f.back() << def << std::endl;
	getchar();

	std::cout << "---Relational operators---" << std::endl;
	{
		ft::list<int> fEq(f);
		ft::list<int> fNeq(5, 100);
		std::cout << "Lists to test. Main list(second argument):" << std::endl;
		for (ft::list<int>::iterator it = f.begin(); it != f.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << "Equal list to test:" << std::endl;
		for (ft::list<int>::iterator it = fEq.begin(); it != fEq.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << "Not equal list to test:" << std::endl;
		for (ft::list<int>::iterator it = fNeq.begin(); it != fNeq.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl << "Lets test. Press enter." << std::endl;
		getchar();

		std::cout << "Operator == :" << std::endl;
		std::cout << "Lists are equal. Result = " << boolToString(fEq == f) << std::endl;
		std::cout << "Lists are not equal. Result = " << boolToString(fNeq == f) << std::endl;
		getchar();

		std::cout << "Operator != :" << std::endl;
		std::cout << "Lists are equal. Result = " << boolToString(fEq != f) << std::endl;
		std::cout << "Lists are not equal. Result = " << boolToString(fNeq != f) << std::endl;
		getchar();

		std::cout << "Operator < :" << std::endl;
		std::cout << "Lists are equal. Result = " << boolToString(fEq < f) << std::endl;
		std::cout << "Lists are not equal. Second list is higher. Result = " << boolToString(fNeq < f) << std::endl;
		getchar();

		std::cout << "Operator <= :" << std::endl;
		std::cout << "Lists are equal. Result = " << boolToString(fEq <= f) << std::endl;
		std::cout << "Lists are not equal. Second list is higher. Result = " << boolToString(fNeq <= f) << std::endl;
		getchar();

		std::cout << "Operator > :" << std::endl;
		std::cout << "Lists are equal. Result = " << boolToString(fEq > f) << std::endl;
		std::cout << "Lists are not equal. Second list is higher. Result = " << boolToString(fNeq > f) << std::endl;
		getchar();

		std::cout << "Operator >= :" << std::endl;
		std::cout << "Lists are equal. Result = " << boolToString(fEq >= f) << std::endl;
		std::cout << "Lists are not equal. Second list is higher. Result = " << boolToString(fNeq >= f) << std::endl;
	}
}

void 		testQueue() {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << blue << "Blue - std " << green << "Green - ft" << def << std::endl;

	ft::queue<std::string> f;
	std::queue<std::string> s;
	std::cout << "---Member functions---\n.empty() on empty queue:" << std::endl;
	std::cout << blue << boolToString(s.empty()) << green << boolToString(f.empty()) << def << std::endl;
	std::cout << "Size on empty queue:" << std::endl;
	std::cout << blue << s.size() << green << f.size() << def << std::endl;
	std::cout << "Push testing. For loop push." << std::endl;
	for (int i = 0; i < 10; ++i) {
		if (i % 2 == 0) {
			f.push("kek");
			s.push("kek");
		} else {
			f.push("lol");
			s.push("lol");
		}
	}
	std::cout << ".empty() after pushing:" << std::endl;
	std::cout << blue << boolToString(s.empty()) << green << boolToString(f.empty()) << def << std::endl;
	std::cout << ".size() after pushing:" << std::endl;
	std::cout << blue << s.size() << green << f.size() << def << std::endl;
	std::cout << ".front() :" << std::endl;
	std::cout << blue << s.front() << green << f.front() << def << std::endl;
	std::cout << ".back() :" << std::endl;
	std::cout << blue << s.back() << green << f.back() << def << std::endl;
	std::cout << "after .pop(): ";
	std::cout << ".front() :" << std::endl;
	std::cout << blue << s.front() << green << f.front() << def << std::endl;
	std::cout << ".back() :" << std::endl;
	std::cout << blue << s.back() << green << f.back() << def << std::endl;
	getchar();

	std::cout << "---Relational operators---" << std::endl;
	ft::queue<std::string> fEq(f);
	std::queue<std::string> sEq(s);
	ft::queue<std::string> fNeq;
	std::queue<std::string> sNeq;

	for (int i = 0; i < 9; ++i) {
		fNeq.push("mem");
		sNeq.push("mem");
	}
	std::cout << "Operator == :" << std::endl;
	std::cout << "Equal containers: " << blue << boolToString(s == sEq) << green << boolToString(f == fEq) << def << std::endl;
	std::cout << "Not equal containers: " << blue << boolToString(s == sNeq) << green << boolToString(f == fNeq) << def << std::endl;

	std::cout << "Operator != :" << std::endl;
	std::cout << "Equal containers: " << blue << boolToString(s != sEq) << green << boolToString(f != fEq) << def << std::endl;
	std::cout << "Not equal containers: " << blue << boolToString(s != sNeq) << green << boolToString(f != fNeq) << def << std::endl;

	std::cout << "Operator > :" << std::endl;
	std::cout << "Equal containers: " << blue << boolToString(s > sEq) << green << boolToString(f > fEq) << def << std::endl;
	std::cout << "Not equal containers: " << blue << boolToString(s > sNeq) << green << boolToString(f > fNeq) << def << std::endl;

	std::cout << "Operator >= :" << std::endl;
	std::cout << "Equal containers: " << blue << boolToString(s >= sEq) << green << boolToString(f >= fEq) << def << std::endl;
	std::cout << "Not equal containers: " << blue << boolToString(s >= sNeq) << green << boolToString(f >= fNeq) << def << std::endl;

	std::cout << "Operator < :" << std::endl;
	std::cout << "Equal containers: " << blue << boolToString(s < sEq) << green << boolToString(f < fEq) << def << std::endl;
	std::cout << "Not equal containers: " << blue << boolToString(s < sNeq) << green << boolToString(f < fNeq) << def << std::endl;

	std::cout << "Operator <= :" << std::endl;
	std::cout << "Equal containers: " << blue << boolToString(s <= sEq) << green << boolToString(f <= fEq) << def << std::endl;
	std::cout << "Not equal containers: " << blue << boolToString(s <= sNeq) << green << boolToString(f <= fNeq) << def << std::endl;
}

void		testVector() {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << blue << "Blue - std " << green << "Green - ft" << def << std::endl;

	std::cout << "---Constructors test---" << std::endl;
	std::cout << "Default constructor" << std::endl;
	std::vector<int> s;
	ft::vector<int> f;
	printVectors(s, f);
	{
		std::cout << "Fill constructor" << std::endl;
		std::vector<int> s1(10, 42);
		ft::vector<int> f1(10, 42);
		printVectors(s1, f1);
		std::cout << "Range constructor" << std::endl;
		std::vector<int> s2(s1.begin(), s1.end());
		ft::vector<int> f2(s1.begin(), s1.end());
		printVectors(s2, f2);
		std::cout << "Copy constructor" << std::endl;
		std::vector<int> s3(s1);
		ft::vector<int> f3(f1);
		printVectors(s3, f3);
		std::cout << "Operator =" << std::endl;
		s = s3;
		f = f3;
		printVectors(s, f);
	}
	getchar();

	std::cout << "---Capacity---" << std::endl;

	std::cout << ".maxsize()" << std::endl;
	std::cout << blue << s.max_size() << " " << green << f.max_size() << def << std::endl;

	std::cout << ".resize() to smaller" << std::endl;
	s.resize(5);
	f.resize(5);
	printVectors(s, f);

	std::cout << ".resize() to higher with val = 13" << std::endl;
	s.resize(12, 13);
	f.resize(12, 13);
	printVectors(s, f);

	std::cout << ".capacity()" << std::endl;
	std::cout << blue << s.capacity() << " " << green << f.capacity() << def << std::endl;

	std::cout << ".empty() not empty vector" << std::endl;
	std::cout << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	std::cout << ".empty() on empty vector" << std::endl;
	{
		std::vector<int> s1;
		ft::vector<int> f1;
		std::cout << blue << boolToString(s1.empty()) << " " << green << boolToString(f1.empty()) << def << std::endl;
	}

	std::cout << ".reserve() to 100. then call .capacity()" << std::endl;
	s.reserve(100);
	f.reserve(100);
	std::cout << blue << s.capacity() << " " << green << f.capacity() << def << std::endl;
	getchar();

	std::cout << "---Element access---" << std::endl;
	std::cout << "Test operator[]. Compare values in both lists in loop" << std::endl;
	for (size_t i = 0; i < s.size(); ++i)
		std::cout << "i = " << i << " values: " << blue << s[i] << " " << green << f[i] << def << std::endl;
	getchar();
	std::cout << ".at(). Same test as before" << std::endl;
	for (size_t i = 0; i < s.size(); ++i)
		std::cout << "i = " << i << " values: " << blue << s.at(i) << " " << green << f.at(i) << def << std::endl;
	std::cout << ".front()" << std::endl;
	std::cout << blue << s.front() << " " << green << f.front() << def << std::endl;
	std::cout << ".back()" << std::endl;
	std::cout << blue << s.back() << " " << green << f.back() << def << std::endl;
	getchar();

	std::cout << "---Modifiers---" << std::endl;
	// assign
	std::cout << ".assign() fill 5 times value = 55" << std::endl;
	s.assign(5, 55);
	f.assign(5, 55);
	printVectors(s, f);
	std::cout << ".assign() with input iterator from other list (for loop filled). Source vectors:" << std::endl;
	ft::vector<int> fAssign;
	std::vector<int> sAssign;
	for (int i = 0; i < 10; ++i) {
		fAssign.push_back(i);
		sAssign.push_back(i);
	}
	printVectors(sAssign, fAssign);
	std::cout << "After .assign() from begin to end source vectors:" << std::endl;
	s.assign(sAssign.begin(), sAssign.end());
	f.assign(fAssign.begin(), fAssign.end());
	printVectors(s, f);
	getchar();

	// push_back
	std::cout << ".push_back() . print vectors before:" << std::endl;
	printVectors(s, f);
	for (int i = 0; i < 10; ++i) {
		s.push_back(i);
		f.push_back(i);
	}
	std::cout << "after .push_back() in for loop vectors:" << std::endl;
	printVectors(s, f);


	// pop_back
	std::cout << ".pop_back() . after 1 use: " << std::endl;
	f.pop_back();
	s.pop_back();
	printVectors(s, f);
	std::cout << ".pop_back() . after for loop 4 uses: " << std::endl;
	for (int i = 0; i < 4; ++i) {
		f.pop_back();
		s.pop_back();
	}
	printVectors(s, f);
	getchar();

	// insert
	std::cout << ".insert() into begin value = 123" << std::endl;
	s.insert(s.begin(), 123);
	f.insert(f.begin(), 123);
	printVectors(s, f);
	std::cout << ".insert() to --end() value = 88 n = 3" << std::endl;
	s.insert(--s.end(), 88, 3);
	f.insert(--f.end(), 88, 3);
	printVectors(s, f);
	std::cout << ".insert() from input iterator other vector to ++begin()" << std::endl;
	ft::vector<int> fInsert(4, 99);
	s.insert(++s.begin(), fInsert.begin(), fInsert.end());
	f.insert(++f.begin(), fInsert.begin(), fInsert.end());
	printVectors(s, f);
	getchar();

	// erase
	std::cout << ".erase() to begin()" << std::endl;
	s.erase(s.begin());
	f.erase(f.begin());
	printVectors(s, f);
	std::cout << ".erase() to --end()" << std::endl;
	s.erase(--s.end());
	f.erase(--f.end());
	printVectors(s, f);
	getchar();

	// swap
	std::cout << ".swap() with vector. Source:" << std::endl;
	ft::vector<int> fSwap(5, 1);
	std::vector<int> sSwap(5, 1);
	printVectors(sSwap, fSwap);
	std::cout << "Our vectors before swap:" << std::endl;
	printVectors(s, f);
	std::cout << "After swap Source vectors:" << std::endl;
	s.swap(sSwap);
	f.swap(fSwap);
	printVectors(sSwap, fSwap);
	std::cout << "Main vectors after swap:" << std::endl;
	printVectors(s, f);
	getchar();

	// clear
	std::cout << ".clear() . print size and capacity after clear" << std::endl;
	s.clear();
	f.clear();
	printVectors(s, f);
	std::cout << "Capacity: " << blue << s.capacity() << " " << green << f.capacity() << def << std::endl;

	std::cout << "---Relational operators---" << std::endl;
	ft::vector<int> fEq(4, 4);
	std::vector<int> sEq(4, 4);
	ft::vector<int> fNotEq(4, 5);
	std::vector<int> sNotEq(4, 5);
	s.assign(4, 4);
	f.assign(4, 4);
	std::cout << "Our main vectors:" << std::endl;
	printVectors(s, f);
	std::cout << "Vectors to be equal:" << std::endl;
	printVectors(sEq, fEq);
	std::cout << "Vectors to be not equal:" << std::endl;
	printVectors(sNotEq, fNotEq);
	getchar();

	std::cout << "Operator ==" << std::endl;
	std::cout << "Equal vectors: " << blue << boolToString(s == sEq) << " " << green << boolToString(f == fEq) << def << std::endl;
	std::cout << "Not equal vectors: " << blue << boolToString(s == sNotEq) << " " << green << boolToString(f == fNotEq) << def << std::endl;

	std::cout << "Operator !=" << std::endl;
	std::cout << "Equal vectors: " << blue << boolToString(s != sEq) << " " << green << boolToString(f != fEq) << def << std::endl;
	std::cout << "Not equal vectors: " << blue << boolToString(s != sNotEq) << " " << green << boolToString(f != fNotEq) << def << std::endl;

	std::cout << "Operator <" << std::endl;
	std::cout << "Equal vectors: " << blue << boolToString(s < sEq) << " " << green << boolToString(f < fEq) << def << std::endl;
	std::cout << "Not equal vectors: " << blue << boolToString(s < sNotEq) << " " << green << boolToString(f < fNotEq) << def << std::endl;

	std::cout << "Operator <=" << std::endl;
	std::cout << "Equal vectors: " << blue << boolToString(s <= sEq) << " " << green << boolToString(f <= fEq) << def << std::endl;
	std::cout << "Not equal vectors: " << blue << boolToString(s <= sNotEq) << " " << green << boolToString(f <= fNotEq) << def << std::endl;

	std::cout << "Operator >" << std::endl;
	std::cout << "Equal vectors: " << blue << boolToString(s > sEq) << " " << green << boolToString(f > fEq) << def << std::endl;
	std::cout << "Not equal vectors: " << blue << boolToString(s > sNotEq) << " " << green << boolToString(f > fNotEq) << def << std::endl;

	std::cout << "Operator >=" << std::endl;
	std::cout << "Equal vectors: " << blue << boolToString(s >= sEq) << " " << green << boolToString(f >= fEq) << def << std::endl;
	std::cout << "Not equal vectors: " << blue << boolToString(s >= sNotEq) << " " << green << boolToString(f >= fNotEq) << def << std::endl;
}

void 		testMap() {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);
	std::cout << blue << "Blue - std " << green << "Green - ft" << def << std::endl;


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
