CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = editor

SRCS = main.c editor.c file.c draw.c flags.c terminalConfig.c helpFunction.c keyBinds.c tools.c loop.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
