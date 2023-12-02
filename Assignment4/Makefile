# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall

# Source files
src = main.c Dssimul.c

# Object files
obj = $(src:.c=.o)

# Executable file name
exe = DSSimul

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
