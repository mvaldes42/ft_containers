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

	ft::vector<int> vector_int_construct(2, 10);
	for (unsigned long int i = 0; i < vector_int_construct.size(); ++i)
		std::cout << i << ": " << vector_int_construct[i] << std::endl;

	vector_int_construct.push_back(10);
	vector_int_construct.push_back(10);
	vector_int_construct.push_back(10);
	vector_int_construct.push_back(10);
	for (unsigned long int i = 0; i < vector_int_construct.size(); ++i)
		std::cout << i << ": " << vector_int_construct[i] << std::endl;

	std::allocator<int>::reference ref = vector_int_construct.front();
	std::cout << "ref: " << ref << std::endl;
	ref = vector_int_construct.back();
	std::cout << "ref: " << ref << std::endl;
}