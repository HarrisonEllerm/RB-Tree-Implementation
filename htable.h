#ifndef HTABLE_H
#define HTABLE_H_

#include <stdio.h>

/*
 * Header file for htable.c which defines the behavior of the htable class.
 */

typedef struct htablerec *htable;

extern void htable_free(htable h);
extern void htable_insert(htable h, char *str, char type);
extern htable htable_new(int capacity);
extern void htable_print(htable h,  void f(char *s));
extern int htable_search(htable h, char *str);
extern void test_htable_creation_and_deletion(htable h);
extern unsigned int htable_word_to_int(char *word, htable h);

#endif
