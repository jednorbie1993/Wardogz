#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../dog.h"
#include "enemy_stage5.h"
#include "../replay_system.h"

/*
    STAGE 5: BLACKSITE LABORATORY
    Zone 1 = index 16: Enhanced Strays
    Zone 2 = index 17: Feral Mutation Ward
    Zone 3 = index 18: Combat Prototype Unit

    NOTE:
    If you add the new Zone 3 skill IDs below, also add them in dog.h enum:
        SKILL_TACTICAL_BITE
        SKILL_ARMOR_BREAK
        SKILL_SUPPRESSION_HOWL
        SKILL_BLACKSITE_EXECUTION

    Then add the skill cases in enemy.c / battle enemy skill switch.
*/

// =========================
// SKILL SETTERS
// =========================

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

void setCombatPrototypeSkills(Dog *enemy)
{
    enemy->skills[0].id = SKILL_TACTICAL_BITE;
    strcpy(enemy->skills[0].name, "Tactical Bite");
    enemy->skills[0].power = 26;

    enemy->skills[1].id = SKILL_ARMOR_BREAK;
    strcpy(enemy->skills[1].name, "Armor Break");
    enemy->skills[1].power = 24;

    enemy->skills[2].id = SKILL_SUPPRESSION_HOWL;
    strcpy(enemy->skills[2].name, "Suppression Howl");
    enemy->skills[2].power = 0;

    enemy->skills[3].id = SKILL_BLACKSITE_EXECUTION;
    strcpy(enemy->skills[3].name, "Blacksite Execution");
    enemy->skills[3].power = 36;

    enemy->numSkills = 4;
}

// =========================
// ENEMY LOADER
// =========================

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
        else
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
        else
        {
            strcpy(enemy->name, "Lycan Rex");
            enemy->attack += 40;
            enemy->defense += 25;
            enemy->speed += 25;
            enemy->maxHP += 160;
        }

        setWildTerritorySkills(enemy);
    }

    // =========================
    // ZONE 3: COMBAT PROTOTYPE UNIT
    // =========================
    else if (zoneIndex == 18)
    {
        enemy->zoneType = ZONE_MUTANT;
        enemy->personalityType = PERSONALITY_TANK;

        if (i == 0)
        {
            strcpy(enemy->name, "K-9 Warden");
            enemy->attack += 30;
            enemy->defense += 24;
            enemy->speed += 10;
            enemy->maxHP += 100;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Steelmaw Unit");
            enemy->attack += 34;
            enemy->defense += 30;
            enemy->speed += 8;
            enemy->maxHP += 120;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Blackclaw Agent");
            enemy->attack += 38;
            enemy->defense += 22;
            enemy->speed += 22;
            enemy->maxHP += 115;
        }
        else
        {
            strcpy(enemy->name, "Commander Cerberus");
            enemy->attack += 48;
            enemy->defense += 36;
            enemy->speed += 24;
            enemy->maxHP += 190;
        }

        setCombatPrototypeSkills(enemy);
    }
    else
    {
        strcpy(enemy->name, "Unknown Blacksite Dog");
        enemy->attack += 20;
        enemy->defense += 20;
        enemy->speed += 20;
        enemy->maxHP += 80;

        setEnhancedStraySkills(enemy);
    }

    enemy->hp = enemy->maxHP;
    enemy->numSkills = 4;
}

// =========================
// ZONE 1 SKILLS
// =========================

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

// =========================
// ZONE 2 SKILLS
// =========================

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

// =========================
// ZONE 3 SKILLS
// =========================

int useTacticalBite(Dog *user, Dog *target)
{
    int dmg = user->attack + 16 + (rand() % 9);

    if (user->speed >= target->speed)
        dmg += 6;

    if (target->defense > 0)
        dmg -= target->defense / 42;

    if (dmg < 5)
        dmg = 5;

    target->hp -= dmg;

    printf("%s uses Tactical Bite! -%d HP\n", user->name, dmg);
    printf("The unit attacks with trained precision.\n");

    return dmg;
}

int useArmorBreak(Dog *user, Dog *target)
{
    int dmg = user->attack + 12 + (rand() % 8);

    if (target->defense > 0)
        dmg -= target->defense / 50;

    if (dmg < 4)
        dmg = 4;

    target->hp -= dmg;

    target->defense -= 5;
    if (target->defense < 0)
        target->defense = 0;

    printf("%s uses Armor Break! -%d HP\n", user->name, dmg);
    printf("%s's defense was lowered by 5!\n", target->name);

    return dmg;
}

int useSuppressionHowl(Dog *user, Dog *target)
{
    user->defense += 8;

    target->attack -= 4;
    if (target->attack < 1)
        target->attack = 1;

    printf("%s releases a Suppression Howl!\n", user->name);
    printf("%s gains Defense +8.\n", user->name);
    printf("%s loses Attack -4.\n", target->name);

    return 0;
}

int useBlacksiteExecution(Dog *user, Dog *target)
{
    int dmg = (user->attack * 1.6) + 18 + (rand() % 12);

    if (target->hp < target->maxHP / 2)
        dmg += 12;

    if (target->defense > 0)
        dmg -= target->defense / 35;

    if (dmg < 8)
        dmg = 8;

    target->hp -= dmg;

    printf("%s uses Blacksite Execution! -%d HP\n", user->name, dmg);
    printf("The combat prototype follows its final order.\n");

    return dmg;
}
