#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define N		(10)

bool trailingDigit = false;
int digits[8];
int numberDigits = 0;
int stack[N];
int i = 0;
int ch;
int line = 1;

bool handleTrail();

int main(void)
{
	while ((ch = getchar()) != EOF) {
		if (ch == '\n') {
			if (handleTrail()) {
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
			digits[numberDigits++] = ch - '0';
			trailingDigit = true;
		} else if (ch == ' ') {
			handleTrail();
		} else { //operator
			handleTrail();
			if (i < 2) { //not enough ints to perform operator
				printf("line %d: error at %c\n", line, ch);
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
				if (a == 0) {
					printf("line %d: error at /\n", line);
					i = 0;
					line++;
				} else {
					int b = stack[--i];
					stack[i++] = b / a;	
				}
			}
		}
	}
	return 0;
}

bool handleTrail() {
	if (trailingDigit) {

		int itr;
		int number = 0;
		for (itr = 0; itr < numberDigits; itr++) {
			number = (number * 10) + (digits[itr]);
		}
		if (i > 9) {
			printf("line %d: error at %d\n", line, number);
			i = 0;
			line++;
			return false;
		} else {
			stack[i++] = number;
			numberDigits = 0;
			trailingDigit = false;	
		}
	}
	return true;
}
