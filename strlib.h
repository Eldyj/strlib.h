#ifndef STRLIB_H
#define STRLIB_H
#define STRLIB_VERSION "1.3.1"
#define string(a) char *a = NULL
#define bool int
#define true 1
#define false 0
// Structure that makes working with string arrays easier
typedef struct {
	char **array;
	unsigned int length;
} StringArray;
// String array functions
StringArray new_strarray(void);
void sa_free(StringArray*);
void sa_add(StringArray*, char*);
void sa_add_sa(StringArray*, StringArray);
void sa_set(StringArray*, unsigned int, char*);
void sa_delete(StringArray*, unsigned int);
char *sa_get(StringArray, unsigned int);
char *sa_join(StringArray, char*);
char *sa_repr(StringArray);
int sa_index_of(StringArray, char*);
unsigned long sa_count(StringArray, char*);
bool sa_contains(StringArray, char*);
void sa_remove(StringArray*, char*);
StringArray sa_slice_fromto(StringArray, unsigned int, unsigned int);
StringArray sa_slice_from(StringArray, unsigned int);
StringArray sa_slice_to(StringArray, unsigned int);
void sa_insert(StringArray*, unsigned int, char*);
void sa_insert_sa(StringArray*, unsigned int, StringArray);
// String functions
void set_str(char**, char*);
void add_str(char**, char*);
char *concat(char*, char*);
char *reverse_str(char*);
bool equals_str(char*, char*);
bool starts_with(char*, char*);
bool ends_with(char*, char*);
char *bash_slice(char*, unsigned int, unsigned int);
unsigned int count_substr(char*, char*);
bool contains_substr(char*, char*);
bool consists_of(char*, char*);
char *slice_fromto(char*, int, int);
char *slice_from(char*, unsigned int);
char *slice_to(char*, unsigned int);
int index_of(char*, char*, unsigned int);
int index_of_char(char*, char, unsigned int);
char *strip(char*, char);
StringArray split(char*, char*);
StringArray split_sa(char*, StringArray);
char *replace(char*, char*, char*);
char *minus_str(char*, char*);
char *mult_str(char*, unsigned int);
// Functions for working with files
char *read_to(FILE*, char);
char *read_file(FILE*);
char *read_line(FILE*);
#endif
