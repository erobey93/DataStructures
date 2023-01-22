//Emily Robey
//CST 211 - Lab 2 - List class 

#ifndef LISTTEMPLATE_H
#define LISTTEMPLATE_H

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::move;
using std::copy; 

#include "Node.h"
#include "Exception.h"

template<typename T>class List {
private:
    Node<T>* l_head;
    Node<T>* l_tail;
    int l_count; //number of nodes in list 
public:
    List();
    List(const T data);
    List(const List& copy);
    List(List&& move) noexcept;
    ~List();

    List& operator=(const List& copy);
    List& operator=(List&& move) noexcept; 
    explicit operator bool() const;

    void Append(const T data);
    void Prepend(const T data);
    void RemoveLast();
    void RemoveFirst();
    void Extract(const T data);
    void InsertAfter(const T data, const T after);
    void InsertBefore(const T data, const T before);
    void Purge() noexcept;

    T& Last();
    T Last() const;
    T& First();
    T First() const;

    Node<T>* getHead();
    Node<T>* getTail();
    bool isEmpty() const noexcept;
    size_t Size() const noexcept;
    bool operator==(const List<T>& rhs) const noexcept;
};

template <typename T>
List<T>::List() : l_head(nullptr), l_tail(nullptr), l_count(0) { }

template <typename T>
List<T>::List(const T data)
{
    l_head = new Node <T>(data); //create space for a new node & set l_head
    l_tail = nullptr; //make sure tail is still nullptr
    l_count++; 
}

template <typename T>
List<T>::List(const List& copy) : l_count(copy.l_count), l_head(nullptr), l_tail(nullptr)
{
    //if copy count is zero, set head & tail to nullptr
    if (copy.l_head == nullptr)
    {
        l_head = l_tail = nullptr;  
    }
    else if (this != &copy)//check for duplicate
    {

        l_head = new Node<T>(copy.l_head -> n_data); //create space for a new node set head 

        //create temp nodes to hold this.head and copy.head
        Node<T>* curr = copy.l_head->next_ptr; //copy
        Node<T>* prev = l_head; //this

        while (curr != nullptr)//make a new DLL, stop w/ next== nullptr
        {
            prev->next_ptr = new Node<T>(curr ->n_data, nullptr, prev); //create memory for next node and set data/ptrs
            prev = prev->next_ptr; //move prev (this) forward 1 node
            curr = curr->next_ptr; //move curr (copy) forward 1 node 
        }
        l_tail = prev; //set tail after entire list has been traversed 

        l_count = copy.l_count; //set l_count
    }
}

template <typename T>
List<T>::List(List&& move) noexcept : l_head(move.l_head), l_tail(move.l_tail), l_count(move.l_count)
{

    if(this != &move)
    {
        move.l_head = nullptr;
        move.l_tail = nullptr;
        move.l_count = 0;
    }
   
}

template <typename T>
List<T>::~List()
{
    if (this)
    {
        Purge();
    }
}

template <typename T>
List<T>& List<T>::operator=(const List& copy)
{
    //check for duplicate
    if (this == &copy)
    {
        return *this;
    }
    //check for a populated list 
    //if populated delete 
    else if (l_head)
    {
        Purge(); 
    }
    //copy
        l_head = new Node<T>(copy.l_head->n_data); //create space for a new node set head 

    //create temp nodes to hold this.head and copy.head
    Node<T>* curr = copy.l_head->next_ptr; //copy
    Node<T>* prev = l_head; //this

    while (curr != nullptr)//make a new DLL, stop w/ next== nullptr
    {
        prev->next_ptr = new Node<T>(curr->n_data, nullptr, prev); //create memory for next node and set data/ptrs
        prev = prev->next_ptr; //move prev (this) forward 1 node
        curr = curr->next_ptr; //move curr (copy) forward 1 node 
    }
    l_tail = prev; //set tail after entire list has been traversed 

    l_count = copy.l_count; //set l_count
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& move) noexcept
{
    //check for duplicate 
    if (this == &move)
    {
        return *this;
    }
    //check for a populated list 
    //if populated delete 
    if (l_head)
    {
        Purge();
    }
    //move
    l_count = move.l_count;
    move.l_count = 0;
    l_head = move.l_head;
    move.l_head = nullptr;
    l_tail = move.l_tail;
    move.l_tail = nullptr;

    return *this;
}

