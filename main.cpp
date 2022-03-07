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
			{ vectorTest.reserve(vectorTest.max_size() + 1); }
		catch (std::exception &e)
			{ std::cerr << "Length error: " << e.what() << std::endl; }
		// std::cout << vectorTest;

		// std::cout << "//// COPY CONSTRUCTOR //// " << std::endl;
		// ft::vector<int> vectorTest2(vectorTest);
		// vectorTest.erase(&vectorTest[0], &vectorTest[4]);
		std::cout << vectorTest;
		// std::cout << vectorTest2;

		std::cout << "front:: " << vectorTest.front() << std::endl;
		std::cout << "back:: " << vectorTest.back() << std::endl;
	
		std::cout << "result: " << ft::is_integral<int>::value << std::endl;

		typedef ft::vector<int>::iterator iter_type;
		iter_type begin(vectorTest.begin());
		ft::reverse_iterator<iter_type> rev_until(begin);
		std::cout << "rev it: " << *rev_until.base() << std::endl;
		ft::reverse_iterator<iter_type> rev_cp(rev_until);
		std::cout << "rev it copy: " << *rev_cp.base() << std::endl;
		ft::reverse_iterator<iter_type> rev_equals = rev_until;
		std::cout << "rev it equals: " << *rev_equals.base() << std::endl;
		std::cout << "rev it operator[0]: " << rev_equals[0] << std::endl;
		std::cout << "rev it operator[2]: " << rev_equals[2] << std::endl;
		std::cout << "rev it operator[-1]: " << rev_equals[-1] << std::endl;
		std::cout << rev_equals[2] << " < " << rev_equals[0] << " : " << (rev_equals[2] < rev_equals[0]) << std::endl;
		std::cout << rev_equals[2] << " == " << rev_equals[0] << " : " << (rev_equals[2] == rev_equals[0]) << std::endl;
		std::cout << rev_equals[2] << " != " << rev_equals[0] << " : " << (rev_equals[2] != rev_equals[0]) << std::endl;
		std::cout << vectorTest;
		// iter_type end(vectorTest.end());
		// ft::reverse_iterator<iter_type> rev_end(end);
		std::cout << "*begin: " << *begin << std::endl;
		begin++;
		std::cout << "*begin++: " << *begin << std::endl;
		begin--;
		std::cout << "*begin--: " << *begin << std::endl;
		++begin;
		std::cout << "*++begin: " << *begin << std::endl;
		std::cout << "*(begin + 2): " << *(begin + 2) << std::endl;
		std::cout << "*(begin - 1): " << *(begin - 1) << std::endl;
		begin += 3;
		std::cout << "*(begin += 3): " << *begin << std::endl;

	// 	std::cout << "rev_end[0]: " << *rev_end << "--" << " : " << (rev_end--) << std::endl;
	// 	std::cout << "rev_end[0]: " << *rev_end << "--" << " : " << (rev_end) << std::endl;
	}
}