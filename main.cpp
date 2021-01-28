
#include <iostream>
//#include "list.hpp"
//#include <list>
#include "vector.hpp"
#include <vector>
//#include "map.hpp"
//#include "stack.hpp"
//#include "queue.hpp"

/*	LIST COMPILES	*/

//void ftList() {
//	ft::list<std::string> f;
//
//	f.push_back("LIST ");
//	f.push_back("compiles ");
//	f.push_back("successfully! ");
//	f.push_back("Go ");
//	f.push_back("check ");
//	f.push_back("unit ");
//	f.push_back("tests!");
//
//	ft::list<std::string>::iterator itf;
//	ft::list<std::string>::iterator itfe = f.end();
//	for (itf = f.begin(); itf != itfe; ++itf) {
//		std::cout << *itf;
//	}
//	std::cout << std::endl << std::endl;
//}
//
///*	VECTOR COMPILES	*/
//
//void ftVector() {
//	ft::vector<std::string> v;
//
//	v.push_back("VECTOR ");
//	v.push_back("compiles ");
//	v.push_back("successfully! ");
//	v.push_back("Go ");
//	v.push_back("check ");
//	v.push_back("unit ");
//	v.push_back("tests!");
//
//	ft::vector<std::string>::iterator itv;
//	ft::vector<std::string>::iterator itve = v.end();
//	for (itv = v.begin(); itv != itve; ++itv)
//	{
//		std::cout << *itv;
//	}
//	std::cout << std::endl << std::endl;
//}
//
///*	MAP COMPILES	*/
//
//void ftMap() {
//	ft::map<int, std::string> m;
//
//	m.insert(std::make_pair(1, "MAP "));
//	m.insert(std::make_pair(2, "compiles "));
//	m.insert(std::make_pair(3, "successfully! "));
//	m.insert(std::make_pair(4, "Go "));
//	m.insert(std::make_pair(5, "check "));
//	m.insert(std::make_pair(6, "unit "));
//	m.insert(std::make_pair(7, "tests!"));
//
//	ft::map<int, std::string>::iterator itm;
//	ft::map<int, std::string>::iterator itme = m.end();
//	for (itm = m.begin(); itm != itme; ++itm) {
//		std::cout << itm->second;
//	}
//	std::cout << std::endl << std::endl;
//}
//
///*	STACK COMPILES	*/
//
//void ftStack() {
//	ft::stack<std::string> s;
//
//	s.push("STACK ");
//	s.push("compiles ");
//	s.push("successfully! ");
//	s.push("Go ");
//	s.push("check ");
//	s.push("unit ");
//	s.push("tests!");
//
//	while (!s.empty()) {
//		std::cout << s.top();
//		s.pop();
//	}
//	std::cout << std::endl << std::endl;
//}
//
///*	QUEUE COMPILES	*/
//
//void ftQueue() {
//	ft::queue<std::string> q;
//
//	q.push("QUEUE ");
//	q.push("compiles ");
//	q.push("successfully! ");
//	q.push("Go ");
//	q.push("check ");
//	q.push("unit ");
//	q.push("tests!");
//
//	while (!q.empty()) {
//		std::cout << q.front();
//		q.pop();
//	}
//	std::cout << std::endl;
//}

int main()
{
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}
	std::cout << "iterator - 5 = " << *(f.end() - 5) << std::endl;
	std::cout << "iterator - 3 = " << *(f.end() - 3) << std::endl;
	f.insert(f.begin() + 1, f.end() - 5, f.end() - 3);
	s.insert(s.begin() + 1, s.end() - 5, s.end() - 3);
	for (ft::vector<int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	for (std::vector<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	return 0;
}
