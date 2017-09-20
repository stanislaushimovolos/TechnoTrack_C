#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "shakspeare.h"

void sortByAlphabet (string_t arrayOfPtrString[], const int numOfStrings);

void writeSorted (string_t arrayOfPtrString[], size_t numOfStrings, int userChoice);


const int writeDisplay = 1;
const int writeFile = 2;
const char inputFilename[] = "test.txt";
const char outputFilename[] = "sorted_poem.txt";


int main ()
{
	// Load file
	FILE *file = fopen (inputFilename, "r");

	if (file == NULL) {
		printf ("FILE ERROR");
		return 0;
	}

	// Get buffer size

	fseek (file, 0, SEEK_END);
	size_t sizeOfBuffer = (size_t) ftell (file);
	fseek (file, 0, SEEK_SET);

	// Create buffer and load file

	char *buffer = (char *) calloc (sizeOfBuffer + 1, sizeof (char));
	fread (buffer, 1, sizeOfBuffer, file);
	fclose (file);

	// Count lines and create array structures

	size_t numOfStrings = countStrings (buffer, sizeOfBuffer);
	string_t *arrayOfPtrString = (string_t *) calloc (numOfStrings, sizeof (string_t));
	createLinesPointers (arrayOfPtrString, buffer, sizeOfBuffer);

	// Sort lines

	sortByAlphabet (arrayOfPtrString, numOfStrings);

	// Print or write sorted lines

	int userChoice = 0;
	printf ("Poem_Sorter \nDisplay(%d) or write to the file(%d)?\n", writeDisplay, writeFile);
	if(!(std::cin >> userChoice)) {
		std::cout << "Wrong input";
		return 0;
	}
	writeSorted (arrayOfPtrString, numOfStrings, userChoice);

	// Finish

	free (arrayOfPtrString);
	free (buffer);
	return 0;
}


void sortByAlphabet (string_t arrayOfPtrString[], const int numOfStrings) {
	for (int i = 0; i < numOfStrings - 1; i++)
		for (int j = 0; j < numOfStrings - i - 1; j++)
			if (strcasecmp (arrayOfPtrString[j].str, arrayOfPtrString[j + 1].str) > 0)
				swapMyStrings (&arrayOfPtrString[j], &arrayOfPtrString[j + 1]);
}


void writeSorted (string_t arrayOfPtrString[], size_t numOfStrings, int userChoice) {
	switch (userChoice) {
		case writeDisplay:
			for (int i = 0; i < numOfStrings; i++)
				if ((int)(arrayOfPtrString[i]).str[0] != 0)
					printf ("%s\n", arrayOfPtrString[i].str);
			break;

		case writeFile: {
			FILE *file2 = fopen (outputFilename, "w");
			for (int i = 0; i < numOfStrings; i++)
				if ((int)(arrayOfPtrString[i].str)[0] != 0)
					fprintf (file2, "%s %d\n", arrayOfPtrString[i].str, arrayOfPtrString[i].length);
			fclose (file2);
			break;
		}

		default:
			break;
	}
}
