/* bfi.c - brainfuck fájlbetöltõ
 * 2013, gmb */

#include "loadf.h"

int loadf(const char *fname, char *program)
{
	FILE* fp;
	int c, i = 0;


	if((fp = fopen(fname, "r")) == NULL)
		return -1;

	do{
		c = fgetc(fp);

		if(c != EOF)
			program[i++] = c;

	}while(c != EOF);

	fclose(fp);

	return i;
}
