//
// Created by stanissslaf on 4/15/18.
//

#ifndef HASHTABLES_WORKWITHFILES_H
#define HASHTABLES_WORKWITHFILES_H


#include <iostream>

size_t SeparateText(const char *buffer);

char **createArrOfWords(char *buffer, size_t *size);

char *getBufFromFile(const char *inputFilename);

#endif //HASHTABLES_WORKWITHFILES_H
