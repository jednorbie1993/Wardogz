#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../replay_system.h"
#include "../console.h"

// =========================
// WILD TERRITORY ENEMIES
// =========================


// =========================
// DAMAGE BALANCE HELPER
// =========================
static int limitWildDamage(int dmg, int minDmg, int maxDmg)
{
    if (dmg < minDmg)
        dmg = minDmg;

    if (dmg > maxDmg)
        dmg = maxDmg;

    return dmg;
}

static void applyWildSkillDamage(Dog *target, int dmg)
{
    /*
        Stage 2 helper:
        - Skill functions still subtract HP here.
        - enemy.c can read the HP difference after the skill.
        - Do NOT call this function inside itself.
    */
    target->hp -= dmg;
    target->hp = clamp(target->hp);
}

void createDiremaw(Dog *enemy)
{
    strcpy(enemy->name, "Diremaw");

    // Secret Stage 2 enemy: tougher stats, but skill damage is capped below.
    enemy->hp = 340;
    enemy->maxHP = 340;
    enemy->attack = 85;
    enemy->defense = 75;
    enemy->speed = 65;
    enemy->accuracy = 90;
    enemy->intelligence = 38;

    enemy->zoneType = ZONE_NORMAL;
    enemy->personalityType = PERSONALITY_DESPERATE;

    enemy->numSkills = 6;

    enemy->skills[0] = (Skill){"Mauling Bite", 16, 0, SKILL_DAMAGE, 95, SKILL_MAULING_BITE, 0, 0, 10};
    enemy->skills[1] = (Skill){"Rabid Claw", 12, 0, SKILL_DAMAGE, 90, SKILL_RABID_CLAW, 0, 0, 18};
    enemy->skills[2] = (Skill){"Blood Scent", 18, 0, SKILL_DAMAGE, 90, SKILL_BLOOD_SCENT, 0, 0, 16};
    enemy->skills[3] = (Skill){"Wild Pounce", 20, 0, SKILL_DAMAGE, 85, SKILL_WILD_POUNCE, 0, 0, 15};
    enemy->skills[4] = (Skill){"Bone Breaker", 24, 0, SKILL_DAMAGE, 80, SKILL_BONE_BREAKER, 0, 0, 20};
    enemy->skills[5] = (Skill){"Predator Frenzy", 8, 0, SKILL_DAMAGE, 80, SKILL_PREDATOR_FRENZY, 3, 0, 25};
}