template <typename T>
List<T>::operator bool() const
{
    if (isEmpty())
    {
        return true;
    }
    else
    {
        return false; 
    }
}
//add to end 
template <typename T>
void List<T>::Append(const T data)
{
    //special cases
    //empty list
    if (l_count == 0)
    {
        l_head = new Node <T>(data); //create space for a new node & set l_head
        l_head->next_ptr = nullptr; //make sure l_head next is still nullptr 
        l_tail = nullptr; //make sure tail is still nullptr
        l_count++; //increment count 
    }
    //1 node
    else if (l_count == 1)
    {
        l_tail = new Node <T>(data); //create space for a new node & set l_head
        l_head->next_ptr = l_tail; //set l_head next to l_tail 
        l_tail->prev_ptr = l_head; //set tail prev to head
        l_count++; //increment count 
     }
    else
    {
        Node<T> *newNode = new Node <T>(data); //create a temp node to hold newNode
        l_tail->next_ptr = newNode; //set l_tail next 
        newNode->prev_ptr = l_tail; //set newNode->prev
        newNode->next_ptr = nullptr; 
        l_tail = newNode; //reset l_tail to end of list 
        l_count++; //increment count 
    }
}
//add to beginning 
template <typename T>
void List<T>::Prepend(const T data)
{
    //special cases
    //empty list
    if (l_count == 0)
    {
        l_head = new Node <T>(data); //create space for a new node & set l_head
        l_head->next_ptr = nullptr; //make sure l_head next is still nullptr 
        l_tail = nullptr; //make sure tail is still nullptr
        l_count++; //increment count 
    }
    else if (l_count == 1)
    {
        Node <T>* newNode = new Node<T>(data);//create memory for a new node 
        newNode->next_ptr = l_head; //set newNode next to head 
        newNode->prev_ptr = nullptr;
        l_head->prev_ptr = newNode; //set head prev to newNode 
        l_tail = l_head; //set tail to head 
        l_head = newNode; //set head to newNode 
        l_count++; //increment count 
    }
    else
    {
        Node <T> *newNode = new Node<T>(data); //create memory for node 
        newNode->next_ptr = l_head;//set newNode next to head 
        newNode->prev_ptr = nullptr;
        l_head->prev_ptr = newNode;//set head prev to newNode 
        l_head = newNode; //set head to newNode 
        l_count++; //incremenet count 
    }
}

template <typename T>
void List<T>::RemoveLast() //TODO --> RemoveLast()
{
    if (l_tail) //if tail not nullptr
    {

        if (l_count == 2) //if 2 nodes in list 
        {
            delete l_tail; //delete tail 
            l_tail = nullptr;
            l_head->next_ptr = nullptr;
            l_count--; 
        }
        else if (l_count > 2) //if more than 2 nodes 
        {
            Node <T>* temp = l_tail; //set temp to tail 
            l_tail = l_tail->prev_ptr;//set tail to tail prev
            l_tail->next_ptr = nullptr;
            delete temp; //delete temp 
            l_count--;
        }
    }
}

template <typename T>
void List<T>::RemoveFirst()
{
    if (l_head) //if head not nullptr
    {
        if (l_count == 1) //if only 1 node delete head 
        {
            delete l_head; 
            l_head = nullptr; 
            l_count--; 
        }
        else if (l_count == 2) //if 2 nodes delete head set head to tail null tail
        {
            delete l_head; 
            l_head = l_tail;
            l_tail = nullptr;
            l_count--; 
        }
        else //if > 2 nodes set temp to head move head to next node delete temp 
        {
            Node <T>* temp = l_head; 
            l_head = l_head->next_ptr;
            delete temp;
            l_count--;
        }
    }
}

