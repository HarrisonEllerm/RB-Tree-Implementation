#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

#include <stdio.h>

/* -------------------------------------------------------*/
/*              Header file for flexarray.c:              */
/*     Defines the behaviour for the flexarray class.     */
/* -------------------------------------------------------*/

typedef struct flexarrayrec *flexarray;

extern void flexarray_append(flexarray f, char *str);
extern void flexarray_free(flexarray f);
extern flexarray flexarray_new();
extern int is_present(flexarray f, char *str);
extern void visit(flexarray g, void f(char *s));

#endif
