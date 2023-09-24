# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall

# Source files
src = main.c list.c

# Object files
obj = $(src:.c=.o)

exe = program

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link into the executable
$(exe): $(obj)
	$(CC) $(CFLAGS) $^ -o $@

all: $(exe)

# Clean up generated files
clean:
	rm -f $(obj) $(exe)
