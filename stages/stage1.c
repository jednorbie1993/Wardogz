#include <stdio.h>
#include <stdlib.h>

#include "stage1.h"
#include "../battle.h"
#include "../dog.h"
#include "../cinematic.h"

#define STAGE1_MAX_ENEMIES 3

static void showStage1Menu(int progress[])
{
    printf("=== STAGE 1: Urban Strays ===\n");

    printf("1. Back Alley (%d/3)\n", progress[0]);

    if (progress[0] >= 3)
        printf("2. Junkyard (%d/3)\n", progress[1]);
    else
        printf("2. Junkyard (Locked)\n");

    if (progress[1] >= 3)
        printf("3. Abandoned Block (%d/3)\n", progress[2]);
    else
        printf("3. Abandoned Block (Locked)\n");

    printf("4. Back\n");
    printf("Choice: ");
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
        printf("Finish Zone 1 first!\n");
        waitForEnter();
        return 0;
    }

    if (zoneChoice == 3 && progress[1] < STAGE1_MAX_ENEMIES)
    {
        printf("Finish Zone 2 first!\n");
        waitForEnter();
        return 0;
    }

    return 1;
}

static void showPlayerMustRest()
{
    system("cls");
    typeText("You must rest before you battle again!\n", 25);
    waitForEnter();
}

static void showStage1ReplayIntro()
{
    int replayLine = rand() % 4;

    printf("\n");

    switch (replayLine)
    {
        case 0:
            printf("\"Territory never stays quiet.\"\n");
            break;

        case 1:
            printf("\"New strays always appear.\"\n");
            break;

        case 2:
            printf("\"The streets always want blood.\"\n");
            break;

        case 3:
            printf("\"Another dog steps into the alley...\"\n");
            break;
    }

    if (systemLog)
        printf(" (REPLAY MODE)\n");

    waitForEnter();
}

static void showStage1BossIntro(int zoneIndex, int progress[])
{
    if (progress[zoneIndex] != 2)
        return;

    system("cls");

    if (zoneIndex == 0)
    {
        typeText("Heavy footsteps echo through the alley.\n", 25);
        typeText("The Alley Alpha finally appears.\n\n", 25);

        typeText("Alley Alpha:\n", 30);
        typeText("\"This territory belongs to ME.\"\n", 30);
    }
    else if (zoneIndex == 1)
    {
        typeText("Metal scraps rattle in the darkness.\n", 25);
        typeText("A massive dog steps out from the junkyard.\n\n", 25);

        typeText("Iron Jaw:\n", 30);
        typeText("\"Scrap or flesh... everything breaks.\"\n", 30);
    }
    else if (zoneIndex == 2)
    {
        typeText("The abandoned block falls completely silent.\n", 25);
        typeText("A terrifying presence approaches slowly.\n\n", 25);

        typeText("Street King:\n", 30);
        typeText("\"Only one king rules these streets.\"\n", 30);
    }

    waitForEnter();
}

static void showStage1SurrenderOutro()
{
    system("cls");

    int outro = rand() % 4;

    printf("\n");

    switch (outro)
    {
        case 0:
            typeText("...That was too close.\n", 25);
            typeText("Phew... lucky this time.\n", 25);
            typeText("I need to be stronger.\n", 25);
            break;

        case 1:
            typeText("Tch... not enough.\n", 25);
            typeText("I'll be back.\n", 25);
            typeText("Next time, I finish this.\n", 25);
            break;

        case 2:
            typeText("That dog... it's different.\n", 25);
            typeText("I felt the pressure.\n", 25);
            typeText("I need more training.\n", 25);
            break;

        case 3:
            typeText("No way... that was intense.\n", 25);
            typeText("I barely made it out.\n", 25);
            typeText("Next time, I won't hesitate.\n", 25);
            break;
    }

    printf("\n");
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
            printf("Please select a number.\n");
            waitForEnter();
            continue;
        }

        if (!isStage1ChoiceValid(zoneChoice))
        {
            printf("Invalid choice! Select 1-4 only.\n");
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