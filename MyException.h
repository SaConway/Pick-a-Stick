#pragma once
#include <exception>
#include <string>

//------------------------------------------------------------

class MyException : public std::exception
{
public:
	MyException() {};
	virtual const char * what() const = 0;
};

//------------------------------------------------------------

class FileException : public MyException
{
public:
	FileException(const std::string & str) : m_str(str){};
	const char * what() const override { return m_str.c_str(); }

private:
	std::string m_str;
};

//------------------------------------------------------------

class Escape : public std::exception
{
public:
	Escape() {};
};
