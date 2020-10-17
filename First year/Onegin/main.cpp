#include "evgeneonege.h"

int main()
{


	char name_of_file[MAXSIZE] = { 0 }; // only for c++

	size_t byte_file_size = 0;

	size_t num_of_str = 0;

	int check_input = Input("Hello! please, enter the name of file:\n", "%s", name_of_file);

	if (check_input == NULL)
	{
		printf("Error with reading name of file.\n");
		return 0;
	}

	unsigned char* buffer = Read_File(name_of_file, &byte_file_size); // считывание текста в буффер

	if (buffer == NULL)
	{
		printf("Error with creating buffer\n");
		return 0;
	}

	Lines * new_text = Create_Ptrs(buffer, '\n', byte_file_size, &num_of_str); //расставка указателей на начало каждый строки

	assert(new_text != NULL);

	qsort(new_text, num_of_str, sizeof(Lines), CompareFunction_FromBegin);   // сортировка строк

	check_input = Input("So, write name of new text file:\n", "%s", name_of_file);

	if (check_input == NULL)
	{
		printf("Error with writing name of file.\n");
	}

	Create_File(name_of_file, new_text, num_of_str);

	Create_A_Sep(name_of_file, WIDTH_OF_SEPARATION, HIGH_OF_SEPARATION);

	qsort(new_text, num_of_str, sizeof(Lines), CompareFunction_FromEnd);

	check_input = Input("So, write name of new text file:\n", "%s", name_of_file);

	if (check_input == NULL)
	{
		printf("Error with writing name of file.\n");
	}

	Create_File(name_of_file, new_text, num_of_str);

	Create_A_Sep(name_of_file, WIDTH_OF_SEPARATION, HIGH_OF_SEPARATION);

	check_input = Input("So, write name of new text file:\n", "%s", name_of_file);

	Put_Into_File(buffer, name_of_file);

	free(buffer);

	free(new_text);

	return 0;

}

