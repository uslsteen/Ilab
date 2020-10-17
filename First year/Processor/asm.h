#ifndef __ASM_H__
#define __ASM_H__

#include "inc_enums.h"


class Asm
{
private:

	Lines* program;
	size_t program_size;

	char* code;
	size_t code_size;

	char* buffer_out;
	size_t buffer_out_size;

public:

	Asm(void);
	~Asm(void);

	bool Start_Working_Asm(const char* name_file_in, const char* name_file_out);

private:

	bool Converter_File(const char* name_file_in);
	bool Text_Processing(const char* name_file_in);

};

#endif 
