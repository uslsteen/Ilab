#ifndef __STACK_H__
#define __STACK_H__


#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <iostream>

#pragma warning (disable: 4996 4090)

#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_COLOR_RESET      "\x1b[0m"

#define STK_CHECK(COND, ERROR) if (COND)								\
                            {											\
                                error = ERROR;							\
                                return false;							\
                            }


#define STK_MODE			printf("Enter the numer to select function.\n\n");                     \
							printf("0 - Exit.\n\n");								   				\
							printf("1 - Push_Function, put the element to stack.\n\n");				 \
							printf("2 - Pop_Function, take the element from stack.\n\n");			  \
							printf("3 - Dump_Function, get information about stack condition.\n\n");


#define START_DUMP			printf(ANSI_COLOR_RED"____________________DUMP FUNCTION STARTED____________________\n" ANSI_COLOR_RESET); \
							printf(ANSI_COLOR_MAGENTA"____________________ADAM'S VERSION 1.0____________________\n" ANSI_COLOR_RESET);\

#define END_DUMP			printf(ANSI_COLOR_RED "____________________END OF DUMP FUNCTION____________________\n\n" ANSI_COLOR_RESET );\



#define CREATE_SEP			printf("_________________________________________________________\n"); \
							printf("                                                         \n"); \
							printf("_________________________________________________________\n");


#define STK_LOCATION __FILE__, __LINE__, __FUNCSIG__



#define DATA(i) ((Elem_t*)(data + sizeof(cannary_t)))[i]


enum
{
	STK_UNDERFLOW = -1,
	STK_OVERFLOW = 2,
	STK_CANNARY1_ERR = 3,
	STK_CANNARY2_ERR = 4,
	STK_PUSH_ERR = 5,
	STK_POP_ERR = 6,
	STK_RESIZE_ERR = 7,
	STK_CANNARY1_DATA = 8,
	STK_CANNARY2_DATA = 9,
	STK_DATA_ERR = 10,
	STK_HASH_DATA_ERROR = 11,
	STK_HASH_STACK_ERROR = 12
};

typedef unsigned long long cannary_t;
typedef unsigned long long hash_t;

const size_t START_STACK_SIZE = 2;
const cannary_t RAVEN1 = 0xBABABEDA;
const cannary_t RAVEN2 = 0xABEDBABA;
const cannary_t RAVEN1_DATA = 0xDEDAABBA;
const cannary_t RAVEN2_DATA = 0xABBADEDA;
const size_t DELTA = 2;

template <typename Elem_t>
const Elem_t POISON_VALUE = -666;


#define LEV_OF_SEC 0


template <typename Elem_t>

class Stack
{

private:

#if LEV_OF_SEC > 0

	cannary_t pigeon1;

#endif

	char* data;

#if LEV_OF_SEC > 0

	cannary_t* pigeon1_data, * pigeon2_data;

#endif

	size_t size;
	size_t stack_maxsize;
	int error;

#if LEV_OF_SEC > 0

	cannary_t pigeon2;

#endif

public:

	Stack(void)
	{

#if LEV_OF_SEC > 0

		pigeon1 = RAVEN1;
		pigeon2 = RAVEN2;

#endif

		data = (char*)calloc(START_STACK_SIZE * sizeof(Elem_t) + sizeof(cannary_t) * 2, sizeof(data[0]));

		if (data == nullptr)
		{
			Stack_Assert();
		}

		size = 0;
		stack_maxsize = START_STACK_SIZE;

		Stack_Fill_Poison(0);


#if LEV_OF_SEC > 0 

		pigeon1_data = (cannary_t*)(data);
		pigeon2_data = (cannary_t*)(data + sizeof(cannary_t) + stack_maxsize * sizeof(Elem_t));

		*pigeon1_data = RAVEN1_DATA;
		*pigeon2_data = RAVEN2_DATA;

#endif

#if LEV_OF_SEC > 1

		hash_data = 0;
		hash_stack = 0;

#endif

		Stack_Assert();
	}


//___________________________________________


	//template <typename Elem_t>
	void Stack_Fill_Poison(size_t elem)
	{
		for (size_t index = elem; index < stack_maxsize; index++)
		{
			DATA(index) = POISON_VALUE<Elem_t>;
		}
	}



