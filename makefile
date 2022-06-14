SRCDIR=src
IDIR=include
CC=clang++
CFLAGS=-I$(IDIR)
VERSION=-std=c++20

ODIR=obj
LIBS=-lncurses

_DEPS=Matrix.hpp Vector.hpp Cube.hpp Engine.hpp
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

_OBJ=main.o Matrix.o Vector.o Cube.o Engine.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(VERSION)

all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(VERSION)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o

run: all
	./all