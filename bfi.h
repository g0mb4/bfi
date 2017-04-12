/* bfi.c - brainfuck értelmezõ, futtató
 * 2013, gmb */

#ifndef __BFI_H__
#define __BFI_H__

#include <conio.h>	/* _getch(), _putch() */
#include <string.h>	/* memset() */

#define MEMSIZE	30000

unsigned int getch10(void);

void init_mem(void);
void run(const char *program);
void do_work(unsigned char inst);

#endif
