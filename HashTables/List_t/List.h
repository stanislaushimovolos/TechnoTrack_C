//
// Created by stanissslaf on 4/15/18.
//

#ifndef HASHTABLES_LIST_H
#define HASHTABLES_LIST_H

#include <iostream>
#include "../../StackTrack/ExceptionList.h"
#include <cstring>

template<typename Data_T>
class List;

template<typename Data_T>
struct Node
{
    Data_T value;
    Node<Data_T> *Next, *Prev;
    List<Data_T> *Master;
};

template<typename Data_T>
class List
{

private :
    size_t _size;
    Node<Data_T> *Head, *Tail;

public :

    List();

    bool push_back(const Data_T &value);

    bool push_front(const Data_T &value);

    int search(const Data_T &elem, int compare(const Data_T &first, const Data_T &second));

    int search(const Data_T &elem, int compare(Data_T first, Data_T second));

    int search_push_back(const Data_T &elem, int compare(const Data_T &first, const Data_T &second));

    int search_push_back(Data_T elem, int compare(Data_T first, Data_T second) = nullptr);

    int insert_before(const Data_T &value, Node<Data_T> *destination);

    int insert_after(const Data_T &value, Node<Data_T> *destination);

    void print();

    Data_T &front();

    Data_T &back();

    Data_T &operator[](int pos);

    size_t getSize();

    Node<Data_T> *getTail();

    ~List();
};


template<typename Data_T>
List<Data_T>::List() :
        Head(new Node<Data_T>),
        Tail(Head),
        _size(0)
{
    Head->Master = this;
}


template<typename Data_T>
bool List<Data_T>::push_back(const Data_T &value)
{
    Tail->value = value;
    Tail->Next = new Node<Data_T>;
    Tail->Next->Next = nullptr;
    Tail->Next->Prev = Tail;
    Tail = Tail->Next;
    _size++;
    Tail->Master = this;
}


template<typename Data_T>
bool List<Data_T>::push_front(const Data_T &value)
{
    Head->Prev = new Node<Data_T>;
    Head->Prev->Prev = 0;
    Head->Prev->Next = Head;
    Head = Head->Prev;
    Head->value = value;
    _size++;
    Head->Master = this;
}


template<typename Data_T>
Data_T &List<Data_T>::front()
{
    return Head->value;
}


template<typename Data_T>
Data_T &List<Data_T>::back()
{
    return Tail->value;
}


template<typename Data_T>
size_t List<Data_T>::getSize()
{
    return _size;
}

template<typename Data_T>
Node<Data_T> *List<Data_T>::getTail()
{
    return Tail;
}

template<typename Data_T>
void List<Data_T>::print()
{
    Node<Data_T> *CurNode = Head;
    for (int i = 0; i < _size; i++) {
        std::cout << CurNode->value << std::endl;
        CurNode = CurNode->Next;
    }

}

template<typename Data_T>
inline int List<Data_T>::search(const Data_T &elem, int compare(const Data_T &first, const Data_T &second))
{
    Node<Data_T> *CurNode = Head;
    while (CurNode != nullptr) {
        if (compare(CurNode->value, elem))
            return 1;
        CurNode = CurNode->Next;
    }
    return 0;
}


template<typename Data_T>
inline int List<Data_T>::search(const Data_T &elem, int compare(Data_T first, Data_T second))
{
    Node<Data_T> *CurNode = Head;
    if (compare) {
        while (CurNode != nullptr) {
            if (compare(CurNode->value, elem))
                return 1;
            CurNode = CurNode->Next;
        }
    } else {
        while (CurNode != nullptr) {
            if (CurNode->value == elem)
                return 1;
            CurNode = CurNode->Next;

        }
        return 0;
    }
}


template<typename Data_T>
int List<Data_T>::search_push_back(const Data_T &elem, int compare(const Data_T &first, const Data_T &second))
{
    if (compare) {
        Node<Data_T> *CurNode = Head;
        if (_size != 0) {
            while (CurNode->Next != nullptr) {
                if (compare(CurNode->value, elem) == 0)
                    return 1;
                CurNode = CurNode->Next;
            }
        }
        push_back(elem);

    } else {
        Node<Data_T> *CurNode = Head;
        if (_size != 0) {
            while (CurNode->Next != nullptr) {
                if (CurNode->value == elem)
                    return 1;
                CurNode = CurNode->Next;
            }
        }
        push_back(elem);

    }
    return 0;
}


template<typename Data_T>
int List<Data_T>::search_push_back(Data_T elem, int compare(Data_T first, Data_T second))
{
    Node<Data_T> *CurNode = Head;
    if (compare) {
        if (_size != 0) {
            while (CurNode->Next != nullptr) {
                if (compare(CurNode->value, elem) == 0)
                    return 1;
                CurNode = CurNode->Next;
            }
        }
        push_back(elem);

    } else {
        if (_size != 0) {
            while (CurNode->Next != nullptr) {
                if (CurNode->value == elem)
                    return 1;
                CurNode = CurNode->Next;
            }
        }
        push_back(elem);

    }
    return 0;
}


template<>
int
List<const char *>::search_push_back(const char *elem, int compare(const char *first, const char *second))
{
    Node<const char *> *CurNode = Head;
    char res = 0;
    while (CurNode->Next) {
        __asm__ (
        "L1:;"
        "lodsb;"
        "test %%al, %%al;"
        "jz EQU;"
        "xorb (%%rdi), %%al ;"
        "jnz EXIT;"
        "inc %%rdi;"
        "jmp L1;"

        "EQU:;"
        "xorb (%%rdi), %%al;"
        "EXIT:;"

        :"=r"(res)
        :
        "S" (CurNode->value), "D" (elem)
        );

        if (res == 0)
            return 1;
        CurNode = CurNode->Next;

    }
    push_back(elem);

    return 0;
}


template<typename Data_T>
Data_T &List<Data_T>::operator[](int pos)
{
    if (pos >= _size || pos < 0)
        throw (new ExpLst(0, "Out of range", __PRETTY_FUNCTION__, __LINE__, __FILE__));

    Node<Data_T> *CurNode = Head;
    int counter = 0;
    while (++counter <= pos) {
        CurNode = CurNode->Next;
    }
    return CurNode->value;
}

template<typename Data_T>
int List<Data_T>::insert_before(const Data_T &value, Node<Data_T> *destination)
{
    if (destination->Master != this)
        return 0;

    auto *NewCell = new Node<Data_T>;

    NewCell->Master = this;
    destination->Prev->Next = NewCell;

    NewCell->Next = destination;
    NewCell->Prev = destination->Prev;
    NewCell->value = value;

    destination->Prev = NewCell;
    _size++;

    return 1;
}

template<typename Data_T>
int List<Data_T>::insert_after(const Data_T &value, Node<Data_T> *destination)
{
    if (destination->Master != this)
        return 0;

    auto *NewCell = new Node<Data_T>;

    NewCell->Master = this;
    destination->Next->Prev = NewCell;

    NewCell->Next = destination->Next;
    NewCell->Prev = destination;
    NewCell->value = value;

    destination->Next = NewCell;
    _size++;
}


template<typename Data_T>
List<Data_T>::~List()
{
    while (Head) {
        Tail = Head->Next;
        delete Head;
        Head = Tail;
    }

    //std::cout << "Hey" << std::endl;
}

#endif //HASHTABLES_LIST_H
