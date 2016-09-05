// min-stack.c

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 3
#define TOW_SIZE 3

typedef struct node {
	int value;
	int min;
} node_t;

typedef struct stack {
	node_t **array;
	int used;
	int size;
} str_t;

str_t* initStack() {
	str_t* st = malloc(sizeof(str_t));

	st->array = malloc(sizeof(node_t**));
	if (st->array == NULL) {
		perror("malloc error initStack:st->array:malloc()\n");
		exit(1);
	}
	st->size = 1;
	st->used = 0;
	return st;
}

void clearStack(str_t* st, int mode) {
	node_t* tmp = NULL;
	for(int i = 0; i < st->used; ++i) {
		if (tmp != NULL) free(tmp);
		tmp = st->array[i];
	}
	if (tmp != NULL) free(tmp);
	free(st->array);
	st->array = NULL;
	st->size = 0;
	if (mode) free(st);
}

void push(str_t *s ,int t) {
	node_t *n = malloc(sizeof(node_t));
	if (n == NULL) {
		perror("malloc error push:n:malloc()\n");
		exit(1);
	}
	n->value = t;

	if (s->size == s->used) {
		s->size *= 2;
		s->array = realloc(s->array, s->size * sizeof(node_t**));
		if (s->array == NULL) {
			perror("realloc error push:s->array:malloc()\n");
			exit(1);
		}
	}

	if (s->used == 0) {
		n->min = t;
	} else if (s->array[s->used - 1]->value < s->array[s->used - 1]->min) {
		n->min = s->array[s->used - 1]->value;
	} else {
		n->min = s->array[s->used - 1]->min;
	}

	s->array[s->used++] = n;
}

int pop(str_t *s) {
	node_t* n = s->array[--s->used];
	int ret = n->value;
	free(n);
	return(ret);
}    

void display(str_t *st) {
	
	for(int i = st->used-1; i >= 0; --i) {
		printf("%03d  [ %3d ],[ %3d ] \n", i, st->array[i]->value, st->array[i]->min);
	}
	printf("====================\n\n") ;
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

	srand(time(NULL));
	int i = atoi(argv[1]);
	str_t* s = initStack();

	for (int j = 0;j < i; ++j) {
		push(s, rand() % 999);
	}

	display(s);

	int te = rand() % s->used;
	for (int j = 0;j < te; ++j) {
		pop(s);
	}

	display(s);

	clearStack(s, 1);
	printf("%s: exiting.\n", argv[0]);
	return(0);
}

