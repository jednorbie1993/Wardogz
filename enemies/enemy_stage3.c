#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../dog.h"
#include "enemy_stage3.h"

void loadStage3Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);
    enemy->numSkills = 6;  // Increased to 6 skills
    enemy->zoneType = ZONE_MILITARY;

    setEnemySkillsMilitary(enemy, zoneIndex);

    // Zone limits
    if (zoneIndex == 8 && i > 1) i = 1;      // Military Outpost (2 enemies)
    if (zoneIndex == 9 && i > 3) i = 3;      // Tactical Grounds (4 enemies)  
    if (zoneIndex == 10 && i > 3) i = 3;     // Sniper Valley (4 enemies)
    if (zoneIndex == 11 && i > 2) i = 2;     // Commander Base (3 enemies)

    // =========================
    // ZONE 1: MILITARY OUTPOST - MILITARY DOGZ
    // =========================
    if (zoneIndex == 8)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Military Dogz Scout");
            enemy->attack += 5;
            enemy->defense += 3;
            enemy->maxHP += 15;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Military Dogz Patrol");
            enemy->attack += 7;
            enemy->speed += 4;
            enemy->defense += 4;
            enemy->maxHP += 20;
            enemy->hp = enemy->maxHP;
        }
    }

    // =========================
    // ZONE 2: TACTICAL TRAINING GROUNDS
    // =========================
    else if (zoneIndex == 9)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Military Dogz Sergeant");
            enemy->attack += 8;
            enemy->defense += 6;
            enemy->maxHP += 25;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Military Dogz Sniper");
            enemy->attack += 10;
            enemy->speed += 5;
            enemy->maxHP += 22;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Military Dogz Gunner");
            enemy->attack += 9;
            enemy->defense += 8;
            enemy->maxHP += 30;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Military Dogz Captain");
            enemy->attack += 12;
            enemy->speed += 6;
            enemy->defense += 7;
            enemy->maxHP += 35;
            enemy->hp = enemy->maxHP;
        }
    }

    // =========================
    // ZONE 3: SNIPER VALLEY
    // =========================
    else if (zoneIndex == 10)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Military Dogz Marksman");
            enemy->attack += 13;
            enemy->speed += 7;
            enemy->maxHP += 28;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Military Dogz Elite Sniper");
            enemy->attack += 15;
            enemy->speed += 8;
            enemy->maxHP += 32;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Military Dogz Spotter");
            enemy->attack += 11;
            enemy->defense += 9;
            enemy->speed += 6;
            enemy->maxHP += 30;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Military Dogz Sharpshooter");
            enemy->attack += 16;
            enemy->speed += 9;
            enemy->defense += 8;
            enemy->maxHP += 38;
            enemy->hp = enemy->maxHP;
        }
    }

    // =========================
    // ZONE 4: COMMANDER BASE
    // =========================
    else if (zoneIndex == 11)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Military Dogz Guard");
            enemy->attack += 14;
            enemy->defense += 10;
            enemy->maxHP += 35;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Military Dogz Lieutenant");
            enemy->attack += 17;
            enemy->speed += 7;
            enemy->defense += 11;
            enemy->maxHP += 40;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Military Dogz Commander");
            enemy->attack += 20;
            enemy->speed += 10;
            enemy->defense += 12;
            enemy->maxHP += 50;
            enemy->hp = enemy->maxHP;
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

// NEW SKILLS
int useBarrageFire(Dog *user, Dog *target)
{
    int dmg = (user->attack * 1.2) + (rand() % 8);
    target->hp -= dmg;
    printf("%s unleashes Barrage Fire! -%d\n", user->name, dmg);
    return dmg;
}

int useMilitaryCharge(Dog *user, Dog *target)
{
    int dmg = user->attack * 1.6;
    target->hp -= dmg;
    user->speed += 3;
    printf("%s charges with Military Force! -%d (Speed +3)\n", user->name, dmg);
    return dmg;
}

void setEnemySkillsMilitary(Dog *enemy, int zoneIndex)
{
    // Core 4 skills
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

    enemy->skills[4].id = SKILL_BARRAGE_FIRE;
    strcpy(enemy->skills[4].name, "Barrage Fire");
    enemy->skills[4].power = 20;

    enemy->skills[4].cooldown = 2; // optional kung may cooldown system ka

    enemy->skills[5].id = SKILL_MILITARY_CHARGE;
    strcpy(enemy->skills[5].name, "Military Charge");
    enemy->skills[5].power = 25;

    enemy->skills[5].cooldown = 3;

    enemy->numSkills = 6;

    // Progressive military buffs per zone
    if (zoneIndex == 8) { // Zone 1
        enemy->attack += 3;
        enemy->defense += 3;
        enemy->speed += 2;
    }
    else if (zoneIndex == 9) { // Zone 2
        enemy->attack += 5;
        enemy->defense += 4;
        enemy->speed += 3;
    }
    else if (zoneIndex == 10) { // Zone 3
        enemy->attack += 7;
        enemy->defense += 5;
        enemy->speed += 4;
    }
    else if (zoneIndex == 11) { // Zone 4 (Strongest)
        enemy->attack += 10;
        enemy->defense += 7;
        enemy->speed += 5;
    }
}