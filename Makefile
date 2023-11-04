CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =

# List the source files
SRCS = nndescent.c graph.c pqueue.c

# Derive object file names from source file names
OBJS = $(SRCS:.c=.o)

# List header files
HEADERS = nndescent.h graph.h pqueue.h

# The executable name
EXEC = nndescent

# The main target
all: $(EXEC)

# Compile each .c file into a .o file
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link all the object files into the executable
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# Clean command to remove generated files
clean:
	rm -f $(OBJS) $(EXEC)