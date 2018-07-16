#include "sorter.h"

int getBuf(Data *data, const char *inputFile)
{
    assert(data);
    assert (inputFile);

    size_t l_buf_sz = 0;
    FILE *file = fopen(inputFile, "r");
    assert (file);

    fseek(file, 0, SEEK_END);
    l_buf_sz = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    data->buffer = (char *) calloc(l_buf_sz + 1, sizeof(char));
    assert(data->buffer);

    data->size = l_buf_sz;

    fread(data->buffer, 1, l_buf_sz, file);
    fclose(file);

    return 0;
}


size_t countTokens(const char *buffer)
{
    assert (buffer);

    size_t tokensAmount = 0;
    const char *nl = NULL;

    for (nl = strchr(buffer, '\n'); nl != NULL; nl = strchr(nl + 1, '\n'))
        tokensAmount++;
    if (nl < buffer + strlen(buffer))
        tokensAmount++;
    return tokensAmount;
}


int makeTokens(Data *data)
{
    assert (data);
    assert (data->buffer);

    size_t _tokensNum = countTokens(data->buffer);
    string_t *tokensArr = (string_t *) calloc(_tokensNum + 1, sizeof(string_t));
    assert(tokensArr);

    data->tokens = tokensArr;
    size_t tokAmount = 0;

    char *curToken = strtok(data->buffer, "\n");
    char *curTokenOld = 0;

    while (curToken != NULL)
    {
        curTokenOld = curToken;
        tokensArr[tokAmount].str = curToken;
        curToken = strtok(NULL, "\n");
        tokensArr[tokAmount].length = curToken - curTokenOld - 1;
        tokAmount++;
    }

    tokensArr[tokAmount - 1].length = strlen(curTokenOld);
    data->tokensAmount = tokAmount;
    return 0;
}


#define FirstLength   firstStr.length
#define SecondLength  secondStr.length
#define FirstStr      firstStr.str
#define SecondStr     secondStr.str


int cmpRhyme(const void *s1, const void *s2)
{
    assert (s1);
    assert (s2);

    string_t firstStr = (*(string_t *) s1);
    string_t secondStr = (*(string_t *) s2);
    int counter = 0;

    while (ispunct (FirstStr[FirstLength]) || isspace (FirstStr[FirstLength]))
        FirstLength--;

    while (ispunct (SecondStr[SecondLength]) || isspace (SecondStr[SecondLength]))
        SecondLength--;

    while (SecondStr[SecondLength - counter] == FirstStr[FirstLength - counter])
        counter++;

    return FirstStr[FirstLength - counter] - SecondStr[SecondLength - counter];
}


#undef SecondStr
#undef FirstStr
#undef FirstLength
#undef SecondLength


int cmpAlphabet(const void *s1, const void *s2)
{
    assert (s1);
    assert (s2);

    char *leftStr = (*(string_t *) s1).str;
    char *rightStr = (*(string_t *) s2).str;

    while (ispunct(*leftStr) || isspace(*leftStr))
        leftStr++;
    while (ispunct(*rightStr) || isspace(*rightStr))
        rightStr++;

    return strcasecmp(leftStr, rightStr);
}


int sort(Data *text, int ( *comparator )(const void *, const void *))
{
    assert (text);
    assert(comparator);
    qsort(text->tokens, text->tokensAmount, sizeof(string_t), comparator);

    return 0;
}


int printText(Data *data, const char *outputFile)
{
    assert (data);
    string_t *arrOfStr = data->tokens;
    FILE *output = fopen(outputFile, "w");

    for (int i = 0; i < data->tokensAmount; i++)
        fprintf(output, "%s\n", arrOfStr[i].str);
    fclose(output);

    return 0;
}

int destructText(Data *data)
{
    free(data->buffer);
    free(data->tokens);

    data->buffer = NULL;
    data->tokens = NULL;
}
