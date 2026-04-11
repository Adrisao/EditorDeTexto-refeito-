#include <stdlib.h>

*int OpenFile(char *dir){
    FILE *dataPointer = fopen(dir, "r");
    return dataPointer;
}
