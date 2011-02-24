TARGET=baash
CC=gcc
CFLAGS+= -ansi -Wall -Wextra -Wdeclaration-after-statement -Wbad-function-cast -Wstrict-prototypes -Wmissing-declarations -Wmissing-prototypes -Wno-unused-parameter -Werror -pedantic -g `pkg-config --cflags glib-2.0`
LDFLAGS=`pkg-config --libs glib-2.0`
SOURCES=$(shell echo *.c)
BSTRING_OBJECTS=bstring/bstrlib.o
OBJECTS=$(SOURCES:.c=.o)


all: $(TARGET)

# BString requiere flags distintos:
$(BSTRING_OBJECTS):CFLAGS=-ansi -Wall -Werror -pedantic -g

$(TARGET): $(OBJECTS) $(BSTRING_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJECTS)  $(BSTRING_OBJECTS) .depend *~
	make -C tests clean

test: $(OBJECTS)
	make -C tests test

memtest: $(OBJECTS)
	make -C tests memtest

.depend: *.[ch]
	$(CC) -MM $(SOURCES) >.depend

-include .depend

.PHONY: clean all
