#pragma once

#include <cstdio>

typedef struct
{
	int length;
	char* str;
} string_t;

size_t countStrings (const char *buffer, size_t sizeOfBuffer);

void createArrayOfString_t (string_t *arrayOfPtrString, char *buffer, const int sizeOfBuffer);

const int writeDisplay = 1;
const int writeFile = 2;
const int sortAlphabet = 1;
const int sortRhyme = 2;
