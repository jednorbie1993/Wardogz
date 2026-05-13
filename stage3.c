#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage3.h"
#include "battle.h"
#include "dog.h"
#include "cinematic.h"
#include "enemies/enemy.h"
#include "enemies/enemy_stage3.h"

void runStage3(Dog *player, int progress[])
{
    int zoneChoice;
    char input[10];

    while (1)
    {
        system("cls");

        printf("=== STAGE 3: MILITARY ZONE ===\n\n");

        printf("1. Military Outpost (%d/2)\n", progress[8]);

        if (progress[8] >= 2)
            printf("2. Tactical Training Grounds (%d/4)\n", progress[9]);
        else
            printf("2. Tactical Training Grounds (Locked)\n");

        if (progress[9] >= 4)
            printf("3. Sniper Valley (%d/4)\n", progress[10]);
        else
            printf("3. Sniper Valley (Locked)\n");

        if (progress[10] >= 4)
            printf("4. Commander Base (%d/3)\n", progress[11]);
        else
            printf("4. Commander Base (Locked)\n");

        printf("5. Back\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            printf("Please select a number.\n");
            waitForEnter();
            continue;
        }

        zoneChoice = atoi(input);

        if (zoneChoice < 1 || zoneChoice > 5)
        {
            printf("Invalid choice! Select 1-5 only.\n");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 5)
            return;

        // =========================
        // ZONE INDEX (OFFSET AFTER STAGE 2)
        // =========================
        int zoneIndex = zoneChoice + 7;

        // =========================
        // LOCK CHECKS
        // =========================
        if (zoneChoice == 2 && progress[8] < 2)
        {
            printf("Finish Zone 1 first!\n");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 3 && progress[9] < 4)
        {
            printf("Finish Zone 2 first!\n");
            waitForEnter();
            continue;
        }

        if (zoneChoice == 4 && progress[10] < 4)
        {
            printf("Finish Zone 3 first!\n");
            waitForEnter();
            continue;
        }

        // =========================
        // CREATE ENEMY
        // =========================
        Dog enemy;
        createEnemy(&enemy);

        enemy.zoneType = ZONE_MILITARY;

        int maxEnemies = 2;

        if (zoneIndex == 9 || zoneIndex == 10)
            maxEnemies = 4;

        if (zoneIndex == 11)
            maxEnemies = 3;

        int i;

        // =========================
        // REPLAY MODE (MILITARY INTEL FILES)
        // =========================
        if (progress[zoneIndex] >= maxEnemies)
        {
            printf("\n");

            int enemyType = rand() % maxEnemies;

            Dog tempEnemy;
            createEnemy(&tempEnemy);

            loadStage3Enemies(&tempEnemy, zoneIndex, enemyType);

            char *intelLog[] = {
                "Enemy patrol pattern recorded.",
                "Tactical movement observed.",
                "Squad formation detected.",
                "Commander response simulated."
            };

            int log = rand() % 4;

            printf("%s appeared\n\n", tempEnemy.name);
            printf("[MILITARY INTEL]: %s\n", intelLog[log]);

            if (systemLog)
                printf(" (REPLAY MODE)\n");

            waitForEnter();

            // elite chance (commander sighting)
            if (rand() % 100 < 20)
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
        loadStage3Enemies(&enemy, zoneIndex, i);

        // =========================
        // ELITE COMMANDER UNIT
        // =========================
        if (i == maxEnemies)
        {
            strcpy(enemy.name, "COMMANDER UNIT");

            enemy.attack += 20;
            enemy.defense += 15;
            enemy.speed += 10;
            enemy.maxHP += 60;
            enemy.hp = enemy.maxHP;
        }

        // =========================
        // INTRO FIGHT
        // =========================
        if (progress[zoneIndex] < maxEnemies)
        {
            printf("\nENGAGING: %s\n", enemy.name);
            waitForEnter();
        }

        // =========================
        // PLAYER CHECK
        // =========================
        if (player->hp <= 0)
        {
            system("cls");
            typeText("You must recover before re-engaging military forces!\n", 25);
            waitForEnter();
            continue;
        }

        // =========================
        // BOSS INTRO
        // =========================
        int isBossFight = (progress[zoneIndex] == maxEnemies - 1);

        if (zoneIndex == 11 && isBossFight)
        {
            system("cls");

            typeText("Surveillance systems activate...\n", 25);
            typeText("A high-ranking commander steps forward.\n\n", 25);

            typeText("COMMANDER AI:\n", 30);
            typeText("\"Order is absolute. Resistance is irrelevant.\"\n", 30);

            waitForEnter();
        }

        // =========================
        // BATTLE
        // =========================
        int result = battle(player, zoneIndex, progress);

        if (result == 0)
            continue;

        // =========================
        // ESCAPE / SURRENDER
        // =========================
        if (result == 2)
        {
            system("cls");

            int outro = rand() % 4;

            printf("\n");

            switch (outro)
            {
                case 0:
                    typeText("Military tactics overwhelmed me...\n", 25);
                    typeText("Need to rethink strategy.\n", 25);
                    break;

                case 1:
                    typeText("Their coordination is insane...\n", 25);
                    typeText("I barely escaped.\n", 25);
                    break;

                case 2:
                    typeText("That commander-level pressure...\n", 25);
                    typeText("Too dangerous.\n", 25);
                    break;

                case 3:
                    typeText("This is no longer wild territory...\n", 25);
                    typeText("It's war.\n", 25);
                    break;
            }

            waitForEnter();
        }
    }
}