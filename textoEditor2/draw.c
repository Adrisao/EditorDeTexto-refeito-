#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "flags.h"

// drawn the text on the screen
void draw(struct document *doc, int flags){
    struct line *current = doc->first;

    // cleaning the screen
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

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
            write(STDOUT_FILENO, n, strlen(n));
            write(STDOUT_FILENO, " ", 1);
        }
        write(STDOUT_FILENO, current->buffer, current->size);
        write(STDOUT_FILENO, "\n", 1);
        current = current->next;
    }
}
