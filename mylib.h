#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>

/* -------------------------------------------------------*/
/*              Header file for mylib.c:                  */
/*     Defines the behaviour for the mylib class.         */
/* -------------------------------------------------------*/

extern void *emalloc(size_t);
extern void *remalloc(void *, size_t);
extern int getword(char *s, int limit, FILE *stream);

#endif