	template <typename Elem_t>
	bool Stack_Push(Elem_t number)
	{
		Stack_Assert();

		if (size >= stack_maxsize)
		{
			if (!Stk_Resize(stack_maxsize * 2))
			{
				printf("Error with resize in push.\n");
				error = STK_PUSH_ERR;
				return false;
			}
		}

		if (size > stack_maxsize)
		{
			printf("Error.\nStack overflow.\n");
			error = STK_OVERFLOW;
			return false;
		}

		DATA(size++) = number;

#if LEV_OF_SEC > 1

		Hash_ReSum();
		Stack_Assert();

#endif

		return true;
	}


	template <typename Elem_t>
	bool Stack_Pop(Elem_t* number)
	{
		Stack_Assert();

		if (stack_maxsize > START_STACK_SIZE && size == (stack_maxsize) / 2 - DELTA)

			if (!Stk_Resize((stack_maxsize) / 2))
			{
				printf("Error with resize in pop\n");
				error = STK_POP_ERR;
				return false;
			}

		if (size == 0)
		{
			printf("Error.\nStack underflow.\n");
			error = STK_UNDERFLOW;
			return 0;
		}

		*number = DATA(--size);

		Stack_Fill_Poison(size);

#if LEV_OF_SEC > 1

		Hash_ReSum();

#endif

		Stack_Assert();

		return true;
	}

	//! The function for distruction stack
	//! @param[in] stk - selected stack structure


	~Stack(void)
	{

#if LEV_OF_SEC > 0

		pigeon1_data = nullptr;
		pigeon2_data = nullptr;
#endif


		if (data != nullptr)
		{
			free(data);
		}

		stack_maxsize = START_STACK_SIZE;
		size = 0;
	}

	//! The function for resizing data
	//! @param[in] stk - selected stack structure
	//! @param[in] delta_size - new stack size



	//template <typename Elem_t>
	bool Stk_Resize(size_t delta_size)
	{
		Stack_Assert();

		if (delta_size < START_STACK_SIZE)
		{
			printf("Error with new size\n");
			error = STK_RESIZE_ERR;

			Stack_Assert();

			return false;
		}


		char* new_data = (char*)realloc(data, delta_size * sizeof(Elem_t) + sizeof(cannary_t) * 2);

		if (new_data == NULL)
		{
			printf("Error with realloc.\n");
			error = STK_RESIZE_ERR;

			return false;
		}

		data = new_data;
		stack_maxsize = delta_size;
		Stack_Fill_Poison(size);

#if LEV_OF_SEC > 0

		pigeon2_data = (cannary_t*)(data + stack_maxsize + sizeof(cannary_t));
		*pigeon2_data = RAVEN2_DATA;

#endif

		Stack_Assert();

		return true;
	}


#if LEV_OF_SEC > 1

