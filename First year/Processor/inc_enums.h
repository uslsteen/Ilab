#ifndef __INC_EMUNS_H__
#define __INC_EMUNS_H__


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <math.h>

#include "Strings/strings.h"
#include "stack/Stack.h"


#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_COLOR_RESET      "\x1b[0m"


const int DBLE_CFF = 1000;
const int MAX_CMD_NAME = 10;

enum WORK_WITH_PROG
{
	MAX_FILE_NAME = 30,
	MEMORY_COEFFS = 2,
	IN_FILE = 0,
	OUT_FILE = 1
};




#endif //__INC_EMUNS_H__