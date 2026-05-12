#include <stdio.h>
#include <string.h>
#include "enemy.h"   // siguro nandito yung Dog struct + createEnemy()

void loadStage1Enemies(Dog *enemy, int zoneIndex, int i)
{
    // reset base stats muna
    createEnemy(enemy);

    // -------------------------
    // ZONE 0: Back Alley
    // -------------------------
    if (zoneIndex == 0)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Skinny Stray");
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Scrap Fighter");
            enemy->attack += 3;
            enemy->defense += 2;
        }
        else
        {
            strcpy(enemy->name, "Alley Alpha");
            enemy->attack += 6;
            enemy->defense += 4;
            enemy->maxHP += 20;
        }
    }

    // -------------------------
    // ZONE 1: Junkyard
    // -------------------------
    else if (zoneIndex == 1)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Rust Hound");
            enemy->defense += 3;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Guard Dog");
            enemy->defense += 5;
        }
        else
        {
            strcpy(enemy->name, "Iron Jaw");
            enemy->defense += 8;
            enemy->maxHP += 25;
        }
    }

    // -------------------------
    // ZONE 2: Abandoned Block
    // -------------------------
    else if (zoneIndex == 2)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Night Stray");
            enemy->speed += 3;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Sneak Biter");
            enemy->accuracy += 5;
        }
        else
        {
            strcpy(enemy->name, "Street King");
            enemy->speed += 5;
            enemy->attack += 5;
        }
    }

    // -------------------------
    // fallback (kung mali index)
    // -------------------------
    else
    {
        strcpy(enemy->name, "Unknown Dog");
    }
}