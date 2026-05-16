#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "dog.h"
#include "cinematic.h"

void startStage(Dog *player)
{
    int stageChoice;

    // progress: Stage1(0-3), Stage2(5-7), Stage3(8-11)
    static int progress[12] = {3,3,3,3,0,0,0,4,0,0,0,0};

    while (1)
    {
        system("cls");

        printf("=== SELECT STAGE ===\n\n");

        printf("1. Urban Strays (COMPLETED)\n");

        if (progress[0] >= 3)
            printf("2. Wild Territory (%d/4)\n", progress[7]);
        else
            printf("2. Wild Territory (Locked)\n");

        if (progress[7] >= 4)
            printf("3. Military Zone (UNLOCKED)\n");
        else
            printf("3. Military Zone (Locked)\n");

        printf("4. Back\n\n");
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

        if (stageChoice < 1 || stageChoice > 4)
        {
            printf("Invalid choice! Select 1-4 only.\n");
            waitForEnter();
            continue;
        }

        if (stageChoice == 4)
            return;

        if (stageChoice == 1)
        {
            runStage1(player, progress);
        }
        else if (stageChoice == 2)
        {
            if (progress[0] < 3)
            {
                printf("Complete Urban Strays first!\n");
                waitForEnter();
                continue;
            }
            runStage2(player, progress);
        }
        else if (stageChoice == 3)
        {
            if (progress[7] < 4)
            {
                printf("Complete Wild Territory first!\n");
                waitForEnter();
                continue;
            }
            runStage3(player, progress);
        }
    }
}