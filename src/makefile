CC = gcc
CFLAGS = -Wall -ansi -pedantic
EXEC = treasure
OBJ = main.o game.o map.o input.o linkedList.o random.o

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h map.h input.h linkedList.h
	$(CC) $(CFLAGS) -c game.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

linkedList.o: linkedList.c linkedList.h
	$(CC) $(CFLAGS) -c linkedList.c

random.o: random.c random.h
	$(CC) $(CFLAGS) -c random.c

dark: CFLAGS += -D DARK_MODE
dark: clean $(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)
