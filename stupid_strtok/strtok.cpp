#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct
{
	char* word;
	int len;
} words; 

char* Change_String(char text[], int len);
void Skip_Spaces(char** text);
void Skip_Non_Spaces(char** text);

int main()
{
	/*char* filename = {};
	scanf("%s", &filename);*/
	char text[] = "Hello, Intel dear user";
	int len = strlen(text);
	char *new_text = Change_String(text, len);
	printf("%s", new_text);

}

char* Change_String(char text[], int len)
{
	char* word_beg = NULL, *word_end = NULL;

	for (int i = 0; text[i] != '\0'; i++)
	{
		Skip_Spaces(&text);
		word_beg = text;

		Skip_Non_Spaces(&text);
		word_end = text;
		*word_end = '\0';
		return word_beg;
	}
}

void Skip_Spaces(char** text)
{
	while (**text == ' ' && **text != '\0')
	{
		*text+= 1;
	}
}

void Skip_Non_Spaces(char** text)
{
	while (**text != ' ' && **text != '\0')
	{
		*text+= 1;
	}
}





