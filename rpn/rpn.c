#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define N		(10)

bool trailing_digit = false;
int digits[8];
int number_digits = 0;
int stack[N];
int i = 0;
int ch;
int line = 1;

bool handle_trail();
void skip_to_next_line();

int main(void)
{
	while ((ch = getchar()) != EOF) {
		if (ch == '\n') {
			if (handle_trail()) {
				if (i != 1) { //check for empty stack/several ints on newline
				printf("line %d: error at \\n\n", line);
				}
				else {
					printf("line %d: %d\n", line, stack[0]);
				}
				i = 0;
				line++;
			} else {
				//do nothing
			}


		} else if (isdigit(ch)) {
			if (i > 9) {
				printf("line %d: error at %c\n", line, ch);
				skip_to_next_line();
				line++;
				i = 0;
			} else {
				digits[number_digits++] = ch - '0';
				trailing_digit = true;
			}
		} else if (ch == ' ') {
			handle_trail();
		} else { //operator
			handle_trail();
			if (i < 2) { //not enough ints to perform operator
				printf("line %d: error at %c\n", line, ch);
				skip_to_next_line();
				i = 0;
				line++;
			} else if (ch == '+') {
				int a = stack[--i];
				int b = stack[--i];
				stack[i++] = a + b;
			} else if (ch == '-') {
				int a = stack[--i];
				int b = stack[--i];
				stack[i++] = b - a;
			} else if (ch == '*') {
				int a = stack[--i];
				int b = stack[--i];
				stack[i++] = a * b;
			} else if (ch == '/') {
				int a = stack[--i];
				if (a == 0) { //div by 0
					printf("line %d: error at /\n", line);
					skip_to_next_line();
					i = 0;
					line++;
				} else {
					int b = stack[--i];
					stack[i++] = b / a;
				}
			} else { //invalid char
				printf("line %d: error at %c\n", line, ch);
				skip_to_next_line();
				i = 0;
				line++;
			}
		}
	}
	return 0;
}

bool handle_trail() {
	if (trailing_digit) {

		int itr;
		int number = 0;
		for (itr = 0; itr < number_digits; itr++) {
			number = (number * 10) + (digits[itr]);
		}
		if (i > 9) {
			printf("line %d: error at %d\n", line, number);
			i = 0;
			line++;
			return false;
		} else {
			stack[i++] = number;
			number_digits = 0;
			trailing_digit = false;
		}
	}
	return true;
}

void skip_to_next_line() {
	while ((ch = getchar()) != EOF) {
		if (ch == '\n') {
			return;
		}
	}
}
