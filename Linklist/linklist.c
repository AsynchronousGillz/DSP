#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char* data;
	int key;
	struct node *next;
} node_t;

typedef struct list {
	struct node *head;
	int length;
} list_t;

//init Linklist
list_t* initList() {
	list_t* ret = malloc(sizeof(list_t));
	ret->head = NULL;
	ret->length = 0;
	return ret;
}

//clear the list
void clearList(list_t* l, int mode) {
	//start from the beginning
	node_t *temp = NULL;
	for(node_t *ptr = l->head; ptr != NULL; ptr = ptr->next) {        
		if (temp != NULL) {
			free(temp->data);
			free(temp);
			temp = NULL;
		}
		temp = ptr;
	}
	if (temp != NULL) {
		free(temp->data);
		free(temp);
		temp = NULL;
	}
	l->head = NULL;
	l->length = 0;
	if (mode != 0) free(l);
}

//print theee node
void printLink(node_t* ptr) {
	if (ptr->data) printf("(%d,%s) ",ptr->key, ptr->data);
}

//display the list
void printList(list_t* l) {
	printf("Current List: [ ");
	//start from the beginning
	for(node_t *ptr = l->head; ptr != NULL; ptr = ptr->next) {        
		printLink(ptr);
	}
	printf(" ]\n");
}

//insert link at the first location
void insert(list_t* l, int key, char* data) {
	//create a link
	node_t *link = malloc(sizeof(node_t));

	link->key = key;

	int strle = sizeof(char)*(strlen(data) + 1);
	link->data = malloc(strle);
	memcpy(link->data, data, strle);

	//point it to old first node
	link->next = l->head;

	//point first to new first node
	l->head = link;
	++l->length;
}

//is list empty
int isEmpty(list_t* l) {
	return l->head == NULL;
}

//how long is the linklist
int length(list_t* l) {
	int length = 0;

	for (node_t *current = l->head; current != NULL; current = current->next) {
		length++;
	}

	return length;
}

//find a link with given key
node_t* find(list_t* l, int key) {

	//if list is empty
	if(l->head == NULL) {
		return NULL;
	}

	node_t* current = l->head;

	//start from the first link
	for (; current->key != key; current = current->next) {
		//if it is last node
		if(current->next == NULL) return NULL;
	}      

	//if data found, return the current Link
	return current;
}

//delete first item
void deleteTop(list_t* l) {

	//if list is empty
	if(l->head == NULL) {
		return;
	}

	//save reference to first link
	node_t *tempLink = l->head;
	free(tempLink->data);

	//mark next to first link as first 
	l->head = tempLink->next;

	//free the link
	free(tempLink);
}

//delete a link with given key
void deleteKey(list_t* l, int key) {

	//start from the first link
	node_t* current = l->head;
	node_t* previous = NULL;

	//if list is empty
	if(l->head == NULL) {
		return;
	}

	//navigate through list
	while (current->key != key) {

		//if it is last node
		if (current->next == NULL){
			return;
		} else {
			//store reference to current link
			previous = current;
			//move to next link
			current = current->next;             
		}

	}

	//found a match, update the link
	if(current == l->head) {
		//change first to point to next link
		l->head = l->head->next;
	} else {
		//bypass the current link
		previous->next = current->next;
	}    

	free(current->data);
	free(current);
}

//sort the linklist
void sort(list_t* l){
	struct node *tmpPtr = l->head;
	struct node *tmpNxt = (tmpPtr == NULL)?NULL:tmpPtr->next;

	while (tmpNxt != NULL) {
		while (tmpNxt != tmpPtr) {
			if (strcmp(tmpNxt->data, tmpPtr->data) > 0) {
				int tmpKey = tmpPtr->key;
				tmpPtr->key = tmpNxt->key;
				tmpNxt->key = tmpKey;

				char* tmpData = tmpPtr->data;
				tmpPtr->data = tmpNxt->data;
				tmpNxt->data = tmpData;
			}
			tmpPtr = tmpPtr->next;
		}
		tmpPtr = l->head;
		tmpNxt = tmpNxt->next;
	}
}

//do a flip
void reverse(list_t* l) {
	node_t* prev   = NULL;
	node_t* current = l->head;
	node_t* next;

	while (current != NULL) {
		next  = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	l->head = prev;
}

int main(int argv, char *argc[]) {

	list_t *link = initList();

	insert(link, 1, "cat");
	insert(link, 2, "dog");
	insert(link, 3, "one");
	insert(link, 4, "two");
	insert(link, 5, "red");
	insert(link, 6, "dis"); 

	printList(link);
	clearList(link, 0);

	printf("List after deleting all items: ");
	printList(link);

	insert(link, 1, "cat");
	insert(link, 2, "dog");
	insert(link, 3, "one");
	insert(link, 4, "two");
	insert(link, 5, "red");
	insert(link, 6, "dis"); 

	printList(link);

	node_t *foundLink = find(link, 4);

	if(foundLink != NULL){
		printf("Element found: ");  
		printLink(foundLink);        
	} else {
		printf("Element not found.");  
	}

	deleteKey(link, 4);
	printf("List after deleting an item: ");  
	printList(link);
	foundLink = find(link, 4);

	if(foundLink != NULL){
		printf("Element found: ");  
		printLink(foundLink);        
		printf("\n");  
	} else {
		printf("Element not found.\n");
	}

	sort(link);

	printf("List after sorting the data: ");  
	printList(link);

	reverse(link);
	printf("List after reversing the data: ");  
	printList(link);

	clearList(link, 1);
}