	template <typename Elem_t>
	hash_t Hash_Sum(const Elem_t stk, size_t size = 1)
	{
		const unsigned char* bytes = (unsigned char*)stk;
		size_t bytes_len = sizeof(*stk) * size;
		hash_t hash = 0;

		for (size_t i = 0; i < bytes_len; i++)
		{
			hash += (bytes[i]);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}


	template <typename Elem_t>
	hash_t Hash_ReSum(void)
	{
		hash_stack = 0;
		hash_stack = Hash_Sum();

		hash_data = 0;
		hash_data = Hash_Sum(data, stack_maxsize * sizeof(Elem_t) + 2 * sizeof(cannary_t));

		return hash_data;
	}

#endif



	bool Stack_Ok(void)
	{
		STK_CHECK(size < 0, STK_UNDERFLOW);
		STK_CHECK(size > (stack_maxsize), STK_OVERFLOW);

#if LEV_OF_SEC > 0

		STK_CHECK(pigeon1 != RAVEN1, STK_CANNARY1_ERR);
		STK_CHECK(pigeon2 != RAVEN2, STK_CANNARY2_ERR);

		STK_CHECK(*pigeon1_data != RAVEN1_DATA, STK_CANNARY1_DATA);
		STK_CHECK(*pigeon2_data != RAVEN2_DATA, STK_CANNARY2_DATA);

#endif

#if LEV_OF_SEC > 1

		hash_t prev_hash_data = hash_data;
		hash_t prev_hash_stack = hash_stack;

		STK_CHECK(prev_hash_data != Hash_ReSum(), STK_HASH_DATA_ERROR);
		STK_CHECK(prev_hash_stack != Hash_ReSum(), STK_HASH_STACK_ERROR);

#endif

		return true;
	}





	bool Stack_Proc_Error(void)
	{
		switch (error)
		{
		case STK_UNDERFLOW: Stack_Dump("STACK IS UNDERFLOW", STK_LOCATION);
			break;

		case STK_OVERFLOW: Stack_Dump("STACK IS UNDERFLOW", STK_LOCATION);
			break;

#if LEV_OF_SEC > 0

		case STK_CANNARY1_DATA: Stack_Dump("CANNARY1_DATA IS DEAD!", STK_LOCATION);
			break;

		case STK_CANNARY2_DATA: Stack_Dump("CANNARY2_DATA IS DEAD!", STK_LOCATION);
			break;

		case STK_CANNARY1_ERR: Stack_Dump("CANNARY1_STACK IS DEAD!", STK_LOCATION);
			break;

		case STK_CANNARY2_ERR: Stack_Dump("CANNARY2_STACK IS DEAD!", STK_LOCATION);
			break;

#endif

		case STK_RESIZE_ERR: Stack_Dump("ERROR WITH RESIZING MEMORY!", STK_LOCATION);
			break;

		case STK_DATA_ERR: Stack_Dump("DATA - NULLPTR!", STK_LOCATION);

#if LEV_OF_SEC > 1

		case STK_HASH_DATA_ERROR: Stack_Dump("ERROR WITH DATA HASH!", STK_LOCATION);

		case STK_HASH_STACK_ERROR: Stack_Dump("ERROR WITH STACK HASH!", STK_LOCATION);
#endif


		default: printf("\n");
		}

		return true;
	}


	//Start Stack_Assert function
	//! The function for 
	//! @param[in] stk - selected stack structure
	//! @param[in] elem - the element from which is filled with poison


	bool Stack_Assert(void)
	{
		//assert(stk);

		if (error != 0)
		{
			Stack_Proc_Error();
			return false;
		}

		if (!Stack_Ok())
		{
			Stack_Proc_Error();
			return false;
		}

		return true;
	}

	//End of stack security function


	void Stack_Dump(const char error_com[], const char filename[], int err_line, const char func_name[])
	{
		START_DUMP

			if (data == NULL)
			{
				printf("DUMP FROM %s %s %d %s.\n\n.DATA - IS NULLPTR!!!\n\n", error_com, filename, err_line, func_name);
			}

		printf(ANSI_COLOR_CYAN"DUMP FROM %s %s %d %s.\n\n" ANSI_COLOR_WHITE, error_com, filename, err_line, func_name);

		printf("{\n\n");

#if LEV_OF_SEC > 0
		printf(ANSI_COLOR_MAGENTA"pidgeon1 = %llX\n\n" ANSI_COLOR_RESET, pigeon1);

#endif

		printf("size = %d\n\n", size);
		printf("Maximum size of stack: maxsize = %d\n\n", stack_maxsize);
		printf("Name of stack array: data[%d]:\n\n", stack_maxsize);

		if (data != NULL)
		{

#if LEV_OF_SEC > 0
			printf(ANSI_COLOR_YELLOW "pidgeon1_data = %llX\n\n" ANSI_COLOR_RESET, *pigeon1_data);

#endif
			for (size_t index = 0; index < stack_maxsize; index++)
			{
				printf("  %c [%d] = ", index < size ? '*' : ' ', index);

				printf(ANSI_COLOR_RED"%d\n" ANSI_COLOR_RESET, ((Elem_t*)(data + sizeof(cannary_t)))[index]);

				if (DATA(index) == POISON_VALUE<Elem_t>)
				{
					printf("   (POISON???)\n");
				}

			}

#if LEV_OF_SEC > 0

			printf(ANSI_COLOR_YELLOW"pidgeon2_data = %llX\n\n" ANSI_COLOR_RESET, *pigeon2_data);

#endif
		}

#if LEV_OF_SEC > 1

		printf("DATA HASH = %llX\n\n", hash_data);
		printf("STACK HASH = %llX\n\n", hash_stack);
#endif

#if LEV_OF_SEC > 0

		printf(ANSI_COLOR_MAGENTA"pidgeon2 = %llX\n\n" ANSI_COLOR_RESET, pigeon2);

#endif
		printf("}\n\n");

		END_DUMP
	}

#if LEV_OF_SEC > 1

	hash_t hash_data;
	hash_t hash_stack;

#endif

	// ______________________________________________________________________________________ // 

};

#endif

