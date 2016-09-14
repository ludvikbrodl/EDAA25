#include <stdio.h>
#include <string.h>

typedef struct list_t list_t;

struct list_t {
	list_t*	succ;
	list_t* pred;
	char 	data;
};

list_t* new_list(char data)
{
	list_t* list;
	list = malloc(sizeof(list_t));

	(*list).succ = NULL;
	list->pred = list;
	(*list).data = data;

	return list;
}

void free_list(list_t** list)
{
	list_t*		p;
	list_t*		q;

	p = *list;
	if (p == NULL) {
		return;
	}
	p->pred->succ = NULL;
	do {
		q = p->succ;
		free(p);
		p = q;
	} while (p != NULL);
	*list = NULL; //dunno why
}

void insert_last(list_t** list, char data)
{
	list_t*		p = *list;
	list_t*		q;

	if (p == NULL) {
		*list = new_list(data);
		return;
	}

	q = malloc(sizeof(list_t));

	q->data 		= data;
	q->pred 		= p->pred;
	q->succ 		= p;
	p->pred->succ 	= q;
	p->pred 		= q;
}

int ch;


int length;
int length_temp;

int main(void)
{
	//list_t* head_temp = new_list(NULL);
	list_t* head = NULL;
	length = 0;
	length_temp = 0;
	while ((ch = getchar()) != EOF) {
		while (ch != '\n' && ch != ' ') {
			insert_last(&head, ch);
			length_temp++;
			ch = getchar();
			
			//printf("%s", (char*)head->data);
		}
		/*
		if (length > length_temp) {
			free_list(&head_temp);
			head_temp = new_list(NULL);
			length_temp = 0;
		} else {
			free_list(&head);
			head = new_list(NULL);
			length = length_temp;
			length_temp = 0;
			memcpy(head, head_temp, sizeof(list_t));
			free_list(&head_temp);
		}*/

	}
	list_t* p = head;
	do {
		printf("%c ", p->data);
		p = p->succ;
	} while (p != head);
	//free_list(&head_temp);
	free_list(&head);
	return 0;
}
