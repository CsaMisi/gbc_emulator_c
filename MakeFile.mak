CC = gcc
CFLAGS = -Iinclude
SRCS = src/cpu.c src/main.c
OBJS = $(SRCS:.c=.o)
TARGET = emulator

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)