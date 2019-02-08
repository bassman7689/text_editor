default: all

SOURCEDIR=src
BUILDDIR=build
TESTDIR=tests
SOURCES=$(wildcard $(SOURCEDIR)/*.c)
OBJS=$(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))
TESTS=$(wildcard $(TESTDIR)/*.c)
TESTOBJS=$(filter-out $(BUILDDIR)/main.o, $(OBJS))
BINARY=text_editor
TESTBINARY=text_editor_tests
CFLAGS=-Wall -Werror
LDFLAGS=-lncurses
TESTLDFLAGS=-lncurses -lcheck -lsubunit -lm -lrt -lpthread

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(BUILDDIR)/%.o : src/%.c $(BUILDDIR)
	gcc $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o : $(TESTDIR)/%.c $(TESTDIR)
	gcc $(CFLAGS) -c $< -o $@

$(BINARY): $(OBJS)
	gcc $(CFLAGS) $^ $(LDFLAGS) -o $@

all: $(OBJS) $(BINARY)

$(TESTBINARY):  $(TESTOBJS) $(TESTS)
	gcc $(CFLAGS) $^ $(TESTLDFLAGS) -o $@

check: $(TESTBINARY)
	./$(TESTBINARY)

.PHONY: cloc

cloc:
	cloc $(SOURCEDIR)/*.c $(SOURCEDIR)/*.h $(TESTDIR)/*.c

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(TESTBINARY) $(BINARY) errorlog
