
#include <iostream>
//#include "list.hpp"
//#include <list>
//#include "vector.hpp"
//#include <vector>
#include "map.hpp"
#include <map>
//#include "stack.hpp"
//#include "queue.hpp"

int main()
{
	std::map<int, int> s;
	ft::map<int, int> f;

	for (int i = 0; i < 100; ++i)
		s.insert(std::pair<int, int>(i, i * 2));
//	s.insert(std::pair<int, int>(26, 10));
//	s.insert(std::pair<int, int>(24, 12));
//	s.insert(std::pair<int, int>(22, 14));
	std::cout << "std size: " << s.size() << std::endl;
	std::cout << "std: ";
	for (std::map<int, int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout << it->first << " ";
	std::cout << std::endl;
	std::cout << "std: ";
	std::map<int, int>::iterator itEnd = s.end();
	--itEnd;
	for (; itEnd != s.begin(); --itEnd)
		std::cout << itEnd->first << " ";
	std::cout << std::endl;
//	f.insert(std::pair<int, int>(26, 10));
//	f.insert(std::pair<int, int>(24, 12));
//	f.insert(std::pair<int, int>(22, 14));
	for (int i = 0; i < 100; ++i)
		f.insert(std::pair<int, int>(i, i * 2));
	std::cout << "ft size: " << f.size() << std::endl;
	std::cout << "ft : ";
//	ft::map<int, int>::iterator it1 = f.begin();
//	std::cout << it1->first << " ";
//	it1++;
//	std::cout << it1->first << " ";
//	it1++;
//	std::cout << it1->first << " ";
//	std::cout << std::endl;
//	std::cout << ((it1 == f.end()) ? "true" : "false");
	for (ft::map<int, int>::iterator it = f.begin(); it != f.end(); ++it)
		std::cout << it->first << " ";
	std::cout << std::endl;
	std::cout << "ft : ";
	ft::map<int, int>::iterator itEndF = f.end();
	itEndF--;
	for (; itEndF != f.begin(); --itEndF)
		std::cout << itEndF->first << " ";
	std::cout << std::endl;
//	ft::map<int, int>::iterator itEnd = f.end();
//	itEnd--;
//	std::cout << "end: " << itEnd->first << std::endl;
	return 0;
}
