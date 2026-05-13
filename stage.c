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

    // progress: 1 = locked, 2 = unlocked, 3 = completed
    static int progress[3] = {3, 3, 0};

    while (1)
    {
        system("cls");

        printf("=== SELECT STAGE ===\n\n");

        printf("1. Urban Strays\n");

        if (progress[0] >= 3)
            printf("2. Wild Territory\n");
        else
            printf("2. Wild Territory (Locked)\n");

        if (progress[1] >= 3)
            printf("3. Military Zone\n");
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
                printf("Stage 2 is locked!\n");
                waitForEnter();
                continue;
            }

            runStage2(player, progress);
        }
        else if (stageChoice == 3)
        {
            if (progress[1] < 3)
            {
                printf("Military Zone is locked!\n");
                waitForEnter();
                continue;
            }

            runStage3(player, progress);
        }
    }
}