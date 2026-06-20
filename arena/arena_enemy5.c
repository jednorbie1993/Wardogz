#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "arena_enemy5.h"
#include "arena_enemy4.h"
#include "arena_enemy3.h"
#include "arena_enemy2.h"
#include "arena_enemy.h"
#include "arena.h"
#include "../skill.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"

/*
    CLASS B BALANCE GUIDE

    Class C high stat      : 350 - 480
    Class B normal high    : 500 - 620
    Class B abnormal stat  : 650 - 720
    Weak stat              : 120 - 220
    Mid stat               : 250 - 450

    Monster Rancher style:
    - Hindi lahat ng stat mataas.
    - Bawat enemy may specialty.
    - May weakness pa rin para hindi pang S/SS agad.
    - 10 enemies total for random arena fights.
*/

void loadArenaClassBEnemy(Dog *enemy, int enemyIndex);
{
    createEnemy(enemy);

    enemy->arenaRank = 'B';
    enemy->numSkills = 4;

    if (index == 0)
    {
        // POWER STRIKER
        // Sobrang lakas ng attack, pero manipis depensa at average speed.
        strcpy(enemy->name, "Ruinjaw");

        enemy->maxHP = 520;
        enemy->hp = enemy->maxHP;
        enemy->attack = 690;
        enemy->defense = 180;
        enemy->speed = 310;
        enemy->accuracy = 330;
        enemy->intelligence = 160;

        enemy->skills[0] = SKILL_ENHANCED_JAW_CRUSH;
        enemy->skills[1] = SKILL_RAZOR_SLASH;
        enemy->skills[2] = SKILL_FANG_STORM;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 1)
    {
        // HEAVY TANK
        // Makunat sobra, pero mabagal at hindi sobrang lakas tumama.
        strcpy(enemy->name, "Fortress Fang");

        enemy->maxHP = 680;
        enemy->hp = enemy->maxHP;
        enemy->attack = 330;
        enemy->defense = 700;
        enemy->speed = 135;
        enemy->accuracy = 260;
        enemy->intelligence = 280;

        enemy->skills[0] = SKILL_BIO_SHIELD;
        enemy->skills[1] = SKILL_CELL_REGENERATION;
        enemy->skills[2] = SKILL_REINFORCED_BITE;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 2)
    {
        // SPEED KILLER
        // Napakabilis at accurate, pero hindi matibay.
        strcpy(enemy->name, "Veloclaw");

        enemy->maxHP = 455;
        enemy->hp = enemy->maxHP;
        enemy->attack = 500;
        enemy->defense = 190;
        enemy->speed = 710;
        enemy->accuracy = 560;
        enemy->intelligence = 260;

        enemy->skills[0] = SKILL_COMBAT_RUSH;
        enemy->skills[1] = SKILL_THUNDER_SURGE;
        enemy->skills[2] = SKILL_PLASMA_BITE;
        enemy->skills[3] = SKILL_SCRATCH;
    }
    else if (index == 3)
    {
        // STATUS / INT SPECIALIST
        // Delikado dahil sa toxin at control skills, pero mahina katawan.
        strcpy(enemy->name, "Mindmaw");

        enemy->maxHP = 430;
        enemy->hp = enemy->maxHP;
        enemy->attack = 310;
        enemy->defense = 210;
        enemy->speed = 440;
        enemy->accuracy = 620;
        enemy->intelligence = 715;

        enemy->skills[0] = SKILL_NEURO_TOXIN;
        enemy->skills[1] = SKILL_CRYO_LOCK;
        enemy->skills[2] = SKILL_ACID_SPIT;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 4)
    {
        // MUTANT BRUISER
        // Malakas at makunat, pero hindi accurate at hindi matalino.
        strcpy(enemy->name, "Brutemane");

        enemy->maxHP = 610;
        enemy->hp = enemy->maxHP;
        enemy->attack = 620;
        enemy->defense = 510;
        enemy->speed = 260;
        enemy->accuracy = 210;
        enemy->intelligence = 150;

        enemy->skills[0] = SKILL_MUTATION_SURGE;
        enemy->skills[1] = SKILL_PREDATOR_INSTINCT;
        enemy->skills[2] = SKILL_REINFORCED_BITE;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 5)
    {
        // GLASS CANNON EVO
        // Attack at accuracy mataas, pero risky dahil low HP/DEF.
        strcpy(enemy->name, "Splinter Rex");

        enemy->maxHP = 400;
        enemy->hp = enemy->maxHP;
        enemy->attack = 720;
        enemy->defense = 150;
        enemy->speed = 390;
        enemy->accuracy = 590;
        enemy->intelligence = 230;

        enemy->skills[0] = SKILL_RAZOR_SLASH;
        enemy->skills[1] = SKILL_FANG_STORM;
        enemy->skills[2] = SKILL_BLOOD_FRENZY;
        enemy->skills[3] = SKILL_SCRATCH;
    }
    else if (index == 6)
    {
        // BIO REGEN TYPE
        // HP/INT/DEF mataas, pero hindi malakas ang attack.
        strcpy(enemy->name, "Mirehound");

        enemy->maxHP = 705;
        enemy->hp = enemy->maxHP;
        enemy->attack = 280;
        enemy->defense = 560;
        enemy->speed = 210;
        enemy->accuracy = 300;
        enemy->intelligence = 610;

        enemy->skills[0] = SKILL_CELL_REGENERATION;
        enemy->skills[1] = SKILL_ACID_SPIT;
        enemy->skills[2] = SKILL_BIO_SHIELD;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 7)
    {
        // ELECTRIC BURST TYPE
        // Speed/attack mataas, pero low defense.
        strcpy(enemy->name, "Voltbreaker");

        enemy->maxHP = 500;
        enemy->hp = enemy->maxHP;
        enemy->attack = 585;
        enemy->defense = 205;
        enemy->speed = 650;
        enemy->accuracy = 455;
        enemy->intelligence = 310;

        enemy->skills[0] = SKILL_THUNDER_SURGE;
        enemy->skills[1] = SKILL_PLASMA_BITE;
        enemy->skills[2] = SKILL_COMBAT_RUSH;
        enemy->skills[3] = SKILL_BITE;
    }
    else if (index == 8)
    {
        // BALANCED ELITE
        // Walang sobrang hina, pero walang 700 stat.
        strcpy(enemy->name, "Argent Howl");

        enemy->maxHP = 590;
        enemy->hp = enemy->maxHP;
        enemy->attack = 545;
        enemy->defense = 500;
        enemy->speed = 520;
        enemy->accuracy = 430;
        enemy->intelligence = 390;

        enemy->skills[0] = SKILL_APEX_OVERDRIVE;
        enemy->skills[1] = SKILL_PREDATOR_INSTINCT;
        enemy->skills[2] = SKILL_ENHANCED_JAW_CRUSH;
        enemy->skills[3] = SKILL_BITE;
    }
    else
    {
        // CLASS B BOSS
        // Malakas all-around, pero hindi pa pang Class A/S.
        strcpy(enemy->name, "Royal Cerberus");

        enemy->maxHP = 725;
        enemy->hp = enemy->maxHP;
        enemy->attack = 680;
        enemy->defense = 610;
        enemy->speed = 560;
        enemy->accuracy = 520;
        enemy->intelligence = 475;

        enemy->skills[0] = SKILL_APEX_OVERDRIVE;
        enemy->skills[1] = SKILL_PREDATOR_INSTINCT;
        enemy->skills[2] = SKILL_PLASMA_BITE;
        enemy->skills[3] = SKILL_ENHANCED_JAW_CRUSH;
    }
}
