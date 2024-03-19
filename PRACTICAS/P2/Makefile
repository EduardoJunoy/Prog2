########################################################
CC = gcc
CFLAGS = -c -Wall -pedantic
EJS = p2_e1a p2_e1b p2_e2 Sp2_e1a Sp2_e1b Sp2_e2
########################################################

all: $(EJS)

#ejecutar los programas con la pila de la librería estática
p2_e1a: p2_e1a.o libstack.a
	$(CC) -o p2_e1a p2_e1a.o libstack.a
	
p2_e1b: p2_e1b.o vertex.o libstack.a
	$(CC) -o p2_e1b vertex.o p2_e1b.o libstack.a

p2_e2: graph.o vertex.o p2_e2.o libstack.a
	$(CC) -o p2_e2 graph.o vertex.o p2_e2.o libstack.a



#ejecutar los programas con la pila del ejercicio 3
Sp2_e1a: p2_e1a.o stack.o file_utils.o
	$(CC) -o Sp2_e1a p2_e1a.o stack.o file_utils.o

Sp2_e1b: p2_e1b.o vertex.o stack.o
	$(CC) -o Sp2_e1b vertex.o p2_e1b.o stack.o

Sp2_e2: graph.o vertex.o p2_e2.o stack.o
	$(CC) -o Sp2_e2 graph.o vertex.o p2_e2.o stack.o



graph.o: graph.c graph.h vertex.h
	$(CC) $(CFLAGS) graph.c
 
vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) vertex.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) stack.c

file_utils.o: file_utils.c file_utils.h
	$(CC) $(CFLAGS) file_utils.c
	

p2_e1a.o: p2_e1a.c stack.h file_utils.h
	$(CC) $(CFLAGS) p2_e1a.c
	
p2_e1b.o: p2_e1b.c stack.h file_utils.h vertex.h
	$(CC) $(CFLAGS) p2_e1b.c
 
p2_e2.o: p2_e2.c graph.h
	$(CC) $(CFLAGS) p2_e2.c


run:
	./p2_e1a grades1.txt grades2.txt 
	./p2_e1b cities1.txt cities2.txt
	./p2_e2 g2.txt 100 700

runS:
	./Sp2_e1a grades1.txt grades2.txt 
	./Sp2_e1b cities1.txt cities2.txt
	./Sp2_e2 g2.txt 100 700


runv:
	valgrind --leak-check=full ./p2_e1a grades1.txt grades2.txt 
	valgrind --leak-check=full ./p2_e1b cities1.txt cities2.txt
	valgrind --leak-check=full ./p2_e2 g2.txt 100 700

runvS:
	valgrind --leak-check=full ./Sp2_e1a grades1.txt grades2.txt 
	valgrind --leak-check=full ./Sp2_e1b cities1.txt cities2.txt
	valgrind --leak-check=full ./Sp2_e2 g2.txt 100 700

clean:
	rm -rf *.o $(EJS)
