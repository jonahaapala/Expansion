CFLAGS = -g -O2 -Wall -Wextra -Isrc/headers -rdynamic $(OPTFLAGS)
LDLIBS = -lm

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c,%,$(SOURCES))

all: $(OBJECTS)
	mv $(OBJECTS) .

test: point.h vector.h polygon.h

.PHONY:
clean:
	@- $(RM)  $(OBJECTS)

distclean: clean
