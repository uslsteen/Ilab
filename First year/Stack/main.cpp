#include "Stack.h"

/*
struct alpha
{
	int num1; 

	char apha1;
};
*/

int main()
{
	//stack_t<char> stk1;
	//stack_t<char> stk2;

	stack_t<char> stk1;

	Stack_Construct(&stk1);

	Stack_Start_Working(&stk1);

	Stack_Distruct(&stk1);

	//Stack_Constuct(&stk1);
	//Stack_Constuct(&stk2);
	//Stack_Start_Working(&stk1);

	//memcpy(&stk2, &stk1, sizeof(stack_t<char>));
	//printf("HHH\n");

	//Stack_Distruct(&stk1);
	//printf("HHH5\n");

	//Stack_Distruct(&stk2);
	//printf("HHH6\n");

	return 0;
}

