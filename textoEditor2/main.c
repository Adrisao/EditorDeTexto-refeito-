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
#include "tools.h"
#include "editor.h"

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
    cursor.x = 0;
    cursor.y = 0;
    cursor.x_try = 0;

    // get flags and path
    if (argc > 1) inputData(argc, argv, &file, &flags);

    // -h flag (help flag)
    if (flags & HELPFLAG){
        help();
        return 0;
    }

    // open file
    if (file) OpenFile(file, &doc);

    cursor.currentLine = doc.first;

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
    unsigned short key = readKey();
    switch(key){
    case KEY_EXIT:
        return 0;
    case KEY_SAVE:
        printf("- Sistema de salvamento não implementado ainda.\n");
        break;
    case KEY_ARROW_UP:
        if (cursor->y > 0 && cursor->currentLine->before != NULL){
            cursor->y--;
            cursor->currentLine = cursor->currentLine->before;
            fixCursorX(cursor);
        }
        break;
    case KEY_ARROW_DOWN:
        if (cursor->currentLine->next != NULL){
            cursor->y++;
            cursor->currentLine = cursor->currentLine->next;
            fixCursorX(cursor);
        }
        break;
    case KEY_ARROW_RIGHT:
        if (cursor->x < cursor->currentLine->size){cursor->x++;
        }else if(cursor->currentLine->next != NULL){
            // go to the next line
            cursor->y ++;
            cursor->currentLine = cursor->currentLine->next;
            cursor->x = 0;
        }
        cursor->x_try = cursor->x;
        break;
    case KEY_ARROW_LEFT:
        if(cursor->x > 0){cursor->x--;
        }else if (cursor->currentLine->before != NULL){
            //come back to the previous line
            cursor->y --;
            cursor->currentLine = cursor->currentLine->before;
            cursor->x = cursor->currentLine->size;
        }
        cursor->x_try = cursor->x;
        break;
    case BACKSPACE:
        if(cursor->x == 0){
            deleteLineFunction(cursor, doc);
            printf("-DELETAR LINHA");
        }else backspace(cursor);
        break;
    case DEL:
        del(cursor);
        break;
    case KEYERROR:
        printf("-KEY ERROR.\n");
        break;
    case ENTER:
        newLineFunction(cursor, doc);
        break;
    case ENTER2:
        printf("-ENTER2.");
        break;
    default:
        if(flags & READONLY) break;
        insert(key, cursor);
        break;
    }
    draw(doc, flags);
    drawCursor(cursor, flags);
    return 1;
}
