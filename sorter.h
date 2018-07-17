#pragma once

#define NDEBUG

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

static const char *const errList[] = {"",
                                      "Invalid arguments in function",
                                      "Certain problems related to opening files",
                                      "System couldn't allocate memory"
};


enum errors
{
    ARGUMENTS = 1,
    OPENFILE,
    MEMORY,
    OUT_OF_RANGE

};



int throw_error(int err_num, const char *msg, const char *_func, int _Line,
                const char *_File);

typedef struct
{
    char *str;
    size_t length;
} string_t;


typedef struct
{
    char *buffer;
    size_t size;
    size_t tokensAmount;
    string_t *tokens;

} text_t;


int swapStr_t(string_t *, string_t *);

int cmpAlphabet(const void *s1, const void *s2);

int cmpRhyme(const void *s1, const void *s2);

int makeTokens(text_t *data, char *separator);

int getBuf(text_t *data, const char *inputFilename);

int printText(text_t *data, const char *outputFile);

int showText(text_t *data);

int sort(text_t *data, int ( *comparator )(const void *, const void *));

int swapTokens(text_t *data);

void destructText(text_t *data);

size_t countTokens(const char *buffer, char sep);


