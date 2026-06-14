#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "flags.h"

#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"

#define CLEAR_SCREEN "\x1b[2J"
#define CURSOR_HOME  "\x1b[H"

// draw the text on the screen
void draw(struct document *doc, int flags){
    struct line *current = doc->first;

    // cleaning the screen
    if(!(flags & JUSTSHOW)){
        write(STDOUT_FILENO, CLEAR_SCREEN, strlen(CLEAR_SCREEN));
        write(STDOUT_FILENO, CURSOR_HOME, strlen(CURSOR_HOME));
    }
    // wrinting again the whole screen
    int line = 0;
    while(current){
        if (flags & LINENUMBERS){
            line ++;
            char n[10];
            snprintf(n, sizeof(n), "%d", line);

            if (line < 10) {
                write(STDOUT_FILENO, "  ", 2);
            }else if (line < 100) {
                write(STDOUT_FILENO, " ", 1);
            }
            write(STDOUT_FILENO, COLOR_BLUE, strlen(COLOR_BLUE));
            write(STDOUT_FILENO, n, strlen(n));
            write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));
            write(STDOUT_FILENO, " ", 1);
        }
        write(STDOUT_FILENO, current->buffer, current->size);
        write(STDOUT_FILENO, "\n", 1);
        current = current->next;
    }
}

int getTextOffset(int flags){
    if(flags & LINENUMBERS)
        return 5;

    return 1;
}

// draw the cursor function
void drawCursor(struct cursor *cursor, int flags){
    // calculate screen cursor position
    unsigned int screenX = cursor->x + getTextOffset(flags);
    unsigned screenY = cursor->y + 1;
    // draw the cursor
    printf("\x1b[%d;%dH", screenY, screenX);
    fflush(stdout);
}
