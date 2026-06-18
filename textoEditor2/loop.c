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

char loop(struct document *doc, struct cursor *cursor, const char *path, struct whereWin *ws, enum FlagData flags, struct winsize *wn, int *line){
    unsigned short key = readKey();
    unsigned char didntIrun = 0;
    switch(key){
    case KEY_EXIT:
        return 0;
    case KEY_ARROW_UP:
        moveCursorUp(cursor, ws, wn, line);
        break;
    case KEY_ARROW_DOWN:
        moveCursorDown(cursor, ws, wn, line);
        break;
    case KEY_ARROW_RIGHT:
        moveCursorRight(cursor, ws, wn, line);
        break;
    case KEY_ARROW_LEFT:
        moveCursorLeft(cursor, ws, wn, line);
        break;
    default:
        didntIrun = 1;
        break;
    }
    if (!(flags & READONLY) && didntIrun){
        switch (key){
        case KEY_SAVE:
            saveFile(doc, path);
            break;
        case BACKSPACE:
            if(cursor->x == 0){
                deleteLineFunction(cursor, doc, ws);
            }else backspace(cursor, ws);
                break;
        case DEL:
            del(cursor, ws);
            break;
        case KEYERROR:
            printf("-KEY ERROR.\n");
            break;
        case ENTER:
            newLineFunction(cursor, doc, ws, wn, line);
            break;
        case ENTER2:
            printf("-ENTER2.");
            break;
        case KEY_TAB:
            #define TAB_SIZE 4
            for(int i = 0; i < TAB_SIZE; i++)insert(' ', cursor, ws);
            break;
        default:
            insert(key, cursor, ws);
            break;
        }
    }else{
        printf("-READ ONLY.\n");
    }
    draw(ws, flags, wn, line);
    drawCursor(ws, flags);
    return 1;
}
