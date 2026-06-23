#include "replay_system.h"
#include "battle.h"
#include <stdlib.h>
#include <string.h>

int chooseReplayEnemyIndex(int zoneIndex, int progress[], int isWildTerritory)
{
    int maxEnemies = getBattleMaxEnemies(zoneIndex);
    static int urbanReplayCount = 0;
    static int wildReplayCount = 0;
    static int militaryReplayCount = 0;
    static int bioReplayCount = 0;
    static int blacksiteReplayCount = 0;

    if (progress[zoneIndex] >= maxEnemies)
    {
        // Back Alley / Urban Strays secret
        if (!isWildTerritory && zoneIndex >= 0 && zoneIndex <= 2)
        {
            urbanReplayCount++;

            if (urbanReplayCount % 10 == 0)
                return SECRET_GRIMFANG_INDEX;

            if (rand() % 100 < 17)
                return SECRET_GRIMFANG_INDEX;

            if (rand() % 100 < 20)
                return maxEnemies;
        }

        // Wild Territory secret kahit anong zone
        if (isWildTerritory)
        {
            wildReplayCount++;

            if (wildReplayCount % 12 == 0)
                return SECRET_DIREMAW_INDEX;

            if (rand() % 100 < 17)
                return SECRET_DIREMAW_INDEX;

            if (rand() % 100 < 20)
                return maxEnemies;
        }

        if (!isWildTerritory && zoneIndex >= 8 && zoneIndex <= 11)
        {
            militaryReplayCount++;

            if (militaryReplayCount % 10 == 0)
                return SECRET_BLACKCLAW_INDEX;

            if (rand() % 100 < 18)
                return SECRET_BLACKCLAW_INDEX;

            if (rand() % 100 < 20)
                return maxEnemies;
        }
        if (!isWildTerritory && zoneIndex >= 12 && zoneIndex <= 15)
        {
            bioReplayCount++;

            if (bioReplayCount % 10 == 0)
                return SECRET_OMEGA_INDEX;

            if (rand() % 100 < 18)
                return SECRET_OMEGA_INDEX;

            if (rand() % 100 < 20)
                return maxEnemies;
        }

        // Stage 5 / Blacksite Laboratory secret
        if (!isWildTerritory && zoneIndex >= 16 && zoneIndex <= 20)
        {
            blacksiteReplayCount++;

            if (blacksiteReplayCount % 12 == 0)
                return SECRET_GRIMFANG_X_INDEX;

            if (rand() % 100 < 18)
                return SECRET_GRIMFANG_X_INDEX;

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
    else if (zoneIndex >= 16 && zoneIndex <= 20)
    {
        strcat(enemy->name, " Blacksite Elite");
        enemy->attack += 20;
        enemy->defense += 14;
        enemy->speed += 12;
        enemy->maxHP += 60;
    }

    enemy->hp = enemy->maxHP;
}