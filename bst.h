#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct dic dic;

/* Create empty dic */
dic* dic_init(int size);

/* Add one element into the dic */
void dic_insert(dic* s, char* v);

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic* s, char* v);

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void dic_free(dic** s);
