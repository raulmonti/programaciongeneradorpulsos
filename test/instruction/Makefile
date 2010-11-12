TARGET = test_instruction
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)

.PHONY : clean dist

LIBS = #-lefence

CC = gcc

CFLAGS = -g -Wall -ansi -pedantic -lm\
#-lssl
#-Waggregate-return \
#-Wbad-function-cast \
#-Wcast-qual \
#-Wcast-align \
#-Wdeclaration-after-statement \
#-Wendif-labels \
#-Werror \
#-Wextra \
#-Wfloat-equal \
#-Wimport \
#-Winline \
#-Winvalid-pch \
#-Wlong-long \
#-Wmissing-declarations \
#-Wmissing-field-initializers \
#-Wmissing-format-attribute \
#-Wmissing-noreturn \
#-Wmissing-prototypes \
#-Wnested-externs \
#-Wold-style-definition \
#-Wpacked \
#-Wpadded \
#-Wpointer-arith \
#-Wpointer-sign \
#-Wredundant-decls \
#-Wshadow \
#-Wsign-compare \
#-Wstrict-prototypes \
#-Wundef \
#-Wunreachable-code \
#-Wunused-macros \
#-Wvariadic-macros \
#-Wwrite-strings \
#-DNDEBUG
#-Wtraditional \
#-Wconversion \
# Las siguientes no andan con gcc de Mandriva :)
#-Wc++-compat \
#-Wno-attributes \
#-Wstack-protector \
#-Wunsafe-loop-optimizations \
#-Wvolatile-register-var \

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS) .depend 

distclean:
	rm -f $(TARGET) $(OBJECTS) .depend *~ *.tgz

-include .depend

.depend: $(SOURCES) $(HEADERS)
	gcc -MM $(SOURCES) $(HEADERS) >.depend

$(TARGET): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LIBS)

dist:
	tar -czvf $(TARGET).tgz $(SOURCES) $(HEADERS) Makefile


