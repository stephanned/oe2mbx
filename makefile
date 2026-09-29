# MAKEFILE FOR LIBOE AND OE2MBX
# Read README for info

PREFIX = /usr
LIBDIR = $(PREFIX)/lib
BINDIR = $(PREFIX)/bin
INCLUDEDIR = $(PREFIX)/include

oe2mbx : src/oe2mbx.c lib/liboe.o
	gcc src/oe2mbx.c lib/liboe.o -o bin/oe2mbx
dynamic : src/oe2mbx.c
	gcc src/oe2mbx.c -DDYNAMIC -o bin/oe2mbx -loe
liboe : src/liboe.c
	gcc -c src/liboe.c -o lib/liboe.so
lib/liboe.o : src/liboe.c
	gcc -c src/liboe.c -o lib/liboe.o	
install : 
	test -e bin/* && install bin/* $(BINDIR) && echo oe2mbx binary installed || echo oe2mbx binary not prepared
	test -e lib/*.so && install lib/*.so $(LIBDIR) && install src/*.h $(INCLUDEDIR) && echo liboe library installed || echo liboe library not prepared
clean	:
	test -e bin/* && rm -f bin/* || test .
	test -e lib/* && rm -f lib/* || test .
