CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
TARGET = wardogz.exe
SOURCES = $(wildcard *.c enemies/*.c stages/*.c dialogue/*.c sparring/*.c sparring/characters/*.c arena/*.c)
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(OBJECTS:.o=.d)
.PHONY: all run clean
all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@
%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
-include $(DEPS)
run: $(TARGET)
	./$(TARGET)
clean:
ifeq ($(OS),Windows_NT)
	-del /s /q *.o *.d 2>nul
	-del /q $(TARGET) 2>nul
else
	rm -f $(OBJECTS) $(DEPS) $(TARGET)
endif
