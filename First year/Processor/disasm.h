#ifndef __DISASM_H__
#define __DISASM_H__

#include "inc_enums.h"


class Disasm
{
public:

	Disasm();
	~Disasm();

	bool Disassembling(char* in_file, char* out_file);

private:

	bool Text_Processing(char* in_file);

	char* program;
	char* buffer_out;

	size_t program_size;
	size_t buffer_out_size;

};

#endif
