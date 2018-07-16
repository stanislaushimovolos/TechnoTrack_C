#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


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

} Data;


int destructText(Data *data);

int cmpAlphabet(const void *s1, const void *s2);

int cmpRhyme(const void *s1, const void *s2);

int makeTokens(Data *data);

int getBuf(Data *data, const char *inputFilename);

size_t countTokens(const char *buffer);

int printText(Data *data, const char *outputFile);

int sort(Data *data, int ( *comparator )(const void *, const void *));


