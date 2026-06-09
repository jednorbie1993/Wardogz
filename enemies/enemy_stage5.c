#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../dog.h"
#include "enemy_stage5.h"
#include "../replay_system.h"

void loadStage5Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);

    enemy->zoneType = ZONE_BIOLAB;
    enemy->personalityType = PERSONALITY_ALPHA;
    enemy->numSkills = 4;

    if (zoneIndex == 16 && i > 3)
        i = 3;

    if (zoneIndex == 16)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Razorfang");
            enemy->attack += 22;
            enemy->defense += 12;
            enemy->speed += 14;
            enemy->maxHP += 55;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Night Howler");
            enemy->attack += 18;
            enemy->defense += 8;
            enemy->speed += 25;
            enemy->maxHP += 45;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Ironjaw");
            enemy->attack += 20;
            enemy->defense += 25;
            enemy->speed += 5;
            enemy->maxHP += 80;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Alpha-X");
            enemy->attack += 35;
            enemy->defense += 22;
            enemy->speed += 20;
            enemy->maxHP += 120;
        }

        enemy->hp = enemy->maxHP;
    }

    enemy->skills[0].id = SKILL_REINFORCED_BITE;
    strcpy(enemy->skills[0].name, "Reinforced Bite");
    enemy->skills[0].power = 24;

    enemy->skills[1].id = SKILL_COMBAT_RUSH;
    strcpy(enemy->skills[1].name, "Combat Rush");
    enemy->skills[1].power = 20;

    enemy->skills[2].id = SKILL_PREDATOR_INSTINCT;
    strcpy(enemy->skills[2].name, "Predator Instinct");
    enemy->skills[2].power = 0;

    enemy->skills[3].id = SKILL_ENHANCED_JAW_CRUSH;
    strcpy(enemy->skills[3].name, "Enhanced Jaw Crush");
    enemy->skills[3].power = 30;

    enemy->numSkills = 4;
}