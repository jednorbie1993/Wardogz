#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage.h"
#include "stage1.h"
#include "stage2.h"
#include "dog.h"
#include "cinematic.h"

void startStage(Dog *player)
{
    int stageChoice;

    static int progress[8] = {3, 3, 3, 3, 3, 3, 4, 4};

    while (1)
    {
        system("cls");

        printf("=== SELECT STAGE ===\n");

        printf("1. Urban Strays\n");

        if (progress[0] >= 3)
            printf("2. Wild Territory\n");
        else
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

        if (stageChoice == 1)
        {
            runStage1(player, progress);
        }

        if (stageChoice == 2)
        {
            if (progress[0] < 3)
            {
                printf("Stage 2 is locked!\n");
                waitForEnter();
                continue;
            }

            runStage2(player, progress);
        }
    }
}