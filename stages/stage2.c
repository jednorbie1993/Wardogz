#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage2.h"
#include "../battle.h"
#include "../dog.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"
#include "../replay_system.h"

void runStage2(Dog *player, int progress[])
{
    int zoneChoice;
    char input[10];

    while (1)
    {
        system("cls");

        printf("=== STAGE 2: Wild Territory ===\n");

        printf("1. River Pack Hideout (%d/3)\n", progress[3]);

        if (progress[3] >= 3)
            printf("2. Forest Ambush Grounds (%d/3)\n", progress[4]);
        else
            printf("2. Forest Ambush Grounds (Locked)\n");

        if (progress[4] >= 3)
            printf("3. Bloodfang Ravine (%d/2)\n", progress[5]);
        else
            printf("3. Bloodfang Ravine (Locked)\n");

        if (progress[5] >= 2)
            printf("4. Alpha's Trial Grounds (%d/4)\n", progress[6]);
        else
            printf("4. Alpha's Trial Grounds (Locked)\n");

        if (progress[6] >= 4)
            printf("5. Mountain Pack Den (%d/4)\n", progress[7]);
        else
            printf("5. Mountain Pack Den (Locked)\n");

        printf("6. Back\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            printf("Please select a number.\n");
            waitForEnter();
            continue;
        }

        zoneChoice = atoi(input);

        if (zoneChoice < 1 || zoneChoice > 6)
        {
            printf("Invalid choice! Select 1-6 only.\n");
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
            printf("Finish Zone 1 first!\n");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 3 && progress[4] < 3)
        {
            printf("Finish Zone 2 first!\n");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 4 && progress[5] < 2)
        {
            printf("Finish Zone 3 first!\n");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 5 && progress[6] < 4)
        {
            printf("Finish Zone 4 first!\n");
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
            /*printf("\n");

            int enemyType = rand() % maxEnemies;

            Dog tempEnemy;
            createEnemy(&tempEnemy);

            loadStage2Enemies(&tempEnemy, zoneIndex, enemyType);

            char *verbs[] = {
                "showed",
                "appeared",
                "arrived",
                "emerged"};

            int verb = rand() % 4;

            printf("%s %s\n\n", tempEnemy.name, verbs[verb]);*/

            // REPLAY QUOTES
            int replayLine = rand() % 4;

            printf("\n");

            switch(replayLine)
            {
                case 0:
                    printf("\"The wild never forgets.\"\n");
                    break;

                case 1:
                    printf("\"Another pack rises from the shadows.\"\n");
                    break;

                case 2:
                    printf("\"The forest still hungers.\"\n");
                    break;

                case 3:
                    printf("\"Only the strong survive here.\"\n");
                    break;
            }

            if (systemLog)
            {
                printf(" (REPLAY MODE)\n");
            }

            waitForEnter();

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
            printf("\nFighting: %s\n", enemy.name);
            waitForEnter();
        }

        // PLAYER DEAD CHECK
        if (player->hp <= 0)
        {
            system("cls");

            typeText("You must rest before you battle again!\n", 25);

            waitForEnter();
            continue;
        }

        // =========================
        // BOSS INTRO
        // =========================

        int isBossFight = (progress[zoneIndex] == maxEnemies - 1);

        if (zoneIndex == 5 && isBossFight)
        {
            system("cls");

            typeText("The river current suddenly grows violent.\n", 25);
            typeText("The leader of the wild pack emerges.\n\n", 25);

            typeText("River Alpha:\n", 30);
            typeText("\"The weak drown here.\"\n", 30);

            waitForEnter();
        }

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
            system("cls");

            int outro = rand() % 4;

            printf("\n");

            switch (outro)
            {
                case 0:
                    typeText("These wild dogs are ruthless...\n", 25);
                    typeText("I need to adapt to their style.\n", 25);
                    break;

                case 1:
                    typeText("Grr... their teamwork is insane.\n", 25);
                    typeText("I need new strategies.\n", 25);
                    break;

                case 2:
                    typeText("That pack formation... dangerous.\n", 25);
                    typeText("I barely escaped.\n", 25);
                    break;

                case 3:
                    typeText("Wild territory lives up to its name.\n", 25);
                    typeText("Next time, I'll be ready.\n", 25);
                    break;
            }

            printf("\n");
            waitForEnter();
        }
    }
}