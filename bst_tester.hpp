#ifndef BST_TESTER
#define BST_TESTER

#include "binary_tree.hpp"
#include <limits>
#include <random>

class BSTTester
{
	public :
		bool test_is_bst() const;
		bool test_max_level() const;
		bool test_max_value() const;
		bool test_min_value() const;
		bool test_delete() const;
		bool test_count_add() const;
		bool test_count_sub() const;
		void print_tree() const;
		
	private:
		template <class T> bool test_is_bst(const Node<T>*	, const T&, const T&) const;
};

bool BSTTester::test_is_bst() const
{
	BinaryTree<int> bin_tree;
	bin_tree.insert(4);
	bin_tree.insert(2);
	bin_tree.insert(5);
	bin_tree.insert(1);
	bin_tree.insert(3);

	return test_is_bst(bin_tree.tree_root(), std::numeric_limits<int>::min(),
											 std::numeric_limits<int>::max());	
}

template <class T>
bool BSTTester::test_is_bst(const Node<T> * const node, const T& min, const T& max) const
{
	if(node == nullptr)
		return true;
	
	if(node->key_value() < min || node->key_value() > max)
		return false;
	
	return 
		test_is_bst(node->left_leaf(), min, node->key_value() - 1) &&
		test_is_bst(node->right_leaf(), node->key_value() + 1, max);
}

bool BSTTester::test_max_level() const
{
	BinaryTree<int> bin_tree;
	bin_tree.insert(4);
	bin_tree.insert(2);
	bin_tree.insert(5);
	bin_tree.insert(1);
	bin_tree.insert(3);
	
	return bin_tree.max_level() == 3;
}

void BSTTester::print_tree() const
{
	BinaryTree<int> bin_tree;
	bin_tree.insert(4);
	bin_tree.insert(2);
	bin_tree.insert(5);
	bin_tree.insert(1);
	bin_tree.insert(3);
	
	bin_tree.print_tree();
}

bool BSTTester::test_max_value() const
{
	BinaryTree<int> bin_tree;
	bin_tree.insert(4);
	bin_tree.insert(2);
	bin_tree.insert(5);
	bin_tree.insert(1);
	bin_tree.insert(3);
	
	std::cout << std::to_string(bin_tree.max()->key_value()) << std::endl;
	
	return bin_tree.max()->key_value() == 5;
}

bool BSTTester::test_min_value() const
{
	BinaryTree<int> bin_tree;
	bin_tree.insert(4);
	bin_tree.insert(2);
	bin_tree.insert(5);
	bin_tree.insert(1);
	bin_tree.insert(3);
	
	std::cout << std::to_string(bin_tree.min()->key_value()) << std::endl;
	
	return bin_tree.min()->key_value() == 1;
}

bool BSTTester::test_delete() const
{
	BinaryTree<int> bin_tree;
	bin_tree.insert(4);
	bin_tree.insert(2);
	bin_tree.insert(5);
	bin_tree.insert(1);
	bin_tree.insert(3);
	
	bin_tree.delete_node(4);
	
	return bin_tree.search(4) == nullptr;
}

bool BSTTester::test_count_add() const
{
	BinaryTree<int> bin_tree;
	bin_tree.insert(4);
	bin_tree.insert(2);
	bin_tree.insert(5);
	bin_tree.insert(1);
	bin_tree.insert(3);
	bin_tree.insert(4);
		
	return bin_tree.search(4)->key_count() == 2;
}

bool BSTTester::test_count_sub() const
{
	BinaryTree<int> bin_tree;
	bin_tree.insert(4);
	bin_tree.insert(2);
	bin_tree.insert(5);
	bin_tree.insert(1);
	bin_tree.insert(3);
	bin_tree.insert(4);
	
	bin_tree.delete_node(4);
	
	return bin_tree.search(4)->key_count() == 1;
}

#endif