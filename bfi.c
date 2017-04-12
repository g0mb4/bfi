#include "bfi.h"

static unsigned char memory[MEMSIZE];
static unsigned char *data_ptr = memory;
static unsigned int inst_ptr;
static unsigned int tmp;

unsigned int getch10(void)
{
	unsigned int ch = _getch();

	if(ch == 13)
		return 10;
	else
		return ch;
}

void init_mem(void)
{
	memset(memory, 0, MEMSIZE);
	inst_ptr = 0;
}

void run(const char* program)
{
	while(inst_ptr < strlen(program))
	{
		do_work(program[inst_ptr]);
		inst_ptr++;
	}
}

void do_work(unsigned char inst)
{
	switch(inst)
	{
		case '+' : ++*data_ptr; break;
		case '-' : --*data_ptr; break;
		case '>' : ++data_ptr; break;
		case '<' : --data_ptr; break;
		case '[' : tmp = inst_ptr; break;
		case ']' : inst_ptr = *data_ptr != 0 ? --tmp : inst_ptr; break;
		case '.' : _putch(*data_ptr); break;
		case ',' : *data_ptr = getch10(); break;
	}
}


