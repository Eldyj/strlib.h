#!/usr/bin/make -f
strlib.o :
	gcc -c -g strlib.c

strlib.a : strlib.o
	ar rcs libstrlib.a strlib.o

install : strlib.a
	cp libstrlib.a /usr/local/lib/
	cp strlib.h /usr/local/include/

uninstall :
	rm /usr/local/lib/libstrlib.a
	rm /usr/local/include/strlib.h
clean :
	rm *.o
