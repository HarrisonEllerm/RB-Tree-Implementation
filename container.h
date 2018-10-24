#ifndef CONTAINER_H
#define CONTAINER_H_

#include <stdio.h>

/* -------------------------------------------------------*/
/*              Header file for container.c:              */
/*     Defines the behaviour for the container class.     */
/* -------------------------------------------------------*/

typedef struct container_c *container;
typedef enum container_e{FLEX_ARRAY, RED_BLACK_TREE} container_t;

extern container container_new(char type);
extern void container_print(container c, int hash_index, void f(char *s));   
extern void container_add(container c, char *str);
extern void container_free(container c);
extern int container_search(container c, char *str);

#endif
