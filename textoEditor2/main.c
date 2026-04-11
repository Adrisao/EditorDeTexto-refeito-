// libs
#include <stdlib.h>
#include "file.h"

int flags = 0;

char *file;

void inputData(int argc, char *argv[]){
    file = argv[1];
    if (argv == 2) return;
    for (int i = 2, i < argc; i++){
    }
}

// main function
int main(int argc, char *argv[]){
    // get flags and path
    if (argc > 1) inputData(argc, argv);

    // open file
    
    return 0;
}
