#include "shakspeare.h"
#include <cstring>

/*   creates the array of structures $arrayOfString_t
 *   the pointer on the array is $buffer
 */

void createArrayOfString_t (const int sizeOfBuffer, char *buffer, string_t *arrayOfString_t) {
	assert (sizeOfBuffer);
	assert (buffer);
	assert (arrayOfString_t);

	arrayOfString_t[0].str = buffer;
	int i_old = 0, nStr = 1;
	for (int i = 0; i < sizeOfBuffer; i++)
		if (buffer[i] == '\n') {
			arrayOfString_t[nStr].str = buffer + i + 1;
			arrayOfString_t[nStr++ - 1].length = i - i_old;
			i_old = i + 1;
			buffer[i] = '\0';
		}
	arrayOfString_t[nStr - 1].length = sizeOfBuffer - i_old;
}

/*   counts the amount of lines in the $buffer
 *   returns  the amount of lines
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


/*   getting the name of input file $inputFilename and writes the amount of symbols to $sizeOfBuffer
 *   returns  the pointer on the text in the file
 */

char *fileOpening (const char *inputFilename, size_t *sizeOfBuffer) {

		assert (inputFilename);
		assert (sizeOfBuffer);

		FILE *file = fopen (inputFilename, "r");

		assert (file);

		fseek (file, 0, SEEK_END);
		*sizeOfBuffer = (size_t) ftell (file);
		fseek (file, 0, SEEK_SET);


		char *helpBuffer = (char *) calloc (*sizeOfBuffer + 1, sizeof (char));
		fread (helpBuffer, 1, *sizeOfBuffer, file);
	fclose (file);

	return helpBuffer;

}