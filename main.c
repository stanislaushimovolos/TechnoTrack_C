
/*!
 * \file main.c
 * \brief Main program module.
 * \author Stanislau Shimovolos
 * \version 1.4
 * \date 2018-7-17
 */


#include "sorter.h"

int main(int argc, char *argv[])
{
    text_t data = {};
    int err_num = executeProgram(&data, argc, argv);

    destructText(&data);
    return err_num;
}