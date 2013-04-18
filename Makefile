CC=gcc
CFLAGS=-c -Wall -std=c99 -O3
LDFLAGS=
SOURCES=src/main.c src/Scanner.c src/Generator.c 
OBJECTS=$(SOURCES:.c=.o)
EXEC=pl0syntaxcolor

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
