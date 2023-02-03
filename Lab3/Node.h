// Emily Robey
//CST 211 - Lab 3 - Stack
//Node Class 

#ifndef NODETEMPLATE_H
#define NODETEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::move; 
using std::copy; 

template<typename T>class Node {

private:
    T n_data;
    Node<T>* next_ptr;
    Node<T>* prev_ptr;

    template<typename U>friend class List;
public:
    Node();
    Node(const Node& copy);
    Node(Node&& move) noexcept;
    Node(const T data);
    Node(const T data, Node<T>* next, Node<T>* prev);
    ~Node() = default; //what is default? --> tells the compiler to indpendently general the corresponding class function, if one is not declared in the class (so basically dtor of whatever data type is in node?)

    Node<T>& operator=(const Node& copy);
    Node<T>& operator=(Node&& copy) noexcept;//noexcept reminder --> basically not allowed to throw exceptions, why? --> first and foremost about semantics with some incidental optimization gains, best improvements on big four functions, most obvious in C++ libraries. 

    T& Value() noexcept;
    T Value() const noexcept;
    void Value(const T data);

    Node<T>* Next() noexcept;
    Node<T>* Next() const noexcept;
    Node<T>* Previous() noexcept;
    Node<T>* Previous() const noexcept;
    void Next(Node<T>* const next) noexcept;
    void Previous(Node<T>* const previous) noexcept;

    template <typename U> friend class List;
    template <typename U> friend class Stack; 
};

template<typename T>
Node<T>::Node() : n_data(0), next_ptr(nullptr), prev_ptr(nullptr) {
}

template <typename T>
Node<T>::Node(const T data)
    : n_data(data)
{
}

template <typename T>
Node<T>::Node(const Node& copy)
{
        n_data = copy.n_data;
        next_ptr = copy.next_ptr;
        prev_ptr = copy.prev_ptr;
}

template <typename T>
Node<T>::Node(Node&& move) noexcept : n_data(move.n_data), next_ptr(move.next_ptr), prev_ptr(move.prev_ptr)
{
    if (this != &move)
    {
        move.n_data = 0;
        move.next_ptr = nullptr;
        move.prev_ptr = nullptr;
    }
}

template <typename T>
Node<T>::Node(const T data, Node<T>* next, Node<T>* prev)
{
    n_data = data;
    next_ptr = next;
    prev_ptr = prev; 

}

template <typename T>
Node<T>& Node<T>::operator=(const Node& copy)
{
    //once data is cleared copy 
    if (n_data != &copy)
    {
        //if this is populated, delete data
        if (n_data)
        {
            delete n_data;
        }
            n_data = copy.n_data;
            next_ptr = copy.next_ptr;
            prev_ptr = copy.prev_ptr;
    }
    return *this; 

}

template <typename T>
Node<T>& Node<T>::operator=(Node&& move) noexcept
{
    if (this != &move)
    {
        if (n_data)
        {
            delete n_data;
        }

        n_data = move.n_data;
        move.n_data = 0;
        next_ptr = move.next_ptr;
        move.next_ptr = nullptr;
        prev_ptr = move.prev_ptr;
        move.prev_ptr = nullptr;
    }

    return *this; 
}

template <class T>
T& Node<T>::Value() noexcept
{ 
    return this->n_data;
}

template <class T>
T Node<T>::Value() const noexcept
{
    return this->n_data;
}

template <class T>
void Node<T>::Value(const T data)
{
    n_data = data; 
}

template <typename T>
Node<T>* Node<T>::Next() noexcept
{
    return this->next_ptr;
}

template <typename T>
Node<T>* Node<T>::Next() const noexcept
{
    return this->next_ptr; 
}

template <typename T>
Node<T>* Node<T>::Previous() noexcept
{
    return this->prev_ptr;
}

template <typename T>
Node<T>* Node<T>::Previous() const noexcept
{
    return this->prev_ptr; 
}

template <typename T>
void Node<T>::Next(Node<T>* const next) noexcept
{
    next_ptr = next; 
}

template <typename T>
void Node<T>::Previous(Node<T>* const previous) noexcept
{
    prev_ptr = previous; 
}

#endif //NODE_TEMPLATE_H
