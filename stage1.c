#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage1.h"
#include "battle.h"
#include "dog.h"
#include "cinematic.h"
#include "enemies/enemy.h"

void runStage1(Dog *player, int progress[])
{
    int zoneChoice;
    char input[10];

    while (1)
    {
        system("cls");

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

        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            printf("Please select a number.\n");
            waitForEnter();
            continue;
        }

        zoneChoice = atoi(input);

        if (zoneChoice < 1 || zoneChoice > 4)
        {
            printf("Invalid choice! Select 1-4 only.\n");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 4)
            return;

        // LOCK CHECKS
        if (zoneChoice == 2 && progress[0] < 3)
        {
            printf("Finish Zone 1 first!\n");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 3 && progress[1] < 3)
        {
            printf("Finish Zone 2 first!\n");
            waitForEnter();
            continue;
        }

        int zoneIndex = zoneChoice - 1;

        // CREATE ENEMY
        Dog enemy;
        createEnemy(&enemy);

        int maxEnemies = 3;
        int i;

        // =========================
        // REPLAY MODE
        // =========================

        if (progress[zoneIndex] >= maxEnemies)
        {
            printf("\n");

            int enemyType = rand() % maxEnemies;

            Dog tempEnemy;
            createEnemy(&tempEnemy);

            loadStage1Enemies(&tempEnemy, zoneIndex, enemyType);

            char *verbs[] = {
                "showed",
                "appeared",
                "arrived",
                "emerged"};

            int verb = rand() % 4;

            printf("%s %s\n\n", tempEnemy.name, verbs[verb]);

            // REPLAY QUOTES
            int replayLine = rand() % 4;

            switch(replayLine)
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
            {
                printf(" (REPLAY MODE)\n");
            }

            waitForEnter();

            // ELITE CHANCE
            if (rand() % 100 < 25)
                i = maxEnemies;
            else
                i = rand() % maxEnemies;
        }
        else
        {
            i = progress[zoneIndex];
        }

        // =========================
        // ENEMY SETUP
        // =========================

        loadStage1Enemies(&enemy, zoneIndex, i);

        // ELITE ENEMY
        if (i == maxEnemies)
        {
            strcpy(enemy.name, "Elite Stray");

            enemy.attack += 10;
            enemy.speed += 10;
            enemy.maxHP += 30;
            enemy.hp = enemy.maxHP;
        }

        // NORMAL ENCOUNTER
        if (progress[zoneIndex] < 3)
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
        // BOSS INTRO SCENES
        // =========================

        if (zoneIndex == 0 && progress[zoneIndex] == 2)
        {
            system("cls");

            typeText("Heavy footsteps echo through the alley.\n", 25);
            typeText("The Alley Alpha finally appears.\n\n", 25);

            typeText("Alley Alpha:\n", 30);
            typeText("\"This territory belongs to ME.\"\n", 30);

            waitForEnter();
        }

        else if (zoneIndex == 1 && progress[zoneIndex] == 2)
        {
            system("cls");

            typeText("Metal scraps rattle in the darkness.\n", 25);
            typeText("A massive dog steps out from the junkyard.\n\n", 25);

            typeText("Iron Jaw:\n", 30);
            typeText("\"Scrap or flesh... everything breaks.\"\n", 30);

            waitForEnter();
        }

        else if (zoneIndex == 2 && progress[zoneIndex] == 2)
        {
            system("cls");

            typeText("The abandoned block falls completely silent.\n", 25);
            typeText("A terrifying presence approaches slowly.\n\n", 25);

            typeText("Street King:\n", 30);
            typeText("\"Only one king rules these streets.\"\n", 30);

            waitForEnter();
        }

        // =========================
        // BATTLE
        // =========================

        int result = battle(player, zoneIndex, progress);

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
    }
}