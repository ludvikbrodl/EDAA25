#include <stdio.h>
#include <ctype.h>

typedef struct list_t list_t;

struct list_t {
	list_t*	succ;
	list_t*	pred;
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




int main(void)
{
	int length, length_temp;
	list_t* head;
	list_t* head_temp;
	head = NULL;
	head_temp = NULL;
	length = 0;
	length_temp = 0;
	while ((ch = getchar()) != EOF) {
		free_list(&head_temp);
		while (isalpha(ch)) {
			insert_last(&head_temp, ch);
			length_temp++;
			ch = getchar();
		}
		if (length_temp > length) {
			free_list(&head);
			head = head_temp;
			length = length_temp;
			head_temp = NULL; //'make room' for new list
		} else {
			free_list(&head_temp);
		}
		length_temp = 0;
	}
	printf("%d characters in longest word: ", length);
	list_t* p = head;
	do {
		printf("%c", p->data);
		p = p->succ;
	} while (p != head);
	printf("\n");
	free_list(&head);
	return 0;
}