#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

//configure the terminal
void enableRawMode(struct termios *original){
    // save the orignal config
    tcgetattr(STDIN_FILENO, original);
    // create and copy the config
    struct termios raw;
    raw = *original;
    // desable the echo and canon
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    // apply
    tcsetattr(STDIN_FILENO, TCSAFLUSH,  &raw);

    // save the terminal
    write(STDOUT_FILENO, "\x1b[?1049h", 8);
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    return;
}

// Configure back the terminal
void disableRawMode(struct termios *original){
    // apply the original config
    tcsetattr(STDIN_FILENO, TCSAFLUSH, original);
    // return to terminal
    write(STDOUT_FILENO, "\x1b[?1049l", 8);
    return;
}
