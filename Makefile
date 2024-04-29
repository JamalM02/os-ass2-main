CC = gcc
CFLAGS = -Wall -Wextra
DEBUG_FLAGS = -ggdb3 -z lazy

TARGET = uniform-length
SOURCES = main.c uniform_length_lines.c  

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

debug: $(SOURCES)
	$(CC) $(DEBUG_FLAGS) -o $(TARGET) $^

clean:
	rm -f $(TARGET) *.o
	