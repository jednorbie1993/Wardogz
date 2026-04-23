#include <stdio.h>
#include <stdlib.h>
#include <string.h>   // ⭐ IMPORTANT
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
        stageChoice = atoi(input);

        if (stageChoice == 3)
            return;

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
            printf("1. Back Alley (%d/3)\n", progress[0]);
            printf("2. Junkyard (%s)\n", progress[0] == 3 ? "Unlocked" : "Locked");
            printf("3. Abandoned Block (%s)\n", progress[1] == 3 ? "Unlocked" : "Locked");
            printf("4. Back\n");
            printf("Choice: ");

            fgets(input, sizeof(input), stdin);
            zoneChoice = atoi(input);

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

            // 🔥 SINGLE BATTLE LANG kapag loop ganito while (progress[zoneIndex] < 3)
            if (progress[zoneIndex] < 3)
            {
                Dog enemy;
                createEnemy(&enemy);

                int i = progress[zoneIndex];

                // ===== ZONE 1 =====
                if (zoneIndex == 0)
                {
                    if (i == 0)
                    {
                        strcpy(enemy.name, "Skinny Stray");
                    }
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

                // 👉 IMPORTANT PART NA KULANG MO
                printf("\nFighting: %s\n", enemy.name);
                battle(player);

                progress[zoneIndex]++;
            }
        }
    }
}            