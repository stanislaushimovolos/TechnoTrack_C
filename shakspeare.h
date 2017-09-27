#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/*
 *  structure which keeps line and length of this line
 */

typedef struct {
	int length;   // Length of the line

	char *str;    // Pointer on the line

} string_t;

/*   counts the amount of lines in the $buffer
 *   returns  the amount of lines
 */

size_t countStrings (const char *buffer);


/*   creates the array of structures $arrayOfString_t
 *   the pointer on the array is $buffer
 */

void createArrayOfString_t (const int sizeOfBuffer, char *buffer, string_t *arrayOfString_t);

/*   getting the name of input file $inputFilename and writes the amount of symbols to $sizeOfBuffer
 *   returns  the pointer on the text in the file
 */

char *fileOpening (const char *inputFilename, size_t *sizeOfBuffer);

const int WriteDisplay = 1;
const int WriteFile = 2;
const int SortAlphabet = 1;
const int SortRhyme = 2;
