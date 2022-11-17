#!/usr/bin/make -f
ifeq ($(shell uname -o),Android)
	PREFIX = /data/data/com.termux/files/usr
else
	PREFIX = /usr/local
endif
strlib.o :
	gcc -c -g strlib.c

strlib.a : strlib.o
	ar rcs libstrlib.a strlib.o

install : strlib.a
	mv libstrlib.a $(PREFIX)/lib
	cp strlib.h $(PREFIX)/include

uninstall :
	rm $(PREFIX)/lib/libstrlib.a
	rm $(PREFIX)/include/strlib.h

clean :
	rm *.o

reinstall : uninstall install
