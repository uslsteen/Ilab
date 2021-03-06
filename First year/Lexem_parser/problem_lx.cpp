#include "problem_lx.h"

struct lex_array_t lex_string(const char* str)
{
	assert(str != NULL);

	struct lex_array_t larr = { (struct lexem_t*)malloc(ICAP * sizeof(struct lexem_t)), 0, ICAP };

	assert(larr.lexems != NULL);

	int i = 0, j = 0;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		larr.size = j;

		if (larr.capacity == j)
		{
			larr.capacity *= 2;
		}

		if (isspace(*(str + i)) != NULL)
		{
			continue;
		}

		else
			if (isdigit(*(str + i)) != NULL)
			{
				larr.lexems[j].lex.num = *(str + i);
				larr.lexems[j].kind = NUM;
				j++;
			}
			else
				if (*(str + i) == '(')
				{
					larr.lexems[j].lex.b = LBRAC;
					larr.lexems[j].kind = BRACE;
					j++;
				}
				else
					if (*(str + i) == ')')
					{
						larr.lexems[j].lex.b = RBRAC;
						larr.lexems[j].kind = BRACE;
						j++;
					}
					else
						if (*(str + i) == '+')
						{
							larr.lexems[j].lex.op = ADD;
							larr.lexems[j].kind = OP;
							j++;
						}
						else
							if (*(str + i) == '-')
							{
								larr.lexems[j].lex.op = SUB;
								larr.lexems[j].kind = OP;
								j++;
							}
							else
								if (*(str + i) == '*')
								{
									larr.lexems[j].lex.op = MUL;
									larr.lexems[j].kind = OP;
									j++;
								}
								else
									if (*(str + i) == '/')
									{
										larr.lexems[j].lex.op = DIV;
										larr.lexems[j].kind = OP;
										j++;
									}
									else
									{
										free(larr.lexems);
										larr.lexems = NULL;
										return larr;
									}
	}
	// TODO:
	// for each char in str
	//   if char reminds space, skip it
	//   if char reminds number, lex number
	//   if char reminds brace, lex brace
	//   if char reminds operation, lex operation
	//   otherwise free lex array, return NULL

	return larr;
}

static void print_op(enum operation_t opcode) 
{
	switch (opcode) 
	{
	case ADD: printf(" PLUS");
		break;

	case SUB: printf(" MINUS"); 
		break;

	case MUL: printf(" MUL"); 
		break;

	case DIV: printf(" DIV"); 
		break;

	default: assert(0 && "unknown opcode");
	}
}

static void print_brace(enum braces_t bracetype) 
{
	switch (bracetype) 
	{
	case LBRAC: printf(" LBRAC"); 
		break;

	case RBRAC: printf(" RBRAC");
		break;

	default: assert(0 && "unknown bracket");
	}
}

static void print_num(int n) 
{
	printf(" NUMBER:%d", n);
}

void
print_lexem(struct lexem_t lxm) 
{
	switch (lxm.kind)
	{
	case OP: print_op(lxm.lex.op); 
		break;

	case BRACE: print_brace(lxm.lex.b);
		break;

	case NUM: print_num(lxm.lex.num);
		break;

	default: assert(0 && "unknown lexem");
	}
}

void dump_lexarray(struct lex_array_t pl)
{
	int i = 0;
	assert(pl.lexems != NULL);

	for (i = 0; i < pl.size; ++i)
	{
		print_lexem(pl.lexems[i]);
	}
}
