// stack.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 3
#define TOW_SIZE 3

typedef struct node {
	int value;
	struct node *nxt;
} node_t;

typedef struct stack {
	node_t *top;
	int size;
} str_t;

str_t* initStack() {
	str_t* st = malloc(sizeof(str_t));
	st->top = NULL;
	st->size = 0;
	return st;
}

void clearStack(str_t* st) {
	node_t* tmp = NULL;
	for(node_t *s = st->top; s !=NULL; s = s->nxt) {
		if (tmp != NULL) free(tmp);
		tmp = s;
	}
	if (tmp != NULL) free(tmp);
	st->top = NULL;
	st->size = 0;
	free(st);
}

void push(str_t *s ,int t) {
	node_t *n = malloc(sizeof(node_t));
	n->value = t;
	n->nxt = s->top;
	s->top = n;
}

int pop(str_t *s) {
	node_t *n = s->top;   
	s->top = n->nxt;
	int val = n->value;
	free(n); 
	return val;
}    

void display(str_t *st) {
	
	for(node_t *s = st->top; s !=NULL; s = s->nxt) {
		printf("  [ %3d ]  \n",s->value);
	}
	printf("===========\n\n") ;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s [ # ]\n", argv[0]);
		return(-1);
	}

	int str_size = strlen(argv[1]);
	for (int j = 0; j < str_size; ++j) {
		if (!(isdigit(argv[1][j]))) {
			fprintf(stderr, "%s is not a valid input.\n", argv[1]);
			return(1);
		}
	}

	int i = atoi(argv[1]);
	str_t* s = initStack();

	for (int j = 0;j <= i; ++j) {
		push(s,j);
	}

	display(s);

	pop(s);
	pop(s);

	display(s);

	clearStack(s);
	printf("%s: exiting.\n", argv[0]);
	return(0);
}

