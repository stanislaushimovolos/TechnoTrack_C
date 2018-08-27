//
// Created by Tom on 13.11.2017.
//


const int maxContentLength = 75;

const char positiveAnswer = 'y';
const char negativeAnswer = 'n';

const char GuessObject = 'g';
const char ExitWithoutSav = 'e';
const char ExitSav = 's';
const char DescribeObj = 'd';
const char CompareObj = 'c';

const char inputFilename[] = "base/base.txt";
const char outFilename[] = "dumps/base.txt";
const char outFilenameForDotDump[] = "picture/dotDump.txt";
const char outFilenameForDotPrint[] = "picture/dotPrint.txt";

void guessObject (const Tree *const tree);

void userWorking (const Tree *const tree);

void addNewObject (Node *negativeUserChoiceCatcher);

bool compareObjects (const Tree *const tree);

