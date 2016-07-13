CFLAGS = -g -O2 -Wall -Wextra -Iheaders -rdynamic $(OPTFLAGS)
LDLIBS = -lm

HEADERS = $(wildcard headers/*.h)
SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst %.c,%,$(SOURCES))

all: $(OBJECTS)

src/test: $(HEADERS)
src/expansion: $(HEADERS)

include .config
run: src/expansion
	@./src/expansion $(WIDTH) $(IN_OUT) $(POINTS)

.PHONY:
clean:
	@- $(RM)  $(OBJECTS)

distclean: clean
