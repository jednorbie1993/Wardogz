#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dog.h"
#include <windows.h>

void enemyAttack(Dog *player, Dog *enemy, int *defending)
{
    printf("\n--- ENEMY TURN ---\n");

    // ================= BASE DAMAGE =================
    int enemyDamage = (enemy->attack / 6) + 4;

    // ================= BEHAVIOR SYSTEM =================
    if (strstr(enemy->name, "Alpha") || strstr(enemy->name, "King"))
    {
        enemyDamage += 6;

        if (rand() % 100 < 20)
        {
            printf("Enemy is enraged!\n");
            enemyDamage += 8;
        }
    }

    if (strstr(enemy->name, "Iron") || strstr(enemy->name, "Guard"))
    {
        enemyDamage -= 2;

        if (rand() % 100 < 30)
        {
            printf("Enemy hardened!\n");
            enemyDamage = (enemyDamage * 70) / 100;
        }
    }

    if (strstr(enemy->name, "Scrap") || strstr(enemy->name, "Fighter"))
    {
        if (enemy->hp < enemy->maxHP / 2)
        {
            enemyDamage += 5;
            printf("Enemy is desperate!\n");
        }
    }

    if (strstr(enemy->name, "Skinny") || strstr(enemy->name, "Stray"))
    {
        enemyDamage -= 2;
    }

    // ================= MOVE =================
    int move = rand() % 3;
    char *moveName = "Attack";

    if (move == 0)
    {
        enemyDamage += 5;
        moveName = "Bite";
    }
    else if (move == 1)
    {
        enemyDamage += 3;
        moveName = "Scratch";
    }
    else
    {
        enemyDamage += 8;
        moveName = "Lock Jaw";
    }

    printf("Enemy used %s...\n", moveName);

    printf("Attacking");
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(120);
    }
    printf("\n");

    // ================= FINAL TUNING =================
    enemyDamage += rand() % 6;
    enemyDamage -= player->defense / 25;

    // 🔥 IMPORTANT SAFETY CLAMP (CRITICAL FIX)
    if (enemyDamage < 1)
        enemyDamage = 1;

    // ================= HIT SYSTEM =================
    int dodgeChance = player->speed * 2;
    int finalAccuracy = enemy->accuracy - dodgeChance;

    if (finalAccuracy < 70) finalAccuracy = 70;
    if (finalAccuracy > 95) finalAccuracy = 95;

    int roll = rand() % 100;

    if (roll < finalAccuracy)
    {
        // ================= DEFEND SYSTEM =================
        if (*defending)
        {
            int counterChance = player->intelligence / 2;
            if (counterChance > 60) counterChance = 60;

            int counterRoll = rand() % 100;

            if (counterRoll < counterChance)
            {
                int counterDamage = player->attack + (player->intelligence / 10);

                printf("You countered the attack!\n");
                printf("Counter Damage: %d\n", counterDamage);

                enemy->hp -= counterDamage;
                enemy->hp = clamp(enemy->hp);
            }
            else
            {
                enemyDamage = (enemyDamage * 60) / 100;

                player->hp -= enemyDamage;
                player->hp = clamp(player->hp);

                printf("You defended! Damage reduced!\n");
                printf("Enemy dealt %d damage!\n", enemyDamage);
            }

            *defending = 0;
        }
        else
        {
            player->hp -= enemyDamage;
            player->hp = clamp(player->hp);

            printf("Enemy dealt %d damage!\n", enemyDamage);
        }
    }
    else
    {
        printf("Enemy missed!\n");
    }

    // ================= OPTIONAL DEBUG =================
    if (systemLog)
    {
        printf("[ENEMY DMG DEBUG] %d\n", enemyDamage);
    }
}