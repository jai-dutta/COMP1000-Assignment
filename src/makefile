CC = gcc
CFLAGS = -Wall -ansi -pedantic
EXEC = treasure
OBJ = main.o game.o map.o input.o linkedlist.o random.o

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h map.h input.h linkedlist.h
	$(CC) $(CFLAGS) -c game.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c

random.o: random.c random.h
	$(CC) $(CFLAGS) -c random.c

dark: CFLAGS += -D DARK_MODE
dark: clean $(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)