void loadStage2Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);
    if (i == SECRET_DIREMAW_INDEX)
    {
        createDiremaw(enemy);
        return;
    }

    // =========================
    // ZONE 3: WILD TERRITORY - RIVER
    // =========================
    if (zoneIndex == 3)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "River Scout");
            enemy->attack += 18;
            enemy->speed += 8;
            enemy->defense += 6;
            enemy->maxHP += 35;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Pack Hunter");
            enemy->attack += 23;
            enemy->speed += 10;
            enemy->defense += 8;
            enemy->maxHP += 50;
        }
        else
        {
            strcpy(enemy->name, "River Alpha");
            enemy->attack += 28;
            enemy->speed += 12;
            enemy->maxHP += 70;
            enemy->defense += 12;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }

    // =========================
    // ZONE 4: FOREST
    // =========================
    else if (zoneIndex == 4)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Forest Stalker");
            enemy->attack += 20;
            enemy->speed += 16;
            enemy->accuracy += 6;
            enemy->defense += 6;
            enemy->maxHP += 40;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Ambush Leader");
            enemy->speed += 20;
            enemy->accuracy += 8;
            enemy->attack += 26;
            enemy->defense += 8;
            enemy->maxHP += 55;
        }
        else
        {
            strcpy(enemy->name, "Shadow Pack");
            enemy->attack += 20;
            enemy->speed += 16;
            enemy->accuracy += 6;
            enemy->defense += 6;
            enemy->maxHP += 40;
            enemy->attack += 3;
            enemy->maxHP += 8;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }

    // =========================
    // ZONE 5: RAVINE
    // =========================
    else if (zoneIndex == 5)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Bloodfang Scout");
            enemy->attack += 32;
            enemy->speed += 18;
            enemy->accuracy += 7;
            enemy->defense += 10;
            enemy->maxHP += 70;
        }
        else
        {
            strcpy(enemy->name, "Ravine Stalker");
            enemy->attack += 36;
            enemy->speed += 20;
            enemy->accuracy += 8;
            enemy->defense += 12;
            enemy->maxHP += 90;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }

    // =========================
    // ZONE 6: TRIAL
    // =========================
    else if (zoneIndex == 6)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Trial Challenger");
            enemy->attack += 36;
            enemy->speed += 22;
            enemy->defense += 12;
            enemy->maxHP += 85;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Trial Hunter");
            enemy->attack += 40;
            enemy->speed += 24;
            enemy->accuracy += 7;
            enemy->defense += 14;
            enemy->maxHP += 95;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Trial Alpha");
            enemy->attack += 45;
            enemy->speed += 26;
            enemy->defense += 16;
            enemy->maxHP += 115;
        }
        else
        {
            strcpy(enemy->name, "Trial Beast");
            enemy->attack += 52;
            enemy->speed += 30;
            enemy->maxHP += 150;
            enemy->defense += 22;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }

    // =========================
    // ZONE 7: MOUNTAIN
    // =========================
    else if (zoneIndex == 7)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Mountain Guard");
            enemy->attack += 38;
            enemy->defense += 22;
            enemy->speed += 12;
            enemy->maxHP += 120;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Peak Warrior");
            enemy->defense += 28;
            enemy->maxHP += 145;
            enemy->attack += 45;
            enemy->speed += 14;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Summit Enforcer");
            enemy->defense += 34;
            enemy->maxHP += 170;
            enemy->attack += 52;
            enemy->speed += 18;
        }
        else
        {
            strcpy(enemy->name, "Mountain King");
            enemy->defense += 42;
            enemy->maxHP += 210;
            enemy->attack += 62;
            enemy->speed += 22;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }

    // =========================
    // FALLBACK
    // =========================
    else
    {
        strcpy(enemy->name, "Unknown Stray");
        enemy->attack += 35;
        enemy->speed += 20;
        enemy->defense += 15;
        enemy->maxHP += 100;
    }

    // sync HP
    enemy->hp = enemy->maxHP;
}

// =====================================================
// PACK / WILD SKILLS
// =====================================================

int usePackAttack(Dog *user, Dog *target)
{
    int hits = 2;
    int total = 0;

    printCenteredFormat("%s calls pack!", user->name);

    for (int i = 0; i < hits; i++)
    {
        int dmg = (user->attack / 4) + 6 + (rand() % 4);
        dmg = limitWildDamage(dmg, 8, 26);
        applyWildSkillDamage(target, dmg);
        total += dmg;
        printCenteredFormat("Hit %d: -%d", i + 1, dmg);
    }

    return total;
}

int useAmbush(Dog *user, Dog *target)
{
    int dmg = 28 + (user->attack / 3) + (rand() % 8);
    dmg = limitWildDamage(dmg, 25, 75);
    applyWildSkillDamage(target, dmg);

    printCenteredFormat("%s ambushes from shadows! -%d", user->name, dmg);

    user->speed += 5;

    return dmg;
}

int useHowlDebuff(Dog *user, Dog *target)
{
    target->accuracyModifier -= 20;
    target->accDebuffTurns = 3;

    int dmg = 10 + (user->attack / 8);
    dmg = limitWildDamage(dmg, 10, 35);
    applyWildSkillDamage(target, dmg);

    printCenteredFormat("%s HOWLS! Accuracy DOWN! -%d", user->name, dmg);

    return dmg;
}

int useFeralRush(Dog *user, Dog *target)
{
    int dmg = 24 + (user->attack / 3) + (rand() % 7);
    dmg = limitWildDamage(dmg, 22, 70);
    applyWildSkillDamage(target, dmg);

    target->bleedTurns += 2;
    target->bleedDamage = 1;

    printCenteredFormat("%s FERAL RUSH! -%d +BLEED!", user->name, dmg);

    return dmg;
}

