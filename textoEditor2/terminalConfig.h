#ifndef TERMINALCONF
#define TERMINALCONF

#include <termios.h>

void enableRawMode(struct termios *original);
void disableRawMode(struct termios *original);

#endif
