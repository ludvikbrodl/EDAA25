#include <stdio.h>
#include "poly.h"

static void poly_test(const char* a, const char* b)
{
	poly_t*		p;
	poly_t*		q;
	poly_t*		r;

	printf("Begin polynomial test of (%s) * (%s)\n", a, b);

	p = new_poly_from_string(a);
	q = new_poly_from_string(b);

	print_poly(p);
	print_poly(q);

	r = mul(p, q);

	print_poly(r);

	free_poly(p);
	free_poly(q);
	free_poly(r);

	printf("End polynomial test of (%s) * (%s)\n", a, b);
}

int main(void)
{
	poly_test("x^2 - 7x + 1", "3x + 2");
	putchar('\n');
	poly_test("-x^10000000 + 2", "2x^2 + 3x + 4");
	putchar('\n');
	//poly_test("775x^108 - 757x^89 + 986x^11 + 9","242x^778 + 128x^716 - 299x^619 + 555x^603 - 764x^582 + 394x^541 + 169x^492 - 278x^425 - 616x^328 - 626x^299 - 756x^227 + 117x^167 - 465x^129 + 681x^68 + 653");
	//poly_test("507x^170 + 72x^162 + 663x^129 + 60x^128 + 795x^126 - 17x^106 - 26x^84 + 997x^11 - 219","346x^485 + 206x^429 - 630x^414 - 294x^315 - 706x^216 + 853x^116 - 871x^44 - 249");
	poly_test("-572x^216 - 936x^124 - 746x^25 - 739","-x^205 + 601x^114 + 324x^58 - 576x^43 + 376x^40 + 469");
	putchar('\n');
	poly_test("x + 2","-3x - 4");
	putchar('\n');
	poly_test("x^2 - 7x + 1","3x + 2");
	putchar('\n');
	poly_test("x^10000000 + 2","2x^2 + 3x + 4");
	putchar('\n');
	poly_test("-572x^216 - 936x^124 - 746x^25 - 739","-x^205 + 601x^114 + 324x^58 - 576x^43 + 376x^40 + 469");
	putchar('\n');
	return 0;
}
