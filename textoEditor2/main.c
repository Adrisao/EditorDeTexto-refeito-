// libs
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

// local files
#include "file.h"
#include "structs.h"
#include "draw.h"
#include "flags.h"
#include "terminalConfig.h"
#include "helpFunction.h"
#include "keyBinds.h"

enum FlagData flags;

// original termios config
struct termios original;

void restoreTerminal(void){
    disableRawMode(&original);
    return;
}

char loop(struct document *doc);

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

    // -h flag (help flag)
    if (flags & HELPFLAG){
        help();
        return 0;
    }

    // open file
    if (file) OpenFile(file, &doc);

    //raw mode
    enableRawMode(&original);
    atexit(restoreTerminal);

    draw(&doc, flags);

    // the -s flag
    if (flags & JUSTSHOW) {
        disableRawMode(&original);
        return 0;
    }

    //main loop
    while (loop(&doc));

    disableRawMode(&original);
    return 0;
}

char loop(struct document *doc){
     unsigned char key;

    if(read(STDIN_FILENO, &key, 1) == 1){

        printf("KEY=%d\n", key);
        fflush(stdout);

        switch(key){
        case KEY_EXIT:
            return 0;
        case KEY_SAVE:
            printf("- Sistema de salvamento não implementado ainda.\n");
            fflush(stdout);
            break;
        }
    }

    return 1;
}
