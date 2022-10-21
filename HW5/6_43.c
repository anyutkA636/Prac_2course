// STACK
//6_43;

#define MAX_SIZE 20
#include <stdlib.h>
#include <stdio.h>


typedef struct stack {
  void *data;
  struct stack *next;
} stack;


int size_stack(stack **s) {
	int count = 0;
	stack *temp = *s;
	for(; temp != NULL; temp = temp -> next)
		count += 1;
	free(temp);
	return count;
}

void push_front(void *d, stack **s) {
    if (size_stack(&(*s)) < MAX_SIZE) {
    	stack *new = (stack *) malloc(sizeof(stack));
    	new -> data = d;
    	new -> next = *s;
    	*s = new;
    }
}

void *pop_front(stack **s) {
	if ((*s) != NULL) {
		stack *tmp = *s;
		void *d = tmp -> data;
		*s = (*s) -> next;
		free(tmp);
		return d;
	}
	return NULL;
}

void delete_stack(stack **s) {
	 stack *tmp;
	 while ((*s) -> next != NULL) {
	    tmp = (*s);
	    (*s) = (*s) -> next;
        free(tmp);
    }
    *s = NULL;    
}

int is_empty(stack **s) {
	if ((*s) == NULL) 
		return 1;
	return 0;
}

int main(void) {
	stack *q = NULL;
    int *j, i;
	char *c = "asd";
	for (i = 0; i < 5; i++) {
	    j = (int*)malloc(sizeof(int));
	    *j = i;
		push_front(j, &q);
	}
	printf("Size: %d\n", size_stack(&q));
	//delete_queue(&q);
	
	while (!is_empty(&q)) 
		printf("%d ", *(int *)pop_front(&q));
	printf("\n");

	printf("Size: %d\n", size_stack(&q));
	
	for (i = 0; i < 3; i++) {
		push_front(c, &q);
		c++;
	}
    printf("Size: %d\n", size_stack(&q));
	while (!is_empty(&q)) 
		printf("%c ", *(char *)pop_front(&q));
}
