#include <cstdio>
#include <iostream>
#include <cstring>

#include "shakspeare.h"

int compareStrAlphabet (const void *s1, const void *s2);

int compareStrRhyme (const void *s1, const void *s2);

void sortByAlphabet (string_t arrayOfPtrString[], size_t numOfStrings);

void sortByRhyme (string_t arrayOfPtrString[], size_t numOfStrings);

void writeSorted (const int userChoice, string_t arrayOfPtrString[], size_t numOfStrings);

void writeSortedFile (string_t *arrayOfPtrString, size_t numOfStrings);

void writeSortedDisplay (string_t arrayOfPtrString[], size_t numOfStrings);

void sortLines (const int userChoice, string_t arrayOfPtrString[], size_t numOfStrings);

const int writeDisplay = 1;
const int writeFile = 2;
const int sortAlphabet = 1;
const int sortRhyme = 2;

const char inputFilename[] = "poem.txt";
const char outputFilename[] = "sorted_poem.txt";


int main () {
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
	string_t *arrayOfString_t = (string_t *) calloc (numOfStrings, sizeof (string_t));
	createArrayOfString_t (arrayOfString_t, buffer, sizeOfBuffer);

	// Sort lines

	sortByRhyme (arrayOfString_t, numOfStrings);

	// Print or write sorted lines

	int userChoiceDsplOrFile = 0;
	int userChoiceAlphOrRhyme = 0;

	printf ("Poem_Sorter \nSort by Alpabet(%d) or by rhyme(%d)?\n", sortAlphabet, sortRhyme);

	std::cin >> userChoiceAlphOrRhyme;

	if (!std::cin) {
		printf ("Wrong input");
		return 0;
	}

	sortLines (userChoiceAlphOrRhyme, arrayOfString_t, numOfStrings);

	printf ("Display(%d) or write to the file(%d) ?\n", writeDisplay, writeFile);

	std::cin >> userChoiceDsplOrFile;

	if (!std::cin) {
		printf ("Wrong input");
		return 0;
	}

	writeSorted (userChoiceDsplOrFile, arrayOfString_t, numOfStrings);

	// Finish

	free (arrayOfString_t);
	free (buffer);
	return 0;
}

int compareStrRhyme (const void *s1, const void *s2) {
	string_t leftStr = (*(string_t *) s1);
	string_t rightStr = (*(string_t *) s2);
	int counter = 0;

	while (ispunct (leftStr.str[leftStr.length]) || isspace (leftStr.str[leftStr.length])) leftStr.length--;
	while (ispunct (rightStr.str[rightStr.length]) || isspace (rightStr.str[rightStr.length])) rightStr.length--;
	while (rightStr.str[rightStr.length - counter] == leftStr.str[leftStr.length - counter]) counter++;

	return -rightStr.str[rightStr.length - counter] + leftStr.str[leftStr.length - counter];
}


int compareStrAlphabet (const void *s1, const void *s2) {
	char *leftStr = (*(string_t *) s1).str;
	char *rightStr = (*(string_t *) s2).str;

	while (ispunct (*leftStr) || isspace (*leftStr)) leftStr++;
	while (ispunct (*rightStr) || isspace (*rightStr)) rightStr++;

	return strcasecmp (leftStr, rightStr);
}

void sortByAlphabet (string_t arrayOfPtrString[], size_t numOfStrings) {
	qsort (arrayOfPtrString, numOfStrings, sizeof (*arrayOfPtrString), compareStrAlphabet);
}

void sortByRhyme (string_t arrayOfPtrString[], size_t numOfStrings) {
	qsort (arrayOfPtrString, numOfStrings, sizeof (*arrayOfPtrString), compareStrRhyme);
}

void sortLines (const int userChoice, string_t arrayOfPtrString[], size_t numOfStrings) {
	switch (userChoice) {
		case 1:
			sortByAlphabet (arrayOfPtrString, numOfStrings);
			break;
		case 2:
			sortByRhyme (arrayOfPtrString, numOfStrings);
			break;
		default:
			break;
	}
}

void writeSortedFile (string_t *arrayOfPtrString, size_t numOfStrings) {
	FILE *file2 = fopen (outputFilename, "w");
	for (int i = 0; i < numOfStrings; i++)
		if ((int) (arrayOfPtrString[i].str)[0] != 0)
			fprintf (file2, "%s\n", arrayOfPtrString[i].str);
	fclose (file2);
}

void writeSortedDisplay (string_t arrayOfPtrString[], size_t numOfStrings) {
	for (int i = 0; i < numOfStrings; i++)
		if ((int) (arrayOfPtrString[i]).str[0] != 0)
			printf ("%s\n", arrayOfPtrString[i].str);
}

void writeSorted (const int userChoice, string_t arrayOfPtrString[], size_t numOfStrings) {
	switch (userChoice) {
		case 1:
			writeSortedDisplay (arrayOfPtrString, numOfStrings);
			break;
		case 2:
			writeSortedFile (arrayOfPtrString, numOfStrings);
			break;
		default:
			break;
	}
}
