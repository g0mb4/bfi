/* bfi.c - brainfuck fájlbetöltõ
 * 2013, gmb */

#ifndef __LOADF_H__
#define __LOADF_H__

#include <stdio.h>	/* fopen(), fclose(), fgetc() */

int loadf(const char *fname, char *program);

#endif
