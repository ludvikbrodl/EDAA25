#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "error.h"
#include "poly.h"

typedef struct list_t list_t;
typedef struct term_t term_t;

struct poly_t {
	list_t* terms;
};

struct term_t {
	int* coff;
	int* exp;
};

struct list_t {
	list_t* succ;
	list_t* pred;
	term_t*	term;
};



list_t* new_list(term_t term)
{
	return NULL;
}

void free_list(list_t** list)
{

}

void insert_last(list_t** list, term_t term)
{

}



term_t* new_term(int coff, int exp)
{
	return NULL;
}

void free_term(term_t** term)
{

}

poly_t*	new_poly_from_string(const char* ch)
{
	return NULL;
}

void free_poly(poly_t* poly)
{

}

poly_t* mul(poly_t* a, poly_t* b)
{
	return NULL;
}

void print_poly(poly_t* poly)
{

}