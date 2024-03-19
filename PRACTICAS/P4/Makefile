########################################################
CC = gcc
CFLAGS = -g -Wall -pedantic
LDLIBS = -L./
LLIBS = -lqueue
EJS = p4_e1 p4_e2
########################################################
include Makefile_ext

all: $(EJS)

p4_e1: p4_e1.o bstree.o vertex.o
	$(CC) -o p4_e1 p4_e1.o bstree.o vertex.o

p4_e1.o: p4_e1.c bstree.h vertex.h types.h
	$(CC) -c $(CFLAGS) $<

p4_e2: p4_e2.o file_utils.o search_queue.o  bstree.o
	$(CC) -o p4_e2 p4_e2.o file_utils.o search_queue.o bstree.o

p4_e2.o: p4_e2.c file_utils.h search_queue.h
	$(CC) -c $(CFLAGS) $<




search_queue.o: search_queue.c search_queue.h types.h bstree.h
	$(CC) -c $(CFLAGS) $<

file_utils.o: file_utils.c file_utils.h
	$(CC) -c $(CFLAGS) $<

bstree.o: bstree.c bstree.h
	$(CC) -c $(CFLAGS) bstree.c

vertex.o: vertex.c vertex.h
	$(CC) -c $(CFLAGS) $<


clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)
