#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage2.h"
#include "../battle.h"
#include "../dog.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"
#include "../replay_system.h"
#include "../console.h"

static void typeCenteredLine(const char *text, int delay)
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

static void showStage2Menu(int progress[])
{
    printBorder();
    printBlankLine();
    printCentered("STAGE 2: WILD TERRITORY");
    printBlankLine();

    printMenuItemFormat(1, "River Pack Hideout (%d/3)", progress[3]);

    if (progress[3] >= 3)
        printMenuItemFormat(2, "Forest Ambush Grounds (%d/3)", progress[4]);
    else
        printMenuItem(2, "Forest Ambush Grounds (Locked)");

    if (progress[4] >= 3)
        printMenuItemFormat(3, "Bloodfang Ravine (%d/2)", progress[5]);
    else
        printMenuItem(3, "Bloodfang Ravine (Locked)");

    if (progress[5] >= 2)
        printMenuItemFormat(4, "Alpha's Trial Grounds (%d/4)", progress[6]);
    else
        printMenuItem(4, "Alpha's Trial Grounds (Locked)");

    if (progress[6] >= 4)
        printMenuItemFormat(5, "Mountain Pack Den (%d/4)", progress[7]);
    else
        printMenuItem(5, "Mountain Pack Den (Locked)");

    printMenuItem(6, "Back");
    printBlankLine();
    printf("%35sChoice: ", "");
}

static void showStage2ReplayIntro()
{
    int replayLine = rand() % 4;

    printBlankLine();

    switch (replayLine)
    {
        case 0:
            printCentered("\"The wild never forgets.\"");
            break;

        case 1:
            printCentered("\"Another pack rises from the shadows.\"");
            break;

        case 2:
            printCentered("\"The forest still hungers.\"");
            break;

        case 3:
            printCentered("\"Only the strong survive here.\"");
            break;
    }

    if (systemLog)
    {
        printCentered("(REPLAY MODE)");
    }

    waitForEnter();
}

static void showPlayerMustRestStage2()
{
    system("cls");
    typeCenteredLine("You must rest before you battle again!", 25);
    waitForEnter();
}

static void showStage2BossIntro(int zoneIndex, int isBossFight)
{
    if (zoneIndex == 5 && isBossFight)
    {
        system("cls");

        typeCenteredLine("The river current suddenly grows violent.", 25);
        typeCenteredLine("The leader of the wild pack emerges.", 25);
        printBlankLine();

        typeCenteredLine("River Alpha:", 30);
        typeCenteredLine("\"The weak drown here.\"", 30);

        waitForEnter();
    }
}

static void showStage2SurrenderOutro()
{
    system("cls");

    int outro = rand() % 4;

    printBlankLine();

    switch (outro)
    {
        case 0:
            typeCenteredLine("These wild dogs are ruthless...", 25);
            typeCenteredLine("I need to adapt to their style.", 25);
            break;

        case 1:
            typeCenteredLine("Grr... their teamwork is insane.", 25);
            typeCenteredLine("I need new strategies.", 25);
            break;

        case 2:
            typeCenteredLine("That pack formation... dangerous.", 25);
            typeCenteredLine("I barely escaped.", 25);
            break;

        case 3:
            typeCenteredLine("Wild territory lives up to its name.", 25);
            typeCenteredLine("Next time, I'll be ready.", 25);
            break;
    }

    printBlankLine();
    waitForEnter();
}

void runStage2(Dog *player, int progress[])
{
    int zoneChoice;
    char input[10];

    while (1)
    {
        system("cls");

        showStage2Menu(progress);

        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            printCentered("Please select a number.");
            waitForEnter();
            continue;
        }

        zoneChoice = atoi(input);

        if (zoneChoice < 1 || zoneChoice > 6)
        {
            printCentered("Invalid choice! Select 1-6 only.");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 6)
            return;

        // ZONE INDEX
        int zoneIndex = zoneChoice + 2;

        // =========================
        // LOCK CHECKS
        // =========================

        if (zoneChoice == 2 && progress[3] < 3)
        {
            printCentered("Finish Zone 1 first!");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 3 && progress[4] < 3)
        {
            printCentered("Finish Zone 2 first!");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 4 && progress[5] < 2)
        {
            printCentered("Finish Zone 3 first!");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 5 && progress[6] < 4)
        {
            printCentered("Finish Zone 4 first!");
            waitForEnter();
            continue;
        }

        // =========================
        // CREATE ENEMY
        // =========================

        Dog enemy;
        createEnemy(&enemy);

        int maxEnemies = 3;

        if (zoneIndex == 5)
            maxEnemies = 2;

        if (zoneIndex == 6 || zoneIndex == 7)
            maxEnemies = 4;

        int i;

        // =========================
        // REPLAY MODE
        // =========================

        if (progress[zoneIndex] >= maxEnemies)
        {
            showStage2ReplayIntro();

            // ELITE CHANCE
            i = chooseReplayEnemyIndex(zoneIndex, progress, 1);
        }
        else
        {
            i = progress[zoneIndex];
        }

        // =========================
        // ENEMY SETUP
        // =========================

        loadStage2Enemies(&enemy, zoneIndex, i);

        // ELITE ENEMY
        if (i == maxEnemies)
        {
            strcpy(enemy.name, "Elite Predator");

            enemy.attack += 15;
            enemy.speed += 15;
            enemy.maxHP += 40;
            enemy.hp = enemy.maxHP;
        }

        // NORMAL ENCOUNTER
        if (progress[zoneIndex] < maxEnemies)
        {
            printBlankLine();
            printCenteredFormat("Fighting: %s", enemy.name);
            waitForEnter();
        }

        // PLAYER DEAD CHECK
        if (player->hp <= 0)
        {
            showPlayerMustRestStage2();
            continue;
        }

        // =========================
        // BOSS INTRO
        // =========================

        int isBossFight = (progress[zoneIndex] == maxEnemies - 1);

        showStage2BossIntro(zoneIndex, isBossFight);

        // =========================
        // BATTLE
        // =========================

        int result = battleWithEnemyIndex(player, zoneIndex, progress, i);

        if (result == 0)
            continue;

        // =========================
        // SURRENDER / ESCAPE
        // =========================

        if (result == 2)
        {
            showStage2SurrenderOutro();
        }
    }
}
