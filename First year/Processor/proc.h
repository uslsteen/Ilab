#ifndef __PROC_H__
#define __PROC_H__

#include "inc_enums.h"

#define DEF_CMD(name, num, asm, proc, disasm)

const int REG_SIZE = 4;


class Proc
{
private:

	char* program;
	size_t program_size;
	int registers[REG_SIZE];


public:

	Proc();
	~Proc();

	bool Processing(char* name_file_in);
};



#endif
