CC=		gcc
CFLAGS=		-g -Wall -std=gnu99 -Iinclude
LD=		gcc
LDFLAGS=	-Llib
LIBS=		-lcrypto
AR=		ar
ARFLAGS=	rcs
TARGETS=	bin/duplicates

all:		$(TARGETS)

# TODO: Add rules for bin/unit_hash, bin/unit_pair, bin/unit_table, bin/duplicates

lib/libtable.a: src/hash.o src/pair.o src/table.o
	@echo Linking $@...
	@$(AR) $(ARFLAGS) $@ $^

src/hash.o: src/hash.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/pair.o: src/pair.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/table.o: src/table.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

bin/unit_hash: src/unit_hash.o lib/libtable.a 
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

src/unit_hash.o: tests/unit_hash.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

bin/unit_pair: src/unit_pair.o lib/libtable.a
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

src/unit_pair.o: tests/unit_pair.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

bin/unit_table: src/unit_table.o lib/libtable.a
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

src/unit_table.o: tests/unit_table.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

bin/duplicates: src/duplicates.o lib/libtable.a
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

src/duplicates.o: src/duplicates.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

test:
	@$(MAKE) -sk test-all

test-all:               test-hash test-pair test-table test-duplicates

test-pair:		bin/unit_pair
	@bin/test_pair.sh

test-hash:		bin/unit_hash
	@bin/test_hash.sh

test-table:		bin/unit_table
	@bin/test_table.sh

test-duplicates:	bin/test_duplicates.sh bin/duplicates
	@bin/test_duplicates.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) bin/unit_pair bin/unit_hash bin/unit_table lib/*.a src/*.o tests/*.o *.log *.input

.PHONY:		all test clean
