#include <stdio.h>
#include <string.h>

typedef struct list_t list_t;

struct list_t {
	list_t*	succ;
	void* 	data;
};

list_t* new_list(void* data)
{
	list_t* list;
	list = malloc(sizeof(list_t));

	(*list).succ = list;
	(*list).data = data;

	return list;
}

void free_list(list_t** head)
{
	list_t*		h = *head;
	list_t*		p;
	list_t*		q;
	if (h == NULL) {
		return;
	}
	p = (*h).succ;
	while (p != NULL) {
		q = (*p).succ;
		free(p);
		p = q;
	}
	//free(p); //probably should no be here, this is to free the LAST node
	*head = NULL; //dunno why
}

void insert_succ(list_t* list, void* data)
{
	list_t*		p = list;
	list_t*		q;

	if (p == NULL) {
		list = new_list(data);
		return;
	}

	q = malloc(sizeof(list_t));

	q->data = data;
	q->succ = NULL;
	p->succ = q;
}

int ch;
list_t* head;
list_t* head_temp;
list_t* current_node;
int length;
int length_temp;

int main(void)
{
	length = 0;
	length_temp = 0;
	head = current_node;
	while ((ch = getchar()) != EOF) {
		if (length > length_temp) {
			free_list(&head_temp);
			length_temp = 0;
		} else {
			free_list(&head);
			length = length_temp;
			length_temp = 0;
			memcpy(head, head_temp, sizeof(list_t));
		}
		while (ch != '\n' && ch != ' ') {
			insert_succ(current_node, &ch);
			length_temp++;
			ch = getchar();
		}
	}
	current_node = head;
	while (current_node->succ != NULL) {
		printf("%s", (char*)current_node->data);
		current_node = current_node->succ;
	}
	free_list(&head_temp);
	free_list(&head);
	return 0;
}
