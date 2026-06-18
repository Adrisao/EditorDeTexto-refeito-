#ifndef TOOLSH
#define TOOLSH

void fixCursorX(struct cursor *cursor);
void newLineFunction(struct cursor *cursor, struct document *doc, struct whereWin *ws, struct winsize *wn, int *line);
void deleteLineFunction(struct cursor *cursor, struct document *doc, struct whereWin *ws);
void freeDocument(struct document *doc);

void moveCursorUp(struct cursor *cursor, struct whereWin *ws, struct winsize *wn, int *line);
void moveCursorDown(struct cursor *cursor, struct whereWin *ws, struct winsize *wn, int *line);
void moveCursorRight(struct cursor *cursor, struct whereWin *ws, struct winsize *wn, int *line);
void moveCursorLeft(struct cursor *cursor, struct whereWin *ws, struct winsize *wn, int *line);

#endif
