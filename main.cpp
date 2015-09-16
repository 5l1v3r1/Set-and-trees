#include "bst_tester.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{	
	BSTTester test;
	
	cout.setf(ios::boolalpha);
	cout << "Test is_BST : " << test.test_is_bst() << endl;
	cout << "Test max_level : " << test.test_max_level() << endl;
	cout << "Test max_value : " << test.test_max_value() << endl;
	cout << "Test min_value : " << test.test_min_value() << endl;
	cout << "Test delete_node : " << test.test_delete() << endl;
	cout << "Test count_add : " << test.test_count_add() << endl;
	cout << "Test count_sub : " << test.test_count_sub() << endl;
	
	cout << endl;
	
	test.print_tree();
	
	cout << endl;
	
	test.print_random_tree();
		
	return 0;
}