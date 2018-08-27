#include <iostream>
#include "HashTable.hpp"
#include "WorkWithFiles/WorkWithFiles.h"
#include "HashFunctions/HashFunctions.h"


const char inputFileName[] = "Test.txt";

int main()
{
    //clock_t t = clock();
    Table<> Roll(1000), Gnu(1000), FirstAscii(26),
            Length(15), AsciiDivLen(50), SumAscii(1000);


    size_t wordsAmount = 0;
    char *buffer = getBufFromFile(inputFileName);
    auto WordArr = (const char **) createArrOfWords(buffer, &wordsAmount);

    try {
        Roll.Fill(WordArr, wordsAmount, RolHash);
        Gnu.Fill(WordArr, wordsAmount, GnuHash);
        FirstAscii.Fill(WordArr, wordsAmount, AsciiCodeHash);
        Length.Fill(WordArr, wordsAmount, StrLengthHash);
        AsciiDivLen.Fill(WordArr, wordsAmount, AsciiAndLenHsh);
        SumAscii.Fill(WordArr, wordsAmount, AsciiSumHash);

        Roll.print("Charts/RollHash.csv");
        Gnu.print("Charts/GnuHash.csv");
        FirstAscii.print("Charts/Ascii.csv");
        Length.print("Charts/Length3.csv");
        AsciiDivLen.print("Charts/Ascii + Length 3.5.csv");
        SumAscii.print("Charts/AsciiSum.csv");
    }

    catch (ExpLst *e) {
        e->dump();
        e->destructRec();
        return 1;

    }

    free(buffer);
    free(WordArr);


    // t = clock() - t;
     /*std::ofstream out;
     out.open("Time ", std::ios::app);

     out << t << std::endl;
     out.close();


     std::ifstream input("Time ");
     int buf = 0, sum = 0;
     while (input >> buf) {
         sum += buf;
     }
     std::cout << sum / 1000;*/


    return 0;
}