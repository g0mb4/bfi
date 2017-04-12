/* bfi.c - brainfuck fájlbetöltõ
 * 2013, gmb */

#ifndef __LOADF_H__
#define __LOADF_H__

#include <stdio.h>	/* fopen(), fclose(), fgetc() */
#include <string.h>	/* memset() */

int loadf(const char *fname, char *program);
int loadf_nocomment(const char *fname, char *program);

#endif
