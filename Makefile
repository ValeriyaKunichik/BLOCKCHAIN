CC = gcc
OUTPUT = my_blockchain
CFLAGS += -Wall -Wextra -Werror -g3 -fsanitize=address
SOURCES = main.c add_block.c blockchain.c add_node.c helpers.c ls.c quit.c readline.c rm_block.c rm_node.c sync.c
HEADERS = header.h
OBJECTS = $(SOURCES:.c=.o) $(HEADERS)


$(OUTPUT): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(OUTPUT)

fclean: clean
	rm -f ${OUTPUT}

re: fclean all
