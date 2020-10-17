#include "strings.h"

int Input(const char* in, const char* type, char* text)
{
	assert(in != NULL);
	assert(type != NULL);
	assert(text != NULL);

	printf(in);

	int result_of_input = scanf(type, text);

	return result_of_input;
}


char* Create_Buffer(const char* name_of_file, size_t* file_size)
{
	char* buffer = nullptr;

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

	buffer = (char*)calloc(num_of_symb + 1, sizeof(buffer[0]));
	assert(buffer);
	//buffer = new char[num_of_symb + 1];


	if (buffer == NULL)
	{
		printf("Error with creating buffer\n");
		fclose(poems);
		return NULL;
	}

	int reading_size = fread(buffer, sizeof(buffer[0]), num_of_symb, poems);


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


Lines* Create_Ptr_Buf(const char* buf, size_t buf_size, size_t* str_cnt, char end_value)
{
	assert(buf != NULL);
	assert(buf_size != 0);
	assert(str_cnt != NULL);

	int num_of_strs = String_Counter(buf, buf_size, end_value);
	int real_str = 0;

	Lines* ptrs_buffer = (Lines*)calloc(num_of_strs, sizeof(ptrs_buffer[0]));
	assert(ptrs_buffer != NULL);

	char* s = (char*)memchr(buf, end_value, buf_size);

	const char* prev = buf;
	char prevch = 0, pre_prevch = 0;

	if (s != buf && s != NULL)
	{
		prevch = *(s - 1);
	}

	if (s != buf + 1 && s != NULL)
	{
		prevch = *(s - 2);
	}

	while (s != NULL)
	{
		ptrs_buffer[real_str].line_ptr = prev;
		ptrs_buffer[real_str++].len = s - prev + 1;

		if ((prevch == '\n' || prevch == '\r') && pre_prevch == '\n')
		{
			real_str--;
		}

		prev = s + 1;

		s = (char*)memchr(s + 1, end_value, buf_size - (s - buf) - 1);

		if (s != NULL)
		{
			prevch = *(s - 1);
			pre_prevch = *(s - 2);
		}
	}

	s = (char*)memchr(prev, 0, buf_size - (s - buf) - 1);

	if (*(s - 1) != '\n')
	{
		ptrs_buffer[real_str].line_ptr = prev;
		ptrs_buffer[real_str++].len = s - prev + 1;
	}

	*str_cnt = real_str;
	return ptrs_buffer;
}



int String_Counter(const char* buffer, size_t buffer_size, char symbol)
{
	assert(buffer != NULL);
	assert(buffer_size != 0);

	int str_counter = 0;

	char* s_ptr = (char*)memchr(buffer, symbol, buffer_size);
	while (s_ptr != NULL)
	{
		str_counter++;
		s_ptr = (char*)memchr(s_ptr + 1, symbol, buffer_size - (s_ptr - buffer) - 1);
	}

	if (buffer[buffer_size - 1] != symbol)
	{
		str_counter++;
	}

	return str_counter;
}



int CompareFunc_Begin(const char* str1, const char* str2)
{
	assert(str1 != NULL);
	assert(str2 != NULL);

	const unsigned char* string1 = (unsigned char*)str1;
	const unsigned char* string2 = (unsigned char*)str2;

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


		if (toupper(*string1) != toupper(*string2) || END_OF_STRING(*string1) || END_OF_STRING(*string2))
			break;

		string1++;
		string2++;

		if (END_OF_STRING(*string1) || END_OF_STRING(*string2))
		{
			break;
		}
	}
	return toupper(*string1) - toupper(*string2);
}



bool Put_Buf_Into_File(const char* name_file_out, const char* buffer, size_t buffer_size)
{
	assert(name_file_out != nullptr);
	assert(buffer != nullptr);
	assert(buffer_size != 0);

	FILE* out = fopen(name_file_out, "wb");

	if (out == NULL)
	{
		return false;
	}


	fwrite(buffer, sizeof(char), buffer_size, out);

	fclose(out);

	return true;
}
