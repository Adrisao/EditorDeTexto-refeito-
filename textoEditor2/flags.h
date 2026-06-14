#ifndef FLAGS
#define FLAGS

enum FlagData{
    LINENUMBERS = 1 << 0,
};

void inputData(int argc, char *argv[], char **file, enum FlagData *flags);

#endif
