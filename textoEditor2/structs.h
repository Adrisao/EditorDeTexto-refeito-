#ifndef STRUCTS_FILE
#define STRUCTS_FILE

struct line{
    char *buffer;
    int capacity;
    int size;

    struct line *next;
    struct line *before;
};

struct document{
    struct line *first;
    struct line *last;

    int totalLines;
};

struct cursor {
    int x;
    int y;
};

#endif
