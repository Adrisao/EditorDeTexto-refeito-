#include "structs.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// the visual cursor position
void fixCursorX(struct cursor *cursor){
    if(cursor->x_try <= cursor->currentLine->size){
        cursor->x = cursor->x_try;
    }else{
        cursor->x = cursor->currentLine->size;
    }
}

//new line function
void newLineFunction(struct cursor *cursor, struct document *doc){
    // create a new line struct, the NEWLINE
    struct line *newLine = (struct line *) malloc(sizeof(struct line));
    //how much chars do i need to copy
    int sizeCP = cursor->currentLine->size - cursor->x + 1;
    newLine->buffer = (char *) malloc(sizeof(char) * sizeCP + 10);

    printf(
        "line=[%s] size=%d cursor=%d capacity=%d\n",
        cursor->currentLine->buffer,
        cursor->currentLine->size,
        cursor->x,
        cursor->currentLine->capacity
    );
    // copy the line after the cursor
    for (int i = cursor->x, j = 0; j < sizeCP; i ++, j++){
        *(newLine->buffer + j) = *(cursor->currentLine->buffer + i);
    }

    printf(
    "new=[%s]\n",
    newLine->buffer
    );

    //sleep(5);
    cursor->currentLine->buffer[cursor->x] = '\0';
    cursor->currentLine->size = cursor->x;

    newLine->size = sizeCP-1;
    newLine->capacity = sizeof(char) * sizeCP + 10;

    // changing the pointers

    // the A line
    struct line *currentLine = cursor->currentLine;
    // the B line
    struct line *nextLine = cursor->currentLine->next;

    // change the pointers of the new line
    // NEWLINE->B
    newLine->next = nextLine;
    // A<-NEWLINE
    newLine->before = currentLine;

    // change the current line and next line pointers
    // before: A<->B, after: A<->NEWLINE<->B
        //B.before = newLine A->B, but NEWLINE<->B
        if(nextLine != NULL){
            nextLine->before = newLine;
        }
        //A.next = newLine A<->NEWLINE and NEWLINE<->B
        if (cursor->currentLine)
        cursor->currentLine->next = newLine;

    // changing the document
    // first line
    if (newLine->before == NULL){
        doc->first = newLine;
    }
    // last line
    if (newLine->next == NULL){
        doc->last == newLine;
    }

    // updating the data
    cursor->currentLine = newLine;
    doc->totalLines ++;
    // updating the cursor
    cursor->y++;
    cursor->x = 0;
}
