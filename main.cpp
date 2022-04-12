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
		std::cout << "test[12]: " << test[12] << std::endl;

		typedef ft::map<int, char>::value_type pair_type;
		test.insert(pair_type(10, 'a'));
		test.insert(pair_type(30, 'b'));
		test.insert(pair_type(6, 'c'));
		test.insert(pair_type(5, 'd'));
		test.insert(pair_type(1, 'e'));
		test.insert(pair_type(90, 'f'));
		test.insert(pair_type(15, 'g'));
		test.insert(pair_type(14, 'i'));

		std::cout << "insert node 500: " << test.insert(pair_type(500, 'y')).second << std::endl;
		// std::cout << "insert node 500: " << test.insert(pair_type(500, 'y')).first.getNode() << std::endl;
		// std::cout << "test[6] parent : " << test.findNode(6, test._racine)->parent->dataPair.first << std::endl;
		// std::cout << "node is found : " << test.contains(node1, test._racine) << std::endl;
		// std::cout << "node is found : " << test.findNode(test.createNode(pair_type(90, 'f')), test._racine)->dataPair.second << std::endl;
		// std::cout << "node is found : " << test.findNode(90, test._racine)->dataPair.second << std::endl;
		// test.removeNode(node1);
		// std::cout << "removed node 90, f" << std::endl;
		// test.removeNode(node2);
		// test.removeNode(node3);
		// std::cout << "removed node 10, a" << std::endl;
		// test.removeNode(node4);
		// std::cout << "removed node 14, i" << std::endl;
		// test.removeNode(node5);

		// std::cout << "test[15] parent : " << test.findNode(15, test._racine)->parent->dataPair.first << std::endl;
		// std::cout << "test[6]: " << test[6] << std::endl;
		// test.printBT();

		// test.find(15);
		// test.find(30000);
		// std::cout << "occurence of key 15: " << test.count(15) << std::endl;
		// std::cout << "occurence of key 300000: " << test.count(300000) << std::endl;

		// std::cout << "Lowerbound of 100: " << test.lower_bound(100).getNode()->dataPair.first << std::endl;
		// std::cout << "Upperbound of 100: " << test.upper_bound(100).getNode()->dataPair.first << std::endl;

		// std::cout << "insert 80 near 30: " << test.insert(test.find(30), pair_type(80, 'd')).getNode()->dataPair.first << std::endl;
		// test.printBT();
		// ft::map<int, char>::iterator itera(test._racine);
		// std::cout << node3->dataPair.first << ", "<< itera->first << std::endl;
		// while (--itera != NULL)
		// {
		// 	std::cout << "--itera " << itera->first << std::endl;
		// }
		// std::cout << "First: " << test.getFirst()->dataPair.first << std::endl;
		// std::cout << "Last: " << test.getLast()->dataPair.first << std::endl;

		ft::map<int, char>::iterator last = test.begin();
		while(last != test.end())
		{
			std::cout << "last++: " << (last++)->first << std::endl;
		}
		last = test.end();
		last--;
		while(last != test.begin())
		{
			std::cout << "last--: " << (last--)->first << std::endl;
		}
		// try
		// {
		// 	ft::map<int, char> test2;
		// 	ft::map<int, char>::iterator firstSecond = test2.end();
		// 	while(firstSecond-- != NULL)
		// 	{
		// 		std::cout << "-- end " << firstSecond->first << std::endl;
		// 	}
		// }
		// catch (const std::exception& e)
		// {
		// 	std::cout << "Error : " << e.what() << std::endl;
		// }

		// test.clear();
		// test.removeNode(test._racine);
		// test.removeNode(test._racine);
		test.printBT();
		// std::cout << (node2)->dataPair.first << std::endl;
		// std::cout << test._racine->dataPair.first<< std::endl;
		// std::cout << "nb nodes: " << test.size() << std::endl;

		// ft::map<int, char> testCopy(test);
		// testCopy.erase(90);
		// testCopy.insert(pair_type(80, 'f'));
		// // testCopy.insert(pair_type(400, 'y'));
		// testCopy.printBT();

		// std::cout << "does (testCopy < test)? " << (test > testCopy) << std::endl;

		// ft::map<int, char> testPartCopy(test.begin(), test.find(15));
		// testPartCopy.printBT();
		// testCopy = testPartCopy;
		// testCopy.printBT();
		std::cout << std::endl << "////////DESTRUCTOR/////////" << std::endl << std::endl;
	}
}