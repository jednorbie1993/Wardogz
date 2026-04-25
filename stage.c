#include <stdio.h>
#include <stdlib.h>
#include <string.h> // ⭐ IMPORTANT
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

        // Enter lang
        if (input[0] == '\n')
        {
            printf("Please select a number.\n");
            waitForEnter();
            continue;
        }

        // convert
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

        // 👉 ZONE SELECT
        static int progress[3] = {0, 0, 0}; // temporary progress

        while (1)
        {
            system("cls");
            printf("=== STAGE 1: Urban Strays ===\n");

            // Zone 1 (always open)
            printf("1. Back Alley (%d/3)\n", progress[0]);

            // Zone 2
            if (progress[0] >= 3)
            {
                printf("2. Junkyard (%d/3)\n", progress[1]);
            }
            else
            {
                printf("2. Junkyard (Locked)\n");
            }

            // Zone 3
            if (progress[1] >= 3)
            {
                printf("3. Abandoned Block (%d/3)\n", progress[2]);
            }
            else
            {
                printf("3. Abandoned Block (Locked)\n");
            }

            printf("4. Back\n");
            printf("Choice: ");

            fgets(input, sizeof(input), stdin);

            // Enter lang
            if (input[0] == '\n')
            {
                printf("Please select a number.\n");
                waitForEnter();
                continue;
            }

            zoneChoice = atoi(input);

            // invalid range
            if (zoneChoice < 1 || zoneChoice > 4)
            {
                printf("Invalid choice! Select 1-4 only.\n");
                waitForEnter();
                continue;
            }

            if (zoneChoice == 4)
                break;

            // 🔒 LOCK CHECK
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

            // 👉 cap for replay
            if (i >= 3)
            {
                i = 2;
            }

            // ===== ZONE 1 =====
            if (zoneIndex == 0)
            {
                if (i == 0)
                    strcpy(enemy.name, "Skinny Stray");
                else if (i == 1)
                {
                    strcpy(enemy.name, "Scrap Fighter");
                    enemy.attack += 3;
                    enemy.defense += 2;
                }
                else
                {
                    strcpy(enemy.name, "Alley Alpha 👑");
                    enemy.attack += 6;
                    enemy.defense += 4;
                    enemy.maxHP += 20;
                }
            }

            // ===== ZONE 2 =====
            else if (zoneIndex == 1)
            {
                if (i == 0)
                {
                    strcpy(enemy.name, "Rust Hound");
                    enemy.defense += 3;
                }
                else if (i == 1)
                {
                    strcpy(enemy.name, "Guard Dog");
                    enemy.defense += 5;
                }
                else
                {
                    strcpy(enemy.name, "Iron Jaw 👑");
                    enemy.defense += 8;
                    enemy.maxHP += 25;
                }
            }

            // ===== ZONE 3 =====
            else if (zoneIndex == 2)
            {
                if (i == 0)
                {
                    strcpy(enemy.name, "Night Stray");
                    enemy.speed += 3;
                }
                else if (i == 1)
                {
                    strcpy(enemy.name, "Sneak Biter");
                    enemy.accuracy += 5;
                }
                else
                {
                    strcpy(enemy.name, "Street King 👑");
                    enemy.speed += 5;
                    enemy.attack += 5;
                }
            }

            enemy.hp = enemy.maxHP;

            printf("\nFighting: %s\n", enemy.name);

            // 👉 replay label
            if (progress[zoneIndex] >= 3)
            {
                printf("(REPLAY MODE)\n");
            }

            battle(player);

            // 👉 progress update (ONLY ONCE)
            if (progress[zoneIndex] < 3)
            {
                progress[zoneIndex]++;
            }

            // 👉 pause para walang double enter / auto loop
            
        }
    }
}