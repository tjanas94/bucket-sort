CC=gcc
RM=rm
CFLAGS=-c -Wall -g
LDFLAGS=-lm
SOURCES=test.c sort.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=sort

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE)
