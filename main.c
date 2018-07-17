#include "sorter.h"

const char defaultOutput[] = "output.txt";
const char defaultInput[] = "poem.txt";

#define execute(_func_)         \
    state = _func_;             \
    if (state)                  \
    {                           \
        destructText(&data);    \
        return state;           \
    }


int main(int argc, char *argv[])
{
    text_t data = {};
    int state = 0;

    execute(getBuf(&data, defaultInput));
    execute(makeTokens(&data, "\n"));

    execute(sort(&data, cmpRhyme));
    execute(swapTokens(&data));
    execute(printText(&data, defaultOutput));

    //execute(showText(&data));
    destructText(&data);

    return EXIT_SUCCESS;
}