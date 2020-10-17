#include "problem_lx.h"

enum { MAXLEN = 1024 };

#pragma warning (disable : 4996)

#if 0
int test_dump() {
	struct lexem_t lxs[5] = 
	{
	  {BRACE, {.b = LBRAC}}, {NUM, {.num = 2}}, {OP, {.op = MUL}}, {NUM, {.num = 2}}, {BRACE, {.b = RBRAC}}
	};

	struct lex_array_t larr = { lxs, 5, 5 };
	dump_lexarray(larr);
}
#endif

int main()
{
	int res = 0;
	struct lex_array_t larr;
	char inp[MAXLEN] = { 0 };
	int i = 0;

	res = scanf("%1023c", inp);
	//assert(res == 1);
	

	larr = lex_string(inp);

	if (larr.lexems == NULL) {
		printf("ERROR\n");
		return 0;
	}

	dump_lexarray(larr);

	free(larr.lexems);
	return 0;
}
