CC=g++
CFLAGS=-c -W -Wall -ansi -pedantic
PATH_SRC=
PATH_DST=../bin/
LDFLAGS=
EXEC=cavendish

all: $(PATH_DST)$(EXEC) launch

$(PATH_DST)cavendish: $(PATH_DST)main.o $(PATH_DST)vertice.o
	$(CC) $(PATH_DST)main.o $(PATH_DST)vertice.o -o $(PATH_DST)$(EXEC)

$(PATH_DST)vertice.o: $(PATH_SRC)vertice.cpp
	$(CC) $(CFLAGS) $(PATH_SRC)vertice.cpp -o $(PATH_DST)vertice.o

$(PATH_DST)main.o: $(PATH_SRC)main.cpp
	$(CC) $(CFLAGS) $(PATH_SRC)main.cpp -o $(PATH_DST)main.o

launch:
	$(PATH_DST)$(EXEC).exe

clean:
	rm -rf $(PATH_DST)*.o

mrproper: clean
	rm -rf $(PATH_DST)$(EXEC)
