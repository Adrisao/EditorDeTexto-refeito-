// libs
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

// local files
#include "file.h"
#include "structs.h"
#include "draw.h"
#include "flags.h"
#include "terminalConfig.h"
#include "helpFunction.h"
#include "keyBinds.h"
#include "tools.h"
#include "editor.h"
#include "loop.h"

enum FlagData flags;

// original termios config
struct termios original;

void restoreTerminal(void){
    disableRawMode(&original);
    return;
}

//char loop(struct document *doc, struct cursor *cursor, const char *path, struct whereWin *ws);

// main function
int main(int argc, char *argv[]){
    //important data
    char *file = NULL;
    struct document doc;
    struct cursor cursor;
    struct winsize wn;
    struct whereWin ws;
    int line = 1;

    // get the sizes
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wn);

    // starting
    doc.totalLines = 0;
    doc.first = NULL;
    doc.last = NULL;
    doc.totalLines = 0;
    cursor.x = 0;
    cursor.y = 0;
    cursor.x_try = 0;
    ws.x = 0;
    ws.y = 0;

    // get flags and path
    if (argc > 1) inputData(argc, argv, &file, &flags);

    // -h flag (help flag)
    if (flags & HELPFLAG){
        help();
        return 0;
    }

    // open file
    if (file) OpenFile(file, &doc, &ws);

    cursor.currentLine = doc.first;
    ws.currentDraw = doc.first;

    //the -s flag
    if(flags & JUSTSHOW){
        draw(&ws, flags, &wn, &line);
        return 0;
    }

    // raw mode
    enableRawMode(&original);
    atexit(restoreTerminal);

    // first draw
    draw(&ws, flags, &wn, &line);
    drawCursor(&ws, flags);

    //main loop
    while (loop(&doc, &cursor, file, &ws, flags, &wn, &line));

    disableRawMode(&original);

    freeDocument(&doc);

    return 0;
}
