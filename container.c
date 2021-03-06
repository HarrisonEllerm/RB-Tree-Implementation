#include <stdio.h>
#include <stdlib.h>
#include "container.h"
#include "mylib.h"
#include "flexarray.h"
#include "rbt.h"

/* -------------------------------------------------------*/
/*                   Container class                      */
/* -------------------------------------------------------*/

/*A struct for a container that has an associated
 *type (either a red-black-tree or flexarray) and a void
 *pointer that will be set to point the associated container.
 */
struct container_c {
    container_t type;
    void *contents;
};

/*Method that creates a new container.
 *First assigns memory to a container and then it allocates an
 *RBT or a flexarray to the container. 
 *Param: type, which is either RBT or flexarray
 *Returns the newly allocatd container.
 */
container container_new(char type){
    container c1 = emalloc(sizeof *c1);
    c1->contents = NULL;
    if(type == 'f') {
        c1->type = FLEX_ARRAY;
        c1->contents = flexarray_new();

    } else {
        c1->type = RED_BLACK_TREE;
        c1->contents = rbt_new();
    }
    return c1;
}

/*Method that prints all the contents of a container.
 *Param: c of type container,
 *Param: hash_index, the hash number
 *Param: function f, which used as a print function
 */
void container_print(container c, int hash_index, void f(char *s)) {
    printf("%d: ", hash_index);
    if(c->type == FLEX_ARRAY) {
        visit(c->contents, f);
    } else {
        rbt_preorder(c->contents, f);
    }
}

/*Method that fills the flexarray or the RBT with strings.
 *Param: c,which is the container 
 *Param: *str, which is the word we want to fill in
 */
void container_add(container c, char *str) {
    if(c->type == FLEX_ARRAY) {
        flexarray_append(c->contents, str);
    } else {
        c->contents = rbt_insert_real(c->contents, str);
    }
}

/*Free method that frees the memory associated with either
 *the flexarray or the RBT.
 *Param: c, the container 
 */
void container_free(container c) {
   
    if(c->type == FLEX_ARRAY) {
        flexarray_free(c->contents);
    } else {
        rbt_free(c->contents);
    }
    free(c);  
}   

/*Method that searches for a certain string in flexarray or RBT.
 *Param: c, the container from struct
 *Param:  key, which is the word we are searching for
 *Returns 0 if the word is not found or a 1 if it is successfully
 *found in the RBT or flexarray.
 *Returns -1 if an error ocurred.
 */
int container_search(container c, char *key) {
    if(c->type == RED_BLACK_TREE) {
        return rbt_search(c->contents, key);
    } else {
        return is_present(c->contents, key);
    }
    return -1;
}
