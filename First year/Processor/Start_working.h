#ifndef __START_WORKING_H__
#define __START_WORKING_H__

#include "inc_enums.h"


#define WELCOME  printf(ANSI_COLOR_MAGENTA"**   -Hello, dude! I am Processor on the Stack.   **\n\n" ANSI_COLOR_RESET);   \
				 printf(ANSI_COLOR_CYAN"**   -Look at my skills. I can do:   **\n\n" ANSI_COLOR_RESET);						     \
				 printf(ANSI_COLOR_YELLOW"           Enter '0' and go away.\n" ANSI_COLOR_RESET);									\
				 printf(ANSI_COLOR_YELLOW"           Enter '1' to assembly your program.\n" ANSI_COLOR_RESET);\
				 printf(ANSI_COLOR_YELLOW"           Enter '2' to process your program.\n" ANSI_COLOR_RESET);					\
				 printf(ANSI_COLOR_YELLOW"           Enter '3' to disassembly your program.\n\n" );




#define COMPLIMENT printf("** - Successful processing, dude! **\n\n");



#define FAILURE printf("** - Something went wrong, man. Check your code and try to find bug. **\n\n");



#define INPUT(MODE, BUF)	if (MODE == IN_FILE)																	\
							{																						\
								if ((check = Input("**   -Input name of in_file:   **\n", "%s", BUF)) == false)		\
									printf("**   -Error in input name of in_file.   **\n");							\
							}																						\
																													\
							else if (MODE == OUT_FILE)																\
							{																						\
								if ((check = Input("**   -Input name of out_file:   **\n", "%s", BUF)) == false);	\
							}				




#define GOODBYE  printf("**   -Bye. Nice to see you, dude! **\n"); 


void Start_working();

#endif
