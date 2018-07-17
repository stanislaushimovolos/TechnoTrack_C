#include "sorter.h"

int main(int argc, char *argv[])
{
    text_t data = {};
    int err_num = executeProgram(&data, argc, argv);

    destructText(&data);
    return err_num;
}