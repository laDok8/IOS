CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic -lpthread -lrt -O2
EXCUTABLE = proj2

all: $(EXCUTABLE)
.PHONY: clean zip

proj2: judge.o imigrant.o proj2.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(EXCUTABLE) proj2.out *.o
zip:
	zip proj2.zip *.c *.h Makefile
