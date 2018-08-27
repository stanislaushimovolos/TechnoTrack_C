//
// Created by stanissslaf on 4/15/18.
//

#ifndef HASHTABLES_HASHTABLE_H
#define HASHTABLES_HASHTABLE_H

#include "../StackTrack/vector.hpp"
#include "List_t/List.h"
#include <fstream>
#include <cstring>

#define DEFAULT_SIZE 200
#define EXCEL_SEP ','

enum
{
    BAD_FILENAME,
    NO_HASH_FUNC
};

template<typename Data_T = const char *>

class Table
{

private:

    size_t _size;

    vector<List<Data_T>> Data;

    size_t (*_calcHash)(Data_T &);

public :

    explicit Table(size_t size = DEFAULT_SIZE);

    int print(const char *outputFileName);

    int
    Fill(Data_T *Arr, size_t ArrSz, size_t calcHash(Data_T &),
         int (*compare)(Data_T, Data_T) = nullptr);

    List<Data_T> &operator[](Data_T ref);

    size_t getSz();
};


template<typename T>
Table<T>::Table(size_t size) :
        Data(vector<List<T>>(size)),
        _size(size),
        _calcHash(nullptr)
{}


template<typename Data_T>
int Table<Data_T>::Fill(Data_T *Arr, size_t ArrSz, size_t calcHash(Data_T &),
                        int (*compare)(Data_T, Data_T))
{
    size_t l_hash = 0;
    _calcHash = calcHash;

    if (compare) {
        for (int i = 0; i < ArrSz; i++) {
            l_hash = (calcHash(Arr[i])) % _size;
            Data[l_hash].search_push_back(Arr[i], compare);
        }
    } else {
        for (int i = 0; i < ArrSz; i++) {
            l_hash = (calcHash(Arr[i])) % _size;
            Data[l_hash].search_push_back(Arr[i]);
        }
    }
    return 0;
}


template<>
int Table<const char *>::Fill(const char **Arr, size_t ArrSz, size_t calcHash(const char *&),
                              int (*compare)(const char *, const char *))
{
    size_t l_hash = 0;
    _calcHash = calcHash;

    for (int i = 0; i < ArrSz; i++) {
        l_hash = (calcHash(Arr[i])) % _size;
        Data[l_hash].search_push_back(Arr[i], compare);
    }

    return 0;
}



template<typename Data_T>
List<Data_T> &Table<Data_T>::operator[](Data_T ref)
{
    if (_calcHash != nullptr) {
        return Data[_calcHash(ref) % _size];
    } else throw (new ExpLst(NO_HASH_FUNC, "Hash-function wasn't define", __PRETTY_FUNCTION__, __LINE__, __FILE__));
}


template<typename T>
int Table<T>::print(const char *outputFileName)
{
    if (!outputFileName)
        throw (new ExpLst(BAD_FILENAME, "Invalid output filename", __PRETTY_FUNCTION__, __LINE__, __FILE__));

    std::ofstream out;
    out.open(outputFileName);

    for (int i = 0; i < _size; i++)
        out << Data[i].getSize() << EXCEL_SEP;

    out.close();
    return 1;

}

template<typename T>
size_t Table<T>::getSz()
{
    return _size;
}

#endif //HASHTABLES_HASHTABLE_H
