########################################################
CC = gcc
CFLAGS = -g -Wall -pedantic
LDLIBS = -L./
LLIBS = -lqueue
EJS = p3_e1 p3_e2a p3_e2b p3_e3
########################################################

all: $(EJS)

p3_e1: p3_e1.o delivery.o vertex.o
	$(CC) -o p3_e1 $^ $(CFLAGS) $(LDLIBS) $(LLIBS)

p3_e2a: p3_e1.o delivery.o vertex.o queue.o
	$(CC) -o p3_e2a $^ $(CFLAGS)

p3_e2b: graph.o vertex.o p3_e2b.o queue.o stack.o
	$(CC) -o p3_e2b graph.o vertex.o p3_e2b.o queue.o stack.o

p3_e3: p3_e3.o list.o file_utils.o
	$(CC) -o p3_e3 p3_e3.o list.o file_utils.o



delivery.o: delivery.c delivery.h
	$(CC) -c $(CFLAGS) $<

vertex.o: vertex.c delivery.h
	$(CC) -c $(CFLAGS) $<

queue.o: queue.c queue.h
	$(CC) -c $(CFLAGS) $<

list.o: list.c list.h
	$(CC) -c $(CFLAGS) $<

file_utils.o: file_utils.c file_utils.h
	$(CC) -c $(CFLAGS) $<



p3_e1.o: p3_e1.c delivery.h vertex.h
	$(CC) -c $(CFLAGS) $<

p3_e2b.o: p3_e2b.c graph.h
	$(CC) -c $(CFLAGS) $<

p3_e3.o: p3_e3.c list.h file_utils.h
	$(CC) -c $(CFLAGS) $<

run:
	./p3_e1 requests.txt
	./p3_e2a requests.txt
	./p3_e2b city_graph.txt 100 700
	./p3_e3 grades.txt -1
	./p3_e3 grades.txt 1

runv:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p3_e1 requests.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p3_e2a requests.txt
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p3_e2b city_graph.txt 100 700
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p3_e3 grades.txt -1
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./p3_e3 grades.txt 1


clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)
