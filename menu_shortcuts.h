#ifndef MENU_SHORTCUTS_H
#define MENU_SHORTCUTS_H

#include "save.h"

void initMenuShortcuts(GameData *game);
void printMenuShortcutLegend(void);
int handleMenuShortcut(const char *input);
int menuNavigationRequested(void);
int consumeHomeRequest(void);
int consumeOptionsRequest(void);
int consumeQuitRequest(void);

#endif
