// Name: Emily Robey 
// Assignment: Lab 1

#ifndef ARRAYTEMPLATE_H
#define ARRAYTEMPLATE_H

#include <iostream>
#include <string>
#include "Exception.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

template <typename T>
class Array {
private:
	T* m_array; //dynamic array of type T
	int m_start_index; //can be any numerical value that makes sense to user 
	int m_length; //number of data members in array 
	int m_newArray; //keep track of the number of arrays there are

public:
	Array() : m_array(nullptr), m_start_index(0), m_length(0) {};	//default constructor
	Array(int length, int start_index = 0);							//constructor
	Array(const Array<T>& copy);									//copy constructor
	Array(Array<T>&& move) noexcept;								//move constructor

	~Array();										//destructor

	Array<T>& operator = (const Array<T>& copy);	//overloaded copy assignment operator 
	Array<T>& operator = (Array<T>&& move) noexcept;	//overloaded move assignment operator
	T& operator [] (const int);						//overloaded subscript operator

	const int getStartIndex();						//gets start index
	void setStartIndex(const int start_index);		//sets start index
	const int getLength();							//gets length of array
	void setLength(int length);						//sets length of array
};

template<typename T>
Array<T>::Array(int length, int start_index) : m_length(length), m_start_index(start_index), m_newArray(0)
{
	m_array = new T [length];

}

template<typename T>
Array<T>::Array(const Array<T>& copy) :m_length(copy.m_length), m_start_index(copy.m_start_index), m_newArray(copy.m_newArray), m_array(nullptr)
{
	if (m_array != copy.m_array) //check for duplicate 
	{ 
		//create appropriate length array 
		m_array = new T[copy.m_length]; 
		//copy each element
		for (int i = 0; i < copy.m_length; i++)
		{
			m_array[i] = copy.m_array[i];
		}
	}


}

template<typename T>
Array<T>::Array(Array<T>&& move) noexcept
{
	if (move.m_array != m_array) //check for duplicate
	{
		//move
		m_array = move.m_array;
		move.m_array = nullptr;
		m_length = move.m_length;
		move.m_length = 0;
		m_start_index = move.m_start_index;
		move.m_start_index = 0;
	}

}

template<typename T>
Array<T>::~Array()
{
	// if not null delete entire array 
	if (m_array)
	{
		delete[] m_array; 
	}
	m_length = 0; 
	m_start_index = 0; 
	m_array = nullptr;

}

template<typename T>
Array<T>& Array<T>::operator = (const Array<T>& copy)
{
	if (this != &copy)//check for duplicate
	{
		if (m_array != nullptr)//check for populated m_array
		{
			delete[] m_array; //delete data
		}
		//copy
			m_array = new T[copy.m_length];
			//copy each element
			for (int i = 0; i < copy.m_length; i++)
			{
				m_array[i] = copy.m_array[i];
			}
			m_length = copy.m_length; 
	}
	return *this; 
}

template<typename T>
Array<T>& Array<T>::operator = (Array<T>&& move) noexcept
{
	if (&move != this) //check for duplicate
	{
		if (m_array != nullptr) //check for populated m_array
		{
			delete[] m_array; //delete data
		}
		//move
		m_array = move.m_array;
		m_length = move.m_length;
		move.m_length = 0;
		m_start_index = move.m_start_index;
		move.m_start_index = 0;
		move.m_array = nullptr;
	}
	return *this; 
}

template<typename T>
T& Array<T>::operator [] (const int index)
{
	int zero_based_index = index - m_start_index; //start_index can start at any number the user desires so this accounts for that 
	//check for -index and index>available elements
	Exception out_of_range; 
	if (abs(zero_based_index) >  (m_length - 1) )//|| zero_based_index < 0 ) //--> fixed after I saw that negative starting index is allowed
	{
		throw out_of_range; 
	}
	else
	{ 
		return m_array[zero_based_index]; //if all checks passes return data at appropriate index 
	}
}
template<typename T>
const int Array<T>::getStartIndex()
{
	return m_start_index; 
}

template<typename T>
void Array<T>::setStartIndex(const int start_index)
{

		m_start_index = start_index;

}

template<typename T>
const int Array<T>::getLength()
{
	return m_length; 
}

template<typename T>
void Array<T>::setLength(int length)
{
	//check for -length value
	Exception out_of_range;
	if (length < 0)
	{
		throw out_of_range;
	}
	//create a new array of user's length
	T* newArray = new T[length];
	for (int i = 0; i < m_length; i++)
	{
		//catch length < m_length
		if (i == length)
		{
			break;
		}
		newArray[i] = m_array[i]; //save m_array to newArray 
	}
	m_length = length; //reset m_length
	delete[] m_array; //clean up! 
	m_array = newArray; //reset m_array 
}

#endif //ARRAY_TEMPLATE_H


