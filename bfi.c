/* bfi.c - brainfuck értelmezõ, futtató
 * 2013, gmb */

#include "bfi.h"

static unsigned char memory[MEMSIZE];
static unsigned char *data_ptr = memory;
static unsigned int inst_ptr;
static unsigned int tmp;
static unsigned int slot;

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
	slot = 0;
}

void run(const char* program)
{
	while(inst_ptr < strlen(program)){

		do_work(program[inst_ptr]);
		inst_ptr++;
	}
}

void do_work(unsigned char inst)
{
	switch(inst){
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

void run_debug(const char *program, int inst)
{
	if(inst < strlen(program)){

		if(program[inst] == '>') slot++;
		else if(program[inst] == '<') slot--;
		else if(program[inst] == '.') printf("o: ");
		else if(program[inst] == ',') printf("i: ");

		do_work(program[inst]);

		if(program[inst] == '.' || program[inst] == ',') printf("\n");

		printf("code: %c\tslot: %d\tdata:\t%u\n", program[inst], slot, *data_ptr);

	}
}


