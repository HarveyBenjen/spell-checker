#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct dict dict;

/* Create empty dic */
dict* dict_init(int size);

/* Add one element into the dic */
void dict_insert(dict* s, char* v);

/* Returns true if v is in the array, false elsewise */
bool dict_isin(dict* s, char* v);

/* Finish up */
/* Clears all space used, and sets pointer to NULL */
void dict_free(dict** s);
