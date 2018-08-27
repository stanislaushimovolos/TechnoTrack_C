//
// Created by stanissslaf on 4/15/18.
//

#include "HashFunctions.h"

size_t AsciiCodeHash(const char *&word)
{
    return (size_t) (*word - 'a');
}

size_t StrLengthHash(const char *&word)
{
    return (size_t) strlen(word);
}

size_t AsciiAndLenHsh(const char *&word)
{
    auto len = strlen(word);
    size_t sum = 0;

    if (len != 0) {
        for (int i = 0; i < len; i++)
            sum = sum + word[i];

        return sum / len;

    } else return 0;

}

size_t AsciiSumHash(const char *&word)
{
    auto len = strlen(word);
    size_t sum = 0;

    for (int i = 0; i < len; i++)
        sum = sum + word[i];

    return sum;
}

size_t GnuHash(const char *&word)
{
    auto len = strlen(word);
    size_t hash = 0;

    for (int i = 0; i < len; i++)
        hash += (hash << 5) + word[i];

    return hash;
}

size_t RolHash(const char *&word)
{
    auto len = strlen(word);
    size_t hash = 0;

    for (int i = 0; i < len; i++) {
        hash = ((hash << 1) | (hash >> 63)) xor word[i];
    }
    return hash;
}

