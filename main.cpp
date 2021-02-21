
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
#include "set.hpp"
#include <set>
#include "deque.hpp"
#include <deque>

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

void 		printMaps(std::map<int, std::string> s, ft::map<int, std::string> f) {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	if (s.size() != f.size()) {
		std::cout << "Error in print maps. Size is not equal." << std::endl;
		return;
	} else if (s.empty() && f.empty())
		return;
	std::map<int, std::string>::iterator sit = s.begin();
	std::map<int, std::string>::iterator site = s.end();
	ft::map<int, std::string>::iterator fit = f.begin();
	ft::map<int, std::string>::iterator fite = f.end();
	while (sit != site && fit != fite) {
		std::cout << blue << sit->first << "-" << sit->second << "\t\t" << green << fit->first << "-" << fit->second << def << std::endl;
		++sit;
		++fit;
	}
}

void 		testMap() {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);
	std::cout << blue << "Blue - std " << green << "Green - ft" << def << std::endl;

	std::cout << "---Constructor tests---" << std::endl;
	std::cout << "Empty constructor. Call .size() and .empty() to both maps after construct:" << std::endl;
	std::map<int, std::string> s;
	ft::map<int, std::string> f;
	printMaps(s, f);
	std::cout << "Is empty? : " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;

	s.insert(std::pair<int, std::string>(22, "first"));
	f.insert(std::pair<int, std::string>(22, "first"));
	s.insert(std::pair<int, std::string>(24, "second"));
	f.insert(std::pair<int, std::string>(24, "second"));
	s.insert(std::pair<int, std::string>(10, "third"));
	f.insert(std::pair<int, std::string>(10, "third"));
	printMaps(s, f);
	{
		std::cout << "Range constructor. Use reverse iterator from rbegin to rend after inserting to empty maps." << std::endl;
		std::map<int, std::string> sRange(s.rbegin(), s.rend());
		ft::map<int, std::string> fRange(s.rbegin(), s.rend());
		printMaps(sRange, fRange);
		std::cout << "Copy constructor. Use previous map as source." << std::endl;
		std::map<int, std::string> sCopy(sRange);
		ft::map<int, std::string> fCopy(fRange);
		printMaps(sCopy, fCopy);
		std::cout << "Operator = . Lets make empty maps and then use assignation operator from previous maps:" << std::endl;
		std::map<int, std::string> sAssign;
		ft::map<int, std::string> fAssign;
		printMaps(sAssign, fAssign);
		std::cout << "After assignation: " << std::endl;
		sAssign = sCopy;
		fAssign = fCopy;
		printMaps(sAssign, fAssign);
	}
	getchar();

	std::cout << "---Capacity---" << std::endl
		<< ".empty() with not empty maps :"
		<< blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	getchar();
	std::cout << ".max_size()" << std::endl
		<< blue << s.max_size() << " " << green << f.max_size() << def << std::endl;

	std::cout << "---Modifiers---" << std::endl
		<< ".insert() values in for loop -10 - 10:" << std::endl;
	for (int i = -10; i <= 10; ++i) {
		s.insert(std::pair<int, std::string>(i, "for-looped-values-insert"));
		f.insert(std::pair<int, std::string>(i, "for-looped-values-insert"));
	}
	printMaps(s, f);
	getchar();
	std::cout << ".insert() using input iterators. Make new map with values 25 - 30 and insert from there:" << std::endl;
	std::map<int, std::string> toInsert;
	for (int i = 25; i <= 30; ++i)
		toInsert.insert(std::pair<int, std::string>(i, "input-iterators-values"));
	s.insert(toInsert.begin(), toInsert.end());
	f.insert(toInsert.begin(), toInsert.end());
	printMaps(s, f);
	getchar();

	std::cout << ".erase() using iterators. Actual size is 29, so use for loop 10 times to iterators and then use 10 times erase." << std::endl;
	{
		std::map<int, std::string>::iterator sit = s.begin();
		ft::map<int, std::string>::iterator fit = f.begin();
		for (int i = 0; i < 10; ++i) {
			++sit;
			++fit;
		}
		for (int i = 0; i < 10; ++i) {
			s.erase(sit++);
			f.erase(fit++);
		}
		printMaps(s, f);
		getchar();
		std::cout << ".erase() with two iterators as arguments." << std::endl;
		std::map<int, std::string>::iterator sit1(sit);
		ft::map<int, std::string>::iterator fit1(fit);
		for (int i = 0; i < 5; ++i) {
			++sit1;
			++fit1;
		}
		s.erase(sit, sit1);
		f.erase(fit, fit1);
		printMaps(s, f);
		getchar();
		std::cout << ".erase() using key value. lets erase values from -9 to - 3:" << std::endl;
		for (int i = -9; i <= -3; ++i) {
			s.erase(i);
			f.erase(i);
		}
		printMaps(s, f);
		getchar();
	}

	std::cout << ".swap() . lets do new maps with values 100 - 120:" << std::endl;
	std::map<int, std::string> sSwap;
	ft::map<int, std::string> fSwap;
	for (int i = 100; i <= 120; ++i) {
		sSwap[i] = "new-map-for-swap";
		fSwap[i] = "new-map-for-swap";
	}
	printMaps(sSwap, fSwap);
	std::cout << "Main maps before swapping:" << std::endl;
	printMaps(s, f);
	getchar();
	s.swap(sSwap);
	f.swap(fSwap);
	std::cout << "After swap new maps:" << std::endl;
	printMaps(sSwap, fSwap);
	std::cout << "After swap main maps:" << std::endl;
	printMaps(s, f);

	// clear
	std::cout << ".clear(). Call .size() and .empty() before clear:" << std::endl;
	std::cout << ".size(): " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << ".empty(): " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	std::cout << "Call .size() and .empty() after clear:" << std::endl;
	s.clear();
	f.clear();
	std::cout << ".size(): " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << ".empty(): " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	getchar();

	std::cout << "---Element access---" << std::endl
			  << "Operator []. Use 66, 33, 77 as keys:" << std::endl;
	s[66] = "element-access-test";
	f[66] = "element-access-test";
	s[33] = "element-access-test";
	f[33] = "element-access-test";
	s[77] = "element-access-test";
	f[77] = "element-access-test";
	printMaps(s, f);
	getchar();

	std::cout << "---Operations---" << std::endl;
	std::cout << "Fill map with new values 30 - 40" << std::endl;
	for (int i = 30; i <= 40; ++i) {
		s[i] = "operations-test";
		f[i] = "operations-test";
	}
	printMaps(s, f);
	getchar();

	std::cout << ".find() using for loop 30 - 35, print ->second:" << std::endl;
	for (int i = 30; i <= 35; ++i) {
		std::cout << ".find(" << i << "): " << blue << s.find(i)->second << " " << green << f.find(i)->second << def << std::endl;
	}
	getchar();

	std::cout << ".count() using for loop 35 - 45:" << std::endl;
	for (int i = 35; i <= 45; ++i) {
		std::cout << ".count(" << i << "): " << blue << s.count(i) << " " << green << f.count(i) << def << std::endl;
	}
	getchar();

	std::cout << "Our maps:" << std::endl;
	printMaps(s, f);
	std::cout << ".lower_bound() with values 45, 20, 70" << std::endl
		<< "45: " << blue << s.lower_bound(45)->first << " " << green << f.lower_bound(45)->first << def << std::endl
		<< "20: " << blue << s.lower_bound(20)->first << " " << green << f.lower_bound(20)->first << def << std::endl
		<< "70: " << blue << s.lower_bound(70)->first << " " << green << f.lower_bound(70)->first << def << std::endl;
	getchar();

	std::cout << ".upper_bound() with values 0, 50, 67" << std::endl
		<< "0: " << blue << s.upper_bound(0)->first << " " << green << f.upper_bound(0)->first << def << std::endl
		<< "50: " << blue << s.upper_bound(50)->first << " " << green << f.upper_bound(50)->first << def << std::endl
		<< "67: " << blue << s.upper_bound(67)->first << " " << green << f.upper_bound(67)->first << def << std::endl;
	getchar();

	std::cout << ".equal_range() with values 40, 33" << std::endl;
	std::cout << blue << s.equal_range(40).first->first << " - " << s.equal_range(40).second->first
		<< " " << green << f.equal_range(40).first->first << " - " << f.equal_range(40).second->first << def << std::endl
		<< blue << s.equal_range(33).first->first << " - " << s.equal_range(33).second->first
		<< " " << green << f.equal_range(33).first->first << " - " << f.equal_range(33).second->first << def << std::endl;
}

