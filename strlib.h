// requires libraries: stdio.h, stdlib.h, string.h, stdbool.h
#define version_of "0.2.0"
#define nullstr(a) char *a = NULL
// Structure that makes working with string arrays easier
typedef struct {
	char **array;
	int length;
} StringArray;

// String functions
// Sets the string value
void set_str(char **str, char *a) {
	if (*str != NULL) free(*str);
	*str = NULL;
	*str = malloc(strlen(a) * sizeof(char));
	strcpy(*str, a);
}
// Concatenates strings
void add_str(char **str, char *a) {
	*str = realloc(*str, (strlen(*str) + strlen(a)) * sizeof(char));
	strcat(*str, a);
}
// string reverse
char *reverse_str(char *a) {
	nullstr(result);
	set_str(&result, a);	
	for (long i = strlen(a) - 1; i > -1; i--)
		result[strlen(a) - i - 1] = a[i];
	return result;
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
// Counts substrings in the string
int count_substr(char *a, char *b) {
	int result = 0, index = 0;
	for (int i = 0; i < strlen(a); i++) {
		while (a[i] == b[index]) {
			index++;
			i++;
		}
		if (index == strlen(b)) result++;
		index = 0;
	}
	if (ends_with(a, b)) result++;
	return result;
}

bool contains_substr(char *a, char *b) {
	return strstr(a, b) != 0;
}


// returns a slice of the string from a to b
char *slice_fromto(char *str, int a, int b) {
	char *result = malloc((b - a) * sizeof(char));
	int index = 0;
	for (int i = a; i < b; i++) {
		result[index] = str[i];
		index++;
	}
	return result;
}

char *slice_from(char *str, int a) {
	return slice_fromto(str, a, strlen(str));
}

char *slice_to(char *str, int a) {
	return slice_fromto(str, 0, a);
}

// split the string `a` by the substring `b`
StringArray split(char*str, char*b) {
	StringArray res;
	char** result;
	nullstr(a);
	if (!starts_with(str, b) && !ends_with(str, b))
		set_str(&a, str);
	else if (starts_with(str, b) && ends_with(str, b))
		set_str(&a, slice_fromto(str, strlen(b), strlen(str) - strlen(b)));
	else if (starts_with(str, b))
		set_str(&a, slice_from(str, strlen(b)));
	else if (ends_with(str, b))
		set_str(&a, slice_to(str, strlen(str) - strlen(b)));
	if (!contains_substr(a, b)) {
		result = malloc(sizeof(char*));
		set_str(&result[0], a);
		res.array = result;
		res.length = 1;
	} else {
		int bcount = count_substr(a, b) + 1;
		result = malloc(bcount * sizeof(char*));
		int** indexes = malloc(bcount * sizeof(int*));
		for (int i = 0; i < bcount; i++) {
			indexes[i] = malloc(2 * sizeof(int));
		}
		int sn = 0, index = 0, cx = 0, pred = 0;
		for (int i = 0; i < strlen(a); i++) {
			if (a[i] == b[index]) cx = i;
			while (a[i] == b[index]) {
				index++;
				i++;
			}
			if (strlen(b) == index) {
				indexes[sn][0] = pred;
				indexes[sn][1] = cx;
				sn++;
				pred = i;
			}
			index = 0;
		}
		indexes[sn][0] = indexes[sn-1][1]+strlen(b);
		indexes[sn][1] = strlen(a);
		sn++;
		for (int i = 0; i < sn; i++) {
			int x = indexes[i][0],
				y = indexes[i][1],
				k = 0;
			result[i] = malloc((y-x)*sizeof(char));
			for (int j=x; j<y; j++) {
				result[i][k] = a[j];
				k++;
			}
		}
		res.array = malloc(bcount * sizeof(char*));
		for (int i = 0; i < bcount; i++)
			set_str(&res.array[i], result[i]);
		res.length = bcount;
	}
	return res;
}

char *join_str(StringArray array, char* sep) {
	long size_res = strlen(sep) * (array.length - 1);
	for (int i = 0; i < array.length; i++) size_res += strlen(array.array[i]);
	char *result = malloc(size_res * sizeof(char));
	for (int i = 0; i < array.length; i++) {
		strcat(result, array.array[i]);
		if (i != array.length - 1) strcat(result, sep);
	}
	return result;
}

char *replace(char *str, char *a, char *b) {
	nullstr(result);
	if (contains_substr(str, a)) {
		if (!starts_with(str, a) && !ends_with(str, a)) {
			set_str(&result, join_str(split(str, a), b));
		} else if (starts_with(str, a) && ends_with(str, a)) {
			nullstr(midr);
			set_str(&midr, slice_fromto(str, strlen(a), strlen(str) - strlen(a)));
			set_str(&result, b);
			add_str(&result, join_str(split(midr, a), b));
			add_str(&result, b);
		} else if (starts_with(str, a)) {
			nullstr(midr);
			set_str(&midr, slice_from(str, strlen(a)));
			set_str(&result, b);
			add_str(&result, join_str(split(midr, a), b));
		} else if (ends_with(str, a)) {
			nullstr(midr);
			set_str(&midr, slice_to(str, strlen(str)-strlen(a)));
			set_str(&result, join_str(split(midr, a), b));
			add_str(&result, b);
		}
	} else {
		set_str(&result, str);
	}
	return result;
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
	sa->array[sa->length - 1] = malloc(strlen(str)*sizeof(char));
	strcpy(sa->array[sa->length - 1], str);
}

void sa_set(StringArray *sa, int index, char *str) {
	if (index >= sa->length) return;
	free(sa->array[index]);
	sa->array[index] = NULL;
	sa->array[index] = malloc(strlen(str) * sizeof(char));
	strcpy(sa->array[index], str);
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
			sa->array[i] = malloc(strlen(sa->array[i+1])*sizeof(char));
			strcpy(sa->array[i], sa->array[i+1]);
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
