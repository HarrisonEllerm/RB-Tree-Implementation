#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"
#include "mylib.h"
#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/* -------------------------------------------------------*/
/*                      rbt class                         */
/* -------------------------------------------------------*/

/*Enumerated type used to define a nodes color.
 */
typedef enum { RED, BLACK } rbt_colour;

/*A struct for an red-black tree node that has a
 *character array key, associated colour and left
 *or right nodes that may or may not be NULL.
 */
struct rbtnode {
    char *key;
    rbt_colour colour;
    rbt left;
    rbt right;
};

/*Method that creates a new RBT and sets the pointer to NULL.
 *Returns NULL
 */
rbt rbt_new() {
    return NULL;
}

/*Method that recursively searches for a specific word in the RBT.
 *Param: b, the RBT
 *Param: *str, the word to search for
 *Returns 0 if the RBT is null, 1 if the words are the same
 */
int rbt_search(rbt b, char *str) {
    if(b == NULL) {
        return 0;
    }
    if(strcmp(b->key, str) == 0) { 
        return 1;
    }
    if(strcmp(b->key, str) > 0) { 
        return rbt_search(b->left, str);
    }
    return rbt_search(b->right, str);
}

/*Method that will do a right rotation in the current RBT.
 *Param: b, the RBT 
 */
static rbt rbt_right_rotate(rbt b) {
    struct rbtnode *temp = b;
    struct rbtnode *root = b;
    root = root->left;
    temp->left = root->right;
    root->right = temp;
    return root;
}
/*Method that will do a left rotation in the current RBT.
 *Param: b, the RBT 
 */
static rbt rbt_left_rotate(rbt b) {
    struct rbtnode *temp = b;
    struct rbtnode *root = b;
    root = root->right;
    temp->right = root->left;
    root->left = temp;
    return root;
}


/*Method that corrects an RBT if it breaks one of the RBT standard rules.
 *Used when an insertion has resulted in two consecutive reds
 *Param: rbt, the RBT
 *Returns the corrected RBT 
 */
rbt rbt_fix(rbt rbt) {
    
    if(IS_RED(rbt->left) && IS_RED(rbt->left->left)) {
        if(IS_RED(rbt->right)) {

            rbt->colour = RED;
            rbt->left->colour = BLACK;
            rbt->right->colour = BLACK;
            
        } else if(IS_BLACK(rbt->right)) {

            rbt = rbt_right_rotate(rbt);
            rbt->colour = BLACK;
            rbt->right->colour = RED;
        }
    
    }else if(IS_RED(rbt->left) && IS_RED(rbt->left->right)) {
        if(IS_RED(rbt->right)) {

            rbt->colour = RED;
            rbt->left->colour = BLACK;
            rbt->right->colour = BLACK;
            
        } else if(IS_BLACK(rbt->right)) {

            rbt->left = rbt_left_rotate(rbt->left);
            rbt = rbt_right_rotate(rbt);
            rbt->colour = BLACK;
            rbt->right->colour = RED;
        }
        
    }else if(IS_RED(rbt->right) && IS_RED(rbt->right->left)) {
        if(IS_RED(rbt->left)) {

            rbt->colour = RED;
            rbt->left->colour = BLACK;
            rbt->right->colour = BLACK;

        } else if(IS_BLACK(rbt->left)) {

            rbt->right = rbt_right_rotate(rbt->right);
            rbt = rbt_left_rotate(rbt);
            rbt->colour = BLACK;
            rbt->left->colour = RED;
        }

    }else if(IS_RED(rbt->right) && IS_RED(rbt->right->right)) {
        if(IS_RED(rbt->left)) {

            rbt->colour = RED;
            rbt->left->colour = BLACK;
            rbt->right->colour = BLACK;

        }else if(IS_BLACK(rbt->left)) {

            rbt = rbt_left_rotate(rbt);
            rbt->colour = BLACK;
            rbt->left->colour = RED;
        }
   
    }
    return rbt;
}

/*Method that will insert a particular word into the RBT.
 *Parameters: the RBT and the word that we want to insert
 *Returns the new RBT with the word in it 
 */
rbt rbt_insert(rbt b, char *str) {
    if(b == NULL) {
        rbt b = emalloc(sizeof *b);
        b->key = emalloc(strlen(str)+1);
        strcpy(b->key, str);
        b->colour = RED;
        b->left = NULL;
        b->right = NULL;;
        return b;
    }
  
    if(strcmp(b->key, str) >= 0) { 
        b->left = rbt_insert(b->left, str);

    }else if(strcmp(b->key, str) < 0) { 
        b->right = rbt_insert(b->right, str);
    }
    b = rbt_fix(b);
    return b;
}

/*Method that fixes the RBT to ensure that the root of the tree is
  always black.
 *Param: b, the RBT to fix
 *Param: *str, the string to insert into the RBT 
 *Returns the corrected RBT with a black root
 */
rbt rbt_insert_real(rbt b, char *str) {
    b = rbt_insert(b, str);
    if(IS_RED(b)) {
        b->colour = BLACK;
    }
    return b;
}

/*Method that traverses the RBT by inorder.
 *Param: b, RBT
 *Param: f, the function that is passed into this method
 */
void rbt_inorder(rbt b, void f(char *str)) {
    if(b == NULL) {
        return;
    }else{
        rbt_inorder(b->left,f);
        f(b->key);
        rbt_inorder(b->right,f);
    }
}
/*Method that traverses the RBT by preorder.
 *Param: b, RBT
 *Param: f, function that is passed into this method 
 */
void rbt_preorder(rbt b, void f(char *s)) {
    if(b == NULL) {
        return;
    }else{
        f(b->key);
   
        rbt_preorder(b->left, f);
        rbt_preorder(b->right, f);
    }
}

/*Method that frees the memory associated with the RBT.
 *Param: b, the RBT
 *Returns the RBT 
 */
rbt rbt_free(rbt b) {
    if(b == NULL) {
        return b;
    }else{
        rbt_free(b->left);
        free(b->key);
        rbt_free(b->right);
        free(b);
    }
    return NULL;
}

/*Method that deletes a specific word in the RBT.
 *Param: b, the RBT
 *Param: *str, the string to delete
 *Returns the new RBT
 */ 
rbt rbt_delete(rbt b, char *str) {

    if(b == NULL) {
        return b;

    }else if(strcmp(b->key, str) > 0) {
        b->left = rbt_delete(b->left, str);

    }else if(strcmp(b->key, str) < 0) {
        b->right = rbt_delete(b->right, str);
    }

    if(strcmp(b->key, str) == 0) {

        if(b->left == NULL && b->right == NULL) {
            free(b->key);
            free(b);
            b = NULL;
            
        }else if((b->left!= NULL && b->right == NULL) ||
                 (b->right!= NULL && b->left == NULL)) {

            if(b->left != NULL) {
                struct rbtnode *temp = b;
                b = b->left;
                free(temp->key);
                free(temp);
            
            }else if(b->right != NULL) {
                struct rbtnode *temp = b;
                b = b->right;
                free(temp->key);
                free(temp);
            }
       
        }else if(b->left!=NULL && b->right!=NULL) {
            rbt tempRBT;
            tempRBT = b->right;
            while(tempRBT->left != NULL) {
                tempRBT = tempRBT->left;
            }
            strcpy(b->key, tempRBT->key);
            b->right = rbt_delete(b->right, tempRBT->key);
        } 
    }
    return b;
}
