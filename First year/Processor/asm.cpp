#include "asm.h"

//_______________________________________________
//define for commands.h


#define DEF_CMD(name, num, asm, proc, disasm)								\
    else																	\
		if (CompareFunc_Begin(cmd_name, #name) == 0)				\
    {																		\
      *buffer_out1++ = num;													\
      buffer_out_size++;													\
      asm																	\
    }

//_________________________________________

Asm::Asm() :

	program(nullptr),
	program_size(0),

	code(nullptr),
	code_size(0),

	buffer_out(nullptr),
	buffer_out_size(0)
{
}

Asm::~Asm()
{
	if (code != nullptr)
	{
		free(code);
	}

	if (program != nullptr)
	{
		free(program);
	}

	if (buffer_out != nullptr)
	{
		free(buffer_out);
	}
}

bool Asm::Start_Working_Asm(const char* name_file_in, const char* name_file_out)
{
	assert(name_file_in);
	assert(name_file_out);

	if (!Converter_File(name_file_in))
	{
		printf("Error in \"Converter file\".\n");
		return false;
	}

	if (!Put_Buf_Into_File(name_file_out, buffer_out, buffer_out_size))
	{
		printf("Error in \"Put_Into_File\".\n");
		return false;
	}

	return true;
}

bool Asm::Text_Processing(const char* name_file_in)
{
	//size_t file_size = 0;

	assert(name_file_in);

	code = Create_Buffer(name_file_in, &code_size);

	if (code == nullptr)
	{
		printf("Text processing return nullptr in \"Read file\"");
		return false;
	}

	program = Create_Ptr_Buf(code, code_size, &program_size, '\n');

	if (program == nullptr)
	{
		printf("Text processing return nullptr in \"Create_ptrs\".\n");
		return false;
	}

	return true;
}


bool Asm::Converter_File(const char* name_file_in)
{
	assert(name_file_in != nullptr);

	char* buffer_out1 = nullptr;

	if (!Text_Processing(name_file_in))
	{
		printf("\"Text processing\" return false");
		return false;
	}

	printf("hui\n");

	buffer_out = (char*)calloc(code_size, sizeof(buffer_out[0]));
	assert(buffer_out);

	buffer_out1 = buffer_out;

	for (size_t program_counter = 0; program_counter < program_size; program_counter++)
	{
		char cmd_name[MAX_CMD_NAME] = { {0} };
		int position = 0;

		if (sscanf(program[program_counter].line_ptr, "%s %n", cmd_name, &position) != 1)
		{
			printf("......\n");
			return false;
		}

#include "commands.h"

		else
		{
			printf("Unrecognized command in line %d: '%s'\n", program_counter + 1, cmd_name);
			return false;
		}
	}
#undef DEF_CMD

	return true;
}
