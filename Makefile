# -- Variable -- #
SOURCES = $(shell find src -name "*.c")
OBJECTS = $(SOURCES:.c=.o)

TARGET = my_ls

CC = gcc
INCLUDE = -I include/
CFLAGS = -fsanitize=address -g3 -Wall -Werror -Wextra

# -- default rule -- #
all: $(TARGET)

# -- executable link -- #
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

# -- clean OBJECTS files -- #
clean:
	rm -f $(OBJECTS)

# -- clean OBJECTS and TARGET files -- #
fclean: clean
	rm -f $(TARGET)

# -- compile again -- #
re: fclean all