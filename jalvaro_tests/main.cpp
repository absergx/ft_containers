/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvaro <jalvaro@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 20:15:42 by jalvaro           #+#    #+#             */
/*   Updated: 2020/09/21 10:55:03 by jalvaro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/map.hpp"
//#include "../srcs/vector.hpp"
//#include "../srcs/list.hpp"
//#include "../srcs/queue.hpp"
//#include "../srcs/stack.hpp"
#include "iostream"

#define RED "\033[1;31m"
#define GREEN "\033[1;33m"
#define RESET "\033[0m"

//int     list_test(void);
//int     vector_test(void);
int     map_test(void);
//int     stack_test(void);
//int     queue_test(void);

int     main(void) {

	int a;

	while (true)
	{
		std::cout << GREEN << "Выберите тест: " << RED << "1. list, \
2. Vector, 3. Map, 4. Stack, 5. Queue, 6. exit" << RESET << std::endl;
		std::cin >> a;
		if (a == 1)
			std::cout << "Skip list tests" << std::endl;
//			list_test();
		else if (a == 2)
			std::cout << "Skip vector tests" << std::endl;
//			vector_test();
		else if (a == 3)
//			std::cout << "Skip map tests" << std::endl;
			map_test();
		else if (a == 4)
			std::cout << "Skip stack tests" << std::endl;
//			stack_test();
		else if (a == 5)
			std::cout << "Skip queue tests" << std::endl;
//			queue_test();
		else if (a == 6)
			return (0);
		else
			continue;
	}
}