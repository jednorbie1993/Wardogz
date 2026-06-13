#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../dog.h"
#include "enemy_stage5.h"
#include "../replay_system.h"

void setEnhancedStraySkills(Dog *enemy)
{
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

void setRazorfangSkills(Dog *enemy)
{
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

void loadStage5Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);

    enemy->zoneType = ZONE_MUTANT;
    enemy->personalityType = PERSONALITY_ALPHA;
    enemy->numSkills = 4;

    if (i > 3)
        i = 3;

    // =========================
    // ZONE 1: ENHANCED STRAYS
    // =========================
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

        setEnhancedStraySkills(enemy);
    }

    // =========================
    // ZONE 2: FERAL MUTATION WARD
    // =========================
    else if (zoneIndex == 17)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Nightmaw");
            enemy->attack += 24;
            enemy->defense += 10;
            enemy->speed += 20;
            enemy->maxHP += 60;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Bloodhowl");
            enemy->attack += 28;
            enemy->defense += 12;
            enemy->speed += 16;
            enemy->maxHP += 80;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Ravagefang");
            enemy->attack += 32;
            enemy->defense += 18;
            enemy->speed += 18;
            enemy->maxHP += 100;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Lycan Rex");
            enemy->attack += 40;
            enemy->defense += 25;
            enemy->speed += 25;
            enemy->maxHP += 160;
        }

        setWildTerritorySkills(enemy);
    }

    enemy->hp = enemy->maxHP;
    enemy->numSkills = 4;
}

int useReinforcedBite(Dog *user, Dog *target)
{
    int hits = (rand() % 3) + 1;
    int total = 0;

    printf("%s uses Reinforced Bite!\n", user->name);

    for (int i = 0; i < hits; i++)
    {
        int dmg = (user->attack * 1.1) + 6 + (rand() % 5);

        if (target->defense > 0)
            dmg -= target->defense / 45;

        if (dmg < 2)
            dmg = 2;

        target->hp -= dmg;
        total += dmg;

        printf("Hit %d! -%d HP\n", i + 1, dmg);
    }

    printf("Total damage: -%d HP\n", total);
    return total;
}

int useCombatRush(Dog *user, Dog *target)
{
    int dmg = user->attack + 10 + (rand() % 8);

    if (user->speed > target->speed)
    {
        dmg += 10;
        printf("%s outsped the target!\n", user->name);
    }

    if (target->defense > 0)
        dmg -= target->defense / 40;

    if (dmg < 3)
        dmg = 3;

    target->hp -= dmg;

    printf("%s uses Combat Rush! -%d HP\n", user->name, dmg);
    return dmg;
}

int usePredatorInstinct(Dog *user, Dog *target)
{
    user->attack += 6;
    user->speed += 5;

    printf("%s activates Predator Instinct!\n", user->name);
    printf("Attack +6 | Speed +5\n");

    return 0;
}

int useEnhancedJawCrush(Dog *user, Dog *target)
{
    int dmg = (user->attack * 1.5) + 12 + (rand() % 10);

    if (target->defense > 0)
        dmg -= target->defense / 35;

    if (dmg < 5)
        dmg = 5;

    target->hp -= dmg;
    user->attack += 4;

    printf("%s uses Enhanced Jaw Crush! -%d HP\n", user->name, dmg);
    printf("%s's reinforced jaw grows stronger! Attack +4\n", user->name);

    return dmg;
}

int useRazorSlash(Dog *user, Dog *target)
{
    int dmg = user->attack + 14 + (rand() % 8);

    if (target->defense > 0)
        dmg -= target->defense / 45;

    if (dmg < 4)
        dmg = 4;

    target->hp -= dmg;

    printf("%s uses Razor Slash! -%d HP\n", user->name, dmg);
    printf("Sharp claws tear through the target!\n");

    return dmg;
}

int useBloodFrenzy(Dog *user, Dog *target)
{
    user->attack += 8;
    user->speed += 4;

    printf("%s enters Blood Frenzy!\n", user->name);
    printf("Attack +8 | Speed +4\n");

    return 0;
}

int useFangStorm(Dog *user, Dog *target)
{
    int hits = 3;
    int total = 0;

    printf("%s uses Fang Storm!\n", user->name);

    for (int i = 0; i < hits; i++)
    {
        int dmg = (user->attack * 0.8) + 8 + (rand() % 5);

        if (target->defense > 0)
            dmg -= target->defense / 50;

        if (dmg < 3)
            dmg = 3;

        target->hp -= dmg;
        total += dmg;

        printf("Fang hit %d! -%d HP\n", i + 1, dmg);
    }

    printf("Total damage: -%d HP\n", total);
    return total;
}

void setWildTerritorySkills(Dog *enemy)
{
    enemy->skills[0].id = SKILL_REINFORCED_BITE;
    strcpy(enemy->skills[0].name, "Reinforced Bite");
    enemy->skills[0].power = 24;

    enemy->skills[1].id = SKILL_RAZOR_SLASH;
    strcpy(enemy->skills[1].name, "Razor Slash");
    enemy->skills[1].power = 22;

    enemy->skills[2].id = SKILL_BLOOD_FRENZY;
    strcpy(enemy->skills[2].name, "Blood Frenzy");
    enemy->skills[2].power = 0;

    enemy->skills[3].id = SKILL_FANG_STORM;
    strcpy(enemy->skills[3].name, "Fang Storm");
    enemy->skills[3].power = 30;

    enemy->numSkills = 4;
}