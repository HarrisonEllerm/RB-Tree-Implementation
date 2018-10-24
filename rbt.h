#ifndef RBT_H_
#define RBT_H_

/* -------------------------------------------------------*/
/*                Header file for rbt.c:                  */
/*     Defines the behaviour for the rbt class.           */
/* -------------------------------------------------------*/

typedef struct rbtnode *rbt;

extern rbt rbt_delete(rbt b, char *str);
extern rbt rbt_free(rbt b);
extern rbt rbt_insert(rbt b, char *str); 
extern rbt rbt_new();
extern void rbt_preorder(rbt b, void f(char *s )); 
extern int rbt_search(rbt b, char *str);
extern rbt rbt_insert_real(rbt b, char *str);

#endif 
