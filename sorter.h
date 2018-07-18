#pragma once

/*!
 * \brief Contains functions headers and some constants.
 * \author Stanislau Shimovolos
 * \version 1.4
 * \date 2018-7-17
 */

/// Release version so asserts were turned off.
#define NDEBUG

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>


static const char *const errList[] = {"",
                                      "Invalid arguments in function.",
                                      "Certain problems related to opening file.",
                                      "System couldn't allocate memory.",
                                      "Error, unknown flag."
};

static const char defaultOutput[] = "output.txt";
static const char defaultInput[] = "poem.txt";

/**
* The list of possible errors
*/

enum error_codes
{
    ARGUMENTS_ERR = 1,      //!< Means that function argument or some of them are equal NULL.
    OPENFILE_ERR,           //!< Means that some problem was detected in process of opening file.
    MEMORY_ERR,             //!< Means that system couldn't allocate memory.
    UNKNOWN_FLAG_ERR,       //!< Means that unknown flag was detected in the command line, possible options: -D, -A
    OUT_OF_ERR_RANGE_ERR    //!< Means that num of the error is too large

};

/*!
     \brief The structure which contains char* string and its length.
 */


typedef struct
{
    char *str;              //!< pointer to the char string
    size_t length;          //!< length of this string str
} string_t;


/*!
     \brief The structure which contains
      all information about the input data.

      It contains the original text data, size of this data,
      an array of tokens and  number of them.
 */

typedef struct
{
    char *buffer;           //!< buffer with input data
    size_t size;            //!< size of the buffer in bytes
    string_t *tokens;       //!< array of tokens to which source data was splitted
    size_t tokensAmount;    //!< the number of tokens
} text_t;

/*!
    \brief Reads information from the command line and executes program.
    \param[in] data  text_t object.
    \param[in] argc, argv Parameters of the command line.
    \return Returns an error code.
*/
int executeProgram(text_t *data, int argc, char **argv);


/*!
    \brief Creates "poem" from sorted in rhyme tokens.
    \param[in] data  text_t object.
    \param[in] separator The literal tokens separator (char).
    \return Returns an error code.
*/
int swapTokens(text_t *data);

/*!
    Splits the data into tokens.
    \param[in] data  text_t object.
    \param[in] separator The literal tokens separator (char).
    \return Returns an error code.
*/
int makeTokens(text_t *data, char *separator);


/*!
    \brief Writes tokens to the text file.
    \param[in] data  data text_t object.
    \param[in] outputFile the name of the output text file.
    \return Returns an error code.
*/
int printText(text_t *data, const char *outputFile);


/*!
    \brief Writes tokens to the standard output.
    \param[in] data  data text_t object.
    \return Returns an error code.
*/
int displayText(text_t *data);


/*!
    \brief Exchange values of two string_t objects.
    \param[in] a,b string_t strings to be exchanged.
    \return Returns an error code.
*/
int swapStr_t(string_t *a, string_t *b);


/*!
    \brief Throws the error code and prints information about the error(standard output + standard error output).
    \param[in] err_num Error code.
    \param[in] usr_msg Information about the error which will be able for user.
    \param[in] _func The  name of the function where the error was detected.
    \param[in] _line The number of the code line where the error was detected.
    \param[in] _file The name of the file where the error was detected.
    \return Returns an error code.
*/
int throw_error(unsigned int err_num, const char *usr_msg, const char *err_msg, const char *_func, int _line,
                const char *_file);

/*!
    \brief Reads the data from the input file.
    \param[in] data text_t object.
    \param[in] inputFilename A name of the input file.
    \return Returns an error code.
*/
int getBuf(text_t *data, const char *inputFilename);


/*!
    \brief Compares the string str1 to the string str2 alphabetically from end.
    \param[in] str1,str2 C or string_t strings to be compared.
    \return Returns an integral value indicating the relationship between the strings.
*/
int cmpAlphabetReverse(const void *s1, const void *s2);


/*!
    \brief Compares the string str1 to the string str2 alphabetically from beginning.
    \param[in] str1,str2 C or string_t strings to be compared.
    \return Returns an integral value indicating the relationship between the strings.
*/
int cmpAlphabet(const void *str1, const void *str2);


/*!
    \brief Sorts tokens of the data.
    \param[in] data The text_t object.
    \param[in] comparator The compare function.
    \return Returns an error code.
*/
int sort(text_t *data, int ( *comparator )(const void *, const void *));


/*!
    \brief Destroys a text_t structure.
    \param[in] data text_t object.
*/
void destructText(text_t *data);


/*!
    \brief Counts the amount of tokens in the  input data.
    \param[in] buffer Input data.
    \param[in] sep Tokens separator.
    \return The number of tokens.
*/
size_t countTokens(const char *buffer, char sep);