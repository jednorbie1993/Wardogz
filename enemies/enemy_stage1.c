#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "enemy.h"
#include "../cinematic.h"
#include "../battle.h"
#include "enemy_stage1.h"


void setEnemySkillsStage1(Dog *enemy)
{
    enemy->numSkills = 0;

    enemy->skills[0] = (Skill){
        "Stray Bite",
        8,
        0,
        SKILL_DAMAGE,
        90,
        SKILL_STRAY_BITE,
        0,
        0,
        10
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
        8
    };

    enemy->skills[2] = (Skill){
        "Lock Jaw",
        12,
        0,
        SKILL_DAMAGE,
        80,
        SKILL_LOCK_JAW,
        0,
        0,
        15
    };

    enemy->numSkills = 3;

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
            20
        };

        enemy->numSkills = 4;
    }
}

void loadStage1Enemies(Dog *enemy, int zoneIndex, int i)
{
    createEnemy(enemy);

    enemy->zoneType = ZONE_CITY;
    enemy->personalityType = PERSONALITY_NORMAL;

    if (zoneIndex == 0)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Skinny Stray");
            enemy->personalityType = PERSONALITY_WEAK;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Scrap Fighter");
            enemy->attack += 3;
            enemy->defense += 2;
            enemy->personalityType = PERSONALITY_DESPERATE;
        }
        else
        {
            strcpy(enemy->name, "Alley Alpha");
            enemy->attack += 6;
            enemy->defense += 4;
            enemy->maxHP += 20;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_ALPHA;
        }
    }
    else if (zoneIndex == 1)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Rust Hound");
            enemy->defense += 3;
            enemy->personalityType = PERSONALITY_TANK;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Guard Dog");
            enemy->defense += 5;
            enemy->personalityType = PERSONALITY_TANK;
        }
        else
        {
            strcpy(enemy->name, "Iron Jaw");
            enemy->defense += 8;
            enemy->maxHP += 25;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_TANK;
        }
    }
    else if (zoneIndex == 2)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Night Stray");
            enemy->speed += 3;
            enemy->personalityType = PERSONALITY_NORMAL;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Sneak Biter");
            enemy->accuracy += 5;
            enemy->personalityType = PERSONALITY_DESPERATE;
        }
        else
        {
            strcpy(enemy->name, "Street King");
            enemy->speed += 5;
            enemy->attack += 5;
            enemy->maxHP += 15;
            enemy->hp = enemy->maxHP;
            enemy->personalityType = PERSONALITY_ALPHA;
        }
    }
    else
    {
        strcpy(enemy->name, "Unknown Dog");
        enemy->personalityType = PERSONALITY_NORMAL;
    }
    setEnemySkillsStage1(enemy);
}

int handleStage1EnemyBehavior(Dog *player, Dog *enemy, int *enemyDamage)
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

    int skillChoice = rand() % enemy->numSkills;
    Skill skill = enemy->skills[skillChoice];

    printf("\n");

    typeText(enemy->name, 25);
    typeText(" used ", 20);
    typeText(skill.name, 35);
    printf("!\n");

    cinematicDots("Enemy attacking");

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

    case SKILL_LOCK_JAW: //updated
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
    }

    return 1;
}

