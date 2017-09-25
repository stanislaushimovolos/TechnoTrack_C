#include "shakspeare.h"

size_t countStrings (const char *buffer, size_t sizeOfBuffer) {
	size_t numberOfStrings = 1;
	for (int i = 0; i < sizeOfBuffer; i++)
		if (buffer[i] == '\n')
			numberOfStrings++;
	return numberOfStrings;
}

void createArrayOfString_t (string_t *arrayOfPtrString, char *buffer, const int sizeOfBuffer) {
	arrayOfPtrString[0].str = buffer;
	int i_old = 0, nStr = 1;
	for (int i = 0; i < sizeOfBuffer; i++)
		if (buffer[i] == '\n') {
			arrayOfPtrString[nStr].str = buffer + i + 1;
			arrayOfPtrString[nStr++ - 1].length = i - i_old;
			i_old = i + 1;
			buffer[i] = '\0';
		}
	arrayOfPtrString[nStr - 1].length = sizeOfBuffer - i_old;
}
