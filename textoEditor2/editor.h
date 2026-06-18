#ifndef EDITORIR
#define EDITORIR

void insert(unsigned short key, struct cursor *cursor, struct whereWin *wn);

void backspace(struct cursor *cursor, struct whereWin *wn);

void del(struct cursor *cursor, struct whereWin *wn);

#endif
