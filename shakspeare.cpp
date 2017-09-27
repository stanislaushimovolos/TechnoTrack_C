#include "shakspeare.h"
#include <cstring>


/*  getting the name of input file $inputFilename and writes the amount of symbols to $sizeOfBuffer
 *  returns  the pointer on the text in the file
 */

char *getBufferFromFileGetSzOfBuf (const char *inputFilename, size_t *sizeOfBuffer) {

	assert (inputFilename);
	assert (sizeOfBuffer);

	size_t sizeOfBuffer1 = 0;
	FILE *file = fopen (inputFilename, "r");

	assert (file);

	fseek (file, 0, SEEK_END);
	sizeOfBuffer1 = (size_t) ftell (file);
	fseek (file, 0, SEEK_SET);

	char *helpBuffer = (char *) calloc (sizeOfBuffer1 + 1, sizeof (char));
	fread (helpBuffer, 1, sizeOfBuffer1, file);
	fclose (file);

	if (sizeOfBuffer != NULL)
		*sizeOfBuffer = sizeOfBuffer1;

	return helpBuffer;

}

/*  counts the amount of lines in the $buffer
 *  returns  the amount of lines
 */

size_t countStrings (const char *buffer) {
	assert (buffer);

	size_t lines = 0;
	const char *nl = NULL;
	for (nl = strchr (buffer, '\n'); nl != NULL; nl = strchr (nl + 1, '\n'))
		lines++;
	if (nl < buffer + strlen (buffer))
		lines++;
	return lines;
}


/*   creates the array of structures $arrayOfString_t
 *   return the pointer on the array of buffers and assigns amount of strings to &numofstrings
 */

string_t *createArrayOfString_t (const int sizeOfBuffer, char *buffer, size_t *numOfstrings) {
	assert (sizeOfBuffer);
	assert (buffer);

	size_t localeNumOfStrings = countStrings (buffer);

	string_t *arrayOfString_t1 = (string_t *) calloc (localeNumOfStrings, sizeof (string_t));

	arrayOfString_t1[0].str = buffer;
	int i_old = 0, nStr = 1;
	for (int i = 0; i < sizeOfBuffer; i++)
		if (buffer[i] == '\n') {
			arrayOfString_t1[nStr].str = buffer + i + 1;
			arrayOfString_t1[nStr++ - 1].length = i - i_old;
			i_old = i + 1;
			buffer[i] = '\0';
		}
	arrayOfString_t1[nStr - 1].length = sizeOfBuffer - i_old;

	if (numOfstrings != NULL) {
		*numOfstrings = localeNumOfStrings;
	}

	return arrayOfString_t1;
}