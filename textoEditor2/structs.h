#ifndef STRUCTS_FILE
#define STRUCTS_FILE

#define DOWNBAR_SIZE 3

struct line{
    char *buffer;
    int capacity;
    int size;

    struct line *next;
    struct line *before;
};

struct document{
    struct line *currentDraw;

    struct line *first;
    struct line *last;
    int totalLines;
};

struct cursor {
    int x;
    int y;
    int x_try;
    struct line *currentLine;
};

struct whereWin{
    struct line *currentDraw;
    int y;
    int x;
};
#endif
