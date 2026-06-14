// libs
#include <stdlib.h>
#include <termios.h>

// local files
#include "file.h"
#include "structs.h"

int flags = 0;

// function of getting flags and path
void inputData(int argc, char *argv[], char **file){
    // get path
    *file = argv[1];
    if (argc <= 2) return;

    // get flags
    for (int i = 2; i < argc; i++){}

    return;
}

// original termios config
struct termios original;

// main function
int main(int argc, char *argv[]){
    //important data
    char *file = NULL;
    struct line firstLine;

    // get flags and path
    if (argc > 1) inputData(argc, argv, &file);

    // open file
    if (file) OpenFile(file, &firstLine);
    return 0;
}
