# Source files.
SRC = src/main.c src/interface.c src/guiao2.c src/User.c src/Commits.c src/Repos.c src/catUsers.c src/catCommits.c src/catRepos.c src/data.c src/queries_estatistic.c src/queriesAux.c src/queries_parameterizable.c src/mainEx2.c src/mainEx1.c src/Tree.c src/query.c src/catQuery.c

OBJ = obj/main.o obj/interface.o obj/guiao2.o obj/User.o obj/Commits.o obj/Repos.o obj/catUsers.o obj/catCommits.o obj/catRepos.o obj/data.o obj/queries_estatistic.o obj/queriesAux.o obj/queries_parameterizable.o obj/mainEx2.o obj/mainEx1.o obj/Tree.o obj/query.o obj/catQuery.o

OBJ2 = obj/timeTests.o obj/guiao2.o  obj/catUsers.o obj/Commits.o obj/User.o  obj/Repos.o obj/data.o obj/query.o obj/catCommits.o obj/catRepos.o  obj/queries_estatistic.o obj/queriesAux.o obj/queries_parameterizable.o obj/mainEx2.o obj/mainEx1.o obj/Tree.o

OUT = guiao-3

OUT2 = tests

# C Compiler
CC = gcc

# Include directories
INCLUDE = `pkg-config --cflags --libs glib-2.0` 

# C compiler flags
CCFLAGS = -O3 -Wall -g

default: $(OUT)

default: $(OUT2)

#Tree
obj/Tree.o: src/Tree.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Ex1
obj/mainEx1.o: src/mainEx1.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Ex2
obj/mainEx2.o: src/mainEx2.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

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

#Query
obj/query.o: src/query.c
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

#CatQuery
obj/catQuery.o: src/catQuery.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Guiao2
obj/guiao2.o: src/guiao2.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Interface
obj/interface.o: src/interface.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Main
obj/main.o: src/main.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

#Testes
obj/timeTests.o: src/timeTests.c
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

$(OUT): $(OBJ)
	$(CC) -o $(OUT) $(CCFLAGS) $(INCLUDE) $(OBJ)

$(OUT2): $(OBJ2)
	$(CC) -o $(OUT2) $(CCFLAGS) $(INCLUDE) $(OBJ2)

clean:
	-rm -f obj/*.o
	-rm -f $(OUT)
	-rm -f $(OUT2)
	-rm -f saida/*.txt
	-rm -f saida/*.csv