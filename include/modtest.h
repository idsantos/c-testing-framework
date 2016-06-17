/* File: modtest.h */
#ifndef MODTEST_H
#define MODTEST_H

#ifdef __cplusplus
extern "C" {
#endif

struct modfunc
{
    const char *func;
    const char *funcname;
    void (*f) (void);
};

struct modcmd
{
    const char *cmd;
    const struct modfunc *funclist;
};

struct cmds
{
    char *cmd;
    char *func;
};

	extern void printcmdlist(const struct modcmd *cmdlist);
	extern void printfunclist(const struct modfunc *funclist);
	extern int initargs(struct cmds *pargs, const char *pmodule, const char *pfuncion);
	extern void freeargs(struct cmds *pargs);
	extern void exectestcmds(const struct modcmd *plist, struct cmds *pargs);

#ifdef __cplusplus
}
#endif

#endif /* MODTEST_H */
