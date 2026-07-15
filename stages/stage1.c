#include <stdio.h>
#include <stdlib.h>

#include "stage1.h"
#include "../battle.h"
#include "../dog.h"
#include "../cinematic.h"
#include "../console.h"

#define STAGE1_MAX_ENEMIES 3

static void showStage1Menu(int progress[])
{
    printBorder();
    printBlankLine();
    printCentered("STAGE 1: URBAN STRAYS");
    printBlankLine();

    printMenuItemFormat(1, "Back Alley (%d/3)", progress[0]);

    if (progress[0] >= 3)
        printMenuItemFormat(2, "Junkyard (%d/3)", progress[1]);
    else
        printMenuItem(2, "Junkyard (Locked)");

    if (progress[1] >= 3)
        printMenuItemFormat(3, "Abandoned Block (%d/3)", progress[2]);
    else
        printMenuItem(3, "Abandoned Block (Locked)");

    printMenuItem(4, "Back");

    printBlankLine();
    printf("%35sChoice: ", "");
}

static int getStage1Choice()
{
    char input[10];

    fgets(input, sizeof(input), stdin);

    if (input[0] == '\n')
        return -1;

    return atoi(input);
}

static int isStage1ChoiceValid(int choice)
{
    return choice >= 1 && choice <= 4;
}

static int isStage1ZoneUnlocked(int zoneChoice, int progress[])
{
    if (zoneChoice == 2 && progress[0] < STAGE1_MAX_ENEMIES)
    {
        printCentered("Finish Zone 1 first!");
        waitForEnter();
        return 0;
    }

    if (zoneChoice == 3 && progress[1] < STAGE1_MAX_ENEMIES)
    {
        printCentered("Finish Zone 2 first!");
        waitForEnter();
        return 0;
    }

    return 1;
}

static void showPlayerMustRest()
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("You must rest before you battle again!");

    waitForEnter();
}

static void showStage1ReplayIntro()
{
    int replayLine = rand() % 4;

    printBorder();
    printBlankLine();
    printCentered("REPLAY MODE");
    printBlankLine();

    switch (replayLine)
    {
        case 0:
            printCentered("\"Territory never stays quiet.\"");
            break;

        case 1:
            printCentered("\"New strays always appear.\"");
            break;

        case 2:
            printCentered("\"The streets always want blood.\"");
            break;

        case 3:
            printCentered("\"Another dog steps into the alley...\"");
            break;
    }

    if (systemLog)
        printCentered("(REPLAY MODE)");

    waitForEnter();
}

static void showStage1BossIntro(int zoneIndex, int progress[])
{
    if (progress[zoneIndex] != 2)
        return;

    system("cls");

    printBorder();
    printBlankLine();
    printCentered("BOSS ENCOUNTER");
    printBlankLine();

    if (zoneIndex == 0)
    {
        printCentered("Heavy footsteps echo through the alley.");
        printCentered("The Alley Alpha finally appears.");

        printBlankLine();
        printCentered("Alley Alpha:");
        printCentered("\"This territory belongs to ME.\"");
    }
    else if (zoneIndex == 1)
    {
        printCentered("Metal scraps rattle in the darkness.");
        printCentered("A massive dog steps out from the junkyard.");

        printBlankLine();
        printCentered("Iron Jaw:");
        printCentered("\"Scrap or flesh... everything breaks.\"");
    }
    else if (zoneIndex == 2)
    {
        printCentered("The abandoned block falls completely silent.");
        printCentered("A terrifying presence approaches slowly.");

        printBlankLine();
        printCentered("Street King:");
        printCentered("\"Only one king rules these streets.\"");
    }

    waitForEnter();
}

static void showStage1SurrenderOutro()
{
    system("cls");

    int outro = rand() % 4;

    printBorder();
    printBlankLine();
    printCentered("SURRENDERED");
    printBlankLine();

    switch (outro)
    {
        case 0:
            printCentered("...That was too close.");
            printCentered("Phew... lucky this time.");
            printCentered("I need to be stronger.");
            break;

        case 1:
            printCentered("Tch... not enough.");
            printCentered("I'll be back.");
            printCentered("Next time, I finish this.");
            break;

        case 2:
            printCentered("That dog... it's different.");
            printCentered("I felt the pressure.");
            printCentered("I need more training.");
            break;

        case 3:
            printCentered("No way... that was intense.");
            printCentered("I barely made it out.");
            printCentered("Next time, I won't hesitate.");
            break;
    }

    waitForEnter();
}

void runStage1(Dog *player, int progress[])
{
    while (1)
    {
        system("cls");

        showStage1Menu(progress);

        int zoneChoice = getStage1Choice();

        if (zoneChoice == -1)
        {
            printCentered("Please select a number.");
            waitForEnter();
            continue;
        }

        if (!isStage1ChoiceValid(zoneChoice))
        {
            printCentered("Invalid choice! Select 1-4 only.");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 4)
            return;

        if (!isStage1ZoneUnlocked(zoneChoice, progress))
            continue;

        int zoneIndex = zoneChoice - 1;

        if (player->hp <= 0)
        {
            showPlayerMustRest();
            continue;
        }

        if (progress[zoneIndex] >= STAGE1_MAX_ENEMIES)
            showStage1ReplayIntro();

        showStage1BossIntro(zoneIndex, progress);

        int result = battle(player, zoneIndex, progress);

        if (result == 0)
            continue;

        if (result == 2)
            showStage1SurrenderOutro();
    }
}
