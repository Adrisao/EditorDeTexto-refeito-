// libs
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>

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
    struct document doc;

    // starting
    doc.totalLines = 0;
    doc.first = NULL;
    doc.last = NULL;

    // get flags and path
    if (argc > 1) inputData(argc, argv, &file);

    // open file
    if (file) OpenFile(file, &doc);

    struct line *teste = doc.last;

    while (teste != NULL){
        printf("- %s\n", teste->buffer);
        teste = teste->before;
    }
    return 0;
}
