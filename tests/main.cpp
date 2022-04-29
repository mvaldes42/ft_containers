#include "../vector.hpp"
#include "../stack.hpp"
#include <vector>
#include <list>
#include <map>
#include "../map.hpp"


/* 	Thanks flosh for the test files <3
	This is a public member function, created for the correction.
	It is based on the answer from @Adrian Schneider :
	https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
	This has to be a public member function since it needs access to the private _root
	
	It is a great way to visualize the tree and it's balanced structure.
	It works best for perfectly balanced trees, 
	with a node total number of 3, 15, 63, 255, 511... ((powers of 2) - 1) */
/*
public :
void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
	if( node && node != _last )
	{
		usleep(125000);
		std::cout << prefix;

		std::cout << (isLeft ? "├──" : "└──" );

		// print the value of the node
		std::cout << node->data.first << std::endl;

		// enter the next tree level - left and right branch
		printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
		printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
	}
}

void printBT()
{
	printBT("", _root, false);    
}
*/
/*	printBT end	*/



int		main()
{

	return (0);
}
