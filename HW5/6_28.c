/*. 6.28. Описать функцию, которая
a) меняет местами первый и последний элементы списка;
b) удаляет из списка первое вхождение элемента с заданным значением (если оно есть);
   1) список с заглавным звеном;
   2) список без заглавного звена;
c) удаляет из списка все вхождения элемента с заданным значением
(если они есть);
   1) список с заглавным звеном;
   2) список без заглавного звена;
d) после каждого звена с заданным значением вставляет еще одно
звено с таким же значением.
Тип данных - double∗, анализируются вещественные числа. 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct s_list {
	int num;
	struct s_list *next;
} t_list;


t_list *create_node(int n) {
	t_list *node = (t_list *) malloc(sizeof(t_list));
	node -> num = n;
	node -> next = NULL;
	return node;
}

void delete_list(t_list **list)
{
    t_list *prev = NULL;
	 while ((*list) -> next != NULL) {
	    prev = (*list);
	    (*list) = (*list) -> next;
        free(prev);
    }
    free(*list);
}

void add_first(t_list **list, int n) {
	t_list *new = create_node(n);
	new -> next = *list;
	*list = new;
}

void add_last(t_list **list, int n) {
	t_list *tmp = *list;
	t_list *new = create_node(n);
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new;
	
}

void print_list(t_list **list) {
    t_list *tmp = *list;
    if (tmp != NULL) {
    	while (tmp != NULL) {
    		printf("%d ", tmp -> num);
    		tmp = tmp -> next;
    	}
    	printf("\n");
    }
    else 
        printf("List is NULL\n");
}

// task A
void swap_first_last(t_list **list) {
	t_list *tmp = *list;
	t_list *first = *list;
	if (tmp != NULL && tmp -> next != NULL) {
		while (tmp -> next -> next != NULL) 
			tmp = tmp -> next;
		*list = tmp -> next;
		tmp -> next -> next = first -> next;
		tmp -> next = first;
		first -> next = NULL;
	}
}

// task B_1
void delete_one_num(t_list **list, int n) {
    t_list *tmp1 = *list;
    t_list *tmp2 = *list;
    while (tmp1 -> num != n && tmp1 -> next != NULL) {
        tmp2 = tmp1;
        tmp1 = tmp1 -> next;
    }
    if (tmp1 -> num == n)  {
        if (tmp1 != tmp2)
            tmp2 -> next = tmp1 -> next;
        else
            *list = tmp1 -> next;
    }
}

// task C_1
void delete_all_num(t_list **list, int n) {
    t_list *tmp1 = *list;
    t_list *tmp2 = *list;
    while (tmp1 -> num == n && tmp1 != NULL) {
        *list = tmp1 -> next;
        tmp1 = tmp1 -> next;
    }
    while (tmp1 -> next != NULL) {
        if (tmp1 -> num == n) {
            tmp1 = tmp1 -> next;
            tmp2 -> next = tmp1;
        }
        else {
            tmp2 = tmp1;
            tmp1 = tmp1 -> next;
        }
    }
    if (tmp1 -> num == n) {
        tmp1 = NULL;
        tmp2 -> next = tmp1;
    }
    
}

// task D
void repeat_num(t_list **list, int n) {
    t_list *tmp1 = *list;
    t_list *tmp2 = *list;
    while (tmp1 -> next != NULL) {
        if (tmp1 -> num == n) {
            t_list *new = create_node(n);
            tmp2 = tmp1;
            tmp1 = tmp1 -> next;
            tmp2 -> next = new;
            new -> next = tmp1;
        }
        else
            tmp1 = tmp1 -> next;
    }
    if (tmp1 -> num == n) {
        t_list *new = create_node(n);
        tmp1 -> next = new;
    }
    
}



int main(void) {
	int i, k, m;
	t_list *l = create_node(1); 
	for (i = 2; i < 6; ++i) {
	    add_last(&l, i);
	}
	//add_first(&l, 0);
	// task A
	printf("Swap first and last: \n");
	print_list(&l);
	swap_first_last(&l);
	print_list(&l);
	printf("\n");
	
	// task B_1
	k = 4;
	printf("Delete one number %d: \n", 1);
	add_first(&l, 5);
	add_first(&l, 4);
	add_last(&l, 4);
    //add_first(&l, 3);
	print_list(&l);
	delete_one_num(&l, 1);
	print_list(&l);
	printf("\n");
	
	// task C_1
	printf("Delete all number %d: \n", k);
	print_list(&l);
	delete_all_num(&l, k);
	print_list(&l);
	printf("\n");
	
	// task D
	m = 3;
	printf("Repeat number %d: \n", m);
	//delete_all_num(&l, 5);
	//delete_all_num(&l, 3);
	add_first(&l, 2);
	print_list(&l);
	repeat_num(&l, m);
	print_list(&l);
	printf("\n");
	
	delete_list(&l);
	return 0;
}