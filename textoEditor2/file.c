#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//local files
#include "structs.h"

//oppening file
void OpenFile(char *dir, struct document *doc, struct whereWin *ws){
    // oppening file
    FILE *dataPointer = fopen(dir, "r");

    // getting lines
    char *buffer = NULL;
    size_t capacity = 0;

    struct line *before = NULL;

    // get line per line
    while (getline(&buffer, &capacity, dataPointer) != -1){
        // remove the \n
        size_t len = strlen(buffer);
        if(len > 0 && buffer[len - 1] == '\n')buffer[len - 1] = '\0';

        // create and alloc memory for the struct
        struct line *rn = (struct line *) malloc(sizeof(struct line));
        if(rn == NULL){
            printf("System: Erro ao alocar memoria man.\n");
            return;
        }
        rn->buffer = (char *) malloc(sizeof(char) * strlen(buffer) + 1);
        if(rn->buffer == NULL){
            printf("System: Erro ao alocar memoria man.\n");
            return;
        }
        strcpy(rn->buffer, buffer);

        // additional data
        rn->capacity = strlen(buffer) + 1;
        rn->size = strlen(buffer);
        rn->next = NULL;

        //other data lol
        if (before){
            before->next = rn;
            rn->before = before;
        }else{
            rn->before = NULL;
            doc->first = rn;
        }
        doc->totalLines ++;
        before = rn;
    }

    fclose(dataPointer);
    free(buffer);

    if (before){
        doc->last = before;
    }else{
        // if the file is empty
        doc->first = (struct line *) malloc(sizeof(struct line));
        if (doc->first == NULL){
            printf("- System: O man compra memoria ram ai pro teu pc.\n");
            return;
        }
 
        // starting the struct
        doc->first->buffer = malloc(sizeof(char) * 1);
        if (doc->first->buffer == NULL) return;
        doc->first->buffer[0] = '\0';
        doc->first->size = 0;
        doc->first->capacity = 0;
        doc->first->next = NULL;
        doc->first->before = NULL;

        // adding the document data
        doc->totalLines = 1;
        doc->last = doc->first;

        printf("- Arquivo vazio.\n");
    }

    ws->currentDraw = doc->first;
    ws->y = 0;
    ws->x = 0;
    return;
}

void saveFile(struct document *doc, const char *path){
    FILE *file = fopen(path, "w");

    if (file == NULL) return;

    struct line *current = doc->first;

    while (current != NULL){
        fputs(current->buffer, file);

        if(current->next != NULL) fputc('\n', file);

        current = current->next;
    }
    fclose(file);
    return;
}
