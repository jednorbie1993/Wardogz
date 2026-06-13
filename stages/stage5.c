#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage5.h"
#include "../battle.h"
#include "../dog.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"
#include "../enemies/enemy_stage5.h"
#include "../replay_system.h"

int getZoneMaxStage5(int zoneIndex)
{
    if (zoneIndex == 16) return 4;
    if (zoneIndex == 17) return 4;

    return 4;
}

void runStage5(Dog *player, int progress[])
{
    int zoneChoice;
    char input[10];

    while (1)
    {
        system("cls");

        printf("====================================\n");
        printf("  STAGE 5: BLACKSITE LABORATORY\n");
        printf("====================================\n\n");

        printf("1. Enhanced Strays (%d/4)\n", progress[16]);

        if (progress[16] >= 4)
            printf("2. Feral Mutation Ward (%d/4)\n", progress[17]);
        else
            printf("2. Feral Mutation Ward (Locked)\n");

        printf("3. Back");
        printf("\n\nChoice: ");

        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            printf("\nPlease select a number.");
            waitForEnter();
            continue;
        }

        zoneChoice = atoi(input);

        if (zoneChoice < 1 || zoneChoice > 3)
        {
            printf("\nInvalid choice! Select 1-3 only.");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 3)
            return;

        if (zoneChoice == 2 && progress[16] < 4)
        {
            printf("\nComplete Enhanced Strays first!");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 3)
            return;

        int zoneIndex;

        if (zoneChoice == 1)
            zoneIndex = 16;
        else
            zoneIndex = 17;

        int zoneMax = getZoneMaxStage5(zoneIndex);

        /*
            FIRST TIME INTRO ONLY:
            This appears only before the first fight of Stage 5 Zone 1.
            It will not show again after progress[16] becomes 1 or higher.
        */
        if (zoneIndex == 16 && progress[16] == 0)
        {
            system("cls");
            typeText("[RESEARCH LOG - DR. BRICKY]\n\n", 25);

            typeText("\"At last... years of research, countless failures, and endless sacrifices have finally paid off.\"\n\n", 25);
            typeText("\"The Stray Enhancement Project is complete.\"\n\n", 25);
            typeText("\"What the world calls ordinary dogs... I see as untapped potential.\"\n\n", 25);
            typeText("\"Strength. Intelligence. Adaptation.\"\n\n", 25);
            typeText("\"Humanity has spent centuries trying to create the perfect soldier.\"\n\n", 25);
            typeText("\"They were looking in the wrong species.\"\n\n", 25);
            typeText("\"These subjects are no longer strays.\"\n\n", 25);
            typeText("\"They are the future.\"\n\n", 25);
            typeText("\"And soon... the entire world will witness my masterpiece.\"\n\n", 25);

            typeText("- Dr. Bricky\n", 25);
            waitForEnter();
        }
        /*
            REPLAY INTRO ONLY:
            This appears only after Zone 1 is already complete.
        */
        else if (progress[zoneIndex] >= zoneMax)
        {
            system("cls");

            if (rand() % 2 == 0)
            {
                typeText("The laboratory remains active...\n", 25);
                typeText("Enhanced subjects continue their patrols.\n", 25);
            }
            else
            {
                typeText("The Blacksite grows quieter...\n", 25);
                typeText("But the experiments are far from over.\n", 25);
            }

            waitForEnter();
        }

        Dog enemy;
        createEnemy(&enemy);
        enemy.zoneType = ZONE_MUTANT;

        int i;

        if (progress[zoneIndex] >= zoneMax)
        {
            i = chooseReplayEnemyIndex(zoneIndex, progress, 0);
        }
        else
        {
            i = progress[zoneIndex];
        }

        loadStage5Enemies(&enemy, zoneIndex, i);

        if (i == zoneMax - 1)
        {
            enemy.attack += 20;
            enemy.defense += 16;
            enemy.speed += 12;
            enemy.maxHP += 90;
            enemy.hp = enemy.maxHP;
        }

        if (player->hp <= 0)
        {
            system("cls");
            typeText("Recover HP before entering the Blacksite Laboratory!\n", 25);
            waitForEnter();
            continue;
        }

        /*
            ALPHA-X BOSS INTRO:
            This appears when the fourth enemy is selected.
        */
        if (zoneIndex == 16 && i == 3)
        {
            system("cls");
            typeText("Dr. Bricky: So you made it this far...\n", 25);
            typeText("Dr. Bricky: Impressive.\n", 25);
            typeText("Dr. Bricky: Allow me to introduce my masterpiece.\n", 25);
            typeText("Dr. Bricky: Alpha-X... awaken.\n\n", 25);

            typeText("Alpha-X steps out of the containment chamber.\n", 25);
            typeText("Its eyes lock onto you.\n", 25);

            waitForEnter();
        }
        if (zoneIndex == 17 && i == 3)
        {
            system("cls");

            typeText("Warning...\n",25);
            typeText("Containment breach detected.\n",25);
            typeText("Subject LYCAN-REX released.\n\n",25);

            typeText("A massive werewolf-like beast emerges from the darkness.\n",25);

            waitForEnter();
        }

        int result = battleWithEnemyIndex(player, zoneIndex, progress, i);

        if (result == 0)
            continue;

        if (result == 1)
        {
            if (zoneIndex == 16 && progress[16] < zoneMax)
            {
                printf("\n[DATA LOG]: Enhanced stray contained.");
                printf("\nZone Progress: %d/%d\n", progress[16], zoneMax);
                waitForEnter();
            }
            else if (zoneIndex == 17 && progress[17] < zoneMax)
            {
                printf("\n[DATA LOG]: Feral mutation contained.");
                printf("\nZone Progress: %d/%d\n", progress[17], zoneMax);
                waitForEnter();
            }

            if (zoneIndex == 16 && progress[16] >= 4)
            {
                system("cls");
                typeText("ZONE 1: ENHANCED STRAYS COMPLETE\n\n", 20);
                typeText("If the old Back Alley strays became this strong...\n", 28);
                typeText("what else is waiting deeper inside the laboratory?\n", 28);
                waitForEnter();
            }

            if (zoneIndex == 17 && progress[17] >= 4)
            {
                system("cls");
                typeText("ZONE 2: FERAL MUTATION WARD COMPLETE\n\n", 20);
                typeText("These were no longer ordinary strays...\n", 28);
                typeText("their instincts had evolved into something savage.\n", 28);
                waitForEnter();
            }
        }

        if (result == 2)
        {
            system("cls");
            char *defeatMsg[] =
                {
                    "Subject overpowered the intruder...\n",
                    "Enhanced combat instincts confirmed...\n",
                    "Blacksite security remains active...\n",
                    "Old strays are no longer ordinary enemies...\n",
                    "The laboratory records another failed entry...\n"};

            int msg = rand() % 5;
            typeText(defeatMsg[msg], 25);
            waitForEnter();
        }
    }
}
