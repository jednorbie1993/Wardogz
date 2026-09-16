#ifndef CONSOLE_H
#define CONSOLE_H

#define CONSOLE_WIDTH 120
#define MENU_MARGIN 35

void setupConsole(void);
void printCentered(const char *text);
void printCenteredNoNewline(const char *text);
void printCenteredFormat(const char *format, ...);
void printBorder(void);
void printBlankLine(void);
void printMenuItem(int num, const char *text);
void printMenuItemFormat(int num, const char *format, ...);

#endif