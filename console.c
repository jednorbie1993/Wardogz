#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "console.h"

void setupConsole()
{
    system("chcp 65001 > nul");
    system("mode con: cols=120 lines=40");
    system("title WARDOGZ");
}

void printCentered(const char *text)
{
    int len = strlen(text);
    int spaces = (CONSOLE_WIDTH - len) / 2;

    if (spaces < 0)
        spaces = 0;

    for (int i = 0; i < spaces; i++)
        printf(" ");

    printf("%s\n", text);
}

void printCenteredNoNewline(const char *text)
{
    int len = strlen(text);
    int spaces = (CONSOLE_WIDTH - len) / 2;

    if (spaces < 0)
        spaces = 0;

    for (int i = 0; i < spaces; i++)
        printf(" ");

    printf("%s", text);
}

void printCenteredFormat(const char *format, ...)
{
    char buffer[256];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    printCentered(buffer);
}

void printBorder()
{
    printCentered("------------------------------------------------------------------------------------------------------");
}

void printBlankLine()
{
    printf("\n");
}

void printMenuItem(int num, const char *text)
{
    printf("%*s%2d. %-25s\n", MENU_MARGIN, "", num, text);
}

void printMenuItemFormat(int num, const char *format, ...)
{
    char buffer[256];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    printMenuItem(num, buffer);
}