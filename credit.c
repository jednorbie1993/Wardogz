#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dog.h"
#include "cinematic.h"
#include "credit.h"
#include "console.h"


static void typeCenteredText(const char *text, int delay)
{
    int len = strlen(text);
    int spaces = (CONSOLE_WIDTH - len) / 2;

    if (spaces < 0)
        spaces = 0;

    for (int i = 0; i < spaces; i++)
        printf(" ");

    typeText(text, delay);
    printf("\n");
}

void showCampaignEnding(void)
{
    system("cls");

    printBorder();
    printBlankLine();
    typeCenteredText("The Blacksite Laboratory has fallen.", 25);
    printBlankLine();
    typeCenteredText("The experiments have been stopped.", 25);
    typeCenteredText("For now...", 25);
    printBlankLine();

    waitForEnter();
}

void showCredits(void)
{
    system("cls");

    printBorder();
    printBlankLine();
    typeCenteredText("WARDOGZ", 10);
    printBlankLine();
    typeCenteredText("A C Console RPG Project", 15);
    printBlankLine();

    typeCenteredText("Created and Developed by", 15);
    typeCenteredText("Jed Jarin", 15);
    printBlankLine();

    typeCenteredText("Special Thanks", 15);
    typeCenteredText("CAP College", 15);
    typeCenteredText("Family and Friends", 15);
    printBlankLine();

    typeCenteredText("Thank you for playing.", 15);
    printBlankLine();
    typeCenteredText("CAMPAIGN COMPLETE", 15);
    printBlankLine();
    printBorder();

    waitForEnter();
}

void showReplayEnding(void)
{
    system("cls");

    printBorder();
    printBlankLine();
    typeCenteredText("The Blacksite grows silent once more...", 25);
    printBlankLine();
    typeCenteredText("Campaign already completed.", 25);
    printBlankLine();

    waitForEnter();
}
