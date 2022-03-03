#include "vector.hpp"

#include <iostream>
#include <vector>


#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

int main()
{
	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::vector<Buffer> vector_buffer;

	ft::vector<int> vectorTest(2, 10);
	std::cout << vectorTest;

	vectorTest.push_back(6);
	vectorTest.push_back(8000);
	vectorTest.push_back(600);
	vectorTest.push_back(5);
	std::cout << "push_back:: " << vectorTest;

	vectorTest.erase(&vectorTest[1]);
	std::cout << "erase:: " << vectorTest;

	vectorTest.insert(&vectorTest[1], 3);
	std::cout << "insert 3 at pos 1:: " << vectorTest;

	std::allocator<int>::reference ref = vectorTest.front();
	std::cout << "front:: " << ref << std::endl;
	ref = vectorTest.back();
	std::cout << "back:: " << ref << std::endl;
}