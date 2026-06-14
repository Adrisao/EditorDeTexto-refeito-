#include "flags.h"
#include <stdio.h>

void inputData(int argc, char *argv[], char **file, enum FlagData *flags){
    for (int i = 1; i < argc; i ++){
        // if it's a flag
        if (argv[i][0] == '-'){
            // if it's a complex flag
            if (argv[i][1] == '-'){
                continue;
            }
            printf("- Rodei aqui tbm.\n");
            switch(argv[i][1]){
            case '\n':
                continue;
            case 'l':
                *flags |= LINENUMBERS;
                continue;
            default:
                continue;
            }
            continue;
        }
        *file = argv[i];
    }
}
