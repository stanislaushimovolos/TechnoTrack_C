//
// Created by stanissslaf on 4/15/18.
//

#include "WorkWithFiles.h"
#include <cstring>
#include <assert.h>

char *getBufFromFile(const char *inputFilename)
{

    assert (inputFilename);

    size_t sizeOfBuffer1 = 0;
    FILE *file = fopen(inputFilename, "r");

    assert (file);

    fseek(file, 0, SEEK_END);
    sizeOfBuffer1 = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    auto helpBuffer = (char *) calloc(sizeOfBuffer1 + 1, sizeof(char));
    fread(helpBuffer, 1, sizeOfBuffer1, file);
    fclose(file);

    return helpBuffer;
}

size_t SeparateText(char *buffer)
{
    assert(buffer);
    size_t wordCounter = 0;
    while (*buffer != 0) {

        while (*buffer == ' ')
            buffer++;

        while (*buffer != ' ' && *buffer != 0)
            buffer++;

        wordCounter++;
        *buffer = 0;
        buffer++;
    }
    return wordCounter;
}

char **createArrOfWords(char *buffer, size_t *size)
{
    assert(buffer);
    size_t numOfStrings = SeparateText(buffer);
    auto Arr = (char **) calloc(sizeof(char *), numOfStrings + 1);

    for (int i = 0; i < numOfStrings; i++) {
        while (*buffer == ' ')
            buffer++;
        Arr[i] = buffer;
        buffer += 1 + strlen(buffer);
    }

    *size = numOfStrings;
    return Arr;
}
