#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemy.h"
#include "../dog.h"
#include "enemy_stage4.h"
#include "../replay_system.h"

/*
    BALANCED BIO-LAB DAMAGE
    - Stage 4 enemy stats were raised so enemies feel tougher.
    - Skill damage was changed from raw attack multipliers to capped scaling.
    - This prevents sudden 700+ damage while keeping battles longer.
*/
static int bioScaledDamage(Dog *user, Dog *target, int base, int atkDiv, int defDiv, int minDmg, int maxDmg)
{
    int dmg = base + (user->attack / atkDiv) + (rand() % 11);

    if (target->defense > 0)
        dmg -= target->defense / defDiv;

    if (dmg < minDmg)
        dmg = minDmg;

    if (dmg > maxDmg)
        dmg = maxDmg;

    return dmg;
}

static void clampDogHP(Dog *d)
{
    if (d->hp < 0)
        d->hp = 0;

    if (d->hp > d->maxHP)
        d->hp = d->maxHP;
}


void createOmegaPrime(Dog *enemy)
{
    createEnemy(enemy);

    strcpy(enemy->name, "Omega Prime");

    enemy->zoneType = ZONE_BIOLAB;
    enemy->personalityType = PERSONALITY_ALPHA;

    enemy->attack += 260;
    enemy->defense += 210;
    enemy->speed += 120;
    enemy->maxHP += 650;
    enemy->hp = enemy->maxHP;

    enemy->numSkills = 4;

    enemy->skills[0].id = SKILL_MUTATION_SURGE;
    strcpy(enemy->skills[0].name, "Mutation Surge");
    enemy->skills[0].power = 28;

    enemy->skills[1].id = SKILL_ACID_SPIT;
    strcpy(enemy->skills[1].name, "Acid Spit");
    enemy->skills[1].power = 26;

    enemy->skills[2].id = SKILL_NEURO_TOXIN;
    strcpy(enemy->skills[2].name, "Neuro Toxin");
    enemy->skills[2].power = 24;

    enemy->skills[3].id = SKILL_CONTAINED_EXPLOSION;
    strcpy(enemy->skills[3].name, "Core Breach");
    enemy->skills[3].power = 60;
}

void loadStage4Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);
    if (i == SECRET_OMEGA_INDEX)
    {
        createOmegaPrime(enemy);
        return;
    }

    enemy->numSkills = 6;
    enemy->zoneType = ZONE_BIOLAB;

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
            enemy->attack += 95;
            enemy->defense += 75;
            enemy->speed += 20;
            enemy->maxHP += 220;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Drone-Assisted K-9");
            enemy->attack += 105;
            enemy->speed += 45;
            enemy->defense += 70;
            enemy->maxHP += 210;
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
            enemy->attack += 120;
            enemy->defense += 90;
            enemy->speed += 24;
            enemy->maxHP += 260;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Experiment Alpha");
            enemy->attack += 132;
            enemy->defense += 100;
            enemy->speed += 28;
            enemy->maxHP += 285;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Failed Enhancement");
            enemy->attack += 138;
            enemy->speed += 42;
            enemy->defense += 82;
            enemy->maxHP += 270;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Unstable Subject");
            enemy->attack += 145;
            enemy->speed += 55;
            enemy->defense += 78;
            enemy->maxHP += 300;
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
            enemy->attack += 155;
            enemy->defense += 125;
            enemy->speed += 30;
            enemy->maxHP += 340;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Bio-Mech Hound");
            enemy->attack += 148;
            enemy->defense += 140;
            enemy->speed += 24;
            enemy->maxHP += 360;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Rage Subject");
            enemy->attack += 170;
            enemy->speed += 50;
            enemy->defense += 105;
            enemy->maxHP += 330;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 3)
        {
            strcpy(enemy->name, "Prototype K-9");
            enemy->attack += 165;
            enemy->defense += 130;
            enemy->speed += 40;
            enemy->maxHP += 380;
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
            enemy->attack += 190;
            enemy->defense += 150;
            enemy->speed += 42;
            enemy->maxHP += 430;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Facility Alpha");
            enemy->attack += 205;
            enemy->defense += 165;
            enemy->speed += 48;
            enemy->maxHP += 470;
            enemy->hp = enemy->maxHP;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "PROTOTYPE ZERO");
            enemy->attack += 225;
            enemy->defense += 180;
            enemy->speed += 65;
            enemy->maxHP += 520;
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
    int dmg = bioScaledDamage(user, target, 32, 5, 42, 18, 95);

    target->hp -= dmg;
    clampDogHP(target);

    printf("%s uses Mutation Surge! -%d HP\n", user->name, dmg);
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
    int heal = 25 + (user->maxHP / 25) + (rand() % 12);

    if (heal > 70)
        heal = 70;

    user->hp += heal;
    clampDogHP(user);

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

    int dmg = bioScaledDamage(user, target, 70, 4, 38, 45, 160);

    target->hp -= dmg;
    clampDogHP(target);

    user->hp = 0;

    printf("%s CONTAINMENT BREACH! Controlled explosion -%d HP\n", user->name, dmg);
    return dmg;
}

int useAcidSpit(Dog *user, Dog *target)
{
    int dmg = bioScaledDamage(user, target, 28, 5, 45, 16, 90);
    int dot = 3 + (rand() % 4);

    target->hp -= dmg;
    clampDogHP(target);

    printf("%s spits Acid! -%d HP\n", user->name, dmg);
    printf("%s takes %d corrosive damage next turn!\n", target->name, dot);
    return dmg;
}

int useNeuroToxin(Dog *user, Dog *target)
{
    int dmg = bioScaledDamage(user, target, 24, 6, 48, 14, 80);
    int speedDrop = 3;

    target->hp -= dmg;
    clampDogHP(target);

    target->speed -= speedDrop;
    if (target->speed < 1)
        target->speed = 1;

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
        enemy->attack += 8;
        enemy->defense += 6;
        enemy->speed += 4;
    }
    else if (zoneIndex == 13) { // Research Hallways
        enemy->attack += 12;
        enemy->defense += 9;
        enemy->speed += 6;
    }
    else if (zoneIndex == 14) { // Containment Labs
        enemy->attack += 16;
        enemy->defense += 12;
        enemy->speed += 8;
    }
    else if (zoneIndex == 15) { // Core Chamber (Strongest)
        enemy->attack += 22;
        enemy->defense += 16;
        enemy->speed += 10;
    }
}