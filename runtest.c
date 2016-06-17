/* File: runtest.c */
#include <stdio.h>
#include "modtest.h"
#include "vbrndtest.h"


/* Declaration Section
 *-------------------------------------------------------------------
 */
static const struct modcmd cmdlist[] = 
{
	{"vbrnd", vbrndtestfunc },
	{NULL, NULL}
};


/* Application Entry Point
 *-------------------------------------------------------------------
 */
int main(int argc, char **argv)
{
	struct cmds args;
	char *func;
	printf("Executing \'%s\'\n", argv[0]);
	args.cmd = NULL;
	args.func = NULL;
	
	if (argc < 2)
	{
		printf("usage: %s <module> <function>\n", argv[0]);
		printcmdlist(cmdlist);
		return 0;
	}
	func = NULL;
	if (argc > 2)
	{
		func = argv[2];
	}
	
	if (initargs(&args, argv[1], func) != 1)
	{
		puts("Unable to initialize args");
		return 1;
	}
	
	exectestcmds(cmdlist, &args);
	
	freeargs(&args);
	printf("cmd:  %p\n", args.cmd);
    printf("func: %p\n", args.func);
	return 0;
}



/* Public (extern) Functions Section
 *-------------------------------------------------------------------
 */



/* Private (static) Functions Section
 *-------------------------------------------------------------------
 */

