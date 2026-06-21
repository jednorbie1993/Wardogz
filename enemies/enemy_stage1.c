#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "enemy.h"
#include "enemy_stage1.h"
#include "../cinematic.h"
#include "../battle.h"
#include "../replay_system.h"

void setEnemySkillsStage1(Dog *enemy)
{
    enemy->numSkills = 3;

    enemy->skills[0] = (Skill){
        "Stray Bite",     // 1. Skill Name
        8,                // 2. Power / Damage
        0,                // 3. Energy Cost / Mana Cost
        SKILL_DAMAGE,     // 4. Skill Type
        90,               // 5. Accuracy (%)
        SKILL_STRAY_BITE, // 6. Skill ID
        0,                // 7. Effect Value 1
        0,                // 8. Effect Value 2
        10                // 9. Cooldown / Duration
    };

    enemy->skills[1] = (Skill){
        "Dirty Scratch",
        6,
        0,
        SKILL_DAMAGE,
        95,
        SKILL_DIRTY_SCRATCH,
        0,
        0,
        8};

    enemy->skills[2] = (Skill){
        "Lock Jaw",
        12,
        0,
        SKILL_DAMAGE,
        80,
        SKILL_LOCK_JAW,
        0,
        0,
        15};

    if (enemy->personalityType == PERSONALITY_ALPHA)
    {
        enemy->skills[3] = (Skill){
            "Alpha Rage",
            15,
            0,
            SKILL_BUFF,
            85,
            SKILL_ALPHA_RAGE,
            0,
            0,
            20};

        enemy->numSkills = 4;
    }
}

void createGrimfang(Dog *enemy)
{
    strcpy(enemy->name, "Grimfang");

    enemy->hp = 260;
    enemy->maxHP = 260;
    enemy->attack = 62;
    enemy->defense = 55;
    enemy->speed = 48;
    enemy->accuracy = 92;
    enemy->intelligence = 40;

    enemy->zoneType = ZONE_CITY;
    enemy->personalityType = PERSONALITY_ALPHA;

    enemy->numSkills = 4;

    enemy->skills[0] = (Skill){"Fang Ripper", 14, 0, SKILL_DAMAGE, 95, SKILL_FANG_RIPPER, 0, 0, 10};
    enemy->skills[1] = (Skill){"Savage Rush", 24, 0, SKILL_DAMAGE, 85, SKILL_SAVAGE_RUSH, 0, 0, 15};
    enemy->skills[2] = (Skill){"Blood Trail", 10, 0, SKILL_DAMAGE, 90, SKILL_BLOOD_TRAIL, 0, 0, 18};
    enemy->skills[3] = (Skill){"Shadow Maw", 35, 0, SKILL_DAMAGE, 80, SKILL_SHADOW_MAW, 3, 0, 25};
}

void loadStage1Enemies(Dog *enemy, int zoneIndex, int enemyIndex)
{
    createEnemy(enemy);
    if (enemyIndex == SECRET_GRIMFANG_INDEX)
    {
        createGrimfang(enemy);
        return;
    }

    enemy->zoneType = ZONE_CITY;
    enemy->personalityType = PERSONALITY_NORMAL;

    if (zoneIndex == 0)
    {
        if (enemyIndex == 0)
        {
            strcpy(enemy->name, "Skinny Stray");
            enemy->attack += 4;
            enemy->defense += 3;
            enemy->speed += 3;
            enemy->maxHP += 12;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_WEAK;
        }
        else if (enemyIndex == 1)
        {
            strcpy(enemy->name, "Scrap Fighter");
            enemy->attack += 8;
            enemy->defense += 6;
            enemy->maxHP += 18;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_DESPERATE;
        }
        else
        {
            strcpy(enemy->name, "Alley Alpha");
            enemy->attack += 13;
            enemy->defense += 10;
            enemy->speed += 4;
            enemy->maxHP += 45;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_ALPHA;
        }
    }
    else if (zoneIndex == 1)
    {
        if (enemyIndex == 0)
        {
            strcpy(enemy->name, "Rust Hound");
            enemy->defense += 8;
            enemy->maxHP += 20;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_TANK;
        }
        else if (enemyIndex == 1)
        {
            strcpy(enemy->name, "Guard Dog");
            enemy->defense += 12;
            enemy->attack += 5;
            enemy->maxHP += 28;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_TANK;
        }
        else
        {
            strcpy(enemy->name, "Iron Jaw");
            enemy->defense += 18;
            enemy->attack += 9;
            enemy->maxHP += 55;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_TANK;
        }
    }
    else if (zoneIndex == 2)
    {
        if (enemyIndex == 0)
        {
            strcpy(enemy->name, "Night Stray");
            enemy->speed += 8;
            enemy->attack += 5;
            enemy->maxHP += 18;
            enemy->hp = enemy->maxHP;
        }
        else if (enemyIndex == 1)
        {
            strcpy(enemy->name, "Sneak Biter");
            enemy->accuracy += 8;
            enemy->attack += 7;
            enemy->speed += 5;
            enemy->maxHP += 22;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_DESPERATE;
        }
        else
        {
            strcpy(enemy->name, "Street King");
            enemy->speed += 12;
            enemy->attack += 12;
            enemy->defense += 6;
            enemy->maxHP += 45;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_ALPHA;
        }
    }
    else
    {
        strcpy(enemy->name, "Unknown Dog");
    }

    setEnemySkillsStage1(enemy);
}

