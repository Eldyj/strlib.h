#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strlib.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		fputs("ERR: not enough arguments\n", stderr);
		return 1;
	}

	char *reversed = reverse_str(argv[1]);
	puts(reversed);
	free(reversed);
	return 0;
}
