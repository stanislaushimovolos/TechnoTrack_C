#pragma once

#include <cstdio>

typedef struct
{
	int length;
	char* str;
} string_t;

void swapMyStrings (string_t *a, string_t *b);

size_t countStrings (const char *buffer, size_t sizeOfBuffer);

void createArrayOfString_t (string_t *arrayOfPtrString, char *buffer, const int sizeOfBuffer);
