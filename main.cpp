#include <iostream>
#include <cstring>

#include "shakspeare.h"

int compareStrAlphabet (const void *s1, const void *s2);

int compareStrRhyme (const void *s1, const void *s2);

void sortByAlphabet (const size_t numOfStrings, string_t arrayOfString_t[]);

void sortFromEnd (const size_t numOfStrings, string_t arrayOfString_t[]);

void writeSorted (const size_t numOfStrings, const int userChoice, string_t arrayOfString_t[]);

void writeSortedFile (const size_t numOfStrings, string_t arrayOfString_t[]);

void writeSortedDisplay (const size_t numOfStrings, string_t arrayOfString_t[]);

void sortLines (const size_t numOfStrings, const int userChoice, string_t arrayOfString_t[]);

const char inputFilename[] = "poem.txt";
const char outputFilename[] = "sorted_poem.txt";


int main () {

	// Open file and get buffer

	size_t sizeOfBuffer = 0;
	char *buffer = fileOpening (inputFilename, &sizeOfBuffer);

	// Count lines and create array structures

	size_t numOfStrings = countStrings (buffer);
	string_t *arrayOfString_t = (string_t *) calloc (numOfStrings, sizeof (string_t));
	createArrayOfString_t (sizeOfBuffer, buffer, arrayOfString_t);

	int userChoiceDsplOrFile = 0;
	int userChoiceAlphOrRhyme = 0;

	printf ("Poem_Sorter\n"
			        "Sort by Alpabet(%d) or by rhyme(%d)?\n", SortAlphabet, SortRhyme);

	// User choice : sort by rhyme or by alphabet

	std::cin >> userChoiceAlphOrRhyme;

	if (!std::cin || (userChoiceAlphOrRhyme != SortAlphabet && userChoiceAlphOrRhyme != SortRhyme)) {
		printf ("Wrong input");
		return 0;
	}

	// Line sorting

	sortLines (numOfStrings, userChoiceAlphOrRhyme, arrayOfString_t);

	printf ("Display(%d) or write to the file(%d) ?\n", WriteDisplay, WriteFile);

	// User choice : display or write to the file

	std::cin >> userChoiceDsplOrFile;

	if (!std::cin || (userChoiceDsplOrFile != WriteFile && userChoiceDsplOrFile != WriteDisplay)) {
		printf ("Wrong input");
		return 0;
	}

	writeSorted (numOfStrings, userChoiceDsplOrFile, arrayOfString_t);

	// Finish

	free (arrayOfString_t);
	free (buffer);
	return 0;
}


int compareStrRhyme (const void *s1, const void *s2) {
	assert (s1);
	assert (s2);

	string_t leftStr = (*(string_t *) s1);
	string_t rightStr = (*(string_t *) s2);
	int counter = 0;

#define LLength_  leftStr.length
#define RLength_  rightStr.length
#define LStr_     leftStr.str
#define RStr_     rightStr.str

	while (ispunct (LStr_[LLength_]) || isspace (LStr_[LLength_]))
		RLength_--;

	while (ispunct (RStr_[RLength_]) || isspace (RStr_[RLength_]))
		RLength_--;

	while (RStr_[RLength_ - counter] == LStr_[LLength_ - counter])
		counter++;

	return LStr_[LLength_ - counter] - RStr_[RLength_ - counter];

#undef RStr_
#undef LStr_
#undef LLength_
#undef RLength_

}


int compareStrAlphabet (const void *s1, const void *s2) {
	assert (s1);
	assert (s2);

	char *leftStr = (*(string_t *) s1).str;
	char *rightStr = (*(string_t *) s2).str;

	while (ispunct (*leftStr) || isspace (*leftStr))
		leftStr++;
	while (ispunct (*rightStr) || isspace (*rightStr))
		rightStr++;

	return strcasecmp (leftStr, rightStr);
}

void sortByAlphabet (const size_t numOfStrings, string_t arrayOfString_t[]) {
	assert (arrayOfString_t);

	qsort (arrayOfString_t, numOfStrings, sizeof (*arrayOfString_t), compareStrAlphabet);
}

void sortFromEnd (const size_t numOfStrings, string_t arrayOfString_t[]) {
	assert (numOfStrings);
	assert (arrayOfString_t);

	qsort (arrayOfString_t, numOfStrings, sizeof (*arrayOfString_t), compareStrRhyme);
}

void sortLines (const size_t numOfStrings, const int userChoice, string_t arrayOfString_t[]) {
	assert (arrayOfString_t);

	switch (userChoice) {
		case 1:
			sortByAlphabet (numOfStrings, arrayOfString_t);
			break;
		case 2:
			sortFromEnd (numOfStrings, arrayOfString_t);
			break;
		default:
			break;
	}
}

void writeSortedFile (const size_t numOfStrings, string_t arrayOfString_t[]) {
	assert (arrayOfString_t);

	FILE *file2 = fopen (outputFilename, "w");
	for (int i = 0; i < numOfStrings; i++)
		if ((int) (arrayOfString_t[i].str)[0] != 0)
			fprintf (file2, "%s\n", arrayOfString_t[i].str);
	fclose (file2);
}

void writeSortedDisplay (const size_t numOfStrings, string_t arrayOfString_t[]) {
	assert (arrayOfString_t);

	for (int i = 0; i < numOfStrings; i++)
		if ((int) (arrayOfString_t[i]).str[0] != 0)
			printf ("%s\n", arrayOfString_t[i].str);
}

void writeSorted (const size_t numOfStrings, const int userChoice, string_t arrayOfString_t[]) {
	assert (arrayOfString_t);

	switch (userChoice) {
		case 1:
			writeSortedDisplay (numOfStrings, arrayOfString_t);
			break;
		case 2:
			writeSortedFile (numOfStrings, arrayOfString_t);
			break;
		default:
			break;
	}
}