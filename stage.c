#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stage.h"
#include "dog.h"

void startStage(Dog *player)
{
    int stageChoice;
    int zoneChoice;

    // 🔥 FIXED: Global or persistent progress (choose one)
    static int progress[8] = {3, 3, 3, 3, 3, 3, 4, 4}; // Expanded for Stage 2: indices 3,4,5

    while (1)
    {
        system("cls");
        printf("=== SELECT STAGE ===\n");
        printf("1. Urban Strays\n");
        
        if (progress[0] >= 3) // Unlock Stage 2 after completing first zone of Stage 1
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

        // STAGE 1: Urban Strays
        if (stageChoice == 1)
        {
            // ZONE SELECTION LOOP FOR STAGE 1
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

                // LOCK CHECK FOR STAGE 1
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

                // Create enemy BEFORE battle
                Dog enemy;
                createEnemy(&enemy);
                int i = progress[zoneIndex];
                if (i >= 3)
                    i = 2;
                setEnemyByZone(&enemy, zoneIndex, i);

                printf("\nFighting: %s", enemy.name);
                if (progress[zoneIndex] >= 3)
                    printf(" (REPLAY MODE)\n");
                else
                    printf("\n");
                waitForEnter();

                if (player->hp <= 0)
                {
                    system("cls");
                    typeText("You must rest before you battle again!\n", 25);
                    waitForEnter();
                    continue;
                }

                int result = battle(player, zoneIndex, progress);

                if (result == 0)
                    continue;

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
        // STAGE 2: Wild Territory
        else if (stageChoice == 2)
        {
            // ZONE SELECTION LOOP FOR STAGE 2
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
                    break;

                // LOCK CHECK FOR STAGE 2
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

                int zoneIndex = zoneChoice + 2; // Stage 2 zones: 3,4,5

                // Create enemy BEFORE battle (same enemies but with new skills)
                Dog enemy;
                createEnemy(&enemy);
                int i = progress[zoneIndex];

                // Zone-specific caps
                if (zoneIndex == 5) // Bloodfang Ravine (0/2)
                {
                    if (i >= 2)
                        i = 1;
                }
                else if (zoneIndex == 6 || zoneIndex == 7) // Alpha Trial + Mountain Den (0/4)
                {
                    if (i >= 4)
                        i = 3;
                }
                else // normal zones (0/3)
                {
                    if (i >= 3)
                        i = 2;
                }
                setEnemyByZone(&enemy, zoneIndex, i);

                printf("\nFighting: %s", enemy.name);
                if ((zoneIndex == 5 && progress[zoneIndex] >= 2) || 
                    ((zoneIndex == 6 || zoneIndex == 7) && progress[zoneIndex] >= 4) ||
                    (zoneIndex <= 4 && progress[zoneIndex] >= 3))
                printf(" (REPLAY MODE)\n");
                else
                    printf("\n");
                    waitForEnter();

                if (player->hp <= 0)
                {
                    system("cls");
                    typeText("You must rest before you battle again!\n", 25);
                    waitForEnter();
                    continue;
                }

                int result = battle(player, zoneIndex, progress);

                if (result == 0)
                    continue;

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
    }
}