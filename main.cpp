#include <stdio.h>
#include <cstring>
#include <cstdlib>

struct myString;

void swapMyStrings (myString *a, myString *b);

size_t countStrings (const char *buffer, size_t sizeOfBuffer);

void createLinesPointers (myString arrayOfPtrmyString[], char *buffer, const int sizeOfBuffer);

void sortByAlphabet (myString arrayOfPtrmyString[], const int numOfStrings);

void writeSorted (myString arrayOfPtrmyString[], size_t numOfStrings, int userChoice);

struct myString
{
	int length;
	char* str;
};


const int writeDisplay = 1;
const int writeFile = 2;

int main ()
{
// Load file
	FILE *file = fopen ("poem.txt", "r");

	if (file == NULL) {
		printf ("FILE ERROR");
		return 0;
	}

	// Get buffer size

	fseek (file, 0, SEEK_END);
	size_t sizeOfBuffer = (size_t) ftell (file);
	fseek (file, 0, SEEK_SET);

	// Create buffer and load file

	char *buffer = (char *) calloc (sizeOfBuffer, sizeof (char));
	fread (buffer, 1, sizeOfBuffer, file);
	fclose (file);

	// Count lines and create array structures

	size_t numOfStrings = countStrings (buffer, sizeOfBuffer);
	myString *arrayOfPtrmyString = (myString *)calloc (numOfStrings, sizeof (myString));
	createLinesPointers (arrayOfPtrmyString, buffer, sizeOfBuffer);

	// Sort lines

	sortByAlphabet (arrayOfPtrmyString, numOfStrings);


	// Print or write sorted lines

	int userChoice = 0;
	printf ("Poem_Sorter \nDisplay(%d) or write to the file(%d)? ", writeDisplay, writeFile);
	scanf ("%d", &userChoice);
	writeSorted (arrayOfPtrmyString, numOfStrings, userChoice);

	// Finish

	free (arrayOfPtrmyString);
	free (buffer);
	return 0;
}


void swapMyStrings (myString *a, myString *b){
	myString c = *a;
	*a = *b;
	*b = c;

}

size_t countStrings (const char *buffer, size_t sizeOfBuffer) {
	size_t numberOfStrings = 1;
	for (int i = 0; i < sizeOfBuffer; i++)
		if (buffer[i] == '\n')
			numberOfStrings++;
	return numberOfStrings;
}

void createLinesPointers ( myString arrayOfPtrmyString[], char *buffer, const int sizeOfBuffer) {
	int counter = 0;
	(arrayOfPtrmyString[0]).str = buffer;
	for (int i = 0, j = 1; i < sizeOfBuffer; i++)
		if (buffer[i] == '\n' || buffer[i] == '\r') {
			if (buffer[i] == '\n')
			{
				(arrayOfPtrmyString[j]).str = buffer + i + 1;
				(arrayOfPtrmyString[j - 1]).length = i - counter - 1;
				counter = i;
				j++;
				buffer[i] = '\0';
			}
			buffer[i] = '\0';
		}
}

void sortByAlphabet (myString arrayOfPtrmyString[], const int numOfStrings) {
	for (int i = 0; i < numOfStrings - 1; i++)
		for (int j = 0; j < numOfStrings - i - 1; j++)
			if (strcasecmp ((arrayOfPtrmyString[j]).str, (arrayOfPtrmyString[j + 1]).str) > 0)
				swapMyStrings (&arrayOfPtrmyString[j], &arrayOfPtrmyString[j + 1]);
}

void writeSorted (myString arrayOfPtrmyString[], size_t numOfStrings, int userChoice) {
	switch (userChoice) {
		case writeDisplay:
			for (int i = 0; i < numOfStrings; i++)
				if ((int)((arrayOfPtrmyString[i]).str)[0] != 0)
					printf ("%s\n", (arrayOfPtrmyString[i]).str);
			break;

		case writeFile: {
			FILE *file2 = fopen ("sorted_poem.txt", "w");
			for (int i = 0; i < numOfStrings; i++)
				if ((int)((arrayOfPtrmyString[i]).str)[0] != 0)
					fprintf (file2, "%s\n", (arrayOfPtrmyString[i]).str);
			fclose (file2);
			break;
		}

		default:
			break;
	}
}