template <typename T>
void List<T>::Extract(const T data)
{
    Exception emptyList ("emptyList");
    Exception noMatch("No Match Found");
    bool match = false; 

    if (isEmpty())//check for empty list
    {
        throw emptyList; 
    }
    else
    {
        Node<T>* temp; //temp node to hold node to be extracted  
        temp = l_head; 
        if (data == First())
        {
            RemoveFirst();
            match = true; 
        }
        //--> TODO fix tabs 
        else if (data == Last())
        {
            RemoveLast();
            match = true;
        }
            
        else
        {  //traverse the list 
            while (temp->next_ptr != nullptr)
            {
                if (data == temp->n_data)//else if (data == temp->n_data)
                {
                    if (temp == l_head)
                    temp->prev_ptr->next_ptr = temp->next_ptr;//reset next ptr
                    temp->next_ptr->prev_ptr = temp->prev_ptr; //reset prev ptr
                    delete temp;
                    temp = l_tail;//to trigger end of loop
                    l_count--;
                    match = true;
                }
                else
                {
                    temp = temp->next_ptr;
                }
            }
        }
        }
        //if no match throw exception 
        if (!match)
        {
            throw noMatch;
        }
}

template <typename T>
void List<T>::InsertAfter(const T data, const T after)
{

    string message = "List is empty ";
    Exception emptyList(message);
    bool match = false; //return true if match, else false 

    if (!isEmpty())
    {
        Node<T>* newNode = new Node<T>(data); //create memory
        if (after == First())//if b/f head 
        {
            //if only 1 node set tail  
            if (l_count == 1)
            {
                l_head->next_ptr = newNode; 
                newNode->prev_ptr = l_head; 
                newNode->next_ptr = nullptr;
                l_tail = newNode;
            }
            else
            {
                newNode->next_ptr = l_head->next_ptr; //point newNode next to head->next
                newNode->prev_ptr = l_head; //point newNode prev to head
                l_head->next_ptr->prev_ptr = newNode; 
                l_head->next_ptr = newNode;
            }
            
            match = true; 
        }
        else if (l_count > 1) //if more than 1 in list
        {
            Node<T>* temp = l_head->next_ptr; //set temp to 2nd node in list 
            if (after == Last()) //check tail first 
            {
                Append(data); 

            }
            else if (temp->n_data == after) //if match 
            {
                Node<T>* newNode = new Node<T>(data); //create memory
                temp->next_ptr->prev_ptr = newNode; //point temp->prev to newNode   
                newNode->next_ptr = temp->next_ptr; //point newNode -> next to temp -> next
                temp->next_ptr = newNode; //point temp to newNode 
                newNode->prev_ptr = temp; //point newNode->prev to temp
                match = true; 
                
            }
            else//if no match 
            {
                temp = temp->next_ptr; //no match, move forward 1 node 
            }
        }
    }
    //increment count if match 
    if (match)
    {
        l_count++;
    }
    if (isEmpty() || !match)
    {
        throw emptyList;
    }
}

