#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "keyBinds.h"

// the keys that use complex sequence like the arrows
unsigned short escKeys(unsigned short *key){
    switch(*key){
        case ESC_BRACKET:
            // if somethin went wrong
            if (read(STDIN_FILENO, key, 1) != 1) return KEYERROR;
            switch(*key){
                // which arror
                case 'A': return KEY_ARROW_UP;
                case 'B': return KEY_ARROW_DOWN;
                case 'C': return KEY_ARROW_RIGHT;
                case 'D': return KEY_ARROW_LEFT;
                default: return KEYERROR;
            }
    }
}

// read Keys
unsigned short readKey(void){
    unsigned short key = 0;

    //waiting an input
    while(read(STDIN_FILENO, &key, 1) != 1);

    switch(key){
    //case if it's ESC or a ESC sequence
    case ESC:
        if(read(STDIN_FILENO, &key, 1) != 1)return ESC;
        return escKeys(&key);

    // ctrl + (some letter) cases
    case KEY_SAVE: return KEY_SAVE; // ctrl + s
    case KEY_EXIT: return KEY_EXIT; // ctrl + x

    // normal keys
    case BACKSPACE: return BACKSPACE;
    }
}
