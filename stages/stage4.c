#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage4.h"
#include "../battle.h"
#include "../dog.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"
#include "../enemies/enemy_stage4.h"
#include "../replay_system.h"
#include "../console.h"

static void typeCentered(const char *text, int delay)
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

int getZoneMaxStage4(int zoneIndex)
{
    if (zoneIndex == 12) return 2;  // Outer Facility
    if (zoneIndex == 13) return 4;  // Research Hallways
    if (zoneIndex == 14) return 4;  // Containment Labs
    if (zoneIndex == 15) return 3;  // Core Chamber

    return 2;
}

static void showStage4Menu(int progress[])
{
    printBorder();
    printBlankLine();
    printCentered("STAGE 4: BIO-CONTAINMENT ZONE");
    printBlankLine();

    printMenuItemFormat(1, "Outer Facility (%d/2)", progress[12]);

    if (progress[12] >= 2)
        printMenuItemFormat(2, "Research Hallways (%d/4)", progress[13]);
    else
        printMenuItem(2, "Research Hallways (LOCKED)");

    if (progress[13] >= 4)
        printMenuItemFormat(3, "Containment Labs (%d/4)", progress[14]);
    else
        printMenuItem(3, "Containment Labs (LOCKED)");

    if (progress[14] >= 4)
        printMenuItemFormat(4, "Core Chamber (%d/3)", progress[15]);
    else
        printMenuItem(4, "Core Chamber (LOCKED)");

    printMenuItem(5, "Back");
    printBlankLine();

    printf("%35sChoice: ", "");
}

static int getStage4Choice()
{
    char input[10];

    fgets(input, sizeof(input), stdin);

    if (input[0] == '\n')
        return -1;

    return atoi(input);
}

static int getStage4ZoneIndex(int zoneChoice)
{
    if (zoneChoice == 1) return 12;
    if (zoneChoice == 2) return 13;
    if (zoneChoice == 3) return 14;
    if (zoneChoice == 4) return 15;

    return -1;
}

static int isStage4ZoneUnlocked(int zoneChoice, int progress[])
{
    if (zoneChoice == 2 && progress[12] < 2)
    {
        printCentered("[ACCESS DENIED] Complete Outer Facility first!");
        waitForEnter();
        return 0;
    }

    if (zoneChoice == 3 && progress[13] < 4)
    {
        printCentered("[ACCESS DENIED] Complete Research Hallways first!");
        waitForEnter();
        return 0;
    }

    if (zoneChoice == 4 && progress[14] < 4)
    {
        printCentered("[ACCESS DENIED] Complete Containment Labs first!");
        waitForEnter();
        return 0;
    }

    return 1;
}

static void showStage4Intro(int zoneIndex)
{
    system("cls");
    printBorder();
    printBlankLine();

    if (zoneIndex == 12)
    {
        typeCentered("[BIO-LAB EXTERIOR]", 20);
        typeCentered("Warning: Unauthorized personnel detected.", 25);
    }
    else if (zoneIndex == 13)
    {
        typeCentered("[RESEARCH HALLWAY]", 20);
        typeCentered("Note: Subject tests in progress...", 25);
    }
    else if (zoneIndex == 14)
    {
        typeCentered("[CONTAINMENT LAB]", 20);
        typeCentered("WARNING: Containment breach imminent!", 28);
    }
    else if (zoneIndex == 15)
    {
        typeCentered("[CORE CHAMBER - RESTRICTED AREA]", 25);
        typeCentered("WARNING: MAXIMUM SECURITY ACTIVE!", 30);
    }

    waitForEnter();
}

static void showStage4RestWarning()
{
    system("cls");
    printBorder();
    printBlankLine();
    typeCentered("Recover HP before engaging bio-subjects!", 25);
    waitForEnter();
}

static void showPrototypeZeroIntro()
{
    system("cls");

    printBorder();
    printBlankLine();
    typeCentered("!!! PROTOTYPE ZERO ACTIVATED !!!", 25);
    printBlankLine();
    typeCentered("Prototype Zero: \"I AM THE FUTURE OF K-9.\"", 25);
    typeCentered("You have witnessed too much.", 25);
    typeCentered("I will complete the program myself.\"", 28);

    waitForEnter();
}

static void showStage4Complete()
{
    system("cls");

    printBorder();
    printBlankLine();
    typeCentered("STAGE 4: BIO-CONTAINMENT COMPLETE", 20);
    printBlankLine();
    typeCentered("WARNING: Containment failure detected.", 28);
    typeCentered("Mutant samples have been stolen.", 28);
    typeCentered("The FINAL STAGE is now open.", 28);

    waitForEnter();
}

static void showStage4DefeatMessage()
{
    char *defeatMsg[] =
    {
        "Subject escaped containment...",
        "Their hybrid strength is overwhelming...",
        "Need more firepower for these prototypes...",
        "The lab has taken another test subject...",
        "Project success rate increases..."
    };

    int msg = rand() % 5;

    system("cls");
    printBorder();
    printBlankLine();
    typeCentered(defeatMsg[msg], 25);
    waitForEnter();
}

void runStage4(Dog *player, int progress[])
{
    while (1)
    {
        system("cls");

        showStage4Menu(progress);

        int zoneChoice = getStage4Choice();

        if (zoneChoice == -1)
        {
            printCentered("Please select a number.");
            waitForEnter();
            continue;
        }

        if (zoneChoice < 1 || zoneChoice > 5)
        {
            printCentered("Invalid choice! Select 1-5 only.");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 5)
            return;

        int zoneIndex = getStage4ZoneIndex(zoneChoice);

        if (!isStage4ZoneUnlocked(zoneChoice, progress))
            continue;

        showStage4Intro(zoneIndex);

        Dog enemy;
        createEnemy(&enemy);
        enemy.zoneType = ZONE_BIOLAB;

        int zoneMax = getZoneMaxStage4(zoneIndex);
        int i;

        if (progress[zoneIndex] >= zoneMax)
            i = chooseReplayEnemyIndex(zoneIndex, progress, 0);
        else
            i = progress[zoneIndex];

        loadStage4Enemies(&enemy, zoneIndex, i);

        if (i == zoneMax - 1)
        {
            enemy.attack += 18;
            enemy.defense += 14;
            enemy.speed += 10;
            enemy.maxHP += 80;
            enemy.hp = enemy.maxHP;
        }

        if (player->hp <= 0)
        {
            showStage4RestWarning();
            continue;
        }

        if (zoneIndex == 15 && i == 2)
            showPrototypeZeroIntro();

        int result = battleWithEnemyIndex(player, zoneIndex, progress, i);

        if (result == 0)
            continue;

        if (result == 1)
        {
            if (progress[zoneIndex] < zoneMax)
            {
                //progress[zoneIndex]++;

                printCentered("[DATA LOG]: Subject contained.");
                printCenteredFormat("Zone Progress: %d/%d", progress[zoneIndex], zoneMax);
                waitForEnter();
            }

            if (zoneIndex == 15 && progress[15] >= 3)
                showStage4Complete();
        }

        if (result == 2)
            showStage4DefeatMessage();
    }
}
