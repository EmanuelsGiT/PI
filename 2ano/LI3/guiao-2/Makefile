# Source files.
SRC = src/main.c src/guiao2.c src/User.c src/Commits.c src/Repos.c src/catUsers.c src/catCommits.c src/catRepos.c src/data.c src/queries_estatistic.c src/queriesAux.c src/queries_parameterizable.c 

OBJ = obj/main.o obj/guiao2.o obj/User.o obj/Commits.o obj/Repos.o obj/catUsers.o obj/catCommits.o obj/catRepos.o obj/data.o obj/queries_estatistic.o obj/queriesAux.o obj/queries_parameterizable.o 

OUT = guiao-2

# C Compiler
CC = gcc

# Include directories
INCLUDE = -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include `pkg-config --cflags --libs glib-2.0` 

# C compiler flags
CCFLAGS = -fno-stack-protector -O2 -Wall -g


default: $(OUT)

#Queries Auxiliar
obj/queriesAux.o: src/queriesAux.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Queries Parameterizable
obj/queries_parameterizable.o: src/queries_parameterizable.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Queries Estatistic
obj/queries_estatistic.o: src/queries_estatistic.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Data
obj/data.o: src/data.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#User
obj/User.o: src/User.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Commmits
obj/Commits.o: src/Commits.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Repos
obj/Repos.o: src/Repos.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#CatUsers
obj/catUsers.o: src/catUsers.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#CatCommits
obj/catCommits.o: src/catCommits.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#CatRepos
obj/catRepos.o: src/catRepos.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Guiao2
obj/guiao2.o: src/guiao2.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Main
obj/main.o: src/main.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(CCFLAGS) $(INCLUDE) $(OBJ)

clean:
	-rm -f obj/*.o
	-rm -f $(OUT)
	-rm -f saida/*.txt