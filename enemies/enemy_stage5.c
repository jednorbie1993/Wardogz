#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../dog.h"
#include "enemy_stage5.h"
#include "../replay_system.h"

// =========================
// STAGE 5 BALANCE HELPERS
// =========================
// Enemy stats are high in Stage 5, so damage must be scaled.
// This keeps 900 HP fights from ending in 1-2 hits.
static int stage5Damage(Dog *user, Dog *target, int base, int diffDiv, int variance, int minDmg, int maxDmg)
{
    int diff = user->attack - target->defense;
    int dmg = base + (diff / diffDiv);

    if (variance > 0)
        dmg += rand() % variance;

    if (dmg < minDmg)
        dmg = minDmg;

    if (dmg > maxDmg)
        dmg = maxDmg;

    return dmg;
}


/*
    STAGE 5: BLACKSITE LABORATORY
    Zone 1 = index 16: Enhanced Strays
    Zone 2 = index 17: Feral Mutation Ward
    Zone 3 = index 18: Combat Prototype Unit
    Zone 4 = index 19: Elemental Apex Chamber
    Zone 5 = index 20: Final Containment / Project Cerberus

    NOTE:
    If you add the new Zone 3 skill IDs below, also add them in dog.h enum:
        SKILL_TACTICAL_BITE
        SKILL_ARMOR_BREAK
        SKILL_SUPPRESSION_HOWL
        SKILL_BLACKSITE_EXECUTION

    If you add the new Zone 4 skill IDs below, also add them in dog.h enum:
        SKILL_PLASMA_BITE
        SKILL_CRYO_LOCK
        SKILL_THUNDER_SURGE
        SKILL_APEX_OVERDRIVE

    Then add the skill cases in enemy.c / battle enemy skill switch.
*/

// =========================
// SKILL SETTERS
// =========================
void createGrimfangX(Dog *enemy)
{
    createEnemy(enemy);

    strcpy(enemy->name, "Grimfang-X");

    enemy->zoneType = ZONE_MUTANT;
    enemy->personalityType = PERSONALITY_ALPHA;

    enemy->attack += 330;
    enemy->defense += 260;
    enemy->speed += 300;
    enemy->accuracy += 250;
    enemy->intelligence += 180;
    enemy->maxHP += 700;
    enemy->hp = enemy->maxHP;

    enemy->numSkills = 4;

    enemy->skills[0].id = SKILL_PLASMA_BITE;
    strcpy(enemy->skills[0].name, "Plasma Bite");
    enemy->skills[0].power = 34;

    enemy->skills[1].id = SKILL_CRYO_LOCK;
    strcpy(enemy->skills[1].name, "Cryo Lock");
    enemy->skills[1].power = 30;

    enemy->skills[2].id = SKILL_THUNDER_SURGE;
    strcpy(enemy->skills[2].name, "Thunder Surge");
    enemy->skills[2].power = 0;

    enemy->skills[3].id = SKILL_APEX_OVERDRIVE;
    strcpy(enemy->skills[3].name, "Apex Overdrive");
    enemy->skills[3].power = 48;
}

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

void setElementalApexSkills(Dog *enemy)
{
    enemy->skills[0].id = SKILL_PLASMA_BITE;
    strcpy(enemy->skills[0].name, "Plasma Bite");
    enemy->skills[0].power = 30;

    enemy->skills[1].id = SKILL_CRYO_LOCK;
    strcpy(enemy->skills[1].name, "Cryo Lock");
    enemy->skills[1].power = 24;

    enemy->skills[2].id = SKILL_THUNDER_SURGE;
    strcpy(enemy->skills[2].name, "Thunder Surge");
    enemy->skills[2].power = 0;

    enemy->skills[3].id = SKILL_APEX_OVERDRIVE;
    strcpy(enemy->skills[3].name, "Apex Overdrive");
    enemy->skills[3].power = 42;

    enemy->numSkills = 4;
}

