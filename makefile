CC = gcc
TARGET = wardogz.exe

SOURCES = $(wildcard *.c) \
          $(wildcard enemies/*.c) \
          $(wildcard stages/*.c) \
          $(wildcard dialogue/*.c) \
          $(wildcard sparring/*.c) \
          $(wildcard sparring/characters/*.c) \
          $(wildcard arena/*.c)

OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	del /s /q *.o
	del /q $(TARGET)

	//mingw32-make run