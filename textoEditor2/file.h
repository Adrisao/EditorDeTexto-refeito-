#ifndef FILE_H
#define FILE_H

#include "structs.h"

void OpenFile(char *dir, struct document *doc);

void saveFile(struct document *doc, const char *path);

#endif
