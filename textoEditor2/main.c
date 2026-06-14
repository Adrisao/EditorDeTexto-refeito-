// libs
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>

// local files
#include "file.h"
#include "structs.h"
#include "draw.h"
#include "flags.h"

enum FlagData flags;

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
    if (argc > 1) inputData(argc, argv, &file, &flags);

    // open file
    if (file) OpenFile(file, &doc);

    draw(&doc, flags);
}
