#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <crtdbg.h>
#include <conio.h>
#include "List.h"
#include "Stack.h"

// Strings to test
const string NAMES[] = { "Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 10;
const int NUM_SIZE = 10;
const int NUM_EXTRACT = 4;

// Test function declaration
bool test_default_ctor();
bool test_copy_ctor();
bool test_move_ctor();
bool test_op_equal();
bool test_move_op_equal();
bool test_is_empty();
bool test_is_full(); 
bool test_peek_with_value();
bool test_peek_empty_list();
bool test_push();
bool test_push_full_list();
bool test_pop_empty();
bool test_pop();
bool test_get_num_elements();

bool test_default_ctor_complex();
bool test_param_ctor_complex();
bool test_copy_ctor_complex();
bool test_move_ctor_complex();
bool test_op_equal_complex();
bool test_move_op_equal_complex();
bool test_is_empty_complex();
bool test_peek_with_value_complex();
bool test_peek_empty_list_complex();
bool test_push_complex();

bool test_append_complex(); //FIXME make sure I don't need any of this 
//bool test_pop_empty_complex(); FIXME check on this 
//bool test_pop_populated_complex(); FIXME check on this 
bool test_dtor(); //I don't think I need this 

//bool test_op_equalEqual(); FIXME 

// Test functions for moves
Stack<int> ReturnIntList();
Stack<string> ReturnStrList();

// Array of test functions
FunctionPointer test_functions[] = { test_default_ctor,
test_copy_ctor, test_move_ctor, test_op_equal, test_move_op_equal, test_is_empty,test_is_full,
test_peek_with_value, test_peek_empty_list,
test_push, test_push_full_list,test_pop_empty,
test_pop, test_pop_empty, test_default_ctor_complex,
test_param_ctor_complex, test_copy_ctor_complex, test_move_ctor_complex, test_op_equal_complex,
test_move_op_equal_complex, test_is_empty_complex, test_peek_with_value_complex, test_peek_empty_list_complex, 
test_append_complex, test_push_complex,test_get_num_elements, test_dtor};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int failed_tests = 0;
	
	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "passed" << endl;
		}
		else
		{
			failed_tests++;
			cout << "***** failed *****" << endl;
		}
	}

	if (failed_tests > 0)
		cout << endl << "You have " << failed_tests << " failed tests";
	else
		cout << endl << "All tests passed! Good job!";

	cout << endl;
	system("pause");
	cout << "Exiting..." << endl;

	return 0;
}

bool test_dtor()
{
	bool pass = true; 
	//delete empty stack
	Stack<int> stack_test;
	stack_test.~Stack(); 
	//check full list
	for (int i = 0; i < NUM_SIZE; ++i)
		stack_test.Push(i);
	stack_test.~Stack(); 

	return pass; 
}
bool test_default_ctor()
{
	bool pass = false;

	Stack<int> stack_test; 

	//check Peek
	//will also check Peeks Underflow exception
	try
	{
		stack_test.Peek();
	}
	//return true
	//if underflow ie empty
	catch (Exception& exception)
	{
		exception.getMessage();
		pass = true;
	}

	cout << "Default ctor test ";

	return pass;
}

bool test_copy_ctor()
{
	bool pass = true;

	Stack<int> test_stack;
	for (int i = 0; i < NUM_SIZE; ++i)
		test_stack.Push(i);

	Stack<int> stack_test(test_stack);

	// Check data integrity
	for (int i = 0; i < NUM_SIZE; ++i)
	{
		if (stack_test.Peek() != test_stack.Peek())
		{
			pass = false;
		}
			
		stack_test.Pop(); //Remove first value
		test_stack.Pop();
	}

	cout << "Copy ctor test ";

	return pass;
}

bool test_move_ctor()
{
	bool pass = true;

	Stack<int> test_stack(ReturnIntList());

	// Check data integrity
	for (int i = 0; i < NUM_SIZE; ++i)
	{
		if (i != test_stack.Peek())
			pass = false;
		test_stack.Pop(); // Remove value
	}

	cout << "Move ctor test ";

	return pass;
}

bool test_op_equal()
{
	bool pass = true;

	Stack<int> test_list;
	for (int i = 0; i < NUM_SIZE; ++i)
		test_list.Push(i);

	Stack<int> list_test;
	list_test = test_list; //Op =

	// Check data integrity
	for (int i = 0; i < NUM_SIZE; ++i)
	{
		if (list_test.Peek() != test_list.Peek())
			pass = false;
		list_test.Pop(); //Remove first value
		test_list.Pop();
	}

	cout << "Op equals test ";

	return pass;
}

