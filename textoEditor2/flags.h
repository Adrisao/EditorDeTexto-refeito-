#ifndef FLAGS
#define FLAGS

enum FlagData{
    LINENUMBERS     = 1 << 0,
    JUSTSHOW        = 1 << 1,
    HELPFLAG        = 1 << 2,
    READONLY        = 1 << 3,
};

void inputData(int argc, char *argv[], char **file, enum FlagData *flags);

#endif
