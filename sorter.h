#pragma once

/*!
 * @file sorter.h
 * @brief Contains function's headers and some constants.
 * @author Stanislau Shimovolos
 * @version 1.4
 * @date 2018-7-17
 */

/*!
  @def NDEBUG
  Release version so asserts were turned off.
*/

#define NDEBUG

#include <assert.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


static const char *const errList[] = {"",
                                      "Invalid arguments in function.",
                                      "Certain problems related to opening file.",
                                      "System couldn't allocate memory.",
                                      "Error, unknown flag."
};

static const char const defaultOutput[] = "output.txt";
static const char const defaultInput[] = "Text.txt";

/*
 * -i input file
 * -o output file
 * -d show print data (stdout)
 * -a sort alphabetically
 */
static const char const commandLineParams[] = "i:o:ad";


/**
* The list of possible errors
*/

enum error_codes
{
    ARGUMENTS_ERR = 1,      //!<Function's argument or some of them are equal NULL.
    OPENFILE_ERR,           //!<Some problem was detected in process of opening file.
    MEMORY_ERR,             //!<System couldn't allocate memory.
    COMMAND_LINE_ERR,       //!<Some error in command line arguments.
    OUT_OF_ERR_RANGE_ERR

};

/*!
     @brief The structure which contains char* string and its length.
 */


typedef struct
{
    char *str;              //!< pointer to the char string
    size_t length;          //!< length of this string str
} string_t;


/*!
     @brief The structure which contains
      all information about the input data.

      It contains the original text data, size of this data,
      an array of tokens and  number of them.
 */

typedef struct
{
    char *buffer;               //!< buffer with input data
    size_t size;                //!< size of the buffer in bytes
    string_t *tokens;           //!< array of tokens to which source data was splitted
    size_t tokensAmount;        //!< the number of tokens
    const char *inputFile;      //!< name of the input file
    const char *outputFile;     //!< name of the output file

    int displayData;            //!< if (displayData == 1) => print data (stdout)
    int alphabetSort;           //!< if (alphabetSort == 1) => sort alphabetically
} text_t;

/*!
    @brief Reads information from the command line and executes program.
    @param[in] data  text_t object.
    @param[in] argc, argv Parameters of the command line.
    @return Returns an error code.
*/
int executeProgram(text_t *data, int argc, char **argv);


/*!
    @brief Creates a "poem" from sorted in rhyme tokens.
    @param[in] data  text_t object.
    @param[in] separator The literal tokens separator (char).
    @return Returns an error code.
*/
int swapTokens(text_t *data);

/*!
    @brief Splits the data into tokens.
    @param[in] data  text_t object.
    @param[in] separator The literal tokens separator (char).
    @return Returns an error code.
*/
int makeTokens(text_t *data, char *separator);


/*!
    @brief Writes tokens in the text file.
    @param[in] data  data text_t object.
    @return Returns an error code.
*/
int printText(text_t *data);


/*!
    @brief Writes tokens in the standard output.
    @param[in] data  data text_t object.
    @return Returns an error code.
*/
int displayText(text_t *data);


/*!
    @brief Exchanges values of two string_t objects.
    @param[in] a,b string_t strings to be exchanged.
    @return Returns an error code.
*/
int swapStr_t(string_t *a, string_t *b);


/*!
    @brief Throws an error code and prints information about the error(standard output + standard error output).
    @param[in] err_num An error code.
    @param[in] usr_msg Information about an error which is available for user.
    @param[in] _func A name of the function where the error was detected.
    @param[in] _line A number of a code line where an error was detected.
    @param[in] _file A name of a file where an error was detected.
    @return Returns an error code.
*/
int throw_error_hard(unsigned int err_num, const char *_func, int _line,
                     const char *_file);

/*!
    @brief Reads the data from the input file.
    @param[in] data text_t object.
    @param[in] inputFilename A name of the input file.
    @return Returns an error code.
*/
int getBuf(text_t *data);


/*!
    @brief Compares the string str1 to the string str2 alphabetically from end.
    @param[in] str1,str2 C or string_t strings to be compared.
    @return Returns an integral value indicating the relationship between the strings.
*/
int cmpAlphabetReverse(const void *str1, const void *str2);


/*!
    @brief Compares the string str1 to the string str2 alphabetically from beginning.
    @param[in] str1,str2 C or string_t strings to be compared.
    @return Returns an integral value indicating the relationship between the strings.
*/
int cmpAlphabet(const void *str1, const void *str2);


/*!
    @brief Sorts tokens of the data.
    @param[in] data text_t object.
    @param[in] comparator A compare function.
    @return Returns an error code.
*/
int sort(text_t *data, int ( *comparator )(const void *, const void *));


/*!
    @brief Destroys a text_t structure.
    @param[in] data text_t object.
*/
void destructText(text_t *data);


/*!
    @brief Counts the amount of tokens in the  input data.
    @param[in] buffer Input data.
    @param[in] sep Tokens separator.
    @return A number of tokens.
*/
size_t countTokens(const char *buffer, char sep);

int parseCommandLine(text_t *data, int argc, char **argv);

int constructText(text_t *data, const char *input, const char *output);