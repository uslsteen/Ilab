#include "evgeneonege.h"


int Input(const char in[], const char type[], char* text)
{
	assert(in != NULL);
	assert(type != NULL);
	assert(text != NULL);

	printf(in);

	int result_of_input = scanf(type, text);

	return result_of_input;
}


unsigned char* Read_File(const char name_of_file[], size_t* file_size)
{
	assert(name_of_file != NULL);
	assert(file_size != NULL);

	FILE* poems = fopen(name_of_file, "rb");

	if (poems == NULL)
	{
		printf("Error opening file!\n");
		return NULL;
	}

	int num_of_symb = Lenght_Of_File(poems);

	if (num_of_symb == 0)
	{
		printf("Error with counting symbols\n");
		return NULL;
	}

	unsigned char* buffer = (unsigned char*)calloc(num_of_symb + 1, sizeof(buffer[0]));

	if (buffer == NULL)
	{
		printf("Error with creating buffer\n");
		fclose(poems);
		return NULL;
	}

	int reading_size = fread(buffer, sizeof(buffer[0]), num_of_symb, poems);

	/*while (reading_size != num_of_symb)
	{
		reading_size += fread(buffer, sizeof(buffer[0]), num_of_symb, poems);
	}

	*/
	if (reading_size == 0)
	{
		printf("Error with transportation file to buffer\n");
		fclose(poems);
		return NULL;
	}

	*file_size = reading_size;

	fclose(poems);

	return buffer;

}

int Lenght_Of_File(FILE* poems)
{
	assert(poems != NULL);

	fseek(poems, 0, SEEK_END);

	int lenght = ftell(poems);

	if (lenght <= 0)
	{
		printf("Error with fseek fucntion\n");
		return 0;
	}

	rewind(poems);

	return lenght;
}

/*int Num_Of_Str(const char buffer[], char symbol, size_t file_size)
{
	assert(buffer != NULL);
	assert(file_size != NULL);

	int str_counter = 0;
	char* ptr = (char*)memchr(buffer, symbol, file_size);
	while (ptr != NULL)
	{
		str_counter++;
		ptr = (char*)memchr(ptr + 1, symbol, file_size - (ptr - buffer) - 1);
	}

	return str_counter;
}
*/

Lines* Create_Ptrs(const unsigned char buffer[], char symbol, size_t file_size, size_t *count_of_str)
{
	assert(buffer != NULL);
	assert(file_size != 0);
	assert(count_of_str != NULL);

	int index = 0; // veriables decloration

	unsigned char s_last = 0;
	unsigned char s_pre_last = 0; // veriables decloration

	int buf_size = SIZE_PTR_BUF;

	//int num_of_str = Num_Of_Str(buffer, '\n', file_size);

	Lines* ptr_buffer = (Lines*)calloc(buf_size, sizeof(ptr_buffer[0])); // custom allocator 

	unsigned char* s_next = (unsigned char*)memchr(buffer, symbol, file_size);

	const unsigned char* s = buffer;

	if (s_next != buffer)
	{
		s_last = *(s_next - 1);
	}

	if (s_next != buffer + 1)
	{
		s_pre_last = *(s_next - 2);
	}

	while (s_next != NULL)
	{
		ptr_buffer[index].line_ptr = s;

		ptr_buffer[index].len = s_next - s + 1;

		if (s_pre_last == '\n' && (s_last == '\r' ))
		{
			index--;
		}

		s = s_next + 1;

		s_next = (unsigned char*)memchr(s_next + 1, symbol, file_size - (s - buffer));

		if (s_next != NULL)
		{
			s_last = *(s_next - 1);

			s_pre_last = *(s_next - 2);
		}

		index++;

		if (Compare_With_Epsilon(index, buf_size))
		{
			buf_size = buf_size * 2;
			ptr_buffer = (Lines*)realloc(ptr_buffer, sizeof(ptr_buffer[0]) * (buf_size));
		}
	}

	if (Compare_With_Delta(index, buf_size))
	{
		ptr_buffer = (Lines*)realloc(ptr_buffer, sizeof(ptr_buffer[0]) * (index + 5));

		if (ptr_buffer == NULL)
		{
			printf("Error with realloc in Compare_With_Delta\n");
			return 0;
		}
	}

	* count_of_str = index;

	return ptr_buffer;
}

