#include <stdio.h>
#include <stdlib.h>
#include "dog.h"
#include "cinematic.h"
#include "credit.h"

void showCampaignEnding(void)
{
    system("cls");

    typeText("The Blacksite Laboratory has fallen.\n\n", 25);
    typeText("The experiments have been stopped.\n", 25);
    typeText("For now...\n\n", 25);

    waitForEnter();
}

void showCredits(void)
{
    system("cls");

    typeText("========================================\n", 10);
    typeText("               WARDOGZ\n", 10);
    typeText("========================================\n\n", 10);

    typeText("A C Console RPG Project\n\n", 15);

    typeText("Created and Developed by\n\n", 15);
    typeText("Jed Jarin\n\n", 15);

    typeText("Special Thanks\n\n", 15);

    typeText("CAP College\n\n", 15);

    typeText("Family and Friends\n\n", 15);

    typeText("Thank you for playing.\n\n", 15);

    typeText("CAMPAIGN COMPLETE\n", 15);

    waitForEnter();
}

void showReplayEnding(void)
{
    system("cls");

    typeText("The Blacksite grows silent once more...\n\n", 25);
    typeText("Campaign already completed.\n\n", 25);

    waitForEnter();
}