/* main.c - Fõprogram
 * brainfuck interpreter
 * v0.8
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
int debug = 0;
int err = 0;
int loaded = 0;

const char *help = "commands:\n"
		   " load x    : load file(x)\n"
		   " list (l)  : display the loaded program\n"
		   " run (r)   : run the loaded program\n"
		   " debug (d) : start debugging\n"
		   " trans (t) : translate code into AT&T assembly\n"
		   " help (h)  : this screen\n"
		   " quit (q)  : quit from bfi";
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
		loaded = 1;
    	}
    }

    memset(program, 0, PROGRAM_SIZE);

    if(loaded){
	    if((char_ctr = loadf(fname, program)) <= 0){
		fprintf(stderr, "Cannot open file: %s\n", fname);
		return 2;
	    }
    }else{
    	fprintf(stderr, "File name wasn't definied.");
	return 2;
    }

    if(as){
    	if(loaded){
		if((err = genS(fname, program)) < 0)
			fprintf(stderr, "Cannot open output file.");
    	}else{
    		fprintf(stderr, "File name wasn't definied.");
		return 2;
    	}

    }else{
    	printf("brainfuck interpreter/translater v0.8\n");
    	printf("2013, gmb\n\n");
	printf("File loaded: %s\n", fname);
	printf("Characters loaded: %d\n", char_ctr);
	printf("\nType 'help' for available commands!\n");

	int instruct = 0;

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
		else if(!strcmp(cmd, "debug") || !strcmp(cmd, "d")){
			printf("Reloading file without comments ... ");

			if((err = loadf_nocomment(fname, program)) <= 0)
				printf("FAILED\n");
			else{
				printf("DONE\n");
				printf("Starting program.\n");
				printf("Controls: n - next step, s - stop debugging\n");
				init_mem();

				char ch;
				do
				{
					if(instruct >= strlen(program))
					{
						printf("Program finished.\n");
						break;
					}
					ch = _getch();

					if(ch == 'n')
						run_debug(program, instruct++);
				}while(ch != 's');
			}
		}
		else if(!strcmp(cmd, "trans") || !strcmp(cmd, "t")){
			printf("Creating output file: %s.s ... ", fname);

			if((err = genS(fname, program)) < 0)
				printf("FAILED\n");
			else
				printf("DONE\n");
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
