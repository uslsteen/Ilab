#ifndef __STRINGS_H_
#define __STRINGS_H_

#include "inc_enums.h"

#define END_OF_STRING(symb) (symb == '\0' || symb == '\n')

#pragma warning (disable: 4996 4090)


typedef struct
{
	const char* line_ptr;
	size_t len;
} Lines;


int Input(const char* in, const char* type, char* text);

char* Create_Buffer(const char* filename, size_t* file_size);

int Lenght_Of_File(FILE* poems);

int String_Counter(const char* buffer, size_t buffer_size, char symbol);

Lines* Create_Ptr_Buf(const char* buffer, size_t buffer_size, size_t* counter_of_strs, char symbol);

bool Put_Buf_Into_File(const char* file_name, const char* buf, size_t buf_size);

int CompareFunc_Begin(const char* str1, const char* str2);

#endif 

