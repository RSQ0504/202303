# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall

# Source files
src = mem_test.c my_malloc.c

# Object files
obj = $(src:.c=.o)

# Executable file name
exe = program

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link into the executable
$(exe): $(obj)
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Default target
all: $(exe)

# Clean up generated files
clean:
	rm -f $(obj) $(exe)
