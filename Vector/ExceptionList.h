//
// Created by stanissslaf on 4/15/18.
//

#ifndef STACKTRACK_EXCEPTIONLIST_H
#define STACKTRACK_EXCEPTIONLIST_H

class ExpLst
{
public :

    const int errNum;
    const int line;

    const char *const message;
    const  char *const function;
    const char *const file;
    ExpLst *prev = nullptr;

    ExpLst(const int _err_num, const char *const _msg, const char *const _func, const int _Line,
           const char *const _File) noexcept :
            line(_Line),
            errNum(_err_num),
            message(_msg),
            function(_func),
            file(_File)
    {}

    bool SetPrev(ExpLst *_prev)
    {
        if (_prev) {
            this->prev = _prev;
            return true;
        }
        return false;
    }

    void dump()
    {
        std::cout << "Error: " << errNum << "  " << message << "  Function: "
                  << function << "  Line: " << line << "  File: " << file << std::endl;
    }

    void destructRec()
    {
        if (this && this->prev)
            (*(this->prev)).destructRec();
        delete this;

    }
};

#endif //STACKTRACK_EXCEPTIONLIST_H
