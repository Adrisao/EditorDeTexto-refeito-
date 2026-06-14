#include "structs.h"

void fixCursorX(struct cursor *cursor){
    if(cursor->x_try <= cursor->currentLine->size){
        cursor->x = cursor->x_try;
    }else{
        cursor->x = cursor->currentLine->size;
    }
}