void 		printDeques(std::deque<int> s, ft::deque<int> f) {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	if (s.size() != f.size()) {
		std::cout << "Error in print deques. Size is not equal." << std::endl;
		return;
	} else if (s.empty() && f.empty())
		return;
	std::deque<int>::iterator sit = s.begin();
	std::deque<int>::iterator site = s.end();
	ft::deque<int>::iterator fit = f.begin();
	ft::deque<int>::iterator fite = f.end();
	while (sit != site && fit != fite) {
		std::cout << blue << *sit << "\t\t" << green << *fit << def << std::endl;
		++sit;
		++fit;
	}
}

void 		printSets(std::set<int> s, ft::set<int> f) {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << "Size: " << blue << s.size() << " " << green << f.size() << def << std::endl;
	if (s.size() != f.size()) {
		std::cout << "Error in print deques. Size is not equal." << std::endl;
		return;
	} else if (s.empty() && f.empty())
		return;
	std::set<int>::iterator sit = s.begin();
	std::set<int>::iterator site = s.end();
	ft::set<int>::iterator fit = f.begin();
	ft::set<int>::iterator fite = f.end();
	while (sit != site && fit != fite) {
		std::cout << blue << *sit << "\t\t" << green << *fit << def << std::endl;
		++sit;
		++fit;
	}
}

