
/*!
 * \brief Implementation of sorter.h functions.
 * \author Stanislau Shimovolos
 * \version 1.4
 * \date 2018-7-17
 */



#include "sorter.h"


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
    if (!data)
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr)",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    int displayFlag = 0;
    int alphabetSortFlag = 0;
    int state = 0;

    argc--;
    int arg_counter = 1;

    if (argc && argv[arg_counter][0] != '-')
    {
        execute(getBuf(data, argv[arg_counter]));
        arg_counter++;
        argc--;
    }
    else
        execute(getBuf(data, defaultInput));

    execute(makeTokens(data, "\n"));

    while (argc && argv[arg_counter][0] == '-')
    {
        switch (argv[arg_counter][1])
        {
            case 'D':
            {
                displayFlag = 1;
                break;
            }

            case 'A':
            {
                alphabetSortFlag = 1;
                break;
            }

            default:
            {
                printf("\nFlags name: %s\n", argv[arg_counter]);
                return throw_error(UNKNOWN_FLAG_ERR, "Name of the flag is unknown.", argv[arg_counter],
                                   __PRETTY_FUNCTION__, __LINE__, __FILE__);
            }
        }

        argc--;
        arg_counter++;
    }


    if (alphabetSortFlag)
        execute(sort(data, cmpAlphabet));
    else
    {
        execute(sort(data, cmpAlphabetReverse));
        execute(swapTokens(data));
    }

    if (displayFlag)
        execute(displayText(data));

    if (argc)
        execute(printText(data, argv[arg_counter]));
    else
        execute(printText(data, defaultOutput));

    return EXIT_SUCCESS;
}

#undef execute


int throw_error(unsigned int err_num, const char *usr_msg, const char *err_msg, const char *_func, int _line,
                const char *_file)
{

    if (usr_msg[0])
        printf("%s\n", usr_msg);

    if (err_num < OUT_OF_ERR_RANGE_ERR)
    {

        fprintf(stderr, "%s\nError № %d: %s\n"
                        "In function: %s\n"
                        "Line %d\n"
                        "File: %s\n\n", err_msg, err_num, errList[err_num], _func, _line, _file);

        return err_num;
    }
    else return OUT_OF_ERR_RANGE_ERR;

}


int swapStr_t(string_t *s1, string_t *s2)
{
    assert(s1);
    assert(s2);

    if (!s1 || !s2)
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr).",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    const string_t temp = *s1;
    *s1 = *s2;
    *s2 = temp;

    return 0;
}


int getBuf(text_t *data, const char *inputFile)
{
    assert(data);
    assert (inputFile);

    if (!data || !inputFile)
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr).",
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
            return throw_error(MEMORY_ERR, "System couldn't allocate memory for the data.",
                               "Buffer error.",
                               __PRETTY_FUNCTION__, __LINE__, __FILE__);

        data->size = l_buf_sz;

        fread(data->buffer, 1, l_buf_sz, file);
        fclose(file);
    }
    else
    {
        printf("Source file name is %s\n", inputFile);
        return throw_error(OPENFILE_ERR, "Can't open source file.",
                           "Input file error.",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);
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

    if (!data || !data->buffer)
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr).",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    size_t _tokensNum = countTokens(data->buffer, separator[0]);
    string_t *tokensArr = (string_t *) calloc(_tokensNum + 1, sizeof(string_t));
    assert(tokensArr);

    if (!tokensArr)
        return throw_error(MEMORY_ERR, "System couldn't allocate memory for the data.",
                           "Tokens error.",
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


int cmpAlphabetReverse(const void *s1, const void *s2)
{
    assert (s1);
    assert (s2);

    if (!s1 || !s2)
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr).",
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
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr).",
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
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr).",
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
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr).",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    qsort(text->tokens, text->tokensAmount, sizeof(string_t), comparator);
    return 0;
}


int printText(text_t *data, const char *outputFile)
{
    assert (data);
    assert(data->tokens);

    if (!data || !data->tokens)
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr).",
                           __PRETTY_FUNCTION__, __LINE__, __FILE__);

    string_t *arrOfStr = data->tokens;
    FILE *output = fopen(outputFile, "w");

    for (int i = 0; i < data->tokensAmount; i++)
        fprintf(output, "%s\n", arrOfStr[i].str);
    fclose(output);

    return 0;
}


int displayText(text_t *data)
{
    assert (data);
    assert(data->tokens);

    if (!data || !data->tokens)
        return throw_error(ARGUMENTS_ERR, "", "Unexpected values of arguments (nullptr).",
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
