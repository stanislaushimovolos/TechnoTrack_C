#include <stdio.h>
#include <cstring>
#include <cstdlib>

void swapCharPointers (char **a, char **b);

void alphabetSorter (char **text, const int numOfStrings);

size_t stringsCounter (const char *buffer, size_t sizeOfBuffer);

void textCreator (char **text, char *buffer, const int sizeOfBuffer);

void writeSorted (char **text, size_t numOfStrings, int userChoice);

const int writeDisplay = 1;
const int writeFile = 2;


int main () {
	int userChoice = 0;

	FILE *file = fopen ("poem.txt", "r");

	if (file == NULL) {
		printf ("FILE ERROR");
		return 0;
	}
	fseek (file, 0, SEEK_END);

	size_t sizeOfBuffer = (size_t) ftell (file);
	char *buffer = (char *) calloc (sizeOfBuffer, sizeof (char));

	fseek (file, 0, SEEK_SET);
	fread (buffer, 1, sizeOfBuffer, file);
	fclose (file);

	size_t numOfStrings = stringsCounter (buffer, sizeOfBuffer);
	char **text = (char **) calloc (numOfStrings, sizeof (char *));

	textCreator (text, buffer, sizeOfBuffer);
	alphabetSorter (text, numOfStrings);

	printf ("Poem_Sorter \nDisplay(%d) or write to the file(%d)? ", writeDisplay, writeFile);
	scanf ("%d", &userChoice);

	writeSorted (text, numOfStrings, userChoice);

	free (text);
	free (buffer);
	return 0;
}


void swapCharPointers (char **a, char **b) {
	char *c = *a;
	*a = *b;
	*b = c;
}


void alphabetSorter (char **text, const int numOfStrings) {
	for (int i = 0; i < numOfStrings - 1; i++)
		for (int j = 0; j < numOfStrings - i - 1; j++)
			if (strcasecmp (text[j], text[j + 1]) > 0)
				swapCharPointers (&text[j], &text[j + 1]);
}


size_t stringsCounter (const char *buffer, size_t sizeOfBuffer) {
	size_t numberOfStrings = 1;
	for (int i = 0; i < sizeOfBuffer; i++)
		if (buffer[i] == '\n')
			numberOfStrings++;
	return numberOfStrings;
}


void textCreator (char **text, char *buffer, const int sizeOfBuffer) {
	text[0] = buffer;
	for (int i = 0, j = 1; i < sizeOfBuffer; i++)
		if (buffer[i] == '\n' || buffer[i] == '\r') {
			if (buffer[i] == '\n')
				text[j++] = buffer + i + 1;
			buffer[i] = '\0';
		}
}

void writeSorted (char **text, size_t numOfStrings, int userChoice) {
	switch (userChoice) {
		case 1:
			for (int i = 0; i < numOfStrings; i++)
				if (text[i][0] != 0)
					printf ("%s\n", text[i]);
			break;

		case 2: {
			FILE *file2 = fopen ("sorted_poem.txt", "w");
			for (int i = 0; i < numOfStrings; i++)
				if (text[i][0] != 0)
					fprintf (file2, "%s\n", text[i]);
			fclose (file2);
			break;
		}

		default:
			break;
	}
}
