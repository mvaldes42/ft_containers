#include "vector.hpp"
#include "utils.hpp"

#include <iostream>
#include <vector>


// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };

int main()
{
	{
		// ft::vector<std::string> vector_str;
		// ft::vector<int> vector_int;
		// ft::vector<Buffer> vector_buffer;

		ft::vector<int> vectorTest(1, 1);
		// std::cout << vectorTest;

		vectorTest.push_back(2);
		vectorTest.push_back(3);
		vectorTest.push_back(4);
		vectorTest.push_back(5);
		// std::cout << vectorTest;

		vectorTest.erase(vectorTest.begin() + 1);
		// std::cout << vectorTest;

		vectorTest.insert(vectorTest.begin() + 1, 2);
		// std::cout << vectorTest;

		vectorTest.insert(vectorTest.end(), 10, 0);
		// std::cout << vectorTest;
		vectorTest.insert(vectorTest.begin(), 10, 9);
		// std::cout << vectorTest;

		std::cout << "//// ERASE FIRST LAST //// " << std::endl;
		vectorTest.erase(vectorTest.begin(), vectorTest.begin() + 10);
		// std::cout << vectorTest;

		vectorTest.erase(vectorTest.end() - 10, vectorTest.end());
		// std::cout << vectorTest;

		vectorTest.pop_back();
		// std::cout << vectorTest;

		vectorTest.resize(10, 9);
		// std::cout << vectorTest;

		// std::cout << "max size: " << vectorTest.max_size() << std::endl;
		try
			{ vectorTest.resize(vectorTest.max_size() + 1); }
		catch (std::exception &e)
			{ std::cerr << "Length error: " << e.what() << std::endl; }
		try
			{ vectorTest.reserve(vectorTest.max_size()); }
		catch (std::exception &e)
			{ std::cerr << "Length error: " << e.what() << std::endl; }
		// std::cout << vectorTest;

		// std::cout << "//// COPY CONSTRUCTOR //// " << std::endl;
		// ft::vector<int> vectorTest2(vectorTest);
		// vectorTest.erase(&vectorTest[0], &vectorTest[4]);
		// std::cout << vectorTest;
		// std::cout << vectorTest2;

		std::allocator<int>::reference ref = vectorTest.front();
		std::cout << "front:: " << ref << std::endl;
		ref = vectorTest.back();
		std::cout << "back:: " << ref << std::endl;
	
		std::cout << "result: " << ft::is_integral<int>::value << std::endl;

		typedef ft::vector<int>::iterator iter_type;
		iter_type begin(vectorTest.begin());
		ft::reverse_iterator<iter_type> rev_until(begin);
		std::cout << "rev it: " << *rev_until.base() << std::endl;
		// std::reverse_iterator<> rev_it;
	}
}