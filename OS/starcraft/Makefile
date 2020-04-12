CC = gcc

CFLAGS = -Wall -Wextra -Werror -pedantic-errors -O2
LDFLAGS = -pthread

SRC_DIR = source

starcraft3: $(SRC_DIR)/main.c $(SRC_DIR)/utils.c 
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC_DIR)/utils.c $(SRC_DIR)/main.c -o starcraft3

clean:
	rm starcraft3