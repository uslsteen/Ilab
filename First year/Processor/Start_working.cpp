#include "start_working.h"
#include "asm.h"
#include "disasm.h"
#include "proc.h"


void Start_working()
{
	Asm assembler;
	Proc processor;
	Disasm disassembler;

	char in_file[MAX_FILE_NAME] = { {0} };
	char out_file[MAX_FILE_NAME] = { {0} };
	int mode = 0, check = 0, choice = 0;

	WELCOME

		while (true)
		{
			printf(ANSI_COLOR_RED"**   -Input num to start working:   **\n" ANSI_COLOR_RESET);

			if ((check = scanf("%d", &mode)) != 1)
			{
				printf("Error in scanf start_working(1)!\n");
				return;
			}

			switch (mode)
			{
			case 0:

				printf("Do you trully want to exit, dude?\n");


				while (true)
				{
					choice = -1;

					printf("Input '1' to leave the program.\n\nInput '0' to continue working.\n\n");

					if (check = scanf("%d", &choice) != 1)
						printf("Error in scanf start_working(2)!\n\n");


					if (choice == 1)
					{
						GOODBYE
							return;
					}

					else if (choice == 0)
						break;
					
					else if (choice != 0 && choice != 1)
					{
						printf("\nYou fucked my brain, dude. Common! Try again. What do you want?\n\n");
					}
				}

				break;


			case 1:

				INPUT(IN_FILE, in_file)

				INPUT(OUT_FILE, out_file)

					if (assembler.Start_Working_Asm(in_file, out_file) == true)
						COMPLIMENT
	
					else
						FAILURE

						break;

			case 2:

				INPUT(IN_FILE, in_file)

					if (processor.Processing(in_file) == true)
					{
						COMPLIMENT
					}
					else
						FAILURE

						break;

			case 3:

				INPUT(IN_FILE, in_file)
					INPUT(OUT_FILE, out_file)

					if (disassembler.Disassembling(in_file, out_file) == true)
					{
						COMPLIMENT
					}
					else
						FAILURE

						break;


			default:
				printf("I don't undestand what you want from me, dude!\n\n");

				break;
			}

		}
}