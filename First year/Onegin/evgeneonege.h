#pragma once

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define END_OF_STRING(string) (string == '\n' || string == '\0')

#pragma warning (disable: 4996 4090)

typedef struct
{
	const unsigned char* line_ptr;
	int len;
} Lines;

const int MAXSIZE = 100;

const int HIGH_OF_SEPARATION = 40;

const int WIDTH_OF_SEPARATION = 60;

const int SIZE_PTR_BUF = 1000;

const int DELTA = 200;

const int EPSILON = 10;

//! The function for input any text
//! @param[in] in[] - input data stream
//! @param[in] type[] - type of input data
//! @param[out] - out put data stream
//! The fucntion return result of input

int Input(const char in[], const char type[], char* text);

//! The fucntion for reading file to buffer
//! @param[in] name_of_file[] - name of original text
//! @param[in] file_size - pointer to the byte size of file (returning from fread)
//! The function return buffer

unsigned char* Read_File(const char name_of_file[], size_t* file_size);

//! The fucntion for counting symbols of the file (lenght)
//! @param[in] FILE* poems - file which text a measured
//! The function return number of symbols from file

int Lenght_Of_File(FILE* poems);

//! The function for creating poinets to the begin of string(in buffer, of course)
//! @param[in] buffer - buffer for making pointers
//! @param[in] symbol - key-symbol(parametr) for quick counting with help memchr()
//! @param[in] file_size - byte size of file, parametr for quick counting with help memchr()
//! @param[in] counter_of_str - pointer to the real number of string
//! The function return massive os structure

Lines* Create_Ptrs(const unsigned char buffer[], char symbol, size_t file_size, size_t* counter_of_str);

//! The function for comparing strings from the beginning
//! @param[in] str1 - pointer to beginning of str1
//! @param[in] str2 - pointer to beginning of str2
//! The function return integer result of comparing str1 and str2

int CompareFunction_FromBegin(const void* str1, const void* str2);

//! The function for comparing strings from the end
//! @param[in] str1 - pointer to the end of str1
//! @param[in] str2 - pointer to he end of str2
//! The function return integer result of comparing str1 and str2

int CompareFunction_FromEnd(const void* str1, const void* str2);

//! The fucntion for writing sorted text in file
//! @param[in] name_of_file - name of file for output
//! @param[in] ptrs[] - massive of structure
//! @param[in] num_of_str - real number of string in sorted file (without useless \n and \r)

void Create_File(const char name_of_file[], const Lines ptrs[], size_t num_of_str);

//! The function for input oirignal text
//! @param[in] buffer - buffer where standing our original text
//! @param[in] name_of_file - file for output

void Put_Into_File(const unsigned char buffer[], const char name_of_file[]);

//! The fucntion for creating seperation between text
//! @param[in] name_of_file - file where input seperation
//! @param[in] width_of_buffer - parametr of seperation
//! @param[in] high_of_buffer - parametr of seperation

void Create_A_Sep(const char name_of_file[], size_t width_of_buffer, size_t high_of_buffer);

//! The fucntions of comparing with epsilon\delta
//! @param[in] num1 - number one for comp
//! @param[in] num2 - number two for comp

int Compare_With_Delta(int num1, int num2);

int Compare_With_Epsilon(int num1, int num2);



