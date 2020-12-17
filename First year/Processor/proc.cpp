#include "proc.h"

//_______________________________________________
//define for commands.h

#define DEF_CMD(name, num, asm, proc, disasm) \
											  \
	case num:								  \
											  \
		program_ptr++;						  \
		proc;								  \
											  \
		break;								  \
//_______________________________________________


Proc::Proc() :

	program(nullptr),
	program_size(0)

{
	for (int i = 0; i < REG_SIZE; i++)
	{
		registers[i] = 0;
	}
}


bool Proc::Processing(char* name_file_in)
{
	assert(name_file_in);

	char* program_ptr = nullptr;
	Stack <int> stk;

	program = Create_Buffer(name_file_in, &program_size);

	if (program == NULL)
	{
		printf("Error in Create buffer\n");
		return false;
	}

	program_ptr = program;

	while (program_ptr - program != program_size)
	{
		switch (*program_ptr)
		{

#include "commands.h"

		default:
			printf("I can't execute this command: %c\n", *program_ptr);
			return false;
		}
	}

#undef DEF_CMD

	return true;
}

Proc::~Proc()
{
	if (program != nullptr)
	{
		free(program);
	}
}
