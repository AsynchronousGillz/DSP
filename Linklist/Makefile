#Makefile

# Compiler and loader commands and flags
GCC             = gcc
GCC_FLAGS       = -g -std=c99 -Wall -O0

EXE 			= Linklist

defualt: all

# Target is the executable
all: Linklist

# Compile .c files
Linklist: linklist.c
	$(GCC) $(GCC_FLAGS) $< -o $@

# Clean up the directory
clean:
	rm -f *.o *~ $(EXE)
