//Emily Robey 
//CST 211 - Lab 3 - Stack
//Exception class

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <iostream>
#include <exception>

using std::string;
using std::exception;
using std::ostream;

class Exception : public exception {

	string m_msg;

public:
	Exception() : m_msg("Unknown Error") {};					//default constructor
	Exception(const string& msg) : m_msg(msg) {};					//constructor with parameters
	Exception(const Exception& copy) : m_msg(copy.m_msg) {};	//copy constructor
	Exception(Exception&& move) noexcept;								//move constructor

	Exception& operator = (const Exception& move);					//copy assignment operator
	Exception& operator = (Exception&& copy) noexcept;						//move assignment operator

	const string getMessage() { return m_msg; }					//gets exception message
	void setMessage(const string& message) { m_msg = message; }    //sets exception message

	friend std::ostream& operator << (std::ostream&, const Exception&);	//overloaded output operator 
};

Exception::Exception(Exception&& copy) noexcept
{
	m_msg = copy.m_msg;
}

Exception& Exception::operator = (const Exception& copy)
{
	m_msg = copy.m_msg;
	return *this;
}

Exception& Exception::operator = (Exception&& move) noexcept
{
	m_msg = move.m_msg;
	return *this;
}

ostream& operator << (ostream& out, const Exception& except)
{
	out << except.m_msg;
	return out;
}

#endif //EXCEPTION_H