int CompareFunction_FromBegin(const void* str1, const void* str2)
{
	assert(str1 != NULL);
	assert(str2 != NULL);

	const unsigned char* string1 = ((Lines*) str1)->line_ptr; // через указатель на структуру получаю доступ к ее полю - массиву указателей
	const unsigned char* string2 = ((Lines*) str2)->line_ptr;

	while (true)
	{
		while (!isalpha(*string1) && !END_OF_STRING(*string1))
		{
			string1++;
		}

		while (!isalpha(*string2) && !END_OF_STRING(*string2))
		{
			string2++;
		}

		if (toupper(*string1) != toupper(*string2))
		{
			break;
		}

		string1++;
		string2++;
	}
	
	return toupper(*string1) - toupper(*string2);
}

int CompareFunction_FromEnd(const void* str1, const void* str2)
{
	assert(str1 != NULL);
	assert(str2 != NULL);

	const unsigned char* string1 = ((Lines*)str1)->line_ptr + (((Lines*)str1)->len - 1); // через указатель на структуру получаю доступ к ее полю - массиву указателей
	const unsigned char* string2 = ((Lines*)str2)->line_ptr + (((Lines*)str2)->len - 1);
	const unsigned char* string1end = ((Lines*)str1)->line_ptr + (((Lines*)str1)->len - 1);
	const unsigned char* string2end = ((Lines*)str2)->line_ptr + (((Lines*)str2)->len - 1);

	while (true)
	{
		while (!isalpha(*string1) &&  string1end - string1 != ((Lines*)str1)->len -1)
		{
			string1--;
		}

		while (!isalpha(*string2) && string2end - string2 != ((Lines*)str2)->len - 1)
		{
			string2--;
		}

		if (toupper(*string1) != toupper(*string2) || string1 == ((Lines*)str1)->line_ptr || string2 == ((Lines*)str2)->line_ptr)
		{
			break;
		}
		
		string1--;
		string2--;
	}

	return toupper(*string1) - toupper(*string2);
}

void Create_File(const char name_of_file[], const Lines ptrs[], size_t num_of_str)
{
	assert(name_of_file != NULL);
	assert(ptrs != NULL);
	assert(num_of_str != NULL);

	FILE* poems1 = fopen(name_of_file, "ab");

	for (int i = 0; i < num_of_str; i++)
	{
		fwrite(ptrs[i].line_ptr, sizeof(ptrs[0].line_ptr[0]), ptrs[i].len, poems1);
	}

	fclose(poems1);

}
void Put_Into_File(const unsigned char buffer[], const char name_of_file[])
{
	assert(buffer != 0);
	assert(name_of_file != 0);

	FILE* poems2 = fopen(name_of_file, "ab");

	fputs((const char*)buffer, poems2);

	fclose(poems2);
}


void Create_A_Sep(const char name_of_file[], size_t width_of_buffer, size_t high_of_buffer)
{
	assert(name_of_file != NULL);

	unsigned char* buffer = (unsigned char*)calloc(width_of_buffer + 2 , sizeof(buffer[0]));

	for (int str = 0; str < width_of_buffer; str++)
	{
		buffer[str] = '#';
	}

	buffer[width_of_buffer] = '\n';

	buffer[width_of_buffer + 1] = '\0';

	for (int i = 0; i < high_of_buffer; i++)
	{
		Put_Into_File(buffer, name_of_file);
	}
	
	free(buffer);
}

int Compare_With_Delta(int num1, int num2)
{
	if (abs(num2 - num1) <= DELTA)
		return 1;
	else
		return 0;
}

int Compare_With_Epsilon(int num1, int num2)
{
	if (abs(num2 - num1) <= EPSILON)
		return 1;
	else
		return 0;
}


