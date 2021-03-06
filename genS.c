#include "genS.h"

int genS(const char *fname, char *program){

	FILE *fp;
	char fout[32];
	int i, loop_ctr = 0;

	sprintf(fout, "%s.s", fname);

	if((fp = fopen(fout, "w")) == NULL)
		return -1;

	const char *header = "# this assembly file was generated by bfi\n\n"
			"\t.section .bss\n"
			"\t.comm memory, 30000\n"
			"\t.comm ptr, 4\n\n"
			"\t.section .text\n"
			"\t.globl _main\n"
			"_main:\n"
			"\tmovl $memory, %%ebx\n"
			"\tmovl $0, ptr\n";

	const char *footer = "\tpushl $0\n"
			     "\tcall _exit\n\n";

	fprintf(fp, header);

	for(i = 0; i < strlen(program); i++)
		switch(program[i]){
			case '+' : fprintf(fp, 	"\tincl (%%ebx)\n");
				   break;
			case '-' : fprintf(fp, 	"\tdecl (%%ebx)\n");
				   break;
			case '>' : fprintf(fp, 	"\tincl %%ebx\n"
						"\tincl ptr\n");
				   break;
			case '<' : fprintf(fp, 	"\tdecl %%ebx\n"
					       	"\tdecl ptr\n");
				   break;
			case '.' : fprintf(fp, 	"\tmovl ptr, %%edx\n"
					       	"\tmovb memory(, %%edx, 1), %%dl\n"
					       	"\tmovb %%dl, (%%esp)\n"
					       	"\tcall _putch\n");
				   break;
			case ',' : fprintf(fp, 	"\tmovl $0, %%eax\n"
					       	"\tcall _getch\n"
					       	"\tmovb %%al, (%%ebx)\n");
				   break;

			case '[' : fprintf(fp, 	"loop%02d:\n"
					       	"\tmovl ptr, %%edx\n"
					       	"\tmovb memory(, %%edx, 1), %%cl\n"
					       	"\tmovb $0, %%al\n"
					       	"\tcmp %%cl, %%al\n"
					       	"\tje loop%02d_end\n", loop_ctr, loop_ctr);
				   break;

			case ']' : fprintf(fp, 	"\tjmp loop%02d\n"
					       	"loop%02d_end:\n", loop_ctr, loop_ctr);
				   loop_ctr++;
				   break;
		}

	fprintf(fp, footer);
	fclose(fp);

	return 1;
}
