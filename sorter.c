#include "sorter.h"


int throw_error(int err_num, const char *msg, const char *_func, int _Line,
                const char *_File)
{
    printf("%s\nError № %d: %s\n"
           "In function: %s\n"
           "Line %d\n"
           "File: %s\n\n", msg, err_num, errList[err_num], _func, _Line, _File);

    return err_num;
}


int swapStr_t(string_t *s1, string_t *s2)
{
    assert(s1);
    assert(s2);

    if (!s1 || !s2)
        return throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    const string_t temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}


int getBuf(text_t *data, const char *inputFile)
{
    assert(data);
    assert (inputFile);

    if (!data || !inputFile)
        return throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    size_t l_buf_sz = 0;
    FILE *file = fopen(inputFile, "r");
    assert (file);

    if (file)
    {
        fseek(file, 0, SEEK_END);
        l_buf_sz = (size_t) ftell(file);
        fseek(file, 0, SEEK_SET);

        data->buffer = (char *) calloc(l_buf_sz + 1, sizeof(char));
        assert(data->buffer);

        if (!data->buffer)
            return throw_error(MEMORY, "Can't allocate memory for the buffer",
                               __PRETTY_FUNCTION__, __LINE__, __FILE__);

        data->size = l_buf_sz;

        fread(data->buffer, 1, l_buf_sz, file);
        fclose(file);
    }
    else
        return throw_error(OPENFILE, "Can't open source file.",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);
    return 0;
}


size_t countTokens(const char *buffer, char sep)
{
    assert (buffer);

    if (!buffer)
        return (size_t) throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                                    __PRETTY_FUNCTION__, __LINE__, __FILE__);

    size_t tokensAmount = 0;
    const char *nl = NULL;

    for (nl = strchr(buffer, sep); nl != NULL; nl = strchr(nl + 1, sep))
        tokensAmount++;
    if (nl < buffer + strlen(buffer))
        tokensAmount++;
    return tokensAmount;
}


int makeTokens(text_t *data, char *separator)
{
    assert (data);
    assert (data->buffer);

    if (!data || !data->buffer)
        return throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    size_t _tokensNum = countTokens(data->buffer, separator[0]);
    string_t *tokensArr = (string_t *) calloc(_tokensNum + 1, sizeof(string_t));
    assert(tokensArr);

    if (!tokensArr)
        return throw_error(MEMORY, "Can't allocate memory for the tokens",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    data->tokens = tokensArr;
    size_t tokAmount = 0;

    char *curToken = strtok(data->buffer, separator);
    char *curTokenOld = 0;

    while (curToken != NULL)
    {
        curTokenOld = curToken;
        tokensArr[tokAmount].str = curToken;
        curToken = strtok(NULL, separator);
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

    if (!s1 || !s2)
        return throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

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

    if (!s1 || !s2)
        return throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    char *leftStr = (*(string_t *) s1).str;
    char *rightStr = (*(string_t *) s2).str;

    while (ispunct(*leftStr) || isspace(*leftStr))
        leftStr++;
    while (ispunct(*rightStr) || isspace(*rightStr))
        rightStr++;

    return strcasecmp(leftStr, rightStr);
}


int swapTokens(text_t *data)
{
    assert(data);
    assert(data->tokens);

    if (!data || !data->tokens)
        return throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    size_t _tokensAmount = data->tokensAmount;
    string_t *_tokens = data->tokens;

    for (int i = 0; i < _tokensAmount / 2; i += 2)
        swapStr_t(&_tokens[i], &_tokens[i + _tokensAmount / 2]);

    return 0;

}


int sort(text_t *text, int ( *comparator )(const void *, const void *))
{
    assert (text);
    assert(comparator);

    if (!text || !comparator)
        return throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    qsort(text->tokens, text->tokensAmount, sizeof(string_t), comparator);
    return 0;
}


int printText(text_t *data, const char *outputFile)
{
    assert (data);
    assert(data->tokens);

    if (!data || !data->tokens)
        return throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    string_t *arrOfStr = data->tokens;
    FILE *output = fopen(outputFile, "w");

    for (int i = 0; i < data->tokensAmount; i++)
        fprintf(output, "%s\n", arrOfStr[i].str);
    fclose(output);

    return 0;
}

int showText(text_t *data)
{
    assert (data);
    assert(data->tokens);

    if (!data || !data->tokens)
        return throw_error(ARGUMENTS, "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    string_t *arrOfStr = data->tokens;

    for (int i = 0; i < data->tokensAmount; i++)
        printf("%s\n", arrOfStr[i].str);

    return 0;
}


void destructText(text_t *data)
{
    if (data)
    {
        if (data->buffer)
            free(data->buffer);
        if (data->tokens)
            free(data->tokens);

        data->buffer = NULL;
        data->tokens = NULL;
    }
}
