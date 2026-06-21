#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../dog.h"
#include "enemy_stage3.h"
#include "../replay_system.h"

// =========================
// BALANCE HELPERS
// =========================
static int capMilitaryDamage(int dmg, int minDmg, int maxDmg)
{
    if (dmg < minDmg)
        dmg = minDmg;

    if (dmg > maxDmg)
        dmg = maxDmg;

    return dmg;
}

static void applyMilitaryDamage(Dog *target, int dmg)
{
    target->hp -= dmg;
    target->hp = clamp(target->hp);
}


void createBlackclaw(Dog *enemy)
{
    createEnemy(enemy);

    strcpy(enemy->name, "Blackclaw");

    enemy->zoneType = ZONE_MILITARY;
    enemy->personalityType = PERSONALITY_ALPHA;

    enemy->attack += 65;
    enemy->defense += 50;
    enemy->speed += 45;
    enemy->maxHP += 210;
    enemy->hp = enemy->maxHP;

    enemy->numSkills = 3;

    enemy->skills[0].id = SKILL_AMBUSH_STRIKE;
    strcpy(enemy->skills[0].name, "Ambush Strike");
    enemy->skills[0].power = 28;

    enemy->skills[1].id = SKILL_PRECISION_SHOT;
    strcpy(enemy->skills[1].name, "Precision Shot");
    enemy->skills[1].power = 18;

    enemy->skills[2].id = SKILL_MILITARY_CHARGE;
    strcpy(enemy->skills[2].name, "Military Charge");
    enemy->skills[2].power = 25;
}

void loadStage3Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);
    
    if (i == SECRET_BLACKCLAW_INDEX)
    {
        createBlackclaw(enemy);
        return;
    }

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
            enemy->attack += 20;
            enemy->defense += 16;
            enemy->maxHP += 75;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Military Dogz Patrol");
            enemy->attack += 24;
            enemy->speed += 14;
            enemy->defense += 18;
            enemy->maxHP += 85;
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
            enemy->attack += 30;
            enemy->defense += 24;
            enemy->maxHP += 110;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Military Dogz Sniper");
            enemy->attack += 34;
            enemy->speed += 22;
            enemy->maxHP += 105;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Military Dogz Gunner");
            enemy->attack += 33;
            enemy->defense += 30;
            enemy->maxHP += 125;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Military Dogz Captain");
            enemy->attack += 38;
            enemy->speed += 24;
            enemy->defense += 28;
            enemy->maxHP += 135;
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
            enemy->attack += 42;
            enemy->speed += 28;
            enemy->maxHP += 145;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Military Dogz Elite Sniper");
            enemy->attack += 46;
            enemy->speed += 32;
            enemy->maxHP += 155;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Military Dogz Spotter");
            enemy->attack += 40;
            enemy->defense += 34;
            enemy->speed += 24;
            enemy->maxHP += 150;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Military Dogz Sharpshooter");
            enemy->attack += 50;
            enemy->speed += 36;
            enemy->defense += 32;
            enemy->maxHP += 170;
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
            enemy->attack += 52;
            enemy->defense += 42;
            enemy->maxHP += 185;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Military Dogz Lieutenant");
            enemy->attack += 58;
            enemy->speed += 30;
            enemy->defense += 46;
            enemy->maxHP += 205;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Military Dogz Commander");
            enemy->attack += 68;
            enemy->speed += 38;
            enemy->defense += 52;
            enemy->maxHP += 240;
            enemy->hp = enemy->maxHP;
        }
    }

    setEnemySkillsMilitary(enemy, zoneIndex);
}
int useAmbushStrike(Dog *user, Dog *target)
{
    int diff = user->attack - target->defense;
    int dmg = 55 + (diff / 10) + (rand() % 11);

    dmg = capMilitaryDamage(dmg, 35, 130);
    applyMilitaryDamage(target, dmg);

    printf("%s uses Ambush Strike! -%d", user->name, dmg);
    return dmg;
}

int useSelfDestruct(Dog *user, Dog *target)
{
    if (user->hp > (user->maxHP * 0.2))
    {
        printf("%s tried Self Destruct but failed!", user->name);
        return 0;
    }

    int dmg = 120 + (user->attack / 12) + (rand() % 21);

    dmg = capMilitaryDamage(dmg, 120, 180);
    applyMilitaryDamage(target, dmg);

    user->hp = 0;

    printf("%s SELF DESTRUCT! MASSIVE EXPLOSION -%d", user->name, dmg);
    return dmg;
}

int usePrecisionShot(Dog *user, Dog *target)
{
    int diff = user->attack - target->defense;
    int dmg = 45 + (diff / 12) + (rand() % 9);

    dmg = capMilitaryDamage(dmg, 28, 110);
    applyMilitaryDamage(target, dmg);

    printf("%s uses Precision Shot! -%d", user->name, dmg);
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
    int heal = 18 + (rand() % 13);

    user->hp += heal;

    if (user->hp > user->maxHP)
        user->hp = user->maxHP;

    printf("%s calls Reinforcements! +%d HP", user->name, heal);
    return heal;
}

// NEW SKILLS
int useBarrageFire(Dog *user, Dog *target)
{
    int diff = user->attack - target->defense;
    int dmg = 38 + (diff / 12) + (rand() % 12);

    dmg = capMilitaryDamage(dmg, 25, 105);
    applyMilitaryDamage(target, dmg);

    printf("%s unleashes Barrage Fire! -%d", user->name, dmg);
    return dmg;
}

int useMilitaryCharge(Dog *user, Dog *target)
{
    int diff = user->attack - target->defense;
    int dmg = 50 + (diff / 10) + (rand() % 10);

    dmg = capMilitaryDamage(dmg, 35, 125);
    applyMilitaryDamage(target, dmg);

    user->speed += 3;

    printf("%s charges with Military Force! -%d (Speed +3)", user->name, dmg);
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
        enemy->attack += 12;
        enemy->defense += 10;
        enemy->speed += 6;
    }
    else if (zoneIndex == 9) { // Zone 2
        enemy->attack += 16;
        enemy->defense += 13;
        enemy->speed += 8;
    }
    else if (zoneIndex == 10) { // Zone 3
        enemy->attack += 20;
        enemy->defense += 16;
        enemy->speed += 10;
    }
    else if (zoneIndex == 11) { // Zone 4 (Strongest)
        enemy->attack += 26;
        enemy->defense += 20;
        enemy->speed += 12;
    }
}