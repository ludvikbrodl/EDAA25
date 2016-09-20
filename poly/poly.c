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

term_t* new_term(const char* str)
{
	term_t* term = malloc(sizeof(term_t));
	//printf("\n%s\n", str);
	const char* temp = str;
	char coff_str[100];
	char exp_str[100];
	memset(coff_str, '\0', sizeof(coff_str));
	memset(exp_str, '\0', sizeof(exp_str));

	if (str[0] == '-') {
		term->coff = -1;
	} else {
		term->coff = 1;
	}
	char* x = strchr(str, 'x');
	if (x != NULL) {
		if (str[0] == 'x' && str[1] == ' ') {
			coff_str[0] = '1';
			coff_str[1] = '\0';
		} else if (str[1] == ' ') {
			temp++;
			memcpy(coff_str, temp, x-(&str[1]));
		} else if (x == str){
			coff_str[0] = '1';
			coff_str[1] = '\0';
		} else if (&str[1] == x && str[0] == '-') {
			coff_str[0] = '1';
			coff_str[1] = '\0';
		} else if (&str[1] != x && str[0] == '-') {
			term->coff = 1;
			memcpy(coff_str, temp, x-(&str[0]));
		} else {
			memcpy(coff_str, temp, x-(&str[0]));
		}
	} else {
		memcpy(coff_str, temp+2, strlen(temp)-2);
	}

	term->coff = term->coff * atoi(coff_str);
	//printf("digit %i \t string %s\n", term->coff, coff_str);
	char* e = strchr(str, '^');
	char* end = strchr(str, '\0');
	if (e != NULL) {
		memcpy(exp_str, e+1, end-e);
	} else if (x != NULL) {
		exp_str[0] = '1';
		exp_str[1] = '\0';
	} else {
		exp_str[0] = '0';
		exp_str[1] = '\0';
	}
	term->exp = atoi(exp_str);
	return term;

}

term_t* new_term2(int coff, int exp) {
	term_t* term = malloc(sizeof(term_t));
	term->coff = coff;
	term->exp = exp;
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

void insert(list_t** list, term_t* term)
{
	if (*list == NULL) {
		insert_last(list, term);
		return;
	}
	insert_last(list, term);


}

poly_t* mul(poly_t* a, poly_t* b)
{
	list_t* alist = a->terms;
	list_t* blist = b->terms;
	list_t* prod = NULL;
	poly_t* product = malloc(sizeof(poly_t));
	do {
		do {
			int coff = alist->term->coff * blist->term->coff;
			int exp = alist->term->exp + blist->term->exp;
			term_t* t = new_term2(coff, exp);
			insert(&prod, t);
			blist = blist->succ;
		} while (blist != b->terms);
		alist = alist->succ;
	} while (alist != a->terms);
	product->terms = prod;
	//check for collisions on exponents
	//pointer-fun!
	list_t* prod_list1 = prod;
	list_t* prod_list2 = prod;
	do {
		do {
			list_t* temp = prod_list2->succ;
			if (prod_list1 != prod_list2) {
				if (prod_list1->term->exp == prod_list2->term->exp) {
					prod_list1->term->coff += prod_list2->term->coff;
					prod_list2->pred->succ = prod_list2->succ;
					prod_list2->succ->pred = prod_list2->pred;
					prod_list2->succ = NULL;
					prod_list2->pred = prod_list2;
					free_list(&prod_list2);
				}
			}
			prod_list2 = temp;
		} while (prod_list2 != prod);
		prod_list1 = prod_list1->succ;
	} while (prod_list1 != prod);
	//sort list the brute force way, cba doing quick sort.
	//hurray
	list_t* p = prod;
	do {
		if (p->term->exp > p->succ->term->exp) {
			p = p->succ;
		} else {
			list_t* q = p->succ;
			p->pred->succ	= q;
			q->pred			= p->pred;
			p->succ			= q->succ;
			q->succ->pred	= p;
			q->succ			= p;
			p->pred			= q;
			p = prod;
		}
	} while (p != prod->pred);

	return product;
}

void print_poly(poly_t* poly)
{
	list_t* p = poly->terms;
	if (p->term->coff == 1) {
		printf("x");
	} else if (p->term->coff == -1) {
		printf("-x");
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