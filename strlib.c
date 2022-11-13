// requires libraries: stdio.h, stdlib.h, string.h, stdbool.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "strlib.h"

// String array functions
StringArray new_strarray() {
	StringArray sa;
	sa.array = NULL;
	sa.length = 0;
	return sa;
}

void sa_free(StringArray *sa) {
	if (sa->length == 0) return;
	for (int i = 0; i < sa->length; i++) {
		free(sa->array[i]);
		sa->array[i] = NULL;
	}
	free(sa->array);
	sa->array = NULL;
	sa->length = 0;
}

void sa_add(StringArray *sa, char *str) {
	sa->length++;
	sa->array = realloc(sa->array, sa->length * sizeof(char*));
	sa->array[sa->length - 1] = malloc((strlen(str)+1)*sizeof(char));
	strcpy(sa->array[sa->length - 1], str);
	strcat(sa->array[sa->length - 1], "\0");
}

void sa_set(StringArray *sa, int index, char *str) {
	if (index > sa->length)
		return;
	else if (index == sa->length)
		sa_add(sa, str);
	else {
		free(sa->array[index]);
		sa->array[index] = NULL;
		sa->array[index] = malloc((strlen(str) + 1) * sizeof(char));
		strcpy(sa->array[index], str);
		strcat(sa->array[index], "\0");
	}
}

void sa_delete(StringArray *sa, int index) {
	if (index >= sa->length) return;
	if (index + 1 == sa->length) {
		free(sa->array[index]);
		sa->array[index] = NULL;
	} else {
		for (int i=index;i<sa->length - 1;i++) {
			free(sa->array[i]);
			sa->array[i] = NULL;
			sa->array[i] = malloc((strlen(sa->array[i+1])+1)*sizeof(char));
			strcpy(sa->array[i], sa->array[i+1]);
			strcat(sa->array[i], "\0");
		}
	}
	sa->length--;
	sa->array = realloc(sa->array,sa->length*sizeof(char*));
}

char *sa_get(StringArray sa, int index) {
	if (index >= sa.length)
		return NULL;
	else
		return sa.array[index];
}

char *sa_join(StringArray array, char* sep) {
	long size_res = strlen(sep) * (array.length - 1);
	for (int i = 0; i < array.length; i++) size_res += strlen(array.array[i]);
	char *result = malloc((size_res + 1) * sizeof(char));
	for (int i = 0; i < array.length; i++) {
		strcat(result, array.array[i]);
		if (i != array.length - 1) strcat(result, sep);
	}
	strcat(result, "\0");
	return result;
}

int sa_index_of(StringArray sa, char *str) {
	int res = -1;
	for (int i = 0; i < sa.length; i++) {
		if (strcmp(sa_get(sa, i), str) == 0) {
			res = i;
			break;
		}
	}
	return res;
}

int sa_count(StringArray sa, char *str) {
	int res = 0;
	for (int i = 0; i < sa.length; i++)
		if (strcmp(sa_get(sa, i), str) == 0)
			res++;
	return res;
}


bool sa_contains(StringArray sa, char *str) {
	return sa_index_of(sa, str) != -1;
}

void sa_remove(StringArray *sa, char *str) {
	while (sa_contains(*sa, str))
		sa_delete(sa, sa_index_of(*sa, str));
}

// String functions
// Sets the string value
void set_str(char **str, char *a) {
	if (*str != NULL) free(*str);
	*str = NULL;
	*str = malloc((strlen(a) + 1) * sizeof(char));
	strcpy(*str, a);
	strcat(*str, "\0");
}
// Appends string
void add_str(char **str, char *a) {
	if (*str != NULL) {
		*str = realloc(*str, (strlen(*str) + strlen(a) + 1) * sizeof(char));
		strcat(*str, a);
		strcat(*str, "\0");
	} else
		set_str(str, a);
}

// Concatenates two strings
char *concat(char *a, char *b) {
	string(res);
	set_str(&res, a);
	add_str(&res, b);
	return res;
}

// string reverse
char *reverse_str(char *a) {
	string(result);
	set_str(&result, a);	
	for (long i = strlen(a) - 1; i > -1; i--)
		result[strlen(a) - i - 1] = a[i];
	add_str(&result, "\0");
	return result;
}

//equals
bool equals_str(char *a, char *b) {
	return a == NULL && b == NULL || a != NULL && b != NULL && strcmp(a, b) == 0;
}

bool starts_with(char *a, char *b) {
	bool result = false;
	if (strstr(a, b) != 0) {
		long index = 0;
		for (int i = 0; i < strlen(b); i++)
			if (a[i] == b[i]) index++;
		if (strlen(b) == index) result = true;
	}
	return result;
}

