/* File: modtest.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "modtest.h"

/* Declaration Section
 *-------------------------------------------------------------------
 */
static void exectestfunc(const struct modfunc *plist, const char *pfunc);
static void tolowchar(char *src);


/* Public (extern) Functions Section
 *-------------------------------------------------------------------
 */
void printcmdlist(const struct modcmd *cmdlist)
{
	const struct modcmd *pcmd;
	if (cmdlist == NULL)
	{
		return;
	}
	pcmd = cmdlist;
	puts("module list:");
	while (pcmd->cmd != NULL)
	{
		printf(" -> %s\n", pcmd->cmd);
		pcmd++;
	}
}

void printfunclist(const struct modfunc *funclist)
{
	const struct modfunc *pfunc;
	if (funclist == NULL)
	{
		return;
	}
	pfunc = funclist;
	puts("function list:");
	while (pfunc->func != NULL)
	{
		printf(" -> %s\n", pfunc->func);
		pfunc++;
	}
}


int initargs(struct cmds *pargs, const char *pmodule, const char *pfunction)
{
	size_t len;
	puts("\nInitializing args structure");
	if (pargs == NULL)
	{
		puts("pargs is NULL error");
		return 0;
	}
	len = strlen(pmodule);
	pargs->cmd = malloc(sizeof(*(pargs->cmd)) * len + 1); /* +1 for the terminating null */
	if (pargs->cmd == NULL)
	{
		puts("Memory allocation error occurred");
		return 0;
	}
	strcpy(pargs->cmd, pmodule);
	pargs->cmd[len] = '\0';
	tolowchar(pargs->cmd);
	printf("cmd: %s [%p]\n", pargs->cmd, pargs->cmd);
	
	if (pfunction == NULL)
	{
	    /* Note: it does not matter wheather pfunction is NULL
	     *  or not because that is handled at a later time
	     *  so we just return 1 at this point.
	     */
	    return 1;
	}
	len = strlen(pfunction);
	pargs->func = malloc(sizeof(*(pargs->func)) * len + 1); /* +1 for the terminating null */
	if (pargs->func == NULL)
	{
	    puts("Memory allocation error occurred");
		return 0;
	}
	strcpy(pargs->func, pfunction);
	pargs->func[len] = '\0';
	tolowchar(pargs->func);
	printf("func: %s [%p]\n", pargs->func, pargs->func);
	return 1;
}

void freeargs(struct cmds *pargs)
{
	puts("\nFreeing the args structure");
	if (pargs == NULL)
	{
		puts("pargs is NULL error");
		return;
	}
	if (pargs->cmd != NULL)
	{
		printf("cmd: %p\n", pargs->cmd);
		free(pargs->cmd);
		pargs->cmd = NULL;
	}
	
	if (pargs->func != NULL)
	{
	    printf("func: %p\n", pargs->func);
	    free(pargs->func);
	    pargs->func = NULL;
	}
}


void exectestcmds(const struct modcmd *plist, struct cmds *pargs)
{
    const struct modcmd *pcmd;
    puts("\nExecuting commands list");
    if (plist == NULL || pargs == NULL)
    {
        return;
    }
    pcmd = plist;
    while (pcmd->cmd != NULL)
    {
        printf("cmd: %s\n", pcmd->cmd);
        if (strcmp(pcmd->cmd, pargs->cmd) == 0)
        {
            /* found a match */
            break;
        }
        pcmd++;
    }
    if (pcmd->cmd == NULL)
    {
        printcmdlist(plist);
        return;
    }
    printf("\ntesting module %s\n", pcmd->cmd);
    exectestfunc(plist->funclist, pargs->func);
}




/* Private (static) Functions Section
 *-------------------------------------------------------------------
 */
void exectestfunc(const struct modfunc *plist, const char *pfunc)
{
    const struct modfunc *pitem;
    puts("\nExecuting function list");
    if (plist == NULL || pfunc == NULL)
    {
        printfunclist(plist);
        return;
    }
    pitem = plist;
    while (pitem->func != NULL)
    {
        printf("func: %s [%s()]\n", pitem->func, pitem->funcname);
        if (strcmp(pitem->func, pfunc) == 0)
        {
            /* found a match */
            break;
        }
        pitem++;
    }
    if (pitem->func == NULL)
    {
        printfunclist(plist);
        return;
    }
    if (pitem->f == NULL)
    {
        return;
    }
    pitem->f();
}
 
 
 
void tolowchar(char *src)
{
    char *pc;
    if (src == NULL)
    {
        return;
    }
    pc = src;
    while (*pc != '\0')
    {
        *pc = tolower(*pc);
        pc++;
    }
}



