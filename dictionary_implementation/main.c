#define _CRT_SECURE_NO_WARNINGS
#include "dictionary.h"
#include <ctype.h>

int readWord(FILE* fp, char* buffer)
{
	int c;
	
	do
	{
		c = fgetc(fp);

		if (c == EOF)
			return 0;

	} while (!isalpha(c));

	do
	{
		*buffer = tolower(c);
		buffer++;

		c = fgetc(fp);

		if (c == 146)
			c = '\'';
		
	} while (isalpha(c) || c == '\'');
	*buffer = '\0';

	return 1;
}

int main()
{
	FILE* fd;
	char buffer[1024];
	Dictionary dict;

	fd = fopen("liar.txt", "rt");
	if (fd == NULL)
	{
		printf("Error opening file.\n");
		return;
	}

	dict = create();

	while (readWord(fd, buffer))
	{
		//printf("%s\n", buffer);
		add(dict, buffer);
	}
	fclose(fd);

	print(dict);

	for(int i = 0; i < 20;i++)
		printf("\n");

	char str[] = "Pozdrav";
	Dictionary newDict = addStringSecondLast(dict, str);

	print(newDict);
	
	for (int i = 0; i < 10; i++)
		printf("\n");

	printf("%s", returnSecondLastWord(newDict));

	destroy(dict);

	return 0;
}