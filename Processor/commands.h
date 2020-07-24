
#ifndef __commands__
#define __commands__


#define DATA_SIZEOF sizeof(int)


#define STACK_PUSH(elem)  stk.Stack_Push(elem)
#define STACK_POP(elem)   stk.Stack_Pop(elem)


#define GET_INIT_VARIABLES  int elem1 = 0, elem2 = 0;										\
																							\
				if (STACK_POP(&elem1) != true || STACK_POP(&elem2) != true)					\
						    {																\
						    	printf("Error in STACK_POP in get_init_variables.\n");		\
						    	return false;												\
						    }																								

#define GET_INIT_VARIABLE int elem = 0;													\
																						\
						if (!STACK_POP(&elem))											\
						{																\
							printf("Error in STACK_POP get_init_variable");				\
							return false;												\
						}																


#define _ ,


DEF_CMD(PUSH, 1,

	{
	double arg_push = 0;

	if (sscanf(program[program_counter].line_ptr + position, "%lf", &arg_push) == 1)
	{
		*((int*)buffer_out1) = (int)(arg_push * DBLE_CFF);
		buffer_out1 = (char*)((int*)buffer_out1 + 1);
		//buffer_out1++;

		buffer_out_size += DATA_SIZEOF;
	}
		else
			{
			  printf("Sorry. I cant find this command, dude %d\n", program_counter + 1);
			  return false;
			}
	},

	{
		STACK_PUSH(*(int*)program_ptr);
		program_ptr += DATA_SIZEOF;
	},

	{
		sprintf(buffer_out1, "%d", *((int*)program_ptr) / DBLE_CFF);

		buffer_out1 += DATA_SIZEOF;
		program_ptr += DATA_SIZEOF;
	})


	DEF_CMD(PUSH_REG, 13,
		{
			char arg_push_reg1 = 0 _ arg_push_reg2 = 0;

			if ((sscanf(program[program_counter].line_ptr + position _ " %c%c" _ & arg_push_reg1 _ & arg_push_reg2) == 2) && toupper(arg_push_reg2) == 'X')
			{
				*buffer_out1++ = toupper(arg_push_reg1) + 1 - 'A';
				buffer_out_size++;
			}

			else
			{
				printf("Sorry, but I cant find argument for push_reg in line: %d.\n\n" _ program_counter);
				return false;
			}

		},

  {

		STACK_PUSH(registers[*program_ptr - 1]);
		program_ptr++;

  },

  {
	   sprintf(buffer_out1, "%c""X"_ * program_ptr - 1 + 'A');
	   buffer_out1 += 2 * sizeof(char);
	   program_ptr++;

  })


		DEF_CMD(ADD, 2, {},

  {
	GET_INIT_VARIABLES
	STACK_PUSH(elem1 + elem2);

  }, {})


	  DEF_CMD(POP, 3,

		  {
			char arg_pop1 = 0 _ arg_pop2 = 0;

			if ((sscanf(program[program_counter].line_ptr + position _ " %c%c" _ & arg_pop1 _ & arg_pop2) == 2) && toupper(arg_pop2) == 'X')
			{
				*buffer_out1++ = toupper(arg_pop1) - 'A' + 1;
				buffer_out_size++;
			}

			else
			{
				printf("Sorry, dude, but I cant find argument for pop in this command %d" _ program_counter + 1);
				return false;
			}
		  },

  {
	if (STACK_POP(registers - 1 + *program_ptr) == false)
	{
		printf("Error in stack_pop.\n");
		return false;
	}

	program_ptr++;
  },

  {

	sprintf(buffer_out1 _ "%c""X" _ * program_ptr + 'A' - 1);

	buffer_out1 += 2 * sizeof(char);
	program_ptr++;

  })


	  DEF_CMD(MUL, 4, {},

	{
		GET_INIT_VARIABLES
		STACK_PUSH((int)((double)(elem1 / DBLE_CFF) * elem2));

	}, {})

	  DEF_CMD(DIV, 5, {},

	{
		GET_INIT_VARIABLES
		STACK_PUSH((int)((double)(elem1 * DBLE_CFF) / elem2));

	}, {})


		DEF_CMD(SQRT, 6, {},

	{
		GET_INIT_VARIABLE

		if (elem < 0)
		{
			printf("I cant calculate this value.\n");
			return false;
		}

		STACK_PUSH((int)(sqrt((double)elem / DBLE_CFF) * DBLE_CFF));

	}, {})


		DEF_CMD(SIN, 7, {},

	{
		GET_INIT_VARIABLE
		STACK_PUSH((int)(sin((double)elem / DBLE_CFF) * DBLE_CFF));

	}, {})

		DEF_CMD(COS, 8, {},

	{
		GET_INIT_VARIABLE
		STACK_PUSH((int)(cos((double)elem / DBLE_CFF) * DBLE_CFF));

	}, {})


		DEF_CMD(OUT, 9, {},

	{
		GET_INIT_VARIABLE
		printf("Take your out_elem, dude: %lf\n", (double)elem / DBLE_CFF);

	}, {})


		DEF_CMD(IN, 10, {},

	{
		double elem = 0;

		scanf("%lf", &elem);
		STACK_PUSH((int)(elem* DBLE_CFF));

	}, {})


		DEF_CMD(SUB, 11, {},

	{
		GET_INIT_VARIABLES
		STACK_PUSH(elem1 - elem2);

	}, {})


		DEF_CMD(MEW, 12, {},

	{
		printf("MSU SOSAT'.\n");

	}, {})



		DEF_CMD(END, -1, {},

	{
		return true;

	}, {})


#undef DATA_SIZEOF

#undef STACK_PUSH

#undef GET_INIT_VARIABLES

#undef GET_INIT_VARIABLE

#undef PUT_REG


#endif