bool test_move_op_equal()
{
	bool pass = true;

	Stack<int> test_list;
	test_list = ReturnIntList(); //Op =

	// Check data integrity
	for (int i = 0; i < NUM_NAMES; ++i)
	{
		if (i != test_list.Peek())
			pass = false;
		test_list.Pop(); //Remove first value
	}

	cout << "Move op equals test ";

	return pass;
}

bool test_is_empty()
{
	bool pass = true;

	Stack<int> full_list;
	for (int i = 0; i < NUM_SIZE; ++i)
		full_list.Push(i);

	Stack<int> empty_list;

	if (full_list.isEmpty())
		pass = false;

	if (!empty_list.isEmpty())
		pass = false;

	cout << "isEmpty test ";

	return pass;
}
bool test_is_full()
{
	bool pass = true;

	Stack<int> full_list;
	for (int i = 0; i < NUM_SIZE; ++i)
		full_list.Push(i);

	Stack<int> empty_list;

	if (!full_list.isFull())
		pass = false;

	if (empty_list.isFull())
		pass = false;

	cout << "isFull test ";

	return pass;
}
bool test_peek_with_value()
{
	bool pass = true;

	Stack<int> full_list;
	for (int i = 9; i > 0; --i)
		full_list.Push(i);

	if (full_list.Peek() != 1)
		pass = false;

	cout << "Peek with value test ";

	return pass;
}

bool test_peek_empty_list()
{
	bool pass = false;

	Stack<int> empty_list;

	try
	{
		empty_list.Peek();
	}
	catch (Exception& exception)
	{
		exception.getMessage();
		pass = true;
	}

	cout << "Peek with empty list test ";

	return pass;
}

//test push w/full stack 
bool test_push_full_list() //dont need 
{
	bool pass = false;

	Stack<int> full_list;

	for (int i = 0; i < NUM_SIZE; ++i)
		full_list.Push(i);
	try
	{
		full_list.Push(10);
	}
	catch (Exception& exception)
	{
		exception.getMessage();
		pass = true;
	}

	cout << "Push with full stack test ";

	return pass;
}
//test push w/ empty and populated stack 
bool test_push() 
{
	bool pass = true;
	int init_value = 5;
	int next_value = 3;

	Stack<int> test_list;

	// Push empty list
	test_list.Push(init_value);
	if (test_list.Peek() != init_value)
		pass = false;

	// Push list with existing values
	test_list.Push(next_value);
	if (test_list.Peek() != next_value)
		pass = false;

	cout << "Push test ";

	return pass;
}

//test pop empty stack 
//also checks pop underflow exception 
bool test_pop_empty() //-->ToDo change to Pop() empty 
{
	bool pass = false;
	int test_value = 5;

	Stack<int> empty_list;

	try
	{
		empty_list.Pop();
	}
	catch (Exception& exception)
	{
		exception.getMessage();
		pass = true;
	}

	cout << "Pop empty list test ";

	return pass;
}
//test pop on 1 and 1+ in stack 
bool test_pop()
{
	bool pass = true;

	Stack<int> test_list;
	//Pop 1 in list 
	//Pop 1+ in list 
	//Pop overflow --> checked in function above
	
	test_list.Push(1);
	test_list.Pop(); 
	if (!test_list.isEmpty())
	{
		return false; 
	}

	for (int i = 0; i < NUM_SIZE ; ++i)
		test_list.Push(i);
	try
	{
		for (int i = 0; i < NUM_SIZE; i++)
		{
			test_list.Pop();
		}
	}
	catch (Exception& exception)
	{
		exception.getMessage();
		pass = false;
	}
	
	cout << "Pop test  ";

	return pass;
}


bool test_default_ctor_complex()
{
	bool pass = false;

	Stack<string> list_test;

	try
	{
		list_test.Peek();
	}
	catch (Exception& exception)
	{
		exception.getMessage();
		pass = true;
	}

	cout << "Default ctor test complex ";

	return pass;
}

bool test_param_ctor_complex()
{
	bool pass = true;
	List<string> test_list("Sandra");
	//test_list.Prepend("Sandra");
	string test_value = test_list.First();

	pass = (test_value == "Sandra");

	cout << "Param ctor test complex FIXME DELETE ME ";

	return pass;
}

