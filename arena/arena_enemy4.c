#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "arena_enemy4.h"
#include "arena_enemy3.h"
#include "arena_enemy2.h"
#include "arena_enemy.h"
#include "arena.h"
#include "../skill.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"

void loadArenaClassCEnemy(Dog *enemy, int index)
{
    createEnemy(enemy);

    enemy->arenaRank = 'C';
    enemy->numSkills = 4;

    if (index == 0)
    {
        strcpy(enemy->name, "Glassjaw");
        enemy->maxHP = 720;
        enemy->hp = enemy->maxHP;
        enemy->attack = 165;
        enemy->defense = 45;
        enemy->speed = 170;
        enemy->accuracy = 115;
        enemy->intelligence = 90;

        enemy->skills[0] = SKILL_RAZOR_SLASH;
        enemy->skills[1] = SKILL_FANG_STORM;
        enemy->skills[2] = SKILL_COMBAT_RUSH;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 1)
    {
        strcpy(enemy->name, "Ironmutt");
        enemy->maxHP = 980;
        enemy->hp = enemy->maxHP;
        enemy->attack = 120;
        enemy->defense = 175;
        enemy->speed = 55;
        enemy->accuracy = 95;
        enemy->intelligence = 70;

        enemy->skills[0] = SKILL_BIO_SHIELD;
        enemy->skills[1] = SKILL_REINFORCED_BITE;
        enemy->skills[2] = SKILL_CELL_REGENERATION;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 2)
    {
        strcpy(enemy->name, "Needlefang");
        enemy->maxHP = 760;
        enemy->hp = enemy->maxHP;
        enemy->attack = 135;
        enemy->defense = 70;
        enemy->speed = 155;
        enemy->accuracy = 135;
        enemy->intelligence = 120;

        enemy->skills[0] = SKILL_NEURO_TOXIN;
        enemy->skills[1] = SKILL_ACID_SPIT;
        enemy->skills[2] = SKILL_RAZOR_SLASH;
        enemy->skills[3] = SKILL_SCRATCH;
    }
    else if (index == 3)
    {
        strcpy(enemy->name, "Bloodgear");
        enemy->maxHP = 850;
        enemy->hp = enemy->maxHP;
        enemy->attack = 175;
        enemy->defense = 90;
        enemy->speed = 100;
        enemy->accuracy = 100;
        enemy->intelligence = 75;

        enemy->skills[0] = SKILL_BLOOD_FRENZY;
        enemy->skills[1] = SKILL_ENHANCED_JAW_CRUSH;
        enemy->skills[2] = SKILL_FANG_STORM;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 4)
    {
        strcpy(enemy->name, "Cryomane");
        enemy->maxHP = 800;
        enemy->hp = enemy->maxHP;
        enemy->attack = 110;
        enemy->defense = 115;
        enemy->speed = 120;
        enemy->accuracy = 125;
        enemy->intelligence = 160;

        enemy->skills[0] = SKILL_CRYO_LOCK;
        enemy->skills[1] = SKILL_NEURO_TOXIN;
        enemy->skills[2] = SKILL_BIO_SHIELD;
        enemy->skills[3] = SKILL_SCRATCH;
    }
    else if (index == 5)
    {
        strcpy(enemy->name, "Plasmutt");
        enemy->maxHP = 780;
        enemy->hp = enemy->maxHP;
        enemy->attack = 155;
        enemy->defense = 65;
        enemy->speed = 140;
        enemy->accuracy = 110;
        enemy->intelligence = 135;

        enemy->skills[0] = SKILL_PLASMA_BITE;
        enemy->skills[1] = SKILL_THUNDER_SURGE;
        enemy->skills[2] = SKILL_COMBAT_RUSH;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 6)
    {
        strcpy(enemy->name, "Sludgehound");
        enemy->maxHP = 1050;
        enemy->hp = enemy->maxHP;
        enemy->attack = 125;
        enemy->defense = 145;
        enemy->speed = 60;
        enemy->accuracy = 90;
        enemy->intelligence = 115;

        enemy->skills[0] = SKILL_ACID_SPIT;
        enemy->skills[1] = SKILL_CELL_REGENERATION;
        enemy->skills[2] = SKILL_MUTATION_SURGE;
        enemy->skills[3] = SKILL_BITE;
    }
    else
    {
        strcpy(enemy->name, "Cobalt Rex");
        enemy->maxHP = 1150;
        enemy->hp = enemy->maxHP;
        enemy->attack = 185;
        enemy->defense = 130;
        enemy->speed = 125;
        enemy->accuracy = 120;
        enemy->intelligence = 140;

        enemy->skills[0] = SKILL_APEX_OVERDRIVE;
        enemy->skills[1] = SKILL_PREDATOR_INSTINCT;
        enemy->skills[2] = SKILL_ENHANCED_JAW_CRUSH;
        enemy->skills[3] = SKILL_PLASMA_BITE;
    }
}