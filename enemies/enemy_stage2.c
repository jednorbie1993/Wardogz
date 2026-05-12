#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"

// =========================
// WILD TERRITORY ENEMIES
// =========================

void loadStage2Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);

    // =========================
    // ZONE 3: WILD TERRITORY - RIVER
    // =========================
    if (zoneIndex == 3)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "River Scout");
            enemy->attack += 4;
            enemy->speed += 2;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Pack Hunter");
            enemy->attack += 6;
            enemy->speed += 3;
            enemy->maxHP += 10;
        }
        else
        {
            strcpy(enemy->name, "River Alpha");
            enemy->attack += 7;
            enemy->speed += 3;
            enemy->maxHP += 12;
            enemy->defense += 3;
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
            enemy->speed += 4;
            enemy->accuracy += 5;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Ambush Leader");
            enemy->speed += 6;
            enemy->accuracy += 8;
            enemy->attack += 3;
        }
        else
        {
            strcpy(enemy->name, "Shadow Pack");
            enemy->speed += 4;
            enemy->accuracy += 5;
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
            enemy->attack += 7;
            enemy->speed += 6;
            enemy->accuracy += 5;
        }
        else
        {
            strcpy(enemy->name, "Ravine Stalker");
            enemy->attack += 6;
            enemy->speed += 4;
            enemy->accuracy += 8;
            enemy->maxHP += 15;
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
            enemy->attack += 8;
            enemy->speed += 7;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Trial Hunter");
            enemy->attack += 9;
            enemy->speed += 8;
            enemy->accuracy += 6;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Trial Alpha");
            enemy->attack += 10;
            enemy->speed += 9;
            enemy->maxHP += 15;
        }
        else
        {
            strcpy(enemy->name, "Trial Beast");
            enemy->attack += 12;
            enemy->speed += 11;
            enemy->maxHP += 35;
            enemy->defense += 7;
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
            enemy->defense += 7;
            enemy->maxHP += 18;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Peak Warrior");
            enemy->defense += 10;
            enemy->maxHP += 25;
            enemy->attack += 5;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Summit Enforcer");
            enemy->defense += 15;
            enemy->maxHP += 35;
            enemy->attack += 8;
            enemy->speed += 3;
        }
        else
        {
            strcpy(enemy->name, "Mountain King");
            enemy->defense += 20;
            enemy->maxHP += 50;
            enemy->attack += 12;
            enemy->speed += 6;
        }

        setEnemySkillsWild(enemy, zoneIndex, i);
    }

    // =========================
    // FALLBACK
    // =========================
    else
    {
        strcpy(enemy->name, "Unknown Stray");
        enemy->attack += 20;
        enemy->speed += 20;
        enemy->maxHP += 50;
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

    printf("%s calls pack!\n", user->name);

    for (int i = 0; i < hits; i++)
    {
        int dmg = (user->attack * 0.35) + (rand() % 4);
        target->hp -= dmg;
        total += dmg;
        printf("Hit %d: -%d\n", i + 1, dmg);
    }

    return total;
}

int useAmbush(Dog *user, Dog *target)
{
    int dmg = user->attack * 1.2 + (rand() % 6);
    target->hp -= dmg;

    printf("%s ambushes from shadows! -%d\n", user->name, dmg);

    user->speed += 5;

    return dmg;
}

int useHowlDebuff(Dog *user, Dog *target)
{
    target->accuracyModifier -= 20;
    target->accDebuffTurns = 3;

    int dmg = user->attack / 5;
    target->hp -= dmg;

    printf("%s HOWLS! Accuracy DOWN! -%d\n", user->name, dmg);

    return dmg;
}

int useFeralRush(Dog *user, Dog *target)
{
    int dmg = (user->attack * 1.05) + (rand() % 4);
    target->hp -= dmg;

    target->bleedTurns += 2;
    target->bleedDamage = 1;

    printf("%s FERAL RUSH! -%d +BLEED!\n", user->name, dmg);

    return dmg;
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

    enemy->attack += 1;
    enemy->speed += 1;
}