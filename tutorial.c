#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tutorial.h"
#include "console.h"
#include "dog.h"
#include "menu_shortcuts.h"

static void showTutorialMenu(void);
static void showBasicControls(void);
static void showBattleGuide(void);
static void showMenuShortcuts(void);
static void showSavingLoading(void);
static void showGameModes(void);

static void showTutorialMenu(void)
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("TUTORIAL / HELP");
    printBlankLine();

    printMenuItem(1, "Basic Controls");
    printMenuItem(2, "Battle Guide");
    printMenuItem(3, "Menu Shortcuts");
    printMenuItem(4, "Saving and Loading");
    printMenuItem(5, "Game Modes");
    printMenuItem(0, "Back");

    printBlankLine();
    printMenuShortcutLegend();
    printBlankLine();
    printf("%35sChoice: ", "");
}

static void showBasicControls(void)
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("BASIC CONTROLS");
    printBlankLine();

    printCentered("Use the number keys shown in each menu to make a selection.");
    printCentered("Press Enter after typing your choice.");
    printCentered("Use Back or Return options to leave a submenu.");
    printCentered("Battle controls are shown when a battle begins.");

    printBlankLine();
    printBorder();
    waitForEnter();
}

static void showBattleGuide(void)
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("BATTLE GUIDE");
    printBlankLine();

    printCentered("Choose an action when it is your dog's turn.");
    printCentered("Skills use the stats, effects, and rules shown by the battle system.");
    printCentered("Enemy turns are controlled automatically by enemy AI.");
    printCentered("Watch HP, fatigue, buffs, debuffs, and other battle effects.");
    printCentered("Menu shortcuts are not used during active battles.");

    printBlankLine();
    printBorder();
    waitForEnter();
}

static void showMenuShortcuts(void)
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("MENU SHORTCUTS");
    printBlankLine();

    printCentered("0 - Back");
    printCentered("H - Home");
    printCentered("S - Save");
    printCentered("L - Load");
    printCentered("O - Options");
    printCentered("Q - Quit");
    printBlankLine();
    printCentered("Letter shortcuts work in safe menus only.");
    printCentered("They are disabled during active battles.");

    printBlankLine();
    printBorder();
    waitForEnter();
}

static void showSavingLoading(void)
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("SAVING AND LOADING");
    printBlankLine();

    printCentered("Wardogz automatically saves game progress during normal play.");
    printCentered("Existing save data is loaded when the game starts.");
    printCentered("Save data is stored in save.dat.");
    printCentered("Use S to save and L to load while you are in a safe menu.");

    printBlankLine();
    printBorder();
    waitForEnter();
}

static void showGameModes(void)
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("GAME MODES");
    printBlankLine();

    printCentered("Campaign - Progress through stages, zones, enemies, and story content.");
    printCentered("Sparring - Practice against special opponents and earn unlock rewards.");
    printCentered("Arena - Challenge progressively stronger arena opponents.");
    printCentered("Training - Improve your dog's core combat stats.");

    printBlankLine();
    printBorder();
    waitForEnter();
}

void tutorialHelpMenu(void)
{
    char input[16];

    while (1)
    {
        showTutorialMenu();

        if (!fgets(input, sizeof(input), stdin))
            return;

        input[strcspn(input, "\n")] = '\0';

        if (handleMenuShortcut(input))
        {
            if (menuNavigationRequested())
                return;

            continue;
        }

        if (strcmp(input, "1") == 0)
        {
            showBasicControls();
        }
        else if (strcmp(input, "2") == 0)
        {
            showBattleGuide();
        }
        else if (strcmp(input, "3") == 0)
        {
            showMenuShortcuts();
        }
        else if (strcmp(input, "4") == 0)
        {
            showSavingLoading();
        }
        else if (strcmp(input, "5") == 0)
        {
            showGameModes();
        }
        else if (strcmp(input, "0") == 0)
        {
            break;
        }
        else
        {
            printBlankLine();
            printCentered("Invalid choice!");
            waitForEnter();
        }
    }
}
