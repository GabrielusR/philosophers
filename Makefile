#Makefile for my C syntax project

CFLAGS=-Wall -g
ANSI=-std=c90 -pedantic
BIN=dining
BINANSI=dining_ansi
SRC=dining.c
OBJ=dining.o
#HDR=dining.h

$(BIN): $(SRC) $(HDR)
	gcc $(CFLAGS) -c $(SRC) -o $(OBJ)
	gcc $(CFLAGS) $(SRC) -o $(BIN)

$(BINANSI): $(SRC) $(HDR)
	gcc $(CFLAGS) $(ANSI) -c $(SRC) -o $(OBJ)
	gcc $(CFLAGS) $(ANSI) $(SRC) -o $(BINANSI)

clean:
	rm -rf $(BIN) $(OBJ)

clean_ansi:
	rm -rf $(BINANSI) $(OBJ)

rebuild: clean $(BIN)

rebuild_ansi: clean_ansi $(BINANSI)
