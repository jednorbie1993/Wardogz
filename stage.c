#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "dog.h"
#include "cinematic.h"

void startStage(Dog *player, int progress[])
{
    int stageChoice;

    // progress: Stage1(0-3), Stage2(5-7), Stage3(8-11)
    
    while (1)
    {
        system("cls");
        /*int progress[12] =
        {
            3,3,3,
            3,3,2,4,4,
            2,4,4,3
        };*/
        
        int urbanComplete =
        (progress[0] >= 3) +
        (progress[1] >= 3) +
        (progress[2] >= 3);

    int wildComplete =
        (progress[3] >= 3) +
        (progress[4] >= 3) +
        (progress[5] >= 2) +
        (progress[6] >= 4) +
        (progress[7] >= 4);

    int militaryComplete =
        (progress[8] >= 2) +
        (progress[9] >= 4) +
        (progress[10] >= 4) +
        (progress[11] >= 3);


        printf("=== SELECT STAGE ===\n\n");

        printf("1. Urban Strays (%d/3)\n", urbanComplete);

        if (urbanComplete >= 3)
            printf("2. Wild Territory (%d/5)\n", wildComplete);
        else
            printf("2. Wild Territory (Locked)\n");

        if (wildComplete >= 5)
            printf("3. Military Zone (%d/4)\n", militaryComplete);
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
            if (urbanComplete < 3)
            {
                printf("Complete Urban Strays first!\n");
                waitForEnter();
                continue;
            }
            runStage2(player, progress);
        }
        else if (stageChoice == 3)
        {
            if (wildComplete < 5)
            {
                printf("Complete Wild Territory first!\n");
                waitForEnter();
                continue;
            }
            runStage3(player, progress);
        }
    }
}