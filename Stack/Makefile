#Makefile

# Compiler and loader commands and flags
GCC             = gcc
GCC_FLAGS       = -g -std=c99 -Wall -O0

EXE 			= Stack min-Stack

defualt: all

# Target is the executable
all: Stack min-Stack

# Compile .c files
Stack: stack.c
	$(GCC) $(GCC_FLAGS) $< -o $@

min-Stack: min-stack.c
	$(GCC) $(GCC_FLAGS) $< -o $@

# Clean up the directory
clean:
	rm -f *.o *~ $(EXE)
