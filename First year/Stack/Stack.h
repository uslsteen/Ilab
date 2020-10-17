#ifndef __STACK_H__
#define __STACK_H__
#endif

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

#define STK_CHECK(COND, ERROR) if (COND) \
                            {                                         \
                                stk->error = ERROR;                    \
                                return false;                               \
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

#define DATA(i) ((Elem_t*)(stk->data + sizeof(cannary_t)))[i]

//#define LENGTH_DATA (Elem_t)(&stk->pigeon2_data - &stk->pigeon1_data)
//#define LENGTH_STACK (Elem_t)(&stk->pigeon2 - &stk->pigeon1)

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

const size_t START_STACK_SIZE = 4;
const cannary_t RAVEN1 = 0xBABABEDA;
const cannary_t RAVEN2 = 0xABEDBABA;
const cannary_t RAVEN1_DATA = 0xDEDAABBA;
const cannary_t RAVEN2_DATA = 0xABBADEDA;
const size_t DELTA = 2;

template <typename Elem_t>
const Elem_t POISON_VALUE = -666;

#define LEV_OF_SEC 3


template <typename Elem_t>

struct stack_t
{
#if LEV_OF_SEC > 0

	cannary_t pigeon1;

#endif

	Elem_t* data;

#if LEV_OF_SEC > 0

	cannary_t *pigeon1_data, *pigeon2_data;

#endif

	size_t size;
	size_t stack_maxsize;
	int error;

#if LEV_OF_SEC > 1

	hash_t hash_data;
	hash_t hash_stack;

#endif

#if LEV_OF_SEC > 0

	cannary_t pigeon2;

#endif
};

//! The function for construction stack
//! @param[in] stk - selected stack structure

template <typename Elem_t>
void Stack_Construct(stack_t<Elem_t>* stk)
{
	assert(stk);

#if LEV_OF_SEC > 0

	stk->pigeon1 = RAVEN1;
	stk->pigeon2 = RAVEN2;

#endif

	stk->data = (Elem_t*)calloc(START_STACK_SIZE * sizeof(Elem_t) + sizeof(cannary_t) * 2, sizeof(stk->data[0]));

	stk->size = 0;
	stk->stack_maxsize = START_STACK_SIZE;

	Stack_Fill_Poison(stk, 0);

#if LEV_OF_SEC > 0 

	stk->pigeon1_data = (cannary_t*)(stk->data);
	stk->pigeon2_data = (cannary_t*)(stk->data + sizeof(cannary_t) + stk->stack_maxsize * sizeof(Elem_t)); 

	*stk->pigeon1_data = RAVEN1_DATA; 
	*stk->pigeon2_data = RAVEN2_DATA;

#endif

#if LEV_OF_SEC > 1

	stk->hash_data = 0; 
	stk->hash_stack = 0; 

#endif

	Stack_Assert(stk);

}

//! The function for filling poison
//! @param[in] stk - selected stack structure
//! @param[in] elem - the element from which is filled with poison

template <typename Elem_t>
void Stack_Fill_Poison(stack_t <Elem_t>* stk, size_t elem)
{
	assert(stk);

	for (size_t index = elem; index < stk->stack_maxsize; index++)
	{
		DATA(index) = POISON_VALUE<Elem_t>;
	}
}

//! The function for push element
//! @param[in] stk - selected stack structure
//! @param[in] elem - the element for pushing

template <typename Elem_t>
bool Stack_Push(stack_t <Elem_t>* stk, Elem_t number)
{
	assert(stk);
	Stack_Assert(stk);

	if (stk->size == stk->stack_maxsize)
	{
		if (!Stk_Resize(stk, stk->stack_maxsize * 2))
		{
			printf("Error with resize in push.\n");
			stk->error = STK_PUSH_ERR;
			return false;
		}
	}

	if (stk->size > stk->stack_maxsize)
	{
		printf("Error.\nStack overflow.\n");
		stk->error = STK_OVERFLOW; 
		return false;
	}

	DATA(stk->size++) = number;

#if LEV_OF_SEC > 1

	Hash_ReSum(stk);
	Stack_Assert(stk);

#endif

	return true;
}

//! The function for pop element
//! @param[in] stk - selected stack structure
//! @param[in] elem - the element for pop

template <typename Elem_t>
bool Stack_Pop(stack_t <Elem_t>* stk, Elem_t* number)
{
	assert(stk);
	Stack_Assert(stk);

	if (stk->stack_maxsize > START_STACK_SIZE && stk->size == (stk->stack_maxsize) / 2 - DELTA)

		if(!Stk_Resize(stk, (stk->stack_maxsize) / 2))
		{
			printf("Error with resize in pop\n");
			stk->error = STK_POP_ERR;
			return false;
		}

	if (stk->size == 0)
	{
		printf("Error.\nStack underflow.\n");
		stk->error = STK_UNDERFLOW; 
		return 0;
	}

	*number = DATA(--stk->size);

	Stack_Fill_Poison(stk, stk->size);

#if LEV_OF_SEC > 1

	Hash_ReSum(stk);

#endif


	Stack_Assert(stk);

	return true;
}

//! The function for distruction stack
//! @param[in] stk - selected stack structure

template <typename Elem_t>
bool Stack_Distruct(stack_t <Elem_t>* stk)
{
	assert(stk);

	Stack_Assert(stk);

	free(stk->data);
	stk->stack_maxsize = START_STACK_SIZE;
	stk->size = 0;

	return true;
}

//! The function for resizing data
//! @param[in] stk - selected stack structure
//! @param[in] delta_size - new stack size

// хранить последние операции со стэком: если послдение 

template <typename Elem_t>
bool Stk_Resize(stack_t <Elem_t>* stk, int delta_size)
{
	assert(stk);
	Stack_Assert(stk);

	
	if (delta_size < START_STACK_SIZE)
	{
		printf("Error with new size\n");
		stk->error = STK_RESIZE_ERR;

		Stack_Assert(stk);
		return false;
	}
	

	Elem_t *new_data = (Elem_t* )realloc(stk->data, delta_size * sizeof(Elem_t) + sizeof(cannary_t) * 2);

	if (new_data == NULL)
	{
		printf("Error with realloc.\n");
		stk->error = STK_RESIZE_ERR; 

		return false; 
	}
	
	stk->data = new_data;
	stk->stack_maxsize = delta_size;
	Stack_Fill_Poison(stk, stk->size);

#if LEV_OF_SEC > 0

	stk->pigeon2_data = (cannary_t*)(stk->data + stk->stack_maxsize * sizeof(Elem_t) + sizeof(cannary_t) * 2);
	*(stk->pigeon2_data) = RAVEN2_DATA;

#endif

	Stack_Assert(stk);

	return true;
}

#if LEV_OF_SEC > 1

template <typename Elem_t>
hash_t Hash_Sum(const Elem_t stk, size_t size = 1)
{
	assert(stk != nullptr);

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
hash_t Hash_ReSum(stack_t<Elem_t>* stk)
{
	assert(stk);

	stk->hash_stack = 0;
	stk->hash_stack = Hash_Sum(stk);

	stk->hash_data = 0;
	stk->hash_data = Hash_Sum(stk->data, stk->stack_maxsize * sizeof(Elem_t) + 2 * sizeof(cannary_t));

	return stk->hash_data;
}

#endif

//!Start of security_helper function:
//! The function for filling stack.error (verification)
//! @param[in] stk - selected stack structure

template <typename Elem_t>
bool Stack_Ok(stack_t <Elem_t>* stk)
{
	assert(stk);

	STK_CHECK(stk->size < 0, STK_UNDERFLOW);
	STK_CHECK(stk->size > (stk->stack_maxsize), STK_OVERFLOW);

#if LEV_OF_SEC > 0

	STK_CHECK(stk->pigeon1 != RAVEN1, STK_CANNARY1_ERR);
	STK_CHECK(stk->pigeon2 != RAVEN2, STK_CANNARY2_ERR);

	STK_CHECK(*(stk->pigeon1_data) != RAVEN1_DATA, STK_CANNARY1_DATA);
	STK_CHECK(*(stk->pigeon2_data) != RAVEN2_DATA, STK_CANNARY2_DATA);

#endif

#if LEV_OF_SEC > 1

	hash_t prev_hash_data = stk->hash_data;
	hash_t prev_hash_stack = stk->hash_stack;

	STK_CHECK(prev_hash_data != Hash_ReSum(stk), STK_HASH_DATA_ERROR);
	STK_CHECK(prev_hash_stack != Hash_ReSum(stk), STK_HASH_STACK_ERROR);

#endif

	return true;
}

//! The function for processing stack.error
//! @param[in] stk - selected stack structure

template <typename Elem_t>
bool Stack_Proc_Error(stack_t <Elem_t>* stk)
{
	assert(stk);

	switch (stk->error)
	{ 
	case STK_UNDERFLOW: Stack_Dump(stk, "STACK IS UNDERFLOW", STK_LOCATION);
		break;

	case STK_OVERFLOW: Stack_Dump(stk, "STACK IS UNDERFLOW", STK_LOCATION);
		break;

#if LEV_OF_SEC > 0

	case STK_CANNARY1_DATA: Stack_Dump(stk, "CANNARY1_DATA IS DEAD!", STK_LOCATION);
		break;

	case STK_CANNARY2_DATA: Stack_Dump(stk, "CANNARY2_DATA IS DEAD!", STK_LOCATION);
		break;

	case STK_CANNARY1_ERR: Stack_Dump(stk, "CANNARY1_STACK IS DEAD!", STK_LOCATION);
		break;

	case STK_CANNARY2_ERR: Stack_Dump(stk, "CANNARY2_STACK IS DEAD!", STK_LOCATION);
		break;

#endif

	case STK_RESIZE_ERR: Stack_Dump(stk, "ERROR WITH RESIZING MEMORY!", STK_LOCATION);
		break;

	case STK_DATA_ERR: Stack_Dump(stk, "DATA - NULLPTR!", STK_LOCATION);

#if LEV_OF_SEC > 1

	case STK_HASH_DATA_ERROR: Stack_Dump(stk, "ERROR WITH DATA HASH!", STK_LOCATION);

	case STK_HASH_STACK_ERROR: Stack_Dump(stk, "ERROR WITH STACK HASH!", STK_LOCATION);
#endif


	default: printf("\n");
	}

	return true;
}


//Start Stack_Assert function
//! The function for 
//! @param[in] stk - selected stack structure
//! @param[in] elem - the element from which is filled with poison


template <typename Elem_t>
bool Stack_Assert(stack_t <Elem_t>* stk)
{
	assert(stk);
	
	if (stk->error != 0)
	{
		Stack_Proc_Error(stk);
		return false; 
	}

	if (!Stack_Ok(stk))
	{
		Stack_Proc_Error(stk);
		return false;
	}
	
	return true;
}

//End of stack security function

template <typename Elem_t>
void Stack_Dump(stack_t <Elem_t>* stk, const char error_com[], const char filename[], int err_line, const char func_name[])
{
	START_DUMP

		if (stk->data == NULL)
		{
			printf("DUMP FROM %s %s %d %s.\n\n.DATA - IS NULLPTR!!!\n\n", error_com, filename, err_line, func_name);
		}

	printf(ANSI_COLOR_CYAN"DUMP FROM %s %s %d %s.\n\n" ANSI_COLOR_WHITE , error_com, filename, err_line, func_name);

	printf("{\n\n");

#if LEV_OF_SEC > 0
	printf(ANSI_COLOR_MAGENTA"pidgeon1 = %llX\n\n" ANSI_COLOR_RESET, stk->pigeon1);

#endif

	printf("size = %d\n\n", stk->size);
	printf("Maximum size of stack: maxsize = %d\n\n", stk->stack_maxsize);
	printf("Name of stack array: data[%d]:\n\n", stk->stack_maxsize);

	if (stk->data != NULL)
	{

#if LEV_OF_SEC > 0
		printf(ANSI_COLOR_YELLOW "pidgeon1_data = %llX\n\n" ANSI_COLOR_RESET , *stk->pigeon1_data);

#endif
		for (size_t index = 0; index < stk->stack_maxsize; index++)
		{
			printf("  %c [%d] = ", index < stk->size ? '*' : ' ', index);

			printf(ANSI_COLOR_RED"%c\n" ANSI_COLOR_RESET, ((Elem_t*)(stk->data + sizeof(cannary_t)))[index]);

			if (DATA(index) == POISON_VALUE<Elem_t>)
			{
				printf("   (POISON???)\n");
			}

		}

#if LEV_OF_SEC > 0
		printf(ANSI_COLOR_YELLOW"pidgeon2_data = %llX\n\n" ANSI_COLOR_RESET, *stk->pigeon2_data);

#endif
	}
	
#if LEV_OF_SEC > 1
	printf("DATA HASH = %llX\n\n", stk->hash_data);
	printf("STACK HASH = %llX\n\n", stk->hash_stack);
#endif

#if LEV_OF_SEC > 0
	printf(ANSI_COLOR_MAGENTA"pidgeon2 = %llX\n\n" ANSI_COLOR_RESET, stk->pigeon2);
#endif
	printf("}\n\n");

	END_DUMP
}

template <typename Elem_t>
void Stack_Start_Working(stack_t<Elem_t>* stk)
{
	int select_mode = 0;
	Elem_t push = 0, pop = 0; // 

	STK_MODE;

	while (true)
	{
		printf("Enter the numer to select function.\n");

		scanf("%d", &select_mode);

		switch (select_mode)
		{

		case 0:

			return;

		case 1:

			std::cin >> push;

			if (Stack_Push(stk, push))
			{
				printf("Input completed successful\n");
				break;
			}
			else
			{
				printf("Error with push.\n");
				break;
			}

		case 2:

			if (Stack_Pop(stk, &pop))
			{
				printf("Output completed successful.\n");
				break;
			}
			else
			{
				printf("Error with pop\n");
				break;
			}

		case 3:

			Stack_Dump(stk, " ", STK_LOCATION);
			break; 

		default:

			printf("Error.\nUnable to determine mode.\n");
		}
	}
}