bool test_copy_ctor_complex()
{
	bool pass = true;

	Stack<string> test_list;
	for (int i = 9; i >= 0; --i)
		test_list.Push(NAMES[i]);

	Stack<string> list_test(test_list);

	// Check data integrity
	for (int i = 0; i < NUM_NAMES; ++i)
	{
		if (list_test.Peek() != test_list.Peek())
			pass = false;
		list_test.Pop(); //Remove first value
		test_list.Pop();
	}
	

	cout << "Copy ctor test complex";

	return pass;
}

bool test_move_ctor_complex()
{
	bool pass = true;

	Stack<string> test_list(ReturnStrList());

	// Check data integrity
	for (int i = 0; i<10; ++i)
	{
		if (NAMES[i] != test_list.Peek())
			pass = false;
		test_list.Pop(); //Remove first value
	}

	cout << "Move ctor test complex ";

	return pass;
}

bool test_op_equal_complex()
{
	bool pass = true;

	Stack<string> test_list;
	for (int i = 0; i < NUM_NAMES; ++i)
		test_list.Push(NAMES[i]);

	Stack<string> list_test;
	list_test = test_list; //Op = 

	// Check data integrity
	for (int i = 0; i < NUM_NAMES; ++i)
	{
		if (list_test.Peek() != test_list.Peek())
			pass = false;
		list_test.Pop(); //Remove first value
		test_list.Pop();
	}

	cout << "Op equals test complex ";

	return pass;
}

bool test_move_op_equal_complex()
{
	bool pass = true;

	Stack<string> test_list;
	test_list = ReturnStrList(); //Op =

	// Check data integrity
	for (int i = 0; i < NUM_NAMES; ++i)
	{
		if (NAMES[i] != test_list.Peek())
			pass = false;
		test_list.Pop(); //Remove first value
	}

	cout << "Move op equals test complex ";

	return pass;
}

bool test_is_empty_complex()
{
	bool pass = true;

	Stack<string> full_list;
	for (int i = 0; i < NUM_NAMES; ++i)
		full_list.Push(NAMES[i]);

	Stack<string> empty_list;

	if (full_list.isEmpty())
		pass = false;

	if (!empty_list.isEmpty())
		pass = false;

	cout << "isEmpty test complex ";

	return pass;
}

bool test_peek_with_value_complex() 
{
	bool pass = false;

	Stack<string> full_list;
	for (int i = 0; i < NUM_NAMES; ++i)
		full_list.Push(NAMES[i]);

	if (full_list.Peek() == NAMES[9])
		pass = true;

	cout << "Peek with value complex ";

	return pass;
}

bool test_peek_empty_list_complex() //FIXME change to test peek
{
	bool pass = true;

	Stack<string> empty_list;

	try
	{
		empty_list.Peek();
	}
	catch (Exception& exception)
	{
		exception.getMessage();
		pass = true;
	}

	cout << "Peek with empty list test complex ";

	return pass;
}


bool test_push_complex()
{
	bool pass = true;
	string init_value = "Person";
	string next_value = "Dog";

	Stack<string> test_list;

	// push empty list
	test_list.Push(init_value);
	if (test_list.Peek() != init_value)
		pass = false;

	// push list with existing values
	test_list.Push(next_value);
	if (test_list.Peek() != next_value)
		pass = false;

	cout << "Prepend test complex ";

	return pass;
}

bool test_append_complex()
{
	bool pass = true;
	string init_value = "Person";
	string next_value = "Dog";

	List<string> test_list;

	// Append empty list
	test_list.Append(init_value);
	if (test_list.First() != init_value || test_list.Last() != init_value)
		pass = false;

	// Append list with existing values
	test_list.Append(next_value);
	if (test_list.First() != init_value || test_list.Last() != next_value)
		pass = false;

	cout << "Append test complex FIXME";

	return pass;
}
bool test_get_num_elements()
{
	Stack <int> aStack;
	bool pass = true; 

	//empty list
	if (aStack.getNumElements() != 0)
	{
		pass = false; 
	}
	// populated list
	for (int i = 0; i < 10; ++i)
	{
		aStack.Push(i);
		//check that it grow appropriately 
		if (aStack.getNumElements() != i + 1)
		{
			pass = false;
		}
	}
	return pass; 
}
Stack<int> ReturnIntList()
{
	Stack<int> tempList;
	for (int i = 9; i >= 0; --i)
		tempList.Push(i);
	return tempList;
}

Stack<string> ReturnStrList()
{
	Stack<string> tempList;
	for (int i = 9; i >= 0; --i)
		tempList.Push(NAMES[i]);
	return tempList;
}
