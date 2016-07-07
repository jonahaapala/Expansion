CFLAGS = -g -O2 -Wall -Wextra -rdynamic $(OPTFLAGS)
LDLIBS = -lm

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%,$(SOURCES))

all: $(OBJECTS)

test: point.h vector.h polygon.h

.PHONY:
clean:
	@- $(RM)  $(OBJECTS)

distclean: clean
