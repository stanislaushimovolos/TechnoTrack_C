#include <iostream>
#include "vector.hpp"
#include <cstring>
#include "ExceptionList.h"


ExpLst *MegaTest(int n);

int main()
{
    ExpLst *b = MegaTest(3);

    b->destructRec();
    
    return 0;
}

ExpLst *MegaTest(int n)
{
    if (n == 0)
        throw (new ExpLst(n, "BAD", __PRETTY_FUNCTION__, __LINE__, __FILE__));

    try {
        MegaTest(n - 1);

    }
    catch (ExpLst *_prevExp) {
        auto *a = new ExpLst(n, "BAD", __PRETTY_FUNCTION__, __LINE__, __FILE__);
        a->SetPrev(_prevExp);
        if (n != 3)
            throw a;
        return a;
    }
}
