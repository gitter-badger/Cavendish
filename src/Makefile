ifdef ComSpec
    PATHSEP2=\\
	RM =del /s
	config=configure_win
else
    PATHSEP2=/
	RM =rm -rf
	config=configure_linux
endif

CC=g++
CFLAGS=-c -W -Wall -ansi -pedantic
PATH_SRC=
PATH_DST=..$(PATHSEP2)bin$(PATHSEP2)
LDFLAGS=
EXEC=cavendish

all: $(config) $(PATH_DST)$(EXEC) launch

$(PATH_DST)cavendish: $(PATH_DST)main.o $(PATH_DST)vertice.o
	$(CC) $(PATH_DST)main.o $(PATH_DST)vertice.o -o $(PATH_DST)$(EXEC)

$(PATH_DST)vertice.o: $(PATH_SRC)vertice.cpp
	$(CC) $(CFLAGS) $(PATH_SRC)vertice.cpp -o $(PATH_DST)vertice.o

$(PATH_DST)main.o: $(PATH_SRC)main.cpp
	$(CC) $(CFLAGS) $(PATH_SRC)main.cpp -o $(PATH_DST)main.o

configure_win:
	@echo off
	if not exist $(PATH_DST) md  $(PATH_DST)

configure_linux:
	mkdir -p $(PATH_DST)

launch:
	$(PATH_DST)$(EXEC).exe

clean:
	$(RM) $(PATH_DST)*.o

mrproper: clean
	$(RM) $(PATH_DST)$(EXEC)
