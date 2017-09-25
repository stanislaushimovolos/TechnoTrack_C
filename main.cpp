#include <cstdio>
#include <iostream>
#include <cstring>

#include "shakspeare.h"

int compareStrAlphabet (const void *s1, const void *s2);

int compareStrRhyme (const void *s1, const void *s2);

void sortByAlphabet (string_t arrayOfString_t[], const size_t numOfStrings);

void sortFromEnd (string_t arrayOfString_t[], const size_t numOfStrings);

void writeSorted (int userChoice, string_t arrayOfString_t[], const size_t numOfStrings);

void writeSortedFile (string_t arrayOfString_t[], const size_t numOfStrings);

void writeSortedDisplay (string_t arrayOfString_t[], const size_t numOfStrings);

void sortLines (int userChoice, string_t arrayOfString_t[], const size_t numOfStrings);

const char inputFilename[] = "poem.txt";
const char outputFilename[] = "sorted_poem.txt";


int main() {

	// Load file
	FILE *file = fopen (inputFilename, "r");

	if (file == NULL) {
		printf("FILE ERROR");
		return 0;
	}

	// Get buffer size

	fseek (file, 0, SEEK_END);
	size_t sizeOfBuffer = (size_t) ftell(file);
	fseek (file, 0, SEEK_SET);

	// Create buffer and load file

	char *buffer = (char *) calloc(sizeOfBuffer + 1, sizeof(char));
	if (buffer == NULL) {
		printf("Memory error");
		return 0;
	}

	fread (buffer, 1, sizeOfBuffer, file);
	fclose( file);

	// Count lines and create array structures

	size_t numOfStrings = countStrings (buffer, sizeOfBuffer);
	string_t *arrayOfString_t = (string_t *) calloc(numOfStrings, sizeof(string_t));
	createArrayOfString_t (arrayOfString_t, buffer, sizeOfBuffer);

	int userChoiceDsplOrFile = 0;
	int userChoiceAlphOrRhyme = 0;

	printf ("Poem_Sorter\nSort by Alpabet(%d) or by rhyme(%d)?\n", sortAlphabet, sortRhyme);

	// User choice : sort by rhyme or by alphabet

	std::cin >> userChoiceAlphOrRhyme;

	if (!std::cin || (userChoiceAlphOrRhyme != sortAlphabet & userChoiceAlphOrRhyme != sortRhyme)) {
		printf("Wrong input");
		return 0;
	}

	// Line sorting

	sortLines (userChoiceAlphOrRhyme, arrayOfString_t, numOfStrings);

	printf ("Display(%d) or write to the file(%d) ?\n", writeDisplay, writeFile);

	// User choice : display or write to the file

	std::cin >> userChoiceDsplOrFile;

	if (!std::cin || (userChoiceDsplOrFile != writeFile & userChoiceDsplOrFile != writeDisplay)) {
		printf("Wrong input");
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

	#define lLength leftStr.length
	#define rLength rightStr.length
	#define lStr leftStr.str
	#define rStr rightStr.str

	while (ispunct (lStr[lLength]) || isspace (lStr[lLength]))
		rLength--;

	while (ispunct (rStr[rLength]) || isspace (rStr[rLength]))
		rLength--;

	while (rStr[rLength - counter] == lStr[lLength - counter])
		counter++;

	return lStr[lLength - counter] - rStr[rLength - counter];

	#undef rStr
	#undef lStr
	#undef lLength
	#undef rLength

}


int compareStrAlphabet (const void *s1, const void *s2) {
	char *leftStr = (*(string_t *) s1).str;
	char *rightStr = (*(string_t *) s2).str;

	while (ispunct (*leftStr) || isspace (*leftStr))
		leftStr++;
	while (ispunct (*rightStr) || isspace (*rightStr))
		rightStr++;

	return strcasecmp (leftStr, rightStr);
}

void sortByAlphabet (string_t arrayOfString_t[], const size_t numOfStrings) {
	qsort (arrayOfString_t, numOfStrings, sizeof (*arrayOfString_t), compareStrAlphabet);
}

void sortFromEnd (string_t arrayOfString_t[], const size_t numOfStrings) {
	qsort (arrayOfString_t, numOfStrings, sizeof (*arrayOfString_t), compareStrRhyme);
}

void sortLines (const int userChoice, string_t arrayOfString_t[], const size_t numOfStrings) {
	switch (userChoice) {
		case 1:
			sortByAlphabet (arrayOfString_t, numOfStrings);
			break;
		case 2:
			sortFromEnd(arrayOfString_t, numOfStrings);
			break;
		default:
			break;
	}
}

void writeSortedFile (string_t arrayOfString_t[], const size_t numOfStrings) {
	FILE *file2 = fopen (outputFilename, "w");
	for (int i = 0; i < numOfStrings; i++)
		if ((int) (arrayOfString_t[i].str)[0] != 0)
			fprintf (file2, "%s\n", arrayOfString_t[i].str);
	fclose (file2);
}

void writeSortedDisplay (string_t arrayOfString_t[], const size_t numOfStrings) {
	for (int i = 0; i < numOfStrings; i++)
		if ((int) (arrayOfString_t[i]).str[0] != 0)
			printf ("%s\n", arrayOfString_t[i].str);
}

void writeSorted (const int userChoice, string_t arrayOfString_t[], const size_t numOfStrings) {
	switch (userChoice) {
		case 1:
			writeSortedDisplay (arrayOfString_t, numOfStrings);
			break;
		case 2:
			writeSortedFile (arrayOfString_t, numOfStrings);
			break;
		default:
			break;
	}
}


