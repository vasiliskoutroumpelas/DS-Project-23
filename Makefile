#FOLDERS
OBJDIR=obj/
SRC=src/
BINDIR=bin/
INCLUDE=header_files/

#VARIABLES
CC=g++
CFLAGS=-g -Wall -I $(INCLUDE)
OBJ=$(OBJDIR)main.o $(OBJDIR)csvExtractor.o $(OBJDIR)mergeSort.o 
BIN=$(BINDIR)main

#RULES
all: $(OBJDIR) $(BINDIR) $(BIN)

$(OBJDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ 

$(OBJDIR)%.o: $(SRC)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BIN)
	$(BIN)

clean:
	$(RM) $(OBJ) $(BIN) 