void		testDeque() {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << blue << "Blue - std " << green << "Green - ft" << def << std::endl;

	std::cout << "---Constructors test---" << std::endl;
	std::cout << "Default constructor" << std::endl;
	std::deque<int> s;
	ft::deque<int> f;
	printDeques(s, f);
	{
		std::cout << "Fill constructor" << std::endl;
		std::deque<int> s1(10, 42);
		ft::deque<int> f1(10, 42);
		printDeques(s1, f1);
		std::cout << "Range constructor" << std::endl;
		std::deque<int> s2(s1.begin(), s1.end());
		ft::deque<int> f2(s1.begin(), s1.end());
		printDeques(s2, f2);
		std::cout << "Copy constructor" << std::endl;
		std::deque<int> s3(s1);
		ft::deque<int> f3(f1);
		printDeques(s3, f3);
		std::cout << "Operator =" << std::endl;
		s = s3;
		f = f3;
		printDeques(s, f);
	}
	getchar();

	std::cout << "---Capacity---" << std::endl;

	std::cout << ".maxsize()" << std::endl;
	std::cout << blue << s.max_size() << " " << green << f.max_size() << def << std::endl;

	std::cout << ".resize() to smaller" << std::endl;
	s.resize(5);
	f.resize(5);
	printDeques(s, f);

	std::cout << ".resize() to higher with val = 13" << std::endl;
	s.resize(12, 13);
	f.resize(12, 13);
	printDeques(s, f);


	std::cout << ".empty() not empty vector" << std::endl;
	std::cout << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	std::cout << ".empty() on empty vector" << std::endl;
	{
		std::deque<int> s1;
		ft::deque<int> f1;
		std::cout << blue << boolToString(s1.empty()) << " " << green << boolToString(f1.empty()) << def << std::endl;
	}

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
	printDeques(s, f);
	std::cout << ".assign() with input iterator from other list (for loop filled). Source vectors:" << std::endl;
	ft::deque<int> fAssign;
	std::deque<int> sAssign;
	for (int i = 0; i < 10; ++i) {
		fAssign.push_back(i);
		sAssign.push_back(i);
	}
	printDeques(sAssign, fAssign);
	std::cout << "After .assign() from begin to end source vectors:" << std::endl;
	s.assign(sAssign.begin(), sAssign.end());
	f.assign(fAssign.begin(), fAssign.end());
	printDeques(s, f);
	getchar();

	// push_back
	std::cout << ".push_back() . print vectors before:" << std::endl;
	printDeques(s, f);
	for (int i = 0; i < 10; ++i) {
		s.push_back(i);
		f.push_back(i);
	}
	std::cout << "after .push_back() in for loop vectors:" << std::endl;
	printDeques(s, f);


	// pop_back
	std::cout << ".pop_back() . after 1 use: " << std::endl;
	f.pop_back();
	s.pop_back();
	printDeques(s, f);
	std::cout << ".pop_back() . after for loop 4 uses: " << std::endl;
	for (int i = 0; i < 4; ++i) {
		f.pop_back();
		s.pop_back();
	}
	printDeques(s, f);
	getchar();

	// push_front
	std::cout << ".push_front(). one use:" << std::endl;
	f.push_front(123);
	s.push_front(123);
	printDeques(s, f);
	getchar();
	std::cout << ".push_front() in for loop:" << std::endl;
	for (int i = 0; i < 5; ++i) {
		f.push_front(i);
		s.push_front(i);
	}
	printDeques(s, f);
	getchar();

	// pop_front
	std::cout << ".pop_front() one use:" << std::endl;
	s.pop_front();
	f.pop_front();
	printDeques(s, f);
	getchar();
	std::cout << ".pop_front() in for loop:" << std::endl;
	for (int i = 0; i < 5; ++i) {
		f.pop_front();
		s.pop_front();
	}
	printDeques(s, f);
	getchar();

	// insert
	std::cout << ".insert() into begin value = 123" << std::endl;
	s.insert(s.begin(), 123);
	f.insert(f.begin(), 123);
	printDeques(s, f);
	std::cout << ".insert() to --end() value = 88 n = 3" << std::endl;
	s.insert(--s.end(), 88, 3);
	f.insert(--f.end(), 88, 3);
	printDeques(s, f);
	std::cout << ".insert() from input iterator other vector to ++begin()" << std::endl;
	ft::deque<int> fInsert(4, 99);
	s.insert(++s.begin(), fInsert.begin(), fInsert.end());
	f.insert(++f.begin(), fInsert.begin(), fInsert.end());
	printDeques(s, f);
	getchar();

	// erase
	std::cout << ".erase() to begin()" << std::endl;
	s.erase(s.begin());
	f.erase(f.begin());
	printDeques(s, f);
	std::cout << ".erase() to --end()" << std::endl;
	s.erase(--s.end());
	f.erase(--f.end());
	printDeques(s, f);
	getchar();

	// swap
	std::cout << ".swap() with vector. Source:" << std::endl;
	ft::deque<int> fSwap(5, 1);
	std::deque<int> sSwap(5, 1);
	printDeques(sSwap, fSwap);
	std::cout << "Our vectors before swap:" << std::endl;
	printDeques(s, f);
	std::cout << "After swap Source vectors:" << std::endl;
	s.swap(sSwap);
	f.swap(fSwap);
	printDeques(sSwap, fSwap);
	std::cout << "Main vectors after swap:" << std::endl;
	printDeques(s, f);
	getchar();

	// clear
	std::cout << ".clear() . print size and capacity after clear" << std::endl;
	s.clear();
	f.clear();
	printDeques(s, f);

	std::cout << "---Relational operators---" << std::endl;
	ft::deque<int> fEq(4, 4);
	std::deque<int> sEq(4, 4);
	ft::deque<int> fNotEq(4, 5);
	std::deque<int> sNotEq(4, 5);
	s.assign(4, 4);
	f.assign(4, 4);
	std::cout << "Our main vectors:" << std::endl;
	printDeques(s, f);
	std::cout << "Vectors to be equal:" << std::endl;
	printDeques(sEq, fEq);
	std::cout << "Vectors to be not equal:" << std::endl;
	printDeques(sNotEq, fNotEq);
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

void 		testSet() {
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);

	std::cout << blue << "Blue - std " << green << "Green - ft" << def << std::endl;

	std::cout << "---Constructor tests---" << std::endl;
	std::cout << "Empty constructor. Call .size() and .empty() to both sets after construct:" << std::endl;
	std::set<int> s;
	ft::set<int> f;
	printSets(s, f);
	std::cout << "Is empty? : " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;

	s.insert(22);
	f.insert(22);
	s.insert(24);
	f.insert(24);
	s.insert(10);
	f.insert(10);
	printSets(s, f);
	{
		std::cout << "Range constructor. Use reverse iterator from rbegin to rend after inserting to empty sets." << std::endl;
		std::set<int> sRange(s.rbegin(), s.rend());
		ft::set<int> fRange(s.rbegin(), s.rend());
		printSets(sRange, fRange);
		std::cout << "Copy constructor. Use previous set as source." << std::endl;
		std::set<int> sCopy(sRange);
		ft::set<int> fCopy(fRange);
		printSets(sCopy, fCopy);
		std::cout << "Operator = . Lets make empty maps and then use assignation operator from previous sets:" << std::endl;
		std::set<int> sAssign;
		ft::set<int> fAssign;
		printSets(sAssign, fAssign);
		std::cout << "After assignation: " << std::endl;
		sAssign = sCopy;
		fAssign = fCopy;
		printSets(sAssign, fAssign);
	}
	getchar();

	std::cout << "---Capacity---" << std::endl
			  << ".empty() with not empty sets :"
			  << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	getchar();

	std::cout << "---Modifiers---" << std::endl
			  << ".insert() values in for loop -10 - 10:" << std::endl;
	for (int i = -10; i <= 10; ++i) {
		s.insert(i);
		f.insert(i);
	}
	printSets(s, f);
	getchar();
	std::cout << ".insert() using input iterators. Make new map with values 25 - 30 and insert from there:" << std::endl;
	std::set<int> toInsert;
	for (int i = 25; i <= 30; ++i)
		toInsert.insert(i);
	s.insert(toInsert.begin(), toInsert.end());
	f.insert(toInsert.begin(), toInsert.end());
	printSets(s, f);
	getchar();

	std::cout << ".erase() using iterators. Actual size is 29, so use for loop 10 times to iterators and then use 10 times erase." << std::endl;
	{
		std::set<int>::iterator sit = s.begin();
		ft::set<int>::iterator fit = f.begin();
		for (int i = 0; i < 10; ++i) {
			++sit;
			++fit;
		}
		for (int i = 0; i < 10; ++i) {
			s.erase(sit++);
			f.erase(fit++);
		}
		printSets(s, f);
		getchar();
		std::cout << ".erase() with two iterators as arguments." << std::endl;
		std::set<int>::iterator sit1(sit);
		ft::set<int>::iterator fit1(fit);
		for (int i = 0; i < 5; ++i) {
			++sit1;
			++fit1;
		}
		s.erase(sit, sit1);
		f.erase(fit, fit1);
		printSets(s, f);
		getchar();
		std::cout << ".erase() using key value. lets erase values from -9 to - 3:" << std::endl;
		for (int i = -9; i <= -3; ++i) {
			s.erase(i);
			f.erase(i);
		}
		printSets(s, f);
		getchar();
	}

	std::cout << ".swap() . lets do new sets with values 100 - 120:" << std::endl;
	std::set<int> sSwap;
	ft::set<int> fSwap;
	for (int i = 100; i <= 120; ++i) {
		sSwap.insert(i);
		fSwap.insert(i);
	}
	printSets(sSwap, fSwap);
	std::cout << "Main sets before swapping:" << std::endl;
	printSets(s, f);
	getchar();
	s.swap(sSwap);
	f.swap(fSwap);
	std::cout << "After swap new sets:" << std::endl;
	printSets(sSwap, fSwap);
	std::cout << "After swap main sets:" << std::endl;
	printSets(s, f);

	// clear
	std::cout << ".clear(). Call .size() and .empty() before clear:" << std::endl;
	std::cout << ".size(): " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << ".empty(): " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	std::cout << "Call .size() and .empty() after clear:" << std::endl;
	s.clear();
	f.clear();
	std::cout << ".size(): " << blue << s.size() << " " << green << f.size() << def << std::endl;
	std::cout << ".empty(): " << blue << boolToString(s.empty()) << " " << green << boolToString(f.empty()) << def << std::endl;
	getchar();

	std::cout << "---Operations---" << std::endl;
	std::cout << "Fill set with new values 30 - 40" << std::endl;
	for (int i = 30; i <= 40; ++i) {
		s.insert(i);
		f.insert(i);
	}
	printSets(s, f);
	getchar();

	std::cout << ".find() using for loop 30 - 35:" << std::endl;
	for (int i = 30; i <= 35; ++i) {
		std::cout << ".find(" << i << "): " << blue << *s.find(i) << " " << green << *f.find(i) << def << std::endl;
	}
	getchar();
	std::cout << ".find() value out of set and check if == end()" << std::endl;
	std::cout << ".find(1000)" << blue << boolToString(s.find(1000) == s.end()) << " "
		<< green << boolToString(f.find(1000) == f.end()) << def << std::endl;

	std::cout << ".count() using for loop 35 - 50:" << std::endl;
	for (int i = 35; i <= 50; ++i) {
		std::cout << ".count(" << i << "): " << blue << s.count(i) << " " << green << f.count(i) << def << std::endl;
	}
	getchar();

	std::cout << "Our sets:" << std::endl;
	printSets(s, f);
	std::cout << ".lower_bound() with values 45, 20, 70" << std::endl
			  << "45: " << blue << *s.lower_bound(45) << " " << green << *f.lower_bound(45) << def << std::endl
			  << "20: " << blue << *s.lower_bound(20) << " " << green << *f.lower_bound(20) << def << std::endl
			  << "70: " << blue << *s.lower_bound(70) << " " << green << *f.lower_bound(70) << def << std::endl;
	getchar();

	std::cout << ".upper_bound() with values 0, 50, 67" << std::endl
			  << "0: " << blue << *s.upper_bound(0) << " " << green << *f.upper_bound(0) << def << std::endl
			  << "50: " << blue << *s.upper_bound(50) << " " << green << *f.upper_bound(50) << def << std::endl
			  << "67: " << blue << *s.upper_bound(67) << " " << green << *f.upper_bound(67) << def << std::endl;
	getchar();

	std::cout << ".equal_range() with values 40, 33" << std::endl;
	std::cout << blue << *s.equal_range(40).first << " - " << *s.equal_range(40).second
			  << " " << green << *f.equal_range(40).first << " - " << *f.equal_range(40).second << def << std::endl
			  << blue << *s.equal_range(33).first << " - " << *s.equal_range(33).second
			  << " " << green << *f.equal_range(33).first << " - " << *f.equal_range(33).second << def << std::endl;
}

