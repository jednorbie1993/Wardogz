#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../dog.h"
#include "enemy_stage4.h"

void loadStage4Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);
    enemy->numSkills = 6;
    enemy->zoneType = ZONE_BIOLAB;

    setEnemySkillsBio(enemy, zoneIndex);

    // Zone limits
    if (zoneIndex == 12 && i > 1) i = 1;      // Outer Facility (2 enemies)
    if (zoneIndex == 13 && i > 3) i = 3;      // Research Hallways (4 enemies)
    if (zoneIndex == 14 && i > 3) i = 3;       // Containment Labs (4 enemies)
    if (zoneIndex == 15 && i > 2) i = 2;     // Core Chamber (3 enemies)

    // =========================
    // ZONE 12: OUTER FACILITY
    // =========================
    if (zoneIndex == 12)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Security K-9");
            enemy->attack += 8;
            enemy->defense += 6;
            enemy->maxHP += 25;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Drone-Assisted K-9");
            enemy->attack += 10;
            enemy->speed += 8;
            enemy->defense += 4;
            enemy->maxHP += 20;
            enemy->hp = enemy->maxHP;
        }
    }

    // =========================
    // ZONE 13: RESEARCH HALLWAYS
    // =========================
    else if (zoneIndex == 13)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Test Subject 001");
            enemy->attack += 12;
            enemy->defense += 8;
            enemy->maxHP += 30;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Experiment Alpha");
            enemy->attack += 14;
            enemy->defense += 10;
            enemy->maxHP += 35;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Failed Enhancement");
            enemy->attack += 16;
            enemy->speed += 6;
            enemy->defense += 6;
            enemy->maxHP += 28;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Unstable Subject");
            enemy->attack += 18;
            enemy->speed += 10;
            enemy->defense += 4;
            enemy->maxHP += 25;
            enemy->hp = enemy->maxHP;
        }
    }

    // =========================
    // ZONE 14: CONTAINMENT LABS
    // =========================
    else if (zoneIndex == 14)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Hybrid Unit K-7");
            enemy->attack += 18;
            enemy->defense += 14;
            enemy->maxHP += 45;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Bio-Mech Hound");
            enemy->attack += 16;
            enemy->defense += 16;
            enemy->maxHP += 50;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Rage Subject");
            enemy->attack += 22;
            enemy->speed += 8;
            enemy->defense += 8;
            enemy->maxHP += 40;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Prototype K-9");
            enemy->attack += 20;
            enemy->defense += 14;
            enemy->speed += 6;
            enemy->maxHP += 55;
            enemy->hp = enemy->maxHP;
        }
    }

    // =========================
    // ZONE 15: CORE CHAMBER
    // =========================
    else if (zoneIndex == 15)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Project Omega");
            enemy->attack += 24;
            enemy->defense += 16;
            enemy->maxHP += 60;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Facility Alpha");
            enemy->attack += 28;
            enemy->defense += 18;
            enemy->maxHP += 70;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "PROTOTYPE ZERO");
            enemy->attack += 32;
            enemy->defense += 20;
            enemy->speed += 8;
            enemy->maxHP += 80;
            enemy->hp = enemy->maxHP;
        }
    }

    setEnemySkillsBio(enemy, zoneIndex);
}

// =========================
// BIO LAB SKILLS
// =========================

int useMutationSurge(Dog *user, Dog *target)
{
    int dmg = user->attack * 1.3 + (rand() % 6);
    target->hp -= dmg;
    printf("%s uses Mutation Surge! -%d\n", user->name, dmg);
    return dmg;
}

int useBioShield(Dog *user, Dog *target)
{
    user->defense += 6;
    user->guardTurns = 3;
    printf("%s activates Bio Shield!\n", user->name);
    return 0;
}

int useCellRegen(Dog *user, Dog *target)
{
    int heal = 15 + (rand() % 10);
    user->hp += heal;
    printf("%s uses Cell Regeneration! +%d HP\n", user->name, heal);
    return heal;
}

int useContainedExplosion(Dog *user, Dog *target)
{
    if (user->hp > (user->maxHP * 0.25))
    {
        printf("%s containment field stable - cannot detonate!\n", user->name);
        return 0;
    }

    int dmg = user->attack * 3;
    target->hp -= dmg;
    user->hp = 0;

    printf("%s CONTAINMENT BREACH! MASSIVE EXPLOSION -%d\n", user->name, dmg);
    return dmg;
}

int useAcidSpit(Dog *user, Dog *target)
{
    int dmg = user->attack * 1.4 + (rand() % 8);
    int dot = 3 + (rand() % 4);
    target->hp -= dmg;
    printf("%s spits Acid! -%d HP\n", user->name, dmg);
    printf("%s takes %d corrosive damage next turn!\n", target->name, dot);
    return dmg;
}

int useNeuroToxin(Dog *user, Dog *target)
{
    int dmg = user->attack * 1.2;
    int speedDrop = 3;
    target->hp -= dmg;
    target->speed -= speedDrop;
    printf("%s releases Neuro Toxin! -%d HP (Speed -%d)\n", user->name, dmg, speedDrop);
    return dmg;
}

void setEnemySkillsBio(Dog *enemy, int zoneIndex)
{
    enemy->skills[0].id = SKILL_MUTATION_SURGE;
    strcpy(enemy->skills[0].name, "Mutation Surge");
    enemy->skills[0].power = 18;

    enemy->skills[1].id = SKILL_BIO_SHIELD;
    strcpy(enemy->skills[1].name, "Bio Shield");
    enemy->skills[1].power = 0;

    enemy->skills[2].id = SKILL_CELL_REGEN;
    strcpy(enemy->skills[2].name, "Cell Regeneration");
    enemy->skills[2].power = 0;

    enemy->skills[3].id = SKILL_CONTAINED_EXPLOSION;
    strcpy(enemy->skills[3].name, "Contained Explosion");
    enemy->skills[3].power = 55;

    enemy->skills[4].id = SKILL_ACID_SPIT;
    strcpy(enemy->skills[4].name, "Acid Spit");
    enemy->skills[4].power = 22;

    enemy->skills[5].id = SKILL_NEURO_TOXIN;
    strcpy(enemy->skills[5].name, "Neuro Toxin");
    enemy->skills[5].power = 20;

    enemy->numSkills = 6;

    // Progressive bio buffs per zone
    if (zoneIndex == 12) { // Outer Facility
        enemy->attack += 5;
        enemy->defense += 4;
        enemy->speed += 3;
    }
    else if (zoneIndex == 13) { // Research Hallways
        enemy->attack += 8;
        enemy->defense += 6;
        enemy->speed += 5;
    }
    else if (zoneIndex == 14) { // Containment Labs
        enemy->attack += 12;
        enemy->defense += 8;
        enemy->speed += 6;
    }
    else if (zoneIndex == 15) { // Core Chamber (Strongest)
        enemy->attack += 15;
        enemy->defense += 10;
        enemy->speed += 8;
    }
}