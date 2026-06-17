#ifndef TOOLSH
#define TOOLSH

void fixCursorX(struct cursor *cursor);
void newLineFunction(struct cursor *cursor, struct document *doc);
void deleteLineFunction(struct cursor *cursor, struct document *doc);
void freeDocument(struct document *doc);

#endif
