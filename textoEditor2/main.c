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

char loop(struct document *doc, struct cursor *cursor);

// main function
int main(int argc, char *argv[]){
    //important data
    char *file = NULL;
    struct document doc;
    struct cursor cursor;

    // starting
    doc.totalLines = 0;
    doc.first = NULL;
    doc.last = NULL;
    cursor.x = 2;
    cursor.y = 1;

    // get flags and path
    if (argc > 1) inputData(argc, argv, &file, &flags);

    // -h flag (help flag)
    if (flags & HELPFLAG){
        help();
        return 0;
    }

    // open file
    if (file) OpenFile(file, &doc);

    //the -s flag
    if(flags & JUSTSHOW){
        draw(&doc, flags);
        return 0;
    }

    // raw mode
    enableRawMode(&original);
    atexit(restoreTerminal);

    // first draw
    draw(&doc, flags);
    drawCursor(&cursor, flags);

    //main loop
    while (loop(&doc, &cursor));

    disableRawMode(&original);
    return 0;
}

char loop(struct document *doc, struct cursor *cursor){
     unsigned char key;

    if(read(STDIN_FILENO, &key, 1) == 1){
        switch(key){
        case KEY_EXIT:
            return 0;
        case KEY_SAVE:
            printf("- Sistema de salvamento não implementado ainda.\n");
            fflush(stdout);
            break;
        }
    }

    drawCursor(cursor, flags);
    return 1;
}