int			main()
{
	Color::Modifier red(Color::FG_RED);
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier blue(Color::FG_BLUE);
	while (true) {
		std::string input;
		std::cout << blue << "Possible commands:\n" << green << "map vector stack list queue deque set exit\n" << blue << "Enter what you want to test:" << std::endl;
		std::getline(std::cin, input);
		if (input == "exit")
			break;
		else if (input == "stack") {
			std::cout << green << "Stack Test:" << def << std::endl;
			testStack();
		}
		else if (input == "list") {
			std::cout << green << "List Test:" << def << std::endl;
			testList();
		}
		else if (input == "vector") {
			std::cout << green << "Vector Test:" << def << std::endl;
			testVector();
		}
		else if (input == "queue") {
			std::cout << green << "Queue Test:" << def << std::endl;
			testQueue();
		}
		else if (input == "map") {
			std::cout << green << "Map Test:" << def << std::endl;
			testMap();
		}
		else if (input == "set") {
			std::cout << green << "Set Test:" << def << std::endl;
			testSet();
		}
		else if (input == "deque") {
			std::cout << green << "Deque Test:" << def << std::endl;
			testDeque();
		}
		else
			std::cout << red << "Oups, i don't know this command." << std::endl;
	}
	std::cout << red << "Have a nice day! Bye!" << std::endl;
	return 0;
}
