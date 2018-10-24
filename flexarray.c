#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "flexarray.h"

/* -------------------------------------------------------*/
/*                   FlexArray class                      */
/* -------------------------------------------------------*/

/*A struct definition for a flexable array that has an
 *associated capacity, itemcount and an array of strings.
 */
struct flexarrayrec {
    int capacity;
    int itemcount;
    char **items; 
};

/*Method that creates a new flexible array.
 *Returns the new flexible array.
 */
flexarray flexarray_new() {
    int index;
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof (char*));
    for(index = 0; index < result->capacity; index++) {
        result->items[index] = NULL;
    }
    return result;
}

/*Method that appends an item to the end of the flex array.
 *Param: the flexarray
 *Param: *str, the word to add to the flexarray
 */
void flexarray_append(flexarray f, char *str) {
    int index;
    if(f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = remalloc(f->items, f->capacity * sizeof (char*));
    }
    f->items[f->itemcount] = emalloc(strlen(str)+1*
                                     sizeof *(f->items+f->itemcount));

    strcpy(f->items[f->itemcount], str);
    f->itemcount++;
    for(index = f->itemcount; index < f->capacity; index++) {
        f->items[index] = NULL;
    }
}

/*Method that checks to see if there is a certain string inside
 *the flex array.
 *Param: f, the flex array
 *Param: *str, the string to search for
 *Returns 1 if the string is in the flexarray, 0 if it is not
 */
int is_present(flexarray f, char *str) {
    int index;
    for(index = 0; index < f->capacity; index++) {
        if(f->items[index] != NULL) {
            if(strcmp(f->items[index], str) == 0){
                return 1;
            }
            
        }
    }
    return 0;
}
/*Method that visits each string in the flexarray to print all
 *the items in the flex array.
 *Param: f, flexarray
 *Param: the function f, a function that will be passed through
 *the method.
 */
void visit(flexarray g, void f(char *s)) {
    int index;
    for(index = 0; index < g->capacity; index++){
        if(g->items[index] != NULL) {
            f(g->items[index]);
        }
    }
}

/*Method that frees the memory associated with the flexarray.
 *Param: f, the flexarray.
 */
void flexarray_free(flexarray f) {
    int index;
    for(index = 0; index < f->capacity; index++){
        if(f->items[index] != NULL){
            free(f->items[index]);
        }
    }
    free(f->items);
    free(f);
}