bool ends_with(char *a, char *b) {
	return starts_with(reverse_str(a), reverse_str(b));
}

char *bash_slice(char *str, unsigned int a, unsigned int c) {
	string(result);
	unsigned long length = 0, to = a + c;
	if (to >= strlen(str))
		to = strlen(str);
	for (int i = a; i < to; i++) {
		length++;
		result = realloc(result, length * sizeof(char));
		result[length - 1] = str[i];
	}
	length++;
	result = realloc(result, length * sizeof(char));
	result[length - 1] = '\0';
	return result;
}

// Counts substrings in the string
unsigned int count_substr(char *a, char *b) {
	unsigned int result = 0;
	for (unsigned int i = 0; i < strlen(a); i++)
		if (strcmp(bash_slice(a, i, strlen(b)), b) == 0)
			result++;
	return result;
}

bool contains_substr(char *a, char *b) {
	return strstr(a, b) != 0;
}

bool consists_of(char *a, char *b) {
	return count_substr(a, b) * strlen(b) == strlen(a);
}

// returns a slice of the string from a to b
char *slice_fromto(char *str, int a, int b) {
	char *result = malloc((b - a + 1) * sizeof(char));
	int index = 0;
	for (int i = a; i < b; i++) {
		result[index] = str[i];
		index++;
	}
	result[index] = '\0';
	return result;
}

char *slice_from(char *str, unsigned int a) {
	return slice_fromto(str, a, strlen(str));
}

char *slice_to(char *str, unsigned int a) {
	return slice_fromto(str, 0, a);
}

int index_of(char *a, char *b, unsigned int entry) {
	if (strstr(a, b) == 0 || entry > count_substr(a, b)) return -1;
	int res = -1, entry_of = 0;
	for (unsigned int i = 0; i < strlen(a); i++) {
		if (strcmp(bash_slice(a, i, strlen(b)), b) == 0) {
			res = i;
			entry_of++;
			if (entry_of == entry) break;
		}
	}
	return res;
}

char *strip(char *str, char a) {
	int start = 0, end = strlen(str);
	while (str[start] == a && start < strlen(str))
		start++;
	while (str[end - 1] == a && end > 0)
		end--;
	if (start == end) return NULL;
	return slice_fromto(str, start, end);
}

// split the string `a` by the substring `b`
StringArray split(char*str, char*b) {
	StringArray res =  new_strarray();
	unsigned int count_b = count_substr(str, b),
		*indexes = malloc(count_b * sizeof(unsigned int));
	if (count_b > 0) {
		for (int i = 0; i < count_b; i++)
			indexes[i] = index_of(str, b, i + 1);
		if (indexes[0] != 0)
			sa_add(&res, slice_to(str, indexes[0]));
		for (int i = 0; i < count_b - 1; i++) {
			while (indexes[i] + strlen(b) == indexes[i + 1]) i++;
			sa_add(&res, slice_fromto(str, indexes[i] + strlen(b), indexes[i + 1]));
		}
		if (indexes[count_b - 1] + strlen(b) < strlen(str))
			sa_add(&res, slice_from(str, indexes[count_b - 1] + strlen(b)));
		free(indexes);
	} else {
		sa_add(&res, str);
	}
	return res;
}

char *replace(char *str, char *b, char *c) {
	string(result);
	unsigned int count_b = count_substr(str, b),
		*indexes = malloc(count_b * sizeof(unsigned int));
	if (!contains_substr(str, b)) {
		set_str(&result, str);
	} else {
		for (int i = 0; i < count_b; i++)
			indexes[i] = index_of(str, b, i + 1);
		if (indexes[0] != 0)
			add_str(&result, slice_to(str, indexes[0]));
		for (int i = 0; i < count_b - 1; i++) {
				add_str(&result, c);
			if (indexes[i] + strlen(b) == indexes[i + 1]) continue;
			add_str(&result, slice_fromto(str, indexes[i] + strlen(b), indexes[i + 1]));
		}
		add_str(&result, c);
		if (indexes[count_b - 1] + strlen(b) < strlen(str))
			add_str(&result, slice_from(str, indexes[count_b - 1] + strlen(b)));
		free(indexes);
	}
	return result;
}

// Functions for working with files
char *read_file(FILE *file) {
	string(res);
	int len = 0, ch;
	if (file == NULL)
		return NULL;
	while (1) {
		ch = getc(file);
		if (ch == EOF || file == stdin && ch == '\n') {
			len++;
			res = realloc(res, len * sizeof(char));
			res[len - 1] = '\0';
			break;
		}
		len++;
		res = realloc(res, len * sizeof(char));
		res[len - 1] = (char)ch;
	}
	return res;
}
