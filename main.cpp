#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"

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

		// ft::vector<int> vectorTest(1, 1);
		// std::cout << vectorTest;

		// vectorTest.push_back(2);
		// vectorTest.push_back(3);
		// vectorTest.push_back(4);
		// vectorTest.push_back(5);
		// std::cout << vectorTest;

		// vectorTest.erase(vectorTest.begin() + 1);
		// // std::cout << vectorTest;

		// vectorTest.insert(vectorTest.begin() + 1, 2);
		// // std::cout << vectorTest;

		// vectorTest.insert(vectorTest.end(), 10, 0);
		// // std::cout << vectorTest;
		// vectorTest.insert(vectorTest.begin(), 10, 9);
		// std::cout << vectorTest;

		// std::cout << "//// ERASE FIRST LAST //// " << std::endl;
		// vectorTest.erase(vectorTest.begin(), vectorTest.begin() + 10);
		// // std::cout << vectorTest;

		// vectorTest.erase(vectorTest.end() - 10, vectorTest.end());
		// // std::cout << vectorTest;

		// vectorTest.pop_back();
		// // std::cout << vectorTest;

		// vectorTest.resize(10, 9);
		// // std::cout << vectorTest;

		// // std::cout << "max size: " << vectorTest.max_size() << std::endl;
		// try
		// 	{ vectorTest.resize(vectorTest.max_size() + 1); }
		// catch (std::exception &e)
		// 	{ std::cerr << "Length error: " << e.what() << std::endl; }
		// try
		// 	{ vectorTest.reserve(vectorTest.max_size() + 1); }
		// catch (std::exception &e)
		// 	{ std::cerr << "Length error: " << e.what() << std::endl; }
		// // std::cout << vectorTest;

		// std::cout << "//// COPY CONSTRUCTOR //// " << std::endl;
		// ft::vector<int> vectorTest2(vectorTest);
		// vectorTest.erase(&vectorTest[0], &vectorTest[1]);
		// std::cout << vectorTest;
		// std::cout << vectorTest2;
		// vectorTest.assign(2, 1);
		// std::cout << vectorTest;

		// std::cout << "front:: " << vectorTest.front() << std::endl;
		// std::cout << "back:: " << vectorTest.back() << std::endl;
	
		// std::cout << "is_integral<int>: " << ft::is_integral<int>::value << std::endl;
		// std::cout << "is_integral<std::string>: " << ft::is_integral<std::string>::value << std::endl;

		// std::cout << vectorTest;
		
		// typedef ft::vector<int>::iterator iter_type;
		// ft::reverse_iterator<iter_type> rbegin = vectorTest.rbegin();
		// ft::reverse_iterator<iter_type> rend = vectorTest.rend();

		// std::cout << "rbegin: " << *rbegin << std::endl;
		// std::cout << "rend: " << *rend << std::endl;
	
		// ft::reverse_iterator<iter_type> revit_copy(rbegin);
		// std::cout << "revit_copy(rbegin): " << *revit_copy << std::endl;
		// ft::reverse_iterator<iter_type> rev_equals = rbegin;
		// std::cout << "rev_equals = rbegin: " << *rev_equals << std::endl;
		// std::cout << "rend[-1]: " << rend[-1] << std::endl;
		// std::cout << "rend[-2]: " << rend[-2] << std::endl;
		// std::cout << "rend[-4]: " << rend[-4] << std::endl;
		// std::cout << rbegin[0] << " < " << rbegin[6] << " : " << (rbegin[0] < rbegin[6]) << std::endl;
		// std::cout << rbegin[0] << " == " << rbegin[6] << " : " << (rbegin[0] == rbegin[6]) << std::endl;
		// std::cout << rbegin[0] << " != " << rbegin[6] << " : " << (rbegin[0] != rbegin[6]) << std::endl;
	
		// std::cout << "*rend: " << *rend << std::endl;
		// rend--;
		// std::cout << "*rend--: " << *rend << std::endl;
		// rend -= 3;
		// std::cout << "*rend -= 3: " << *rend << std::endl;
		// rend++;
		// std::cout << "*rend++: " << *rend << std::endl;
		// ++rend;
		// std::cout << "*++rend: " << *rend << std::endl;
		// std::cout << "*(rend - 2): " << *(rend - 2) << std::endl;
		// std::cout << "*(rend + 1): " << *(rend + 1) << std::endl;
		// rend += 1;
		// std::cout << "*(rend += 1): " << *rend << std::endl;
		ft::map<int, char> test;
		std::cout << "test[6]: " << test[6] << std::endl;

		// test.prefix(test._racine);
		typedef ft::map<int, char>::value_type pair_type;
		pair_type pairTest(10, 'a');
		ft::map<int, char>::node_type *node3 = test.createNode(pairTest);
		(void)node3;
		// std::cout << "cool" << std::endl;
		test.insertNode(node3, test._racine);
		std::cout << "super" << std::endl;

		ft::map<int, char>::node_type *node2 = test.createNode(pair_type(30, 'b'));
		test.insertNode(node2, test._racine);
		test.insertNode(test.createNode(pair_type(6, 'c')), test._racine);
		test.insertNode(test.createNode(pair_type(5, 'd')), test._racine);
		test.insertNode(test.createNode(pair_type(3, 'e')), test._racine);
		ft::map<int, char>::node_type *node1 = test.createNode(pair_type(90, 'f'));
		test.insertNode(node1, test._racine);
		test.insertNode(test.createNode(pair_type(15, 'g')), test._racine);
		// test.insertNode(test.createNode(pair_type(15, 'h')), test._racine);
		test.insertNode(test.createNode(pair_type(14, 'i')), test._racine);

		std::cout << "node is found : " << test.contains(node1, test._racine) << std::endl;
		std::cout << "node is found : " << test.findNode(test.createNode(pair_type(90, 'f')), test._racine)->dataPair.second << std::endl;
		std::cout << "node is found : " << test.findNode(90, test._racine)->dataPair.second << std::endl;
		// test.removeNode(node1, test._racine);
		// std::cout << "removed node 90, f" << std::endl;

		test.printBT();
		std::cout << "removed node 10, a" << std::endl;
		test.removeNode(node1, test._racine);
		test.printBT();
		std::cout << "test[6]: " << test[6] << std::endl;
		test.printBT();
		std::cout << "nb nodes: " << test.size() << std::endl;
	}
}