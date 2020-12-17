#include "disasm.h"

//______________________________________________________________
//define for commands.h
#define DEF_CMD(name, num, asm, proc, disasm)					\
																\
	case num:													\
																\
		/*sprintf(buffer_out1, #name "%n", &position);*/		\
		sprintf(buffer_out1, #name " ");						\
		buffer_last = buffer_out1;								\
																\
		/*buffer_out1 += position;*/							\
		buffer_out1 += strlen(#name) + 1;						\
		program_ptr++;											\
																\
		disasm;													\
																\
		*buffer_out1++ = '\n';									\
		buffer_out_size += buffer_out1 - buffer_last;			\
																\
      break;
//______________________________________________________________



Disasm::Disasm() :

	program(nullptr),
	buffer_out(nullptr),

	program_size(0),
	buffer_out_size(0)

{
}

bool Disasm::Disassembling(char* file_in, char* file_out)
{
	char* buffer_out1 = nullptr;
	char* program_ptr = nullptr;
	char* buffer_last = nullptr;
	int position = 0;
	_set_printf_count_output(1);

	assert(file_in != nullptr);
	assert(file_out != nullptr);


	if (!Text_Processing(file_in))
	{
		printf("Error in text processing\n");
		return false;
	}

	buffer_out = (char*)calloc(program_size * MEMORY_COEFFS, sizeof(buffer_out[0]));
	assert(buffer_out != nullptr);

	buffer_out1 = buffer_out;
	program_ptr = program;


	while (program_ptr - program != program_size)
	{
		switch (*program_ptr)
		{

#include "commands.h"

		default:
			printf("I cant disassembly this command, dude, %c\n", *program_ptr);
			return false;
		}
	}


#undef DEF_CMD


	if (!Put_Buf_Into_File(file_out, buffer_out, buffer_out_size))
	{
		printf("Error in Put_Buf_Into_File\n");
		return false;
	}


	return true;

}

bool Disasm::Text_Processing(char* file_in)
{
	assert(file_in != nullptr);

	program = Create_Buffer(file_in, &program_size);

	if (program == nullptr)
	{
		printf("Error in Create buffer.\n");
		return false;
	}

	return true;
}

Disasm::~Disasm()
{
	if (program != nullptr)
	{
		free(program);
	}

	if (buffer_out != nullptr)
	{
		free(buffer_out);
	}
}
