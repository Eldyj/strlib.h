#include<stdio.h>
#include<strlib.h>
#include<string.h>
#include<strlib.h>

int main(int argc, char **argv) {
	if (argc < 3) {
		fputs("ERR: not enough arguments\n", stderr);
		return 1;
	}
	
	StringArray parts = split(argv[1], argv[2]);
	
	for (unsigned long i = 0; i < parts.length; ++i)
		puts(sa_get(parts, i));

	sa_free(&parts);
	return 0;
}