template <typename T>
void List<T>::InsertBefore(const T data, const T before)
{
    string message = "List is empty ";
    Exception emptyList(message);
    bool match = false; //return true if match, else false 

    if (!isEmpty())
    {
        if (before == First())//if b/f head 
        {
            Prepend(data);
            match = true; 
        }
        else if (l_head -> next_ptr) //if more than 1 in list
        {
            Node<T>* temp = l_head->next_ptr; //set temp to 2nd node in list 
            if (before == Last()) //if b/f tail 
            {
                Node<T>* newNode = new Node<T>(data); //create memory
                newNode->prev_ptr = l_tail->prev_ptr; //set newNode previous
                newNode->next_ptr = l_tail; //set newNode next 
                l_tail->prev_ptr->next_ptr = newNode; //reset temp prev to newNode
                l_tail->prev_ptr = newNode; //reset temp next to newNode
                //l_tail = newNode; 
                l_count++; 
                match = true; 

            }
            else if (temp -> n_data == before)
            {
                Node<T>* newNode = new Node<T>(data); //create memory
                newNode->prev_ptr = temp->prev_ptr; //set newNode previous
                newNode->next_ptr = temp->next_ptr; //set newNode next 
                temp->prev_ptr->next_ptr = newNode; //reset temp prev to newNode
                temp->next_ptr->prev_ptr = newNode; //reset temp next to newNode
                l_count++; 
                match = true; 
            }
            else
            {
                temp = temp->next_ptr; //no match, move forward 1 node 
            }
        }
    }
    if (isEmpty() || !match)
    {
        throw emptyList;
    }

}

template <typename T>
void List<T>::Purge() noexcept
{ 
    if (l_head)
    {   
        if (l_count == 1) //if 1 node 
        {
            delete l_head;
            //l_count = 0; 
        }
        else if (l_count == 2) //if 2 nodes 
        {
            delete l_head;
            delete l_tail; 
            //l_count = 0;
        }
        else //if > 2 nodes 
        {
            //create a temp point 
            Node<T>* temp = l_head;
            //traverse through list using temp 
            //deleting as it goes
            for (int i = 0; i < l_count; i++)
            {
                temp = l_head->next_ptr;
                delete l_head;
                l_head = temp;
            }
            //clean up
            l_head = nullptr;
            l_tail = nullptr;
            l_count = 0;
        }
    }
}

template <typename T>
T& List<T>::Last()
{
    //Exception object
    Exception emptyTail("Tail is nullptr");
    //if tail is nullptr
    if (l_count == 1)
    {
        if (!l_head)//if no tail check for head (case = 1 node) 
        {
            throw emptyTail;
        }
        return l_head->n_data; 
    }
  else if (!l_tail)
    {
        throw emptyTail;
    }
    else
    {
        return l_tail->n_data;

    }
}

template <typename T>
T List<T>::Last() const
{
    //Exception object
    Exception emptyTail("Tail is nullptr");
    //if tail is nullptr
    if (!l_tail)
    {
        if (!l_head)
        {
            throw emptyTail;
        }
        else
        { 
        return l_head->n_data;
        }
    }
    else
    {
        return l_tail->n_data;

    }
}

template <typename T>
T& List<T>::First()
{
    //Exception object
    Exception emptyHead("Head is nullptr");
    //if head is nullptr
    if (!l_head)
   {
        throw emptyHead;
    }
    else
    {
        return l_head->n_data;

    }
   
}

template <typename T>
T List<T>::First() const
{
    //Exception object
    Exception emptyHead("Head is nullptr");
    //if head is nullptr
    if (!l_head)
    {
        throw emptyHead;
    }
    else
    {
        return l_head->n_data;

    }
}

template <typename T>
Node<T>* List<T>::getHead()
{

        return l_head;

}

template <typename T>
Node<T>* List<T>::getTail()
{

        return l_tail;
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
    if (l_count <= 0)
    {
        return true;
    }
    else
    {
        return false; 
    }
}

template <typename T>
size_t List<T>::Size() const noexcept
{
    return l_count; 
}

template <typename T>
bool List<T>::operator==(const List<T>& rhs) const noexcept
{
    //if size is different can't be ==
    if (rhs.Size() != l_count)
    {
        return false; 
    }
    //if size is == check each node in list 
    //temp nodes to hold each node 
    Node<T>* temp = l_head; 
    Node<T>* tempRhs = rhs.l_head; 

    for (int i = 0; i < l_count; i++)
    {
        if (temp.n_data != tempRhs.n_data)
        {
            return false;
        }
        //move temp nodes to next node
        temp = temp->next; 
        tempRhs = tempRhs->next; 
    }
    //if all == return true
    return true;
}


#endif //LIST_TEMPLATE_H
