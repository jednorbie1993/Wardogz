#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage.h"
#include "dog.h"

void startStage(Dog *player)
{
    int stageChoice;
    int zoneChoice;

    while (1)
    {
        system("cls");
        printf("=== SELECT STAGE ===\n");
        printf("1. Urban Strays\n");
        printf("2. Wild Territory (Locked)\n");
        printf("3. Back\n");
        printf("Choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            printf("Please select a number.\n");
            waitForEnter();
            continue;
        }

        stageChoice = atoi(input);

        if (stageChoice < 1 || stageChoice > 3)
        {
            printf("Invalid choice! Select 1-3 only.\n");
            waitForEnter();
            continue;
        }

        if (stageChoice == 3)
        {
            system("cls");
            return;
        }

        if (stageChoice != 1)
        {
            printf("Stage locked!\n");
            waitForEnter();
            continue;
        }

        // PROGRESS SYSTEM
        static int progress[3] = {0, 0, 0};

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
                break;

            // LOCK CHECK
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

            Dog enemy;
            createEnemy(&enemy);

            int i = progress[zoneIndex];

            if (i >= 3)
                i = 2;

            setEnemyByZone(&enemy, zoneIndex, i);

            printf("\nFighting: %s\n", enemy.name);

            if (progress[zoneIndex] >= 3)
            {
                printf("(REPLAY MODE)\n");
            }

            // 🔥 IMPORTANT FIX HERE
            battle(player, &enemy);

            // progress update
            if (progress[zoneIndex] < 3)
            {
                progress[zoneIndex]++;
            }

            waitForEnter();
        }
    }
}