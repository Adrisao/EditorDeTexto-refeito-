#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "structs.h"
#include "flags.h"

#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

#define CLEAR_SCREEN "\x1b[2J"
#define CURSOR_HOME  "\x1b[H"

int getTextOffset(int flags){
    if(flags & LINENUMBERS)
        return 5;

    return 1;
}

// draw the text on the screen
void draw(struct whereWin *ws, int flags, struct winsize *wn, int *line){
    struct line *current = ws->currentDraw;

    // cleaning the screen
    if(!(flags & JUSTSHOW)){
        write(STDOUT_FILENO, CLEAR_SCREEN, strlen(CLEAR_SCREEN));
        write(STDOUT_FILENO, CURSOR_HOME, strlen(CURSOR_HOME));
    }

    int indice = 0;
    int firstLine = *line;

    while(current){

        // print the text
        if (flags & LINENUMBERS){
            char n[10];
            snprintf(n, sizeof(n), "%d", firstLine);

            if (firstLine < 10) {
                write(STDOUT_FILENO, "  ", 2);
            }else if (firstLine < 100) {
                write(STDOUT_FILENO, " ", 1);
            }
            write(STDOUT_FILENO, COLOR_BLUE, strlen(COLOR_BLUE));
            write(STDOUT_FILENO, n, strlen(n));
            write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));
            write(STDOUT_FILENO, " ", 1);
            firstLine ++;
        }
        write(STDOUT_FILENO, current->buffer, current->size);
        write(STDOUT_FILENO, "\n", 1);
        current = current->next;
        indice ++;
        // if the screen is full
        if (!(flags & JUSTSHOW) && indice >= wn->ws_row - DOWNBAR_SIZE) break;
    }
}

// draw the cursor function
void drawCursor(struct whereWin *ws, int flags){
    // calculate screen cursor position
    unsigned int screenX = ws->x + getTextOffset(flags);
    unsigned screenY = ws->y + 1;
    // draw the cursor
    printf("\x1b[%d;%dH", screenY, screenX);
    fflush(stdout);
}
