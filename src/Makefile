CC=gcc
CFLAGS=-I$(IDIR)

IDIR =../header
ODIR=../build
LDIR =../lib

LIBS=

_DEPS =
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


# A dummy make RULE
# target : prequisite1 [prequisiteN]
#
# %  declares a pattern
# $@ the target
# $< the first prequisite
# $^ all prequisites speparated by spaces


# Rule for generating object files
#
$(ODIR)/%.o : %.c $(DEPS)

	$(CC) -c -o $@ $< $(CFLAGS)


# Rule for creating the binary
#
daemon : $(OBJ)

	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


# .PHONY rule to keep make doing something with file named clean
#
.PHONY: clean


# Simple command
#
clean:

	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