void setFinalContainmentSkills(Dog *enemy)
{
    /*
        Zone 5 uses existing skill IDs so this file will not force
        extra dog.h enum changes yet.

        The display names are final-boss themed, but the actual effects
        still come from the matching IDs in enemy.c:
            SKILL_APEX_OVERDRIVE       -> big damage
            SKILL_ENHANCED_JAW_CRUSH   -> heavy bite + attack growth
            SKILL_FANG_STORM           -> multi-hit
            SKILL_PREDATOR_INSTINCT    -> attack/speed buff
    */

    enemy->skills[0].id = SKILL_APEX_OVERDRIVE;
    strcpy(enemy->skills[0].name, "Mutation Overdrive");
    enemy->skills[0].power = 45;

    enemy->skills[1].id = SKILL_ENHANCED_JAW_CRUSH;
    strcpy(enemy->skills[1].name, "Humanoid Jaw Crush");
    enemy->skills[1].power = 38;

    enemy->skills[2].id = SKILL_FANG_STORM;
    strcpy(enemy->skills[2].name, "Timeline Maul");
    enemy->skills[2].power = 34;

    enemy->skills[3].id = SKILL_PREDATOR_INSTINCT;
    strcpy(enemy->skills[3].name, "Cursed Instinct");
    enemy->skills[3].power = 0;

    enemy->numSkills = 4;
}

// =========================
// ENEMY LOADER
// =========================

void loadStage5Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);

    if (i == SECRET_GRIMFANG_X_INDEX)
    {
        createGrimfangX(enemy);
        return;
    }

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
            enemy->attack = 520;
            enemy->defense = 470;
            enemy->speed = 500;
            enemy->maxHP = 560;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Night Howler");
            enemy->attack = 500;
            enemy->defense = 440;
            enemy->speed = 560;
            enemy->maxHP = 540;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Ironjaw");
            enemy->attack = 510;
            enemy->defense = 560;
            enemy->speed = 430;
            enemy->maxHP = 620;
        }
        else
        {
            strcpy(enemy->name, "Alpha-X");
            enemy->attack = 590;
            enemy->defense = 540;
            enemy->speed = 540;
            enemy->maxHP = 700;
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
            enemy->attack = 570;
            enemy->defense = 490;
            enemy->speed = 580;
            enemy->maxHP = 650;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Bloodhowl");
            enemy->attack = 610;
            enemy->defense = 510;
            enemy->speed = 550;
            enemy->maxHP = 700;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Ravagefang");
            enemy->attack = 640;
            enemy->defense = 550;
            enemy->speed = 570;
            enemy->maxHP = 760;
        }
        else
        {
            strcpy(enemy->name, "Lycan Rex");
            enemy->attack = 700;
            enemy->defense = 610;
            enemy->speed = 630;
            enemy->maxHP = 850;
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
            enemy->attack = 650;
            enemy->defense = 620;
            enemy->speed = 500;
            enemy->maxHP = 760;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Steelmaw Unit");
            enemy->attack = 680;
            enemy->defense = 680;
            enemy->speed = 480;
            enemy->maxHP = 820;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Blackclaw Agent");
            enemy->attack = 700;
            enemy->defense = 590;
            enemy->speed = 650;
            enemy->maxHP = 800;
        }
        else
        {
            strcpy(enemy->name, "Commander Cerberus");
            enemy->attack = 760;
            enemy->defense = 700;
            enemy->speed = 660;
            enemy->maxHP = 930;
        }

        setCombatPrototypeSkills(enemy);
    }

    // =========================
    // ZONE 4: ELEMENTAL APEX CHAMBER
    // =========================
    else if (zoneIndex == 19)
    {
        enemy->zoneType = ZONE_MUTANT;
        enemy->personalityType = PERSONALITY_DESPERATE;

        if (i == 0)
        {
            strcpy(enemy->name, "Pyroclaw");
            enemy->attack = 720;
            enemy->defense = 600;
            enemy->speed = 680;
            enemy->maxHP = 840;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Frostmaw");
            enemy->attack = 700;
            enemy->defense = 720;
            enemy->speed = 560;
            enemy->maxHP = 880;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Voltfang");
            enemy->attack = 740;
            enemy->defense = 610;
            enemy->speed = 760;
            enemy->maxHP = 860;
        }
        else
        {
            strcpy(enemy->name, "Apex Chimera");
            enemy->attack = 820;
            enemy->defense = 760;
            enemy->speed = 720;
            enemy->maxHP = 980;
        }

        setElementalApexSkills(enemy);
    }
    // =========================
    // ZONE 5: FINAL CONTAINMENT
    // =========================
    else if (zoneIndex == 20)
    {
        /*
            Final boss only: progress is 0/1 in stage5.c.
            This is the humanoid mutant dog that should be defeated
            before the 22-24 turn regeneration and 2-minute meltdown timer.
            Regen/timer logic should be handled inside battle.c because
            enemy_stage5.c only loads enemy data and skills.
        */

        enemy->zoneType = ZONE_MUTANT;
        enemy->personalityType = PERSONALITY_DESPERATE;

        strcpy(enemy->name, "Project Cerberus");

        enemy->attack = 850;
        enemy->defense = 790;
        enemy->speed = 740;
        enemy->maxHP = 999;

        enemy->regenerationTurn = 22 + (rand() % 3); // 22-24 turns
        enemy->regenerationUsed = 0;

        setFinalContainmentSkills(enemy);
    }

    else
    {
        strcpy(enemy->name, "Unknown Blacksite Dog");
        enemy->attack = 560;
        enemy->defense = 520;
        enemy->speed = 520;
        enemy->maxHP = 650;

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

    printf("%s uses Reinforced Bite!", user->name);

    for (int i = 0; i < hits; i++)
    {
        int dmg = stage5Damage(user, target, 32, 16, 6, 18, 55);

        target->hp -= dmg;
        target->hp = clamp(target->hp);
        total += dmg;

        printf("Hit %d! -%d HP", i + 1, dmg);
    }

    printf("Total damage: -%d HP", total);
    return total;
}

