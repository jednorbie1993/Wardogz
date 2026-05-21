#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "enemy.h"
#include "../cinematic.h"
#include "../battle.h"

void loadStage1Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);

    enemy->zoneType = ZONE_CITY;
    enemy->personalityType = PERSONALITY_NORMAL;

    if (zoneIndex == 0)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Skinny Stray");
            enemy->personalityType = PERSONALITY_WEAK;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Scrap Fighter");
            enemy->attack += 3;
            enemy->defense += 2;
            enemy->personalityType = PERSONALITY_DESPERATE;
        }
        else
        {
            strcpy(enemy->name, "Alley Alpha");
            enemy->attack += 6;
            enemy->defense += 4;
            enemy->maxHP += 20;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_ALPHA;
        }
    }
    else if (zoneIndex == 1)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Rust Hound");
            enemy->defense += 3;
            enemy->personalityType = PERSONALITY_TANK;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Guard Dog");
            enemy->defense += 5;
            enemy->personalityType = PERSONALITY_TANK;
        }
        else
        {
            strcpy(enemy->name, "Iron Jaw");
            enemy->defense += 8;
            enemy->maxHP += 25;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_TANK;
        }
    }
    else if (zoneIndex == 2)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Night Stray");
            enemy->speed += 3;
            enemy->personalityType = PERSONALITY_NORMAL;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Sneak Biter");
            enemy->accuracy += 5;
            enemy->personalityType = PERSONALITY_DESPERATE;
        }
        else
        {
            strcpy(enemy->name, "Street King");
            enemy->speed += 5;
            enemy->attack += 5;
            enemy->maxHP += 15;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_ALPHA;
        }
    }
    else
    {
        strcpy(enemy->name, "Unknown Dog");
        enemy->personalityType = PERSONALITY_NORMAL;
    }
}

int handleStage1EnemyBehavior(Dog *player, Dog *enemy, int *enemyDamage)
{
    if (enemy->personalityType == PERSONALITY_ALPHA)
    {
        *enemyDamage += 6;

        if (rand() % 100 < 20)
        {
            printf("\n");
            typeText(enemy->name, 30);
            typeText(" is ENRAGED!\n", 30);

            *enemyDamage += 8;

            waitForEnter();

            system("cls");
            displayBattleStatus(*player, *enemy);
        }
    }
    else if (enemy->personalityType == PERSONALITY_TANK)
    {
        *enemyDamage -= 2;

        if (rand() % 100 < 30)
        {
            printf("\nEnemy HARDENED!\n");

            *enemyDamage = (*enemyDamage * 70) / 100;

            waitForEnter();

            system("cls");
            displayBattleStatus(*player, *enemy);
        }
    }
    else if (enemy->personalityType == PERSONALITY_DESPERATE)
    {
        if (enemy->hp < enemy->maxHP / 2)
        {
            *enemyDamage += 5;

            printf("\nEnemy is DESPERATE!\n");

            waitForEnter();

            system("cls");
            displayBattleStatus(*player, *enemy);
        }
    }
    else if (enemy->personalityType == PERSONALITY_WEAK)
    {
        *enemyDamage -= 2;
    }

    int moveType = rand() % 3;
    char *moveName = "Attack";

    if (moveType == 0)
    {
        *enemyDamage += 5;
        moveName = "Bite";
    }
    else if (moveType == 1)
    {
        *enemyDamage += 3;
        moveName = "Scratch";
    }
    else
    {
        *enemyDamage += 8;
        moveName = "Lock Jaw";
    }

    printf("\n");

    typeText(enemy->name, 25);
    typeText(" used ", 20);
    typeText(moveName, 35);
    printf("!\n");

    cinematicDots("Enemy attacking");

    return 1;
}