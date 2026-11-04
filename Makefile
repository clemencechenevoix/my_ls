# -- Variable -- #
CC = gcc
CFLAGS = -fsanitize=address -g3 -Wall
SOURCES = my_ls.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = my_ls

# -- default rule -- #
all: $(TARGET)

# -- executable link -- #
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CFLAGS)

# -- clean OBJECTS files -- #
clean:
	rm -f $(OBJECTS)

# -- clean OBJECTS and TARGET files -- #
fclean: clean
	rm -f $(TARGET)

# -- compile again -- #
re: fclean all