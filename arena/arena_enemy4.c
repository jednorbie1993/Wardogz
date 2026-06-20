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

/*
    CLASS C BALANCE GUIDE

    Class C normal high stat  : 350 - 400
    Class C abnormal stat     : 420 - 480
    Weak stat                 : 70  - 150
    Mid stat                  : 160 - 300

    Monster Rancher style:
    - Hindi lahat mataas.
    - Bawat enemy may 1 or 2 abnormal stats.
    - May kapalit na mahinang stats.
*/

void loadArenaClassCEnemy(Dog *enemy, int index)
{
    createEnemy(enemy);

    enemy->arenaRank = 'C';
    enemy->numSkills = 4;

    if (index == 0)
    {
        // POWER TYPE
        // Sobrang lakas ng attack, pero glass cannon.
        strcpy(enemy->name, "Glassjaw");

        enemy->maxHP = 310;
        enemy->hp = enemy->maxHP;
        enemy->attack = 475;
        enemy->defense = 95;
        enemy->speed = 115;
        enemy->accuracy = 210;
        enemy->intelligence = 80;

        enemy->skills[0] = SKILL_RAZOR_SLASH;
        enemy->skills[1] = SKILL_FANG_STORM;
        enemy->skills[2] = SKILL_COMBAT_RUSH;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 1)
    {
        // TANK TYPE
        // Matigas sobra, pero mabagal at hindi ganun kalakas tumama.
        strcpy(enemy->name, "Ironhide");

        enemy->maxHP = 430;
        enemy->hp = enemy->maxHP;
        enemy->attack = 210;
        enemy->defense = 460;
        enemy->speed = 75;
        enemy->accuracy = 175;
        enemy->intelligence = 120;

        enemy->skills[0] = SKILL_BIO_SHIELD;
        enemy->skills[1] = SKILL_REINFORCED_BITE;
        enemy->skills[2] = SKILL_CELL_REGENERATION;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 2)
    {
        // STATUS / INT TYPE
        // Mataas skill/intelligence at accuracy, pero mahina katawan.
        strcpy(enemy->name, "Neurofang");

        enemy->maxHP = 285;
        enemy->hp = enemy->maxHP;
        enemy->attack = 180;
        enemy->defense = 135;
        enemy->speed = 330;
        enemy->accuracy = 420;
        enemy->intelligence = 470;

        enemy->skills[0] = SKILL_NEURO_TOXIN;
        enemy->skills[1] = SKILL_ACID_SPIT;
        enemy->skills[2] = SKILL_CRYO_LOCK;
        enemy->skills[3] = SKILL_SCRATCH;
    }
    else if (index == 3)
    {
        // BERSERKER TYPE
        // Mataas attack, decent speed, pero mahina intelligence.
        strcpy(enemy->name, "Bloodmaw");

        enemy->maxHP = 365;
        enemy->hp = enemy->maxHP;
        enemy->attack = 445;
        enemy->defense = 180;
        enemy->speed = 260;
        enemy->accuracy = 170;
        enemy->intelligence = 90;

        enemy->skills[0] = SKILL_BLOOD_FRENZY;
        enemy->skills[1] = SKILL_ENHANCED_JAW_CRUSH;
        enemy->skills[2] = SKILL_FANG_STORM;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 4)
    {
        // BIO TANK TYPE
        // HP/DEF/INT mataas, pero mabagal at hindi accurate.
        strcpy(enemy->name, "Sludgehound");

        enemy->maxHP = 480;
        enemy->hp = enemy->maxHP;
        enemy->attack = 170;
        enemy->defense = 390;
        enemy->speed = 90;
        enemy->accuracy = 150;
        enemy->intelligence = 420;

        enemy->skills[0] = SKILL_ACID_SPIT;
        enemy->skills[1] = SKILL_MUTATION_SURGE;
        enemy->skills[2] = SKILL_CELL_REGENERATION;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 5)
    {
        // SPEED TYPE
        // Sobrang bilis, okay attack, pero manipis defense.
        strcpy(enemy->name, "Shockfang");

        enemy->maxHP = 300;
        enemy->hp = enemy->maxHP;
        enemy->attack = 350;
        enemy->defense = 120;
        enemy->speed = 460;
        enemy->accuracy = 300;
        enemy->intelligence = 160;

        enemy->skills[0] = SKILL_THUNDER_SURGE;
        enemy->skills[1] = SKILL_PLASMA_BITE;
        enemy->skills[2] = SKILL_COMBAT_RUSH;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 6)
    {
        // MUTANT BALANCED TYPE
        // Malakas at makunat, pero mababa speed/accuracy/int.
        strcpy(enemy->name, "Chimera");

        enemy->maxHP = 410;
        enemy->hp = enemy->maxHP;
        enemy->attack = 405;
        enemy->defense = 310;
        enemy->speed = 145;
        enemy->accuracy = 140;
        enemy->intelligence = 100;

        enemy->skills[0] = SKILL_PREDATOR_INSTINCT;
        enemy->skills[1] = SKILL_REINFORCED_BITE;
        enemy->skills[2] = SKILL_ENHANCED_JAW_CRUSH;
        enemy->skills[3] = SKILL_BITE;
    }
    else
    {
        // CLASS C BOSS
        // Strong all around, pero hindi pa pang Class B/S.
        strcpy(enemy->name, "Cobalt Rex");

        enemy->maxHP = 450;
        enemy->hp = enemy->maxHP;
        enemy->attack = 470;
        enemy->defense = 370;
        enemy->speed = 320;
        enemy->accuracy = 250;
        enemy->intelligence = 260;

        enemy->skills[0] = SKILL_APEX_OVERDRIVE;
        enemy->skills[1] = SKILL_PREDATOR_INSTINCT;
        enemy->skills[2] = SKILL_PLASMA_BITE;
        enemy->skills[3] = SKILL_ENHANCED_JAW_CRUSH;
    }
}
