//
// Created by stanissslaf on 4/15/18.
//

#ifndef HASHTABLES_HASHFUNCTIONS_H
#define HASHTABLES_HASHFUNCTIONS_H

#include <cstring>

size_t AsciiCodeHash(const char *&word);

size_t StrLengthHash(const char *&word);

size_t AsciiAndLenHsh(const char *&word);

size_t AsciiSumHash(const char *&word);

size_t RolHash(const char *&word);

size_t GnuHash(const char *&word);

#endif //HASHTABLES_HASHFUNCTIONS_H
