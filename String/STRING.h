#ifndef __STRING_H__
#define __STRING_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_COLOR_RESET      "\x1b[0m"


#pragma warning (disable: 4996 4090)

enum
{
	CAPACITY = 50,
};

namespace ADM
{

	class String
	{
	public:

		char data[CAPACITY + 1];
		size_t cap;
		size_t size;

	public:

		// constructors and distrcutor
		String();
		String(String& str);
		String(const char* str);
		~String();

		// 
		size_t len();
		size_t capacity();

		// func for working with strings
		void clear();
		bool empty();
		void pop_back();
		void push_back(char ch);
		void print();

		size_t my_strcpy(char* dest, const char* source);

		String& operator = (const String& str);
		String& operator = (const char* str);

		char& operator [] (size_t pos);

		String& operator += (const String& str);
		String& operator += (const char* str);

		String& operator + (const String& str);
		String& operator + (const char* str);

	};

}


#endif  //__STRING_H__//