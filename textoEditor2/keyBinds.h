#ifndef KEYBINDS
#define KETBINDS

#define KEYERROR 999999

// key binds
#define CTRL_KEY(k) ((k) & 0x1f)

#define KEY_SAVE CTRL_KEY('s')
#define KEY_EXIT CTRL_KEY('x')

#define KEY_ARROW_UP    1000
#define KEY_ARROW_DOWN  1001
#define KEY_ARROW_LEFT  1002
#define KEY_ARROW_RIGHT 1003

#define ESC '\x1b'

#define ESC_BRACKET '['

// function

int readKey(void);

#endif
