#ifndef TOOLSH
#define TOOLSH

void fixCursorX(struct cursor *cursor);
void newLineFunction(struct cursor *cursor, struct document *doc);
void deleteLineFunction(struct cursor *cursor, struct document *doc);
void freeDocument(struct document *doc);

void moveCursorUp(struct cursor *cursor);
void moveCursorDown(struct cursor *cursor);
void moveCursorRight(struct cursor *cursor);
void moveCursorLeft(struct cursor *cursor);

#endif
