// QUEUE
//6_42;

#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 30

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

int is_empty(queue **q) {
	if ((*q) == NULL) 
		return 1;
	return 0;
}

int main(void) {
	queue *q = NULL;
    int *j, i;
	char *c = "asd";
	for (i = 0; i < 5; i++) {
	    j = (int*)malloc(sizeof(int));
	    *j = i;
		push_back(j, &q);
	}
	printf("Size: %d\n", size_queue(&q));
	//delete_queue(&q);
	
	while (!is_empty(&q)) 
		printf("%d ", *(int *)pull_front(&q));
	printf("\n");
	printf("Size: %d\n", size_queue(&q));
	for (i = 0; i < 3; i++) {
		push_back(c, &q);
		c++;
	}
	printf("Size: %d\n", size_queue(&q));
	while (!is_empty(&q)) 
		printf("%c ", *(char *)pull_front(&q));
}
