#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <algorithm>
#include "node.hpp"

template <class T>
class BinaryTree
{
	public:
		explicit BinaryTree<T>();
		BinaryTree<T>(const BinaryTree<T> &) = delete;
		BinaryTree<T>& operator=(const BinaryTree<T> &) = delete;
		~BinaryTree<T>();
		
		inline const Node<T>* min() const;
		inline const Node<T>* max() const;
		inline void insert(const T&);
		inline Node<T>* search(const T&) const;
		inline void destroy_tree();
		inline void print_tree() const;
		inline int max_level() const;
		
		inline void delete_node(const T&);
		
		constexpr const Node<T>* tree_root() const;
		
	private:
		inline Node<T>* max_subtree(Node<T>*) const;
		inline Node<T>* min_subtree(Node<T>*) const;
		inline Node<T>* delete_node(Node<T>*, const T&);
		inline int max_level(const Node<T>*) const;
		inline void destroy_tree(Node<T>*);
		inline Node<T>* insert(Node<T> *, const T&);
		inline Node<T>* search(Node<T> *, const T&) const;
		inline void print_tree(const Node<T> *, std::string, bool) const;
		
		Node<T>* root;
};

template <class T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

//Returns the root of the tree

template <class T>
constexpr const Node<T>* BinaryTree<T>::tree_root() const
{
	return root;
}

//Public interface to destroy entire tree

template <class T>
inline void BinaryTree<T>::destroy_tree()
{
	destroy_tree(root); //Destroy at the root
}

template <class T>
inline void BinaryTree<T>::destroy_tree(Node<T>* leaf)
{
	if(leaf != nullptr) //Check if we don't reach the end of a branch
	{
		destroy_tree(leaf->left_leaf()); //Destroy the left leaf
		destroy_tree(leaf->right_leaf()); //Destroy the right leaf
		delete leaf;
	}
}

template <class T>
inline const Node<T>* BinaryTree<T>::min() const
{
	return min_subtree(root); //Return the lowest value of the tree
}


//Get the smallest node starting from arbitary node
template <class T>
inline Node<T>* BinaryTree<T>::min_subtree(Node<T> *current) const
{
	while(current->left_leaf() != nullptr)
		current = current->left_leaf(); //Iterate through left branch
	
	return current;
}

template <class T>
inline const Node<T>* BinaryTree<T>::max() const
{
	return max_subtree(root); //Return highest value
}

//Get the highest node starting from arbitrary node

template <class T>
inline Node<T>* BinaryTree<T>::max_subtree(Node<T> *current) const
{	
	while(current->right_leaf() != nullptr) //Iterate through right branch
		current = current->right_leaf();
	
	return current;
}

//Helper public method to look for a key

template <class T>
inline Node<T>* BinaryTree<T>::search(const T &key) const
{
	return search(root, key);
}

//Look for any subtree with leaf as root

template <class T>
inline Node<T>* BinaryTree<T>::search(Node<T> *leaf, const T &key) const
{
	if(leaf == nullptr || leaf->key_value() == key) //Reached the end or
		return leaf;								//Found the key, return node
	
	if(leaf->key_value() < key) //Search right leaf for highest values
		return search(leaf->right_leaf(), key);
	
	return search(leaf->left_leaf(), key); //Lowest value, check left leaf
}

//Helper method to insert a key

template <class T>
inline void BinaryTree<T>::insert(const T &key)
{
	Node<T>* to_add = search(key); //Check if key is already there
	
	if(to_add != nullptr)
		(*to_add)++; //Increment the count for duplicates
	
	else
		root = insert(root, key); //Insert value 
}

template <class T>
inline Node<T>* BinaryTree<T>::insert(Node<T> *leaf, const T &key)
{
	if(leaf == nullptr) //Reach the end of branch, add key
		return new Node<T>(key);
	
	if(key < leaf->key_value()) //Lowest values go left
		leaf->change_left(insert(leaf->left_leaf(), key));
	
	else if(key >= leaf->key_value()) //Highest values go right
		leaf->change_right(insert(leaf->right_leaf(), key));
	
	return leaf; //Return the changed node
}

//Get the height of the tree

template <class T>
inline int BinaryTree<T>::max_level() const
{
	return max_level(root);
}

template <class T>
inline int BinaryTree<T>::max_level(const Node<T> *node) const
{
	if(node == nullptr) //No subtree
		return 0;
	
	return std::max(max_level(node->left_leaf()), max_level(node->right_leaf())) + 1;
}

//Print the tree, inspired by Unix's tree command

template <class T>
inline void BinaryTree<T>::print_tree(const Node<T> *node, std::string prefix, bool is_tail) const
{
	if(node == nullptr) //Don't print anything
		return;
	
	std::cout << prefix + (is_tail ? "└── " : "├── ") + std::to_string(node->key_value()) 
			  << " (" << std::to_string(node->key_count()) << ")" << std::endl;
	
	print_tree(node->right_leaf(), prefix + (is_tail ? "    " : "│   "), false);
	print_tree(node->left_leaf(), prefix + (is_tail ? "    " : "│   "), true);
}

template <class T>
inline void BinaryTree<T>::print_tree() const
{
	print_tree(root, "", true);
}

//Delete node with said key

template <class T>
inline void BinaryTree<T>::delete_node(const T& key)
{
	if(search(key) == nullptr)
		return;
	
	root = delete_node(root, key);
}

template <class T>
inline Node<T>* BinaryTree<T>::delete_node(Node<T> *node, const T& key)
{
	if(node == nullptr)
		return node;
	
	if(key < node->key_value())
		node->change_left(delete_node(node->left_leaf(), key));
	
	else if(key > node->key_value())
		node->change_right(delete_node(node->right_leaf(), key));
	
	else
	{
		if(node->key_count() > 1)
		{
			(*node)--;
			return node;
		}
		
		if(node->left_leaf() == nullptr)
		{
			Node<T> *temp = node->left_leaf();
			delete node;
			return temp;
		}
		
		else if(node->right_leaf() == nullptr)
		{
			Node<T> *temp = node->right_leaf();
			delete node;
			return temp;
		}
		
		Node<T>* temp = min_subtree(node->right_leaf());
		
		node->set_key(temp->key_value());
		
		node->change_right(delete_node(node->right_leaf(), temp->key_value()));
	}
	
	return node;
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
	destroy_tree();
}

#endif