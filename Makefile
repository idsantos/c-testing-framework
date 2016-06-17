CC=gcc
CFLAGS=-Wall -Werror -g
INCDIR=include
MODDIR=modules
OBJS=runtest.o modtest.o vbrndtest.o vbrnd.o

.PHONY: clean


all: runtest
	@echo runtest compiled successfully


runtest: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)


clean:
	$(RM) runtest
	$(RM) *.o


# $< = input
# $@ = output
.c.o:
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MODDIR) -c -o $@ $<


runtest.o: runtest.c $(INCDIR)/modtest.h $(INCDIR)/vbrndtest.h

modtest.o: modtest.c $(INCDIR)/modtest.h

vbrndtest.o: vbrndtest.c $(INCDIR)/vbrndtest.h $(MODDIR)/vbrnd.h

vbrnd.o: $(MODDIR)/vbrnd.c $(MODDIR)/vbrnd.h
	$(CC) $(CFLAGS) -I$(MODDIR) -c -o $@ $<

