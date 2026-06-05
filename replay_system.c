#include "replay_system.h"
#include "battle.h"
#include <stdlib.h>
#include <string.h>

int chooseReplayEnemyIndex(int zoneIndex, int progress[])
{
    int maxEnemies = getBattleMaxEnemies(zoneIndex);

    if (progress[zoneIndex] >= maxEnemies)
    {
        if (zoneIndex >= 0 && zoneIndex <= 2)
        {
            if (rand() % 100 < 20)
                return maxEnemies;
        }
        if (zoneIndex >= 3 && zoneIndex <= 7)
        {
            // Stage 2 replay: 25% chance for the secret/elite enemy.
            if (rand() % 100 < 25)
                return maxEnemies;
        }
        else if (zoneIndex >= 8 && zoneIndex <= 15)
        {
            // Stage 3/4 replay: 20% chance for elite replay version.
            if (rand() % 100 < 20)
                return maxEnemies;
        }

        return rand() % maxEnemies;
    }

    return progress[zoneIndex];
}

void applyReplayEliteBonus(Dog *enemy, int zoneIndex, int enemyIndex)
{
    int maxEnemies = getBattleMaxEnemies(zoneIndex);

    if (enemyIndex != maxEnemies)
        return;

    if (zoneIndex >= 0 && zoneIndex <= 2)
    {
        strcat(enemy->name, " Elite");
        enemy->attack += 8;
        enemy->defense += 5;
        enemy->speed += 4;
        enemy->maxHP += 25;
    }
    else if (zoneIndex >= 3 && zoneIndex <= 7)
    {
        strcpy(enemy->name, "Elite Predator");
        enemy->attack += 15;
        enemy->speed += 15;
        enemy->maxHP += 40;
    }
    else if (zoneIndex >= 8 && zoneIndex <= 11)
    {
        strcat(enemy->name, " Elite");
        enemy->attack += 12;
        enemy->defense += 8;
        enemy->speed += 6;
        enemy->maxHP += 35;
    }
    else if (zoneIndex >= 12 && zoneIndex <= 15)
    {
        strcat(enemy->name, " Omega");
        enemy->attack += 15;
        enemy->defense += 10;
        enemy->speed += 8;
        enemy->maxHP += 45;
    }

    enemy->hp = enemy->maxHP;
}