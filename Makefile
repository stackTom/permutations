CC = gcc
CFLAGS = -g
DEPS =
OBJ = permutations.o
LIBS = -lm

all: permutations

permutations.o: generate_permutations.c $(DEPS)
	$(CC) -c -o permutations.o $< $(CFLAGS) $(LIBS)

permutations: $(OBJ)
	$(CC) -o permutations $^ $(CFLAGS) $(LIBS)

valgrind: all
	valgrind ./permutations

run: all
	./permutations

clean:
	rm -rf *.o
	rm -rf permutations

