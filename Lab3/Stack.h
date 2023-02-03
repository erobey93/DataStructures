#pragma once
#include <iostream>
#include <string>

#include "list.h"
#include "node.h"

template<typename T>
class Stack
{
public:
	Stack();
	//Stack(const T data); 
	Stack(const Stack& copy);
	Stack(Stack&& move) noexcept;
	~Stack();

	Stack& operator=(const Stack& copy);
	Stack& operator=(Stack&& move) noexcept;

	void Push(const T data);
	T Pop();
	T Peek() const;
	bool isEmpty() const;
	bool isFull() const;
	int getNumElements() const;

private:
	List<T> m_stack;
	int num_elements;
	const int max = 10;//max elements = 10  
};
template <typename T>
Stack<T>::Stack() : m_stack(), num_elements(0) { }

template <typename T>
Stack<T>::Stack(const Stack& copy) : num_elements(copy.num_elements)//base member initialization 
{
	m_stack = copy.m_stack; //should call list copy assign
}
template <typename T>
Stack<T>::Stack(Stack&& move) noexcept : m_stack(move.m_stack),  num_elements(move.num_elements)// base member initialization with move.dataMembers
{
}
template <typename T>
Stack<T>::~Stack()
{
	//reset num_elements; 
	num_elements = 0; 
	//destroy stack should all happen in list
}
template <typename T>
Stack<T> &Stack<T>::operator=(const Stack& copy)
{
	num_elements = copy.num_elements;
	m_stack = copy.m_stack; 

	return *this; 
}
template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& move) noexcept
{
	num_elements = move.num_elements;
	m_stack = move.m_stack; 

	return *this; 
}
template <typename T>
void Stack<T>:: Push(const T data)
{
	Exception Overflow("Overflow Push");

	//OverFlow exception
	//if empty 
	if (getNumElements() >= max)
	{
		throw Overflow;
	}
	//if not empty 
	else
	//if not full 
	{
		m_stack.Prepend(data); //add to top of list 
		num_elements++; //increment num_elements 
	}
	
}
template <typename T>
T Stack<T>::Pop()
{
	Exception Underflow("Underflow Pop");

	//Underflow exception
	//if empty 
	if (!m_stack.l_head)
	{
		throw Underflow;
	}
	//if not empty 
	else
	{
		T var = m_stack.l_head -> n_data; 
		m_stack.RemoveFirst();//remove head
		num_elements --; //decrement num_elements
		return var; 
	}
}
template <typename T>
T Stack<T>::Peek() const
{	
	Exception Underflow("Underflow Peek");

	//Underflow exception
	//if empty 
	if (!m_stack.l_head)
	{
		throw Underflow;
	}
	//if not empty 
	else
	{
		return m_stack.l_head -> n_data;
	}
	
}
template <typename T>
bool Stack<T>::isEmpty() const
{
	// return list isEmpty 
	return m_stack.isEmpty(); 

}
template <typename T>
bool Stack<T>::isFull() const
{
	if (num_elements == max)
	{
		return true;
	}
	else
	{
		return false; 
	}
}
template <typename T>
int Stack<T>::getNumElements() const
{
	return num_elements; 
}
