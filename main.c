/* main.c - Fõprogram
 * brainfuck interpreter
 * v0.6
 * 2013, gmb */

#include <stdio.h>	/* printf() */
#include <conio.h>	/* _getch() */

#include "bfi.h"	/* init_mem(), run() */
#include "loadf.h"

#define PROGRAM_SIZE	1024

char program[PROGRAM_SIZE];
int char_ctr = 0;
char cmd[128];

const char *help = "commands: \n list (l) : display the loaded program\n run (r) : run the loaded program\n help (h) : this screen\n quit (q) : quit from bfi";

int main(int argc, char** argv)
{
    printf("brainfuck interpreter v0.6\n");
    printf("2013, gmb\n\n");

    if(argc != 2){
    	fprintf(stderr, "usage: bfi <file_name>\n");
    	return 1;
    }

    memset(program, 0, PROGRAM_SIZE);

    if((char_ctr = loadf(argv[1], program)) <= 0)
    {
    	fprintf(stderr, "Cannot open file: %s\n", argv[1]);
    	return 2;
    }

    printf("File loaded: %s\n", argv[1]);
    printf("Characters loaded: %d\n", char_ctr);
    printf("\nType 'help' for avaliable commands!\n", char_ctr);

    while(strcmp(cmd, "quit") != 0 && strcmp(cmd, "q") != 0)
    {
    	printf("\n# ");
    	scanf("%s", &cmd);
	int i;
	if(!strcmp(cmd, "list") || !strcmp(cmd, "l"))
	{
		for(i = 0; i < char_ctr; i++)
			_putch(program[i]);
	}else if(!strcmp(cmd, "run") || !strcmp(cmd, "r")){
		init_mem();
    		run(program);
	}
	else if(!strcmp(cmd, "help") || !strcmp(cmd, "h"))
		printf(help);
	else if(!strcmp(cmd, "quit") || !strcmp(cmd, "q"))
		printf("Bye!\n");
	else
		printf("dafuq?!");
    }

    return 0;
}
