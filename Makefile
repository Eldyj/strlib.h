#!/usr/bin/make -f
ifeq ($(shell uname -o),Android)
	PREFIX = /data/data/com.termux/files/usr
else
	PREFIX = /usr/local
endif
objectfile :
	gcc -c -g3 -o3 -Wextra -Wall -o strlib.o strlib.c

staticlib : objectfile
	ar rcs libstrlib.a strlib.o

install : staticlib
	mv libstrlib.a $(PREFIX)/lib
	cp strlib.h $(PREFIX)/include

uninstall :
	rm $(PREFIX)/lib/libstrlib.a
	rm $(PREFIX)/include/strlib.h

clean :
	rm *.o

reinstall : uninstall install
