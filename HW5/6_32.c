/*6.32. Описать функцию, которая строит список L2 - копию списка L1.
        struct lnode { struct data ∗p;
                       struct lnode ∗next; };
        struct data { double f; char ∗s[2];};
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data { 
    double f; 
    char *s[2];
} t_data; 

typedef struct s_lnode { 
    struct t_data *p;
	struct s_lnode *next; 
    
} t_lnode;


t_lnode *copy_list(t_lnode **l1) {
    if (*l1 != NULL) {
        t_lnode *l2, *tmp = *l1;
        t_lnode *copy = (t_lnode *) malloc(sizeof(t_lnode));
        l2 = copy;
        while (tmp -> next != NULL) {
            memcpy(copy -> p, tmp -> p, sizeof(t_data));
            copy -> next = (t_lnode *) malloc(sizeof(t_lnode));
            tmp = tmp -> next;
        }
        memcpy(copy -> p, tmp -> p, sizeof(t_data));
        copy -> next = NULL;
        return l2;
    }
    return *l1;
}