int useCombatRush(Dog *user, Dog *target)
{
    int dmg = stage5Damage(user, target, 58, 14, 10, 30, 115);

    if (user->speed > target->speed)
    {
        dmg += 10;
        printf("%s outsped the target!", user->name);
    }

    if (dmg > 125)
        dmg = 125;

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    printf("%s uses Combat Rush! -%d HP", user->name, dmg);
    return dmg;
}

int usePredatorInstinct(Dog *user, Dog *target)
{
    user->attack += 6;
    user->speed += 5;

    if (user->attack > 999)
        user->attack = 999;
    if (user->speed > 999)
        user->speed = 999;

    printf("%s activates Predator Instinct!\n", user->name);
    printf("Attack +6 | Speed +5\n");

    return 0;
}

int useEnhancedJawCrush(Dog *user, Dog *target)
{
    int dmg = stage5Damage(user, target, 78, 12, 12, 45, 145);

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    user->attack += 4;
    if (user->attack > 999)
        user->attack = 999;

    printf("%s uses Enhanced Jaw Crush! -%d HP", user->name, dmg);
    printf("%s's reinforced jaw grows stronger! Attack +4", user->name);

    return dmg;
}

// =========================
// ZONE 2 SKILLS
// =========================

int useRazorSlash(Dog *user, Dog *target)
{
    int dmg = stage5Damage(user, target, 62, 13, 10, 32, 120);

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    printf("%s uses Razor Slash! -%d HP", user->name, dmg);
    printf("Sharp claws tear through the target!");

    return dmg;
}

int useBloodFrenzy(Dog *user, Dog *target)
{
    user->attack += 8;
    user->speed += 4;

    if (user->attack > 999)
        user->attack = 999;
    if (user->speed > 999)
        user->speed = 999;

    printf("%s enters Blood Frenzy!\n", user->name);
    printf("Attack +8 | Speed +4\n");

    return 0;
}

int useFangStorm(Dog *user, Dog *target)
{
    int hits = 3;
    int total = 0;

    printf("%s uses Fang Storm!", user->name);

    for (int i = 0; i < hits; i++)
    {
        int dmg = stage5Damage(user, target, 28, 18, 6, 16, 52);

        target->hp -= dmg;
        target->hp = clamp(target->hp);
        total += dmg;

        printf("Fang hit %d! -%d HP", i + 1, dmg);
    }

    printf("Total damage: -%d HP", total);
    return total;
}

// =========================
// ZONE 3 SKILLS
// =========================

int useTacticalBite(Dog *user, Dog *target)
{
    int dmg = stage5Damage(user, target, 68, 13, 10, 35, 130);

    if (user->speed >= target->speed)
        dmg += 6;

    if (dmg > 140)
        dmg = 140;

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    printf("%s uses Tactical Bite! -%d HP", user->name, dmg);
    printf("The unit attacks with trained precision.");

    return dmg;
}

int useArmorBreak(Dog *user, Dog *target)
{
    int dmg = stage5Damage(user, target, 58, 14, 10, 30, 115);

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    target->defense -= 5;
    if (target->defense < 0)
        target->defense = 0;

    printf("%s uses Armor Break! -%d HP", user->name, dmg);
    printf("%s's defense was lowered by 5!", target->name);

    return dmg;
}

int useSuppressionHowl(Dog *user, Dog *target)
{
    user->defense += 8;
    if (user->defense > 999)
        user->defense = 999;

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
    int dmg = stage5Damage(user, target, 88, 12, 14, 50, 160);

    if (target->hp < target->maxHP / 2)
        dmg += 12;

    if (dmg > 175)
        dmg = 175;

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    printf("%s uses Blacksite Execution! -%d HP", user->name, dmg);
    printf("The combat prototype follows its final order.");

    return dmg;
}

// =========================
// ZONE 4 SKILLS
// =========================

int usePlasmaBite(Dog *user, Dog *target)
{
    int dmg = stage5Damage(user, target, 72, 13, 12, 40, 135);

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    target->defense -= 3;
    if (target->defense < 0)
        target->defense = 0;

    printf("%s uses Plasma Bite! -%d HP", user->name, dmg);
    printf("The heated bite weakens %s's defense by 3!", target->name);

    return dmg;
}

int useCryoLock(Dog *user, Dog *target)
{
    int dmg = stage5Damage(user, target, 62, 14, 10, 35, 125);

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    target->speed -= 6;
    if (target->speed < 1)
        target->speed = 1;

    printf("%s uses Cryo Lock! -%d HP", user->name, dmg);
    printf("%s's speed was lowered by 6!", target->name);

    return dmg;
}

int useThunderSurge(Dog *user, Dog *target)
{
    user->attack += 6;
    user->speed += 8;

    if (user->attack > 999)
        user->attack = 999;
    if (user->speed > 999)
        user->speed = 999;

    printf("%s activates Thunder Surge!\n", user->name);
    printf("Attack +6 | Speed +8\n");

    return 0;
}

int useApexOverdrive(Dog *user, Dog *target)
{
    int dmg = stage5Damage(user, target, 95, 12, 16, 60, 175);

    if (user->hp < user->maxHP / 2)
        dmg += 16;

    if (dmg > 190)
        dmg = 190;

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    printf("%s uses Apex Overdrive! -%d HP", user->name, dmg);
    printf("Elemental energy overloads the chamber.");

    return dmg;
}

int useMutationOverdrive(Dog *user, Dog *target)
{
    user->attack += 10;
    user->defense += 6;
    user->speed += 5;

    if (user->attack > 999)
        user->attack = 999;
    if (user->defense > 999)
        user->defense = 999;
    if (user->speed > 999)
        user->speed = 999;

    printf("%s activates Mutation Overdrive!\n", user->name);
    printf("Attack +10 | Defense +6 | Speed +5\n");

    return 0;
}

int useHumanoidJawCrush(Dog *user, Dog *target)
{
    int dmg = stage5Damage(user, target, 82, 12, 12, 45, 150);

    target->hp -= dmg;
    target->hp = clamp(target->hp);

    printf("%s uses Humanoid Jaw Crush! -%d HP", user->name, dmg);
    printf("The humanoid mutant clamps down with unnatural force.");

    return dmg;
}

int useTimelineMaul(Dog *user, Dog *target)
{
    int hits = 3;
    int total = 0;

    printf("%s uses Timeline Maul!", user->name);

    for (int i = 0; i < hits; i++)
    {
        int dmg = stage5Damage(user, target, 34, 18, 7, 20, 60);

        target->hp -= dmg;
        target->hp = clamp(target->hp);
        total += dmg;

        printf("Timeline hit %d! -%d HP", i + 1, dmg);
    }

    printf("Total damage: -%d HP", total);
    return total;
}

int useCursedInstinct(Dog *user, Dog *target)
{
    user->attack += 6;
    if (user->attack > 999)
        user->attack = 999;

    target->defense -= 6;

    if (target->defense < 0)
        target->defense = 0;

    printf("%s awakens Cursed Instinct!\n", user->name);
    printf("%s gains Attack +6.\n", user->name);
    printf("%s's Defense -6.\n", target->name);

    return 0;
}