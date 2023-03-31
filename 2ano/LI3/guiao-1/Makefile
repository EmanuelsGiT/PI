# Source files.
SRC =  src/main.c src/mainEx1.c src/mainEx2.c src/Tree.c 

OBJ = $(SRC)

OUT = guiao-1

# C Compiler
CC = gcc

# C compiler flags
CCFLAGS = -O2 -Wall -g 

default: $(OUT)

#EX1
obj/exercicio-1.o: src/mainEx1.c
	$(CC) $(CCFLAGS) -c $< -o $@

#EX2
obj/exercicio-2.o: src/mainEx2.c
	$(CC) $(CCFLAGS) -c $< -o $@

obj/tree.o: src/Tree.c
	$(CC) $(CCFLAGS) -c $< -o $@

#MAIN
obj/main.o: src/main.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(OUT): obj/main.o
	$(CC) $(CCFLAGS) obj/main.o -o $(OUT)

clean:
	-rm -f obj/*.o
	-rm -f $(OUT)

