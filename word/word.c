#include <stdio.h>
#include <ctype.h>


int main(void)
{
	int ch;
	char* str;
	char* str_temp;
	int index, index_temp, max;
	index = 0;
	index_temp = 0;
	max 		= 10;
	str 		= calloc(max, sizeof(char));
	str_temp 	= calloc(max, sizeof(char));

	while ((ch = getchar()) != EOF) {
		while (isalpha(ch)) {
			if (index_temp > max) {
				max = max * 2;
				str_temp = realloc(str_temp, sizeof(char)*max);
			}
			str_temp[index_temp++] = ch;
			ch = getchar();
		}
		if (index_temp > index) {
			index = index_temp;
			free(str);
			str = str_temp;
			str_temp = calloc(max, sizeof(char));
		}
		index_temp = 0;
	}
	printf("%d characters in longest word: ", index);
	int i = 0;
	while (i < index) {
		printf("%c", str[i++]);
	}
	printf("\n");
	free(str);
	free(str_temp);
	
	return 0;
}