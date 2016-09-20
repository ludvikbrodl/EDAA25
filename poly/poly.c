#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "error.h"
#include "poly.h"



typedef struct list_t list_t;
typedef struct term_t term_t;

struct poly_t {
	list_t* terms;
};

struct term_t {
	int coff;
 	int exp;
};

void free_term(term_t* term);

struct list_t {
	list_t* succ;
	list_t* pred;
	term_t*	term;
};

list_t* new_list(term_t* term)
{
	list_t* list = malloc(sizeof(list_t));
	if (list == NULL) {
		exit(1);
	}
	list->succ = NULL;
	list->pred = list;
	list->term = term;
	return list;
}

void free_list(list_t** list)
{
	//no need to free term since coff and exp is saved from the stack strings on input
	list_t* p;
	list_t* q;

	p = *list;
	if (p == NULL) {
		return;
	}
	p->pred->succ = NULL;
	q = p->succ;
	free_term(p->term);
	free(p);
	p = q;
	while (p != NULL) {
		q = p->succ;
		free_term(p->term);
		free(p);
		p = q;
	}
	//*list = NULL; //for the lulz
}

void insert_last(list_t** list, term_t* term)
{
	list_t*		p = *list;
	list_t*		q;

	if (p == NULL) {
		*list = new_list(term);
		return;
	}

	q = malloc (sizeof(list_t));
	q->succ			= p;
	q->pred			= p->pred;
	q->term 		= term;
	p->pred->succ 	= q;
	p->pred			= q;
}
// - 2x^2 
term_t* new_term(const char* str)
{	
	term_t* term = malloc(sizeof(term_t));
	term->coff = 1;
	if (str[0] == '-') {
		term->coff = -1;
		str++;
		str++;
	} else if(str[0] == '+') {
		str++;
		str++;
	}
	char coff_str[100];
	char exp_str[100];

	char* x = strchr(str, 'x');
	if (x != NULL && (x-str) == 0) {
		term->coff = 1;
	} else if ((x-str) == 0) {
		memcpy(coff_str, str, x-str+1);
		term->coff = term->coff * atoi(coff_str);
	} else {
		term->coff = term->coff * atoi(str);
	}
	
	char* e = strchr(str, '^');
	if (e != NULL) {
		strncpy(exp_str, x+2, strlen(str)*sizeof(char)-(x-str));
		term->exp = atoi(exp_str);
	} else if (x != NULL) {
		term->exp = 1;
	} else {
		term->exp = 0;
	}
	return term;
}

void free_term(term_t* term)
{
	free(term);
}

poly_t*	new_poly_from_string(const char* str)
{
	poly_t* poly = malloc(sizeof(poly));
	list_t* list = NULL;
	char temp[100]; //can't take larger terms than 100 long

	int len = strlen(str);
	int i, term_start;
	term_start = 0;
	for (i = 0; i < len; i++) {
		//for the first term
		if (str[i] == ' ' || str[i] == '\0') {
			//reset the temp array.
			memset(temp, '\0', sizeof(temp));
			memcpy(temp, str+term_start, sizeof(char)*(i-term_start+1));
			insert_last(&list, new_term(temp));
			term_start = i + 1;
		}
		//the rest of the terms
		else if (str[i] == '+' || str[i] == '-') {
			i++; //pass the sign;
			i++; //pass the whitepsace;
			//reset the temp array.
			memset(temp, '\0', sizeof(temp));
			int temp_i;
			for (temp_i = 0; temp_i < 100; temp_i++) {
				temp[temp_i] = 0;
			}
			//find the end
			while (str[i] != ' ' && str[i] != '\0') {
				i++;
			}
			memcpy(temp, str+term_start, sizeof(char)*(i-term_start+1));
			insert_last(&list, new_term(temp));
			term_start = i + 1;
		}
	}
	poly->terms = list;
	return poly;
}

void free_poly(poly_t* poly)
{
	free_list(&poly->terms);
	free(poly);
}

poly_t* mul(poly_t* a, poly_t* b)
{
	git 
	return NULL;
}

void print_poly(poly_t* poly)
{
	printf("\n");
	list_t* p = poly->terms;
	if (p->term->coff == 1) {
		printf("x");
	} else {
		printf("%dx", p->term->coff);
	}
	if (p->term->exp != 1) {
		printf("^%d", p->term->exp);
	}

	p = p->succ;
	while (p != poly->terms) {
		printf(" ");
		if (p->term->coff < 0) {
				putchar('-');
			} else {
				putchar('+');
			}
			putchar(' ');
		if (p->term->exp != 0) {			
			if (p->term->coff == 1) {
				putchar('x');
			} else {
				printf("%dx", abs(p->term->coff));
			}
			if (p->term->exp != 1) {
				printf("^%d", p->term->exp);
			}
		} else {
			printf("%d", abs(p->term->coff));
		}

		p = p->succ;
	}
	printf("\n");
}