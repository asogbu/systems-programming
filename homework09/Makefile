CC=		gcc
CFLAGS=		-g -Wall -std=gnu99 -Iinclude
LD=		gcc
LDFLAGS=	-Llib
AR=		ar
ARFLAGS=	rcs
TARGETS=	bin/thor

# -----------------------------------------------------------------------------

all:		$(TARGETS)

# TODO: Add rules for lib/libthor.a, bin/unit_{timestamp,socket,request,hammer},
# bin/thor and any objects they require
lib/libthor.a: src/hammer.o src/request.o src/socket.o src/timestamp.o
	@echo Linking $@...
	@$(AR) $(ARFLAGS) $@ $^

src/hammer.o: src/hammer.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/request.o: src/request.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/socket.o: src/socket.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

src/timestamp.o: src/timestamp.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

bin/unit_timestamp: src/unit_timestamp.o lib/libthor.a 
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

src/unit_timestamp.o: tests/unit_timestamp.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

bin/unit_socket: src/unit_socket.o lib/libthor.a
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

src/unit_socket.o: tests/unit_socket.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

bin/unit_request: src/unit_request.o lib/libthor.a
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

src/unit_request.o: tests/unit_request.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

bin/unit_hammer: src/unit_hammer.o lib/libthor.a
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

src/unit_hammer.o: tests/unit_hammer.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^

bin/thor: src/thor.o lib/libthor.a
	@echo Linking $@...
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

src/thor.o: src/thor.c
	@echo Compiling $@...
	@$(CC) $(CFLAGS) -c -o $@ $^


# -----------------------------------------------------------------------------

test:
	@$(MAKE) -sk test-all

test-all:               test-timestamp test-socket test-request test-hammer test-thor

test-timestamp:		bin/unit_timestamp
	@bin/test_timestamp.sh

test-socket:		bin/unit_socket
	@bin/test_socket.sh

test-request:		bin/unit_request
	@bin/test_request.sh

test-hammer:		bin/unit_hammer
	@bin/test_hammer.sh

test-thor:		bin/thor
	@bin/test_thor.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) bin/unit_* lib/*.a src/*.o tests/*.o *.log *.input

.PHONY:		all test clean
