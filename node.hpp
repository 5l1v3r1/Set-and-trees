#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <iostream>

template<class T>
class Node
{
	public:
			Node(const T&);
			inline Node<T>* left_leaf() const;
			inline Node<T>* right_leaf() const;
			inline T key_value() const;
			inline int key_count() const;
			
			inline void create_left(const T&);
			inline void create_right(const T&);
			inline void change_right(Node<T>*);
			inline void change_left(Node<T>*);
			
			inline void set_key(const T&);
			
			Node<T> operator++(int);
			Node<T> operator--(int);
			Node<T>& operator++();
			Node<T>& operator--();
	private:
		Node<T>* left;
		Node<T>* right;
	
		int count;
	
		T key;
};

template <class T> 
Node<T>::Node(const T &_key) : key(_key),
			left(nullptr),
			right(nullptr),
			count(1)
{
}

template <class T>
inline T Node<T>::key_value() const
{
	return key;
}

template <class T>
inline int Node<T>::key_count() const
{
	return count;
}

template <class T>
inline void Node<T>::set_key(const T &_key)
{
	key = _key;
}

template <class T>
inline Node<T>* Node<T>::left_leaf() const
{
	return left;
}

template <class T>
inline Node<T>* Node<T>::right_leaf() const
{
	return right;
}

template <class T>
inline void Node<T>::create_left(const T &key)
{
	left = new Node<T>(key);
}

template <class T>
inline void Node<T>::create_right(const T &key)
{
	right = new Node<T>(key);
}

template <class T>
inline void Node<T>::change_left(Node<T> *new_node)
{
	left = new_node;
}

template <class T>
inline void Node<T>::change_right(Node<T> *new_node)
{
	right = new_node;
}

template <class T>
Node<T> Node<T>::operator++(int)
{
	Node<T> tmp(*this);
	operator++();
	return tmp;
}

template <class T>
Node<T>& Node<T>::operator++()
{
	count++;
	return *this;
}

template <class T>
Node<T> Node<T>::operator--(int)
{
	Node<T> tmp(*this);
	operator--();
	return tmp;
}

template <class T>
Node<T>& Node<T>::operator--()
{
	count--;
	return *this;
}

#endif