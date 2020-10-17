#include "STRING.h"

using namespace ADM;
// constructor for const char*

String::String(const char* str1) :

	data{ {0} },
	cap(CAPACITY),
	size(my_strcpy(data, str1))
{
	std::cout << ANSI_COLOR_RED "Hello I'm constructor for char*\n\n" ANSI_COLOR_RESET;
}

//constructor for class String

String::String(String& str1) :

	data{ {0} },
	cap(CAPACITY),
	size(str1.size)
{
	std::cout << ANSI_COLOR_RED "Hello, I'm constructor for class String!\n\n" ANSI_COLOR_RESET;
	strcpy(data, str1.data);
}

String::String() :
	data{ {0} },
	cap(CAPACITY),
	size(0)
{
	std::cout << ANSI_COLOR_RED "Hello, I'm pretty constructor!\n\n" ANSI_COLOR_RESET;
}

String::~String()
{
	std::cout << ANSI_COLOR_BLUE "Hello, I'm distructor!\n\n" ANSI_COLOR_RESET;
}


//my_strcpy, return len of source/dest

size_t String::my_strcpy(char* dest, const char* source)
{
	size_t len = 0; 

	while (*(source + len) != '\0')
	{
		*(dest + len) = *(source + len);
		len++;
	}

	return len;
}


//printf of string
void String::print()
{
	std::cout << ANSI_COLOR_MAGENTA << data << ANSI_COLOR_RESET;
}


//return capacity of string
size_t String::capacity()
{
	return cap;
}

//return size of string
size_t String::len()
{
	return size;
}

void String::clear()
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		data[i] = '\0';
	}

	size = 0;
}

bool String::empty()
{
	/*
	if (size == 0)
		return true;
	else
		false;
	*/
	bool res = 0;

	size == 0 ? res = true : res = false;
	return res; 
}


void String::push_back(char ch)
{
	assert(cap >= size);

	data[++size] = ch;
}

void String::pop_back()
{
	data[size] = '\0';
	--size;
}


/*_____________overloaded operator_____________*/


String& String::operator = (const char* str)
{
	//checking for normal size of str
	assert(str != nullptr);

	clear();

	for (size_t i = 0; (size <= cap) & (str[i] != '\0'); ++i)
	{
		data[i] = str[i];
		++size;
	}

	return (*this);
}

String& String::operator = (const String& str)
{
	//checking for normal size of str
	clear();

	for (size_t i = 0; (size <= cap) && ((str.data) != '\0'); ++i)
	{
		data[i] = str.data[i];
		++size;
	}

	return (*this);
}


char& String::operator [] (size_t num)
{
	if (num > size || num < 0)
	{
		std::cout << "You caught Segmentation fault, dude!\n";
		exit(0);
	}

	else
		return data[num];
}

String& String::operator += (const char* str)
{
	assert(str != nullptr);

	for (size_t i = 0; (size <= cap) && *(str + i) != '\0'; ++i)
	{
		data[size] = str[i];
		++size;
	}
	return *this;
}


String& String::operator += (const String& str)
{
	for (size_t i = 0; (size <= cap) && str.data[i] != '\0'; ++i)
	{
		data[size] = str.data[i];
		++size;
	}
	return *this;
}





/*
String& String::operator = (const char* str)
{
	//checking for normal size of str
	assert(str != nullptr);

	memcpy(data, str, size + 1);

	return *this;
}

String& String::operator = (const String& str)
{
	//checking for normal size of str

	memcpy(data, &(str.data[0]), size + 1);

	return *this;
}
*/





