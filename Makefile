#FOLDERS
OBJ=obj/
SRC=src/
BINDIR=bin/
INCLUDE=header_files/

#VARIABLES
CC=g++
CFLAGS=-g -Wall -I $(INCLUDE)
OBJS=$(OBJ)main.o $(OBJ)csvExtractor.o $(OBJ)mergeSort.o 
BIN=$(BINDIR)main

#RULES
all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(OBJ)%.o: $(SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	$(BIN)

clean:
	$(RM) $(OBJS) $(BIN) 
