CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
TARGET = wardogz.exe

SOURCES = $(wildcard *.c) \
          $(wildcard enemies/*.c) \
          $(wildcard stages/*.c) \
          $(wildcard dialogue/*.c) \
          $(wildcard sparring/*.c) \
          $(wildcard sparring/characters/*.c) \
          $(wildcard arena/*.c)

OBJECTS = $(SOURCES:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	del /s /q *.o 2>nul
	del /q $(TARGET) 2>nul

	
	//mingw32-make clean
	//mingw32-make
	
	//mingw32-make run

	//for /r %f in (*.o) do del "%f"
	//del wardogz.exe
	//pang delete ng .o