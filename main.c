/* main.c - F�program
 * brainfuck interpreter
 * v0.7
 * 2013, gmb */

#include <stdio.h>	/* printf() */
#include <conio.h>	/* _getch() */

#include "bfi.h"	/* init_mem(), run() */
#include "loadf.h"
#include "genS.h"

#define PROGRAM_SIZE	1024

char program[PROGRAM_SIZE];
int char_ctr = 0;
char cmd[128];
int as = 0;

const char *help = "commands:\n"
		   " list (l) : display the loaded program\n"
		   " run (r)  : run the loaded program\n"
		   " help (h) : this screen\n"
		   " quit (q) : quit from bfi";
char *fname;

int main(int argc, char** argv)
{
    if(argc < 2){
    	fprintf(stderr, "usage: bfi <file_name> <options>\n\n"
			"options:\n"
			" -S : generate .s file w/ AT&T syntax\n\n"
			" no option means the interpreter\n");
    	return 1;
    }

    int i;
    for(i = 0; i < argc; i++)
    {
    	if(argv[i][0] == '-')
    	{
    		switch(argv[i][1])
    		{
    			case 'S': as = 1; break;

    		}
    	}else{
    		fname = argv[i];

    	}
    }

    memset(program, 0, PROGRAM_SIZE);

    if((char_ctr = loadf(fname, program)) <= 0)
    {
    	fprintf(stderr, "Cannot open file: %s\n", argv[1]);
    	return 2;
    }

    if(as){
	int err = genS(fname, program);

	if(err < 0)
		fprintf(stderr, "Cannot open output file.");

    }else{
    	printf("brainfuck interpreter/translater v0.7\n");
    	printf("2013, gmb\n\n");
	printf("File loaded: %s\n", fname);
	printf("Characters loaded: %d\n", char_ctr);
	printf("\nType 'help' for available commands!\n");

	while(strcmp(cmd, "quit") != 0 && strcmp(cmd, "q") != 0){

		printf("\n# ");
		scanf("%s", &cmd);
		int i;
		if(!strcmp(cmd, "list") || !strcmp(cmd, "l")){
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
    }

    return 0;
}
