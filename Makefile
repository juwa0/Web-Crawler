CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lcurl

SRC = crawler.c curl.c pagedir.c url.c hashtable.c set.c bag.c

OBJ = $(SRC:.c=.o)

EXEC = crawler

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJ)