void applyStage1Personality(Dog *player, Dog *enemy, int *enemyDamage)
{
    if (enemy->personalityType == PERSONALITY_ALPHA)
    {
        *enemyDamage += 6;

        if (rand() % 100 < 20)
        {
            printf("\n");
            typeText(enemy->name, 30);
            typeText(" is ENRAGED!\n", 30);

            *enemyDamage += 8;

            waitForEnter();
            system("cls");
            displayBattleStatus(*player, *enemy);
        }

        if (enemy->zoneType == ZONE_MUTANT &&
            enemy->hp < enemy->maxHP * 0.70 &&
            !enemy->mutationTriggered)
        {
            char *mutationLines[] =
            {
                "Experimental genes activated!",
                "Prototype limiters released!",
                "Predatory instincts unleashed!",
                "Mutation level rising!",
                "Combat adaptation detected!"
            };

            int randomLine = rand() % 5;

            printf("\n");

            typeText(enemy->name, 30);
            typeText(" is mutating!\n", 30);

            typeText(mutationLines[randomLine], 30);
            printf("\n");

            typeText("Attack increased!\n", 30);

            *enemyDamage += 3;

            enemy->mutationTriggered = 1;

            waitForEnter();
            system("cls");
            displayBattleStatus(*player, *enemy);
        }
    }
    else if (enemy->personalityType == PERSONALITY_TANK)
    {
        *enemyDamage -= 2;

        if (rand() % 100 < 30)
        {
            printf("\nEnemy HARDENED!\n");

            *enemyDamage = (*enemyDamage * 70) / 100;

            waitForEnter();
            system("cls");
            displayBattleStatus(*player, *enemy);
        }
    }
    else if (enemy->personalityType == PERSONALITY_DESPERATE)
    {
        if (enemy->hp < enemy->maxHP / 2)
        {
            *enemyDamage += 5;

            printf("\nEnemy is DESPERATE!\n");

            waitForEnter();
            system("cls");
            displayBattleStatus(*player, *enemy);
        }
    }
    else if (enemy->personalityType == PERSONALITY_WEAK)
    {
        *enemyDamage -= 2;
    }

    if (*enemyDamage < 0)
    {
        *enemyDamage = 0;
    }
}

void useStage1EnemySkill(Dog *player, Dog *enemy, Skill skill, int *enemyDamage)
{
    switch (skill.id)
    {
    case SKILL_STRAY_BITE:
        *enemyDamage += skill.power;
        break;

    case SKILL_DIRTY_SCRATCH:
        *enemyDamage += skill.power;

        if (rand() % 100 < 20)
        {
            player->isBleeding = 1;
            player->bleedTurns = 2;
            player->bleedDamage = 3;

            printf("You started bleeding!\n");
        }
        break;

    case SKILL_LOCK_JAW:
        *enemyDamage += skill.power;
        break;

    case SKILL_ALPHA_RAGE:
        *enemyDamage += skill.power;
        enemy->attack += 2;

        printf("%s grows more aggressive!\n", enemy->name);
        break;

    default:
        *enemyDamage += 4;
        break;
    case SKILL_FANG_RIPPER:
        *enemyDamage += skill.power;
        break;

    case SKILL_SAVAGE_RUSH:
        *enemyDamage += skill.power;
        enemy->hp -= 6;
        printf("%s took 6 recoil damage!\n", enemy->name);
        break;

    case SKILL_BLOOD_TRAIL:
        *enemyDamage += skill.power;

        if (rand() % 100 < 35)
        {
            player->isBleeding = 1;
            player->bleedTurns = 3;
            player->bleedDamage = 4;
            printf("You are bleeding from Blood Trail!\n");
        }
        break;

    case SKILL_SHADOW_MAW:
        *enemyDamage += skill.power;

        if (rand() % 100 < 25)
        {
            player->isBleeding = 1;
            player->bleedTurns = 3;
            player->bleedDamage = 5;
            printf("Shadow Maw caused heavy bleeding!\n");
        }
        break;
    }
}

int handleStage1EnemyBehavior(Dog *player, Dog *enemy, int *enemyDamage)
{
    if (enemy->numSkills <= 0)
    {
        return 0;
    }

    int skillChoice = rand() % enemy->numSkills;
    Skill skill = enemy->skills[skillChoice];

    printf("\n");

    typeText(enemy->name, 25);
    typeText(" used ", 20);
    typeText(skill.name, 35);
    printf("!\n");

    cinematicDots("Enemy attacking");

    useStage1EnemySkill(player, enemy, skill, enemyDamage);

    applyStage1Personality(player, enemy, enemyDamage);

    // Damage safety cap for Stage 1.
    // Keeps early-game fights fair even after enemy stat increases.
    if (*enemyDamage < 3)
        *enemyDamage = 3;

    if (*enemyDamage > 55)
        *enemyDamage = 55;

    return 1;
}