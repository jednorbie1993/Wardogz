#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "menu_shortcuts.h"
#include "console.h"
#include "dog.h"

static GameData *activeGame = NULL;
static int homeRequested = 0;
static int optionsRequested = 0;
static int quitRequested = 0;

static void normalizeInput(const char *input, char *output, size_t outputSize)
{
    size_t j = 0;

    if (outputSize == 0)
        return;

    while (*input != '\0' && isspace((unsigned char)*input))
        input++;

    while (*input != '\0' && *input != '\n' && *input != '\r' && j + 1 < outputSize)
    {
        output[j++] = (char)tolower((unsigned char)*input);
        input++;
    }

    while (j > 0 && isspace((unsigned char)output[j - 1]))
        j--;

    output[j] = '\0';
}

void initMenuShortcuts(GameData *game)
{
    activeGame = game;
    homeRequested = 0;
    optionsRequested = 0;
    quitRequested = 0;
}

void printMenuShortcutLegend(void)
{
    printCentered("H Home | S Save | L Load | O Options | Q Quit");
}

int handleMenuShortcut(const char *input)
{
    char command[16];
    normalizeInput(input, command, sizeof(command));

    if (strcmp(command, "h") == 0 || strcmp(command, "home") == 0)
    {
        homeRequested = 1;
        return 1;
    }

    if (strcmp(command, "s") == 0 || strcmp(command, "save") == 0)
    {
        if (activeGame != NULL && saveGame(activeGame))
            printCentered("Game saved successfully.");
        else
            printCentered("Unable to save the game.");

        waitForEnter();
        return 1;
    }

    if (strcmp(command, "l") == 0 || strcmp(command, "load") == 0)
    {
        if (activeGame != NULL && loadGame(activeGame))
            printCentered("Game loaded successfully.");
        else
            printCentered("No save data could be loaded.");

        waitForEnter();
        return 1;
    }

    if (strcmp(command, "o") == 0 || strcmp(command, "options") == 0)
    {
        optionsRequested = 1;
        return 1;
    }

    if (strcmp(command, "q") == 0 || strcmp(command, "quit") == 0)
    {
        quitRequested = 1;
        return 1;
    }

    return 0;
}

int menuNavigationRequested(void)
{
    return homeRequested || optionsRequested || quitRequested;
}

int consumeHomeRequest(void)
{
    int requested = homeRequested;
    homeRequested = 0;
    return requested;
}

int consumeOptionsRequest(void)
{
    int requested = optionsRequested;
    optionsRequested = 0;
    return requested;
}

int consumeQuitRequest(void)
{
    int requested = quitRequested;
    quitRequested = 0;
    return requested;
}
