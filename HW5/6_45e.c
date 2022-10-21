//_________________________________________________
//6_45_e;

#define MAX_SIZE 20
#include <stdlib.h>
#include <stdio.h>
//#include "queuelib.h"


typedef struct tnode {
  int data;           
  struct tnode *left;  
  struct tnode *right; 
} tnode;


typedef struct queue {
  void *data;
  struct queue *next;
} queue;

int size_queue(queue **q) {
    int count = 0;
    queue *temp = *q;
    for(; temp != NULL; temp = temp -> next)
        count += 1;
    free(temp);
    return count;
}

void push_back(void *d, queue **q) {
        if (size_queue(&(*q)) < MAX_SIZE) {
            queue *tmp = *q;
            queue *new = (queue *) malloc(sizeof(queue));
            new -> data = d;
            new -> next = NULL;
            if (tmp != NULL) {
                while (tmp -> next != NULL)
                    tmp = tmp -> next;
                tmp -> next = new;
            }
            else 
                *q = new;
        }
}

void *pull_front(queue **q) {
    if ((*q) != NULL) {
        queue *tmp = *q;
        void *d = tmp -> data;
        *q = (*q) -> next;
        free(tmp);
        return d;
    }
    return NULL;
}


void delete_queue(queue **q) {
     queue *tmp;
     while ((*q) -> next != NULL) {
        tmp = (*q);
        (*q) = (*q) -> next;
        free(tmp);
    }
    *q = NULL;    
}


void add_tnode(int x, tnode **t) {
    if (*t == NULL) { 
        *t = (tnode *) malloc(sizeof(tnode));
        (*t) -> data = x;   
        (*t) -> left = NULL;
        (*t) -> right = NULL; 
    }
    else  if (x < ((*t) -> data))   
        add_tnode(x, &((*t) -> left));
    else    
        add_tnode(x, &((*t) -> right));
}

void free_tnode(tnode **t) {
    if (*t != NULL) {
        free_tnode(&((*t) -> left));
        free_tnode(&((*t) -> right));
        free(*t);
    }
}

void print_tree(tnode **t) {
  if (*t != NULL) { 
    printf("%d ", (*t) -> data); 
    print_tree(&((*t) -> left));
    print_tree(&((*t) -> right));
  }
}

/*подсчитывает количество узлов на N-ом уровне непустого двоичного
дерева (корень считать узлом нулевого уровня) */

int count_level(int level, tnode **t) {
    int count = 0;
    if ((level < 0) || (*t == NULL))
        return count;
    else {
        tnode *tmp = *t;
        int i, j, count = 1;
        queue *q = NULL;
        push_back(tmp, &q);
        for(i = 0; (q != NULL) && (i < level); i++) {
            j = 0;
            for(; count > 0; count--) {
                tmp = (tnode *)pull_front(&q);
                if (tmp -> left != NULL){
                    j++;
                    push_back(tmp -> left, &q);
                }
                if (tmp -> right != NULL){
                    j++;
                    push_back(tmp -> right, &q);
                }
            }
            if (j == 0)
                break;
            count = j;
        }
        delete_queue(&q);
        return count;
    }
}
    



int main(void) {
    tnode *tree = NULL;
    add_tnode(7, &tree);
    add_tnode(2, &tree);
    add_tnode(3, &tree);
    add_tnode(1, &tree);
    add_tnode(10, &tree);
    add_tnode(9, &tree);
    add_tnode(11, &tree);
    add_tnode(100, &tree);
    add_tnode(110, &tree);
    print_tree(&tree);
    printf("\n");
    printf("%d\n", count_level(0, &tree));
    printf("%d\n", count_level(1, &tree));
    printf("%d\n", count_level(2, &tree));
    printf("%d\n", count_level(3, &tree));
    free_tnode(&tree);
    return 0;
}
