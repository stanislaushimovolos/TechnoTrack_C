#include "sorter.h"

const char inputFilename[] = "poem.txt";
const char outputFilename[] = "sorted_poem.txt";

int main(int argc, char *argv[])
{

    Data data = {};
    getBuf(&data, inputFilename);
    makeTokens(&data);
    sort(&data, cmpRhyme);
    printText(&data, outputFilename);

    destructText(&data);
    return 0;
}