int useMaulingBite(Dog *user, Dog *target)
{
    int dmg = 26 + (user->attack / 3) + (rand() % 7);
    dmg = limitWildDamage(dmg, 24, 80);
    applyWildSkillDamage(target, dmg);

    printCenteredFormat("%s uses Mauling Bite! -%d", user->name, dmg);

    return dmg;
}

int useRabidClaw(Dog *user, Dog *target)
{
    int dmg = 22 + (user->attack / 4) + (rand() % 7);
    dmg = limitWildDamage(dmg, 20, 70);
    applyWildSkillDamage(target, dmg);

    target->isBleeding = 1;
    target->bleedTurns = 3;
    target->bleedDamage = 5;

    printCenteredFormat("%s uses Rabid Claw! -%d +BLEED!", user->name, dmg);

    return dmg;
}

int useBloodScent(Dog *user, Dog *target)
{
    int dmg = 24 + (user->attack / 3) + (rand() % 7);

    if (target->isBleeding)
    {
        dmg += 12;
        printCenteredFormat("%s smells blood! Bonus damage!", user->name);
    }

    dmg = limitWildDamage(dmg, 22, 85);
    applyWildSkillDamage(target, dmg);

    printCenteredFormat("%s uses Blood Scent! -%d", user->name, dmg);

    return dmg;
}

int useWildPounce(Dog *user, Dog *target)
{
    int dmg = 28 + (user->attack / 3) + (rand() % 8);
    dmg = limitWildDamage(dmg, 25, 85);
    applyWildSkillDamage(target, dmg);

    user->speed += 5;

    printCenteredFormat("%s uses Wild Pounce! -%d Speed UP!", user->name, dmg);

    return dmg;
}

int useBoneBreaker(Dog *user, Dog *target)
{
    int dmg = 34 + (user->attack / 3) + (rand() % 8);
    dmg = limitWildDamage(dmg, 30, 95);
    applyWildSkillDamage(target, dmg);

    target->defense -= 5;

    if (target->defense < 0)
        target->defense = 0;

    printCenteredFormat("%s uses Bone Breaker! -%d Defense DOWN!", user->name, dmg);

    return dmg;
}

int usePredatorFrenzy(Dog *user, Dog *target)
{
    int hits = 1 + rand() % 3;
    int total = 0;

    printCenteredFormat("%s uses Predator Frenzy!", user->name);

    for (int i = 0; i < hits; i++)
    {
        int dmg = 12 + (user->attack / 5) + (rand() % 5);
        dmg = limitWildDamage(dmg, 12, 35);
        applyWildSkillDamage(target, dmg);
        total += dmg;

        printCenteredFormat("Hit %d: -%d", i + 1, dmg);
    }

    applyWildSkillDamage(user, 8);
    printCenteredFormat("%s took 8 recoil damage!", user->name);

    return total;
}

// =====================================================
// SKILL SETUP
// =====================================================

void setEnemySkillsWild(Dog *enemy, int zoneIndex, int enemyLevel)
{
    enemy->skills[0].id = SKILL_PACK_ATTACK;
    strcpy(enemy->skills[0].name, "Pack Attack");
    enemy->skills[0].power = 10;

    enemy->skills[1].id = SKILL_AMBUSH;
    strcpy(enemy->skills[1].name, "Ambush");
    enemy->skills[1].power = 14;

    if (zoneIndex == 3 || zoneIndex == 5)
    {
        enemy->skills[2].id = SKILL_HOWL_DEBUFF;
        strcpy(enemy->skills[2].name, "Howl");
    }
    else
    {
        enemy->skills[2].id = SKILL_FERAL_RUSH;
        strcpy(enemy->skills[2].name, "Feral Rush");
    }

    enemy->skills[2].power = 12;
    enemy->numSkills = 3;

    enemy->attack += 4 + enemyLevel;
    enemy->defense += 2 + (enemyLevel / 2);
    enemy->speed += 3;
}