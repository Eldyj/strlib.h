#ifndef STRLIB_H
#define STRLIB_H
#define STRLIB_VERSION "1.0.0"
#define string(a) char *a = NULL
// Structure that makes working with string arrays easier
typedef struct {
	char **array;
	unsigned int length;
} StringArray;

// String array functions
StringArray new_strarray(void);
void sa_free(StringArray*);
void sa_add(StringArray*, char*);
void sa_set(StringArray*, int, char*);
void sa_delete(StringArray*, int);
char *sa_get(StringArray, int);
char *sa_join(StringArray, char*);
int sa_index_of(StringArray, char*);
int sa_count(StringArray, char*);
bool sa_contains(StringArray, char*);
void sa_remove(StringArray*, char*);
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
char *strip(char*, char);
StringArray split(char*, char*);
char *replace(char*, char*, char*);
// Functions for working with files
char *read_file(FILE*);
#endif
