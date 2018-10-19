# Makefile for programs in directory 08-Abstract-Data-Types
# ***************************************************************

all: driver

# ***************************************************************
# Parameters to control Makefile operation
# Note that the gccx command script must be defined

#CC = clang -I booklib 
#gcc -I..booklib  -o prog   prog.c  ../booklib/cslib.a
CC = gcc -I booklib
CFLAGS = 

# ***************************************************************
# Entry to bring the package up to date

all: $(PROGRAMS)

# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    scratch -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out graphics.ps

scratch: tidy
	rm -f *.o *.a $(PROGRAMS)

# ***************************************************************
# C compilations
	$(CC) $(CFLAGS) -c stack.c

driver.o: driver.c stack.h
	$(CC) $(CFLAGS) -c driver.c
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

# ***************************************************************
# Executable programs

driver: driver.o stack.o
	$(CC) $(CFLAGS) -o driver driver.o stack.o booklib/cslib.a
