CC = gcc

CFLAGS = -Wall -g

TARGET = main

all:	$(TARGET)

$(TARGET):	$(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
