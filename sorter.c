
/*!
 * @file sorter.c
 * @brief Implementation of sorter.h functions.
 * @author Stanislau Shimovolos
 * @version 1.4
 * @date 2018-7-17
 */


#include "sorter.h"

/*!
    @def throw(num, msg1, msg2)
 *  Returns a value of @ref throw_error (uses for generation of code)
 */

#define throw(num)                                                                  \
     return throw_error_hard(num,                                                   \
        __PRETTY_FUNCTION__, __LINE__, __FILE__);                                   \


/*!
 * \def execute(_func_)
 * Uses for error checking.
 */


#define execute(_func_)         \
do                              \
{                               \
    state = _func_;             \
    if (state)                  \
    {                           \
        destructText(data);     \
        return state;           \
    }                           \
}while(0)


int executeProgram(text_t *data, int argc, char **argv)
{
    assert(data);

    int state = 0;

    execute(parseCommandLine(data, argc, argv));
    execute(getBuf(data));
    execute(makeTokens(data, "\n"));

    if (!data->alphabetSort)
    {
        sort(data, cmpAlphabetReverse);
        swapTokens(data);
    }
    else
        sort(data, cmpAlphabet);

    if (data->displayData)
        displayText(data);

    execute(printText(data));
    return 0;
}

#undef execute


int parseCommandLine(text_t *data, int argc, char **argv)
{
    assert(data);

    int opt = 0;
    while ((opt = getopt(argc, argv, commandLineParams)) != -1)
    {
        switch (opt)
        {
            case 'i':
            {
                data->inputFile = optarg;
                break;
            }
            case 'o':
            {
                data->outputFile = optarg;
                break;
            }
            case 'd':
            {
                data->displayData = 1;
                break;
            }
            case 'a':
            {
                data->alphabetSort = 1;
                break;
            }
            case '?':
            case ':':
            default:
                return COMMAND_LINE_ERR;
        }
    }
    return 0;
}


int swapStr_t(string_t *s1, string_t *s2)
{
    assert(s1);
    assert(s2);

    if (!s1 || !s2)
        throw(ARGUMENTS_ERR);

    const string_t temp = *s1;
    *s1 = *s2;
    *s2 = temp;

    return 0;
}


int getBuf(text_t *data)
{
    assert(data);
    assert(data->inputFile);

    size_t l_buf_sz = 0;
    FILE *file = fopen(data->inputFile, "r");
    assert (file);

    if (file)
    {
        fseek(file, 0, SEEK_END);
        l_buf_sz = (size_t) ftell(file);
        fseek(file, 0, SEEK_SET);

        data->buffer = (char *) calloc(l_buf_sz + 1, sizeof(char));
        assert(data->buffer);

        if (!data->buffer)
            throw(MEMORY_ERR);

        data->size = l_buf_sz;
        fread(data->buffer, 1, l_buf_sz, file);
        fclose(file);
    }
    else
    {
        printf("Can't open \"%s\"\n", data->inputFile);
        return OPENFILE_ERR;
    }
    return 0;
}


size_t countTokens(const char *buffer, char sep)
{
    assert (buffer);

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
    assert(separator);

    size_t _tokensNum = countTokens(data->buffer, separator[0]);
    string_t *tokensArr = (string_t *) calloc(_tokensNum + 1, sizeof(string_t));

    if (!tokensArr)
        throw(MEMORY_ERR);

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


int cmpAlphabetReverse(const void *str1, const void *str2)
{
    assert (str1);
    assert (str2);

    string_t firstStr = (*(string_t *) str1);
    string_t secondStr = (*(string_t *) str2);
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


int swapTokens(text_t *data)
{
    assert(data);
    assert(data->tokens);

    size_t _tokensAmount = data->tokensAmount;
    string_t *_tokens = data->tokens;

    for (int i = 0; i < _tokensAmount / 2; i += 2)
        swapStr_t(&_tokens[i], &_tokens[i + _tokensAmount / 2]);

    return 0;
}


int sort(text_t *text, int ( *comparator )(const void *, const void *))
{
    assert(text);
    assert(comparator);

    qsort(text->tokens, text->tokensAmount, sizeof(string_t), comparator);
    return 0;
}


int printText(text_t *data)
{
    assert(data);
    assert(data->outputFile);
    assert(data->tokens);

    string_t *arrOfStr = data->tokens;
    FILE *output = fopen(data->outputFile, "w");

    if (!output)
    {
        printf("Can't open \"%s\"\n", data->outputFile);
        return OPENFILE_ERR;
    }

    for (int i = 0; i < data->tokensAmount; i++)
        fprintf(output, "%s\n", arrOfStr[i].str);
    fclose(output);
    return 0;
}


int displayText(text_t *data)
{
    assert (data);
    assert(data->tokens);

    string_t *arrOfStr = data->tokens;

    for (int i = 0; i < data->tokensAmount; i++)
        printf("%s\n", arrOfStr[i].str);

    return 0;
}


int constructText(text_t *data, const char *input, const char *output)
{
    assert(data);
    data->size = 0;
    data->buffer = NULL;
    data->tokens = NULL;
    data->tokensAmount = 0;
    data->inputFile = input;
    data->outputFile = output;

    return 0;
}


void destructText(text_t *data)
{
    if (data)
    {
        free(data->buffer);
        free(data->tokens);

        data->buffer = NULL;
        data->tokens = NULL;
    }
}


int throw_error_hard(unsigned int err_num, const char *_func, int _line,
                     const char *_file)
{
    if ((err_num < OUT_OF_ERR_RANGE_ERR) && _func && _file)
    {
        fprintf(stderr, "Error № %d: %s\n"
                        "In function: %s\n"
                        "Line %d\n"
                        "File: %s\n\n", err_num, errList[err_num], _func, _line, _file);

        return err_num;
    }
    else return OUT_OF_ERR_RANGE_ERR;
}

#undef throw
