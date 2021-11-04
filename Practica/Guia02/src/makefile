# file structure:
# target: dependencies
# 	action

CC=gcc

CFLAGS= -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -o
# CFLAGS= -g -Wall -o

RM=rm

write: write.c
	$(CC) $(CFLAGS) $< -o $@

run:
	./write
	
valcheck:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

clean:
	$(RM) write
	$(RM) alumnos.bin