#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>

char NUMBER_TOKENS[10][2] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

struct StructTokens
{
	char token[50];
	char *tokenType;
};

struct StructTokens arrayToken[100] = { "\0" };
int next = 0;
int quantityToken = 0;
char flagHeightPower = 0;
char flagPower = 1;

char *getTokenType(char *token);
int E();
int SIGN();
int term(char *tok);
int EXPR();
int VARIABLE();

void main()
{
	FILE *myFile;
	char *fileName = "input.txt";
	char myString[255] = { "\0" };
	char flag = 1;
	myFile = fopen(fileName, "r");

	char *pointerString;
	int len = 0;
	char delim[] = "*+-=^";
	printf("Input:   ");
	while (!feof(myFile))
	{
		fscanf(myFile, "%s", myString);
		printf("%s", myString);
		for (int i = 0; i < strlen(myString); i++)
			myString[i] = towupper(myString[i]);
		for (pointerString = myString; *pointerString != '\0'; (len > 0) ? pointerString += len : pointerString++)
		{
			len = strcspn(pointerString, delim);
			if (len == 0)
			{
				arrayToken[quantityToken].token[0] = *pointerString;
				quantityToken++;
				continue;
			}
			for (int i = 0; i < len; i++)
			{
				arrayToken[quantityToken].token[i] = *(pointerString + i);
			}
			quantityToken++;
		}
	}
	printf("\n\n");
	for (int i = 0; i < quantityToken; i++)
	{
		arrayToken[i].tokenType = getTokenType(arrayToken[i].token);
		printf("%d.<%s> [%s]\n", i + 1, arrayToken[i].token, arrayToken[i].tokenType);
	}
	if (E() == 0)
	{
		printf("\nERROR:\n   Token number: [%d]\n   Token name: <%s>\n", next, arrayToken[next - 1].token);
	}
	else
		if (flagHeightPower != 1)
			printf("\nERROR:\n   The highest power is not!\n");
		else
			printf("\nCompilation passed successful!\n");
	system("pause");
}

char *getTokenType(char *token)
{
	char flag = 1;
	for (int i = 0; i < 10; i++)
	{
		if (strncmp(token, NUMBER_TOKENS[i], 1) == 0)
		{
			flag = 0;
			break;
		}
	}
	if (flag == 0)
		return "CONST";
	else
	{
		if (strcmp(token, "=") == 0)
			return "EQUALLY";
		else
			if (strcmp(token, "+") == 0)
				return "PLUS";
			else
				if (strcmp(token, "-") == 0)
					return "MINUS";
				else
					if (strcmp(token, "*") == 0)
						return "COMP";
					else
						if (strcmp(token, "^") == 0)
							return "POWER";
						else
							return "VAR";
	}
}


int term(char *tok)
{
	if (next < quantityToken)
	{
		flagPower = 1;
		if (next != 0)
		{
			if ((strcmp(tok, "CONST") == 0) && (strcmp(arrayToken[next - 1].tokenType, "POWER") == 0) && (strcmp(arrayToken[next].token, "4") == 0))
				flagHeightPower = 1;
			if ((strcmp(tok, "CONST") == 0) && (strcmp(arrayToken[next - 1].tokenType, "POWER") == 0) && ((strlen(arrayToken[next].token) > 1) || (atoi(arrayToken[next].token) > 4)))
				flagPower = 0;
		}
		return !strcmp(arrayToken[next++].tokenType, tok);
	}
	else
		return 0;
}

int VARIABLE()
{
	int save = next;
	/*if (term("MINUS") && term("VAR") && term("POWER") && term("CONST"))
	{
		printf("term(""MINUS"") && term(""VAR"") && term(""POWER"") && term(""CONST"")\n");
		return 1;
	}
	else
	{
		next = save;
		if (term("VAR") && term("POWER") && term("CONST"))
		{
			printf("term(""VAR"") && term(""POWER"") && term(""CONST"")\n");
			return 1;
		}
		else
		{
			next = save;
			if (term("MINUS") && term("VAR"))
			{
				printf("term(""MINUS"") && term(""VAR"")\n");
				return 1;
			}
			else
			{
				next = save;
				if (term("VAR"))
				{
					printf("term(""VAR"")\n");
					return 1;
				}
				else
				{
					next = save;
					if (term("MINUS") && term("CONST"))
					{
						printf("term(""MINUS"") && term(""CONST"")\n");
						return 1;
					}
					else
					{
						next = save;
						if (term("CONST"))
						{
							printf("term(""CONST"")\n");
							return 1;
						}
					}
				}
			}
		}
	}*/
	return ((next = save, term("MINUS") && term("VAR") && term("POWER") && term("CONST"))
		|| (next = save, term("VAR") && term("POWER") && term("CONST"))
		|| (next = save, term("MINUS") && term("VAR"))
		|| (next = save, term("VAR"))
		|| (next = save, term("MINUS") && term("CONST"))
		|| (next = save, term("CONST"))) && flagPower;
}

int EXPR()
{
	int save = next;
	/*if (term("CONST") && term("COMP") && VARIABLE() && SIGN() && EXPR())
	{
		printf("term(""CONST"") && term(""COMP"") && VARIABLE() && SIGN() && EXPR()\n");
		return 1;
	}
	else
	{
		next = save;
		if (VARIABLE() && SIGN() && EXPR())
		{
			printf("VARIABLE() && SIGN() && EXPR()\n");
			return 1;
		}
		else
		{
			next = save;
			if (VARIABLE())
			{
				printf("VARIABLE()\n");
				return 1;
			}
		}
	}*/
	return (next = save, term("CONST") && term("COMP") && VARIABLE() && SIGN() && EXPR())
		|| (next = save, VARIABLE() && SIGN() && EXPR())
		|| (next = save, VARIABLE());
}

int SIGN()
{
	int save = next;
	/*if (term("PLUS"))
	{
		printf("term(""PLUS"")\n");
		return 1;
	}
	else
	{
		next = save;
		if (term("MINUS"))
		{
			printf("term(""MINUS"")\n");
			return 1;
		}
	}*/
	return (next = save, term("PLUS")) 
		 || (next = save, term("MINUS"));
}

int E()
{
	int save = next;
	/*if (EXPR() && term("EQUALLY") && term("CONST"))
	{
		printf("EXPR() && term(""EQUALLY"") && term(""CONST"")\n");
		return 1;
	}*/
	return (next = save, EXPR() && term("EQUALLY") && term("CONST"));
}