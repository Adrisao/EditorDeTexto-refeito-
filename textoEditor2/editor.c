#include <stdlib.h>
#include <stdio.h>

#include "keyBinds.h"
#include "structs.h"

void insert(unsigned short key, struct cursor *cursor, struct whereWin *wn){

    // if needed realloc + 20 chars
    if(cursor->currentLine->size >= cursor->currentLine->capacity -1){
        char *tmp = (char *)realloc(cursor->currentLine->buffer, sizeof(char) * (cursor->currentLine->capacity + 20));
        if (tmp == NULL){
            printf("- Falta MEMORIA para inserir");
        }
        cursor->currentLine->buffer = tmp;
        cursor->currentLine->capacity += 20;
    }

    //printf("- capacidade atual: %d.", cursor->currentLine->capacity);
    // move the line
    for(int i = cursor->currentLine->size + 1; i > cursor->x; i--){
        *(cursor->currentLine->buffer + i) = *(cursor->currentLine->buffer + i - 1);
    }
    cursor->currentLine->size ++;
    *(cursor->currentLine->buffer + cursor->x) = key;
    cursor->x ++;
    wn->x ++;
    return;
}

void backspace(struct cursor *cursor, struct whereWin *wn){
    if (cursor->x == 0) return;
    for(int i = cursor->x-1; i < cursor->currentLine->size + 1; i++){
        *(cursor->currentLine->buffer + i) = *(cursor->currentLine->buffer + i + 1);
    }
    cursor->currentLine->size--;
    cursor->x--;
    wn->x --;
    return;
}

void del(struct cursor *cursor, struct whereWin *wn){
    if(cursor->x >= cursor->currentLine->size) return;
    for(int i = cursor->x; i < cursor->currentLine->size + 1; i++){
        *(cursor->currentLine->buffer + i) = *(cursor->currentLine->buffer + i + 1);
    }
    cursor->currentLine->size--;
    return;
}
