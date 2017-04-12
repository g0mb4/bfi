/* bfi.c - brainfuck fájlbetöltõ
 * 2013, gmb */

#include "loadf.h"

int loadf(const char *fname, char *program)
{
	FILE* fp;
	int c, i = 0;


	if((fp = fopen(fname, "r")) == NULL)
		return -1;

	memset(program, 0, 1024);

	do{
		c = fgetc(fp);

		if(c != EOF)
			program[i++] = c;

	}while(c != EOF);

	program[i] = '\0';

	fclose(fp);

	return i;
}

int loadf_nocomment(const char *fname, char *program)
{
	FILE* fp;
	int c, i = 0;

	memset(program, 0, 1024);

	if((fp = fopen(fname, "r")) == NULL)
		return -1;

	do{
		c = fgetc(fp);

		if(c != EOF && (c == '+' || c == '-' || c == '>' || c == '<' || c == '[' || c == ']' || c == '.' || c == ','))
			program[i++] = c;

	}while(c != EOF);

	program[i] = '\0';

	fclose(fp);

	return i;
}
