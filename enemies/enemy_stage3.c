#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../dog.h"

#include "enemy_stage3.h"


void loadStage3Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);
    enemy->numSkills = 4;
    enemy->zoneType = ZONE_MILITARY;

    if (zoneIndex == 3 && i > 1)
    i = 1;

    if (zoneIndex == 4 && i > 3)
    i = 3;
    // =========================
    // ZONE 1: MILITARY OUTPOST
    // =========================
    if (zoneIndex == 3)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Rookie Soldier");
            enemy->attack += 3;
            enemy->defense += 2;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Field Scout");
            enemy->attack += 4;
            enemy->speed += 3;
        }
    }

    // =========================
    // ZONE 2: MILITARY BASE
    // =========================
    else if (zoneIndex == 4)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Sergeant Unit");
            enemy->attack += 5;
            enemy->defense += 4;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Sniper Unit");
            enemy->attack += 7;
            enemy->speed += 2;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Heavy Gunner");
            enemy->attack += 6;
            enemy->defense += 6;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Commander AI");
            enemy->attack += 8;
            enemy->speed += 4;
            enemy->defense += 5;
        }
    }

    setEnemySkillsMilitary(enemy, zoneIndex);
}

int useSelfDestruct(Dog *user, Dog *target)
{
    if (user->hp > (user->maxHP * 0.2))
    {
        printf("%s tried Self Destruct but failed!\n", user->name);
        return 0;
    }

    int dmg = user->attack * 3;

    target->hp -= dmg;
    user->hp = 0;

    printf("%s SELF DESTRUCT! MASSIVE EXPLOSION -%d\n", user->name, dmg);

    return dmg;
}

int usePrecisionShot(Dog *user, Dog *target)
{
    int dmg = user->attack * 1.4 + (rand() % 5);

    target->hp -= dmg;

    printf("%s uses Precision Shot! -%d\n", user->name, dmg);

    return dmg;
}

int useTacticalGuard(Dog *user, Dog *target)
{
    user->defense += 5;
    user->guardTurns = 3;

    printf("%s raises Tactical Guard!\n", user->name);

    return 0;
}

int useReinforcement(Dog *user, Dog *target)
{
    int heal = 10 + (rand() % 6);

    user->hp += heal;

    printf("%s calls Reinforcements! +%d HP\n", user->name, heal);

    return heal;
}

void setEnemySkillsMilitary(Dog *enemy, int zoneIndex)
{
    enemy->skills[0].id = SKILL_PRECISION_SHOT;
    strcpy(enemy->skills[0].name, "Precision Shot");
    enemy->skills[0].power = 16;

    enemy->skills[1].id = SKILL_TACTICAL_GUARD;
    strcpy(enemy->skills[1].name, "Tactical Guard");
    enemy->skills[1].power = 0;

    enemy->skills[2].id = SKILL_REINFORCEMENT;
    strcpy(enemy->skills[2].name, "Reinforcement");
    enemy->skills[2].power = 0;

    enemy->skills[3].id = SKILL_SELF_DESTRUCT;
    strcpy(enemy->skills[3].name, "Self Destruct");
    enemy->skills[3].power = 50;

    enemy->numSkills = 4;

    // Military buff scaling
    enemy->attack += 2;
    enemy->defense += 2;
    enemy->speed += 1;
}