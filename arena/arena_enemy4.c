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

void loadArenaClassCEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->arenaRank = 'C';
    enemy->zoneType = ZONE_MUTANT;
    enemy->personalityType = PERSONALITY_NORMAL;
    enemy->numSkills = 4;

    if (enemyIndex == 0)
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
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Razor Slash", 36, 84, SKILL_RAZOR_SLASH);
        setArenaSkill(enemy, 1, "Fang Storm", 34, 82, SKILL_FANG_STORM);
        setArenaSkill(enemy, 2, "Combat Rush", 30, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 3, "Bite", 26, 92, SKILL_BITE);
    }
    else if (enemyIndex == 1)
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
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Bio Shield", 0, 100, SKILL_BIO_SHIELD);
        setArenaSkill(enemy, 1, "Reinforced Bite", 32, 84, SKILL_REINFORCED_BITE);
        setArenaSkill(enemy, 2, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 3, "Bite", 25, 92, SKILL_BITE);
    }
    else if (enemyIndex == 2)
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
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Neuro Toxin", 28, 88, SKILL_NEURO_TOXIN);
        setArenaSkill(enemy, 1, "Acid Spit", 31, 86, SKILL_ACID_SPIT);
        setArenaSkill(enemy, 2, "Cryo Lock", 24, 82, SKILL_CRYO_LOCK);
        setArenaSkill(enemy, 3, "Scratch", 22, 95, SKILL_SCRATCH);
    }
    else if (enemyIndex == 3)
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
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Blood Frenzy", 0, 100, SKILL_BLOOD_FRENZY);
        setArenaSkill(enemy, 1, "Enhanced Jaw Crush", 38, 80, SKILL_ENHANCED_JAW_CRUSH);
        setArenaSkill(enemy, 2, "Fang Storm", 35, 82, SKILL_FANG_STORM);
        setArenaSkill(enemy, 3, "Bite", 26, 92, SKILL_BITE);
    }
    else if (enemyIndex == 4)
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
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Acid Spit", 30, 84, SKILL_ACID_SPIT);
        setArenaSkill(enemy, 1, "Mutation Surge", 0, 100, SKILL_MUTATION_SURGE);
        setArenaSkill(enemy, 2, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 3, "Bite", 24, 92, SKILL_BITE);
    }
    else if (enemyIndex == 5)
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
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Thunder Surge", 34, 86, SKILL_THUNDER_SURGE);
        setArenaSkill(enemy, 1, "Plasma Bite", 36, 84, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 2, "Combat Rush", 32, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 3, "Bite", 25, 92, SKILL_BITE);
    }
    else if (enemyIndex == 6)
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
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 1, "Reinforced Bite", 34, 84, SKILL_REINFORCED_BITE);
        setArenaSkill(enemy, 2, "Enhanced Jaw Crush", 37, 80, SKILL_ENHANCED_JAW_CRUSH);
        setArenaSkill(enemy, 3, "Bite", 26, 92, SKILL_BITE);
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
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Apex Overdrive", 0, 100, SKILL_APEX_OVERDRIVE);
        setArenaSkill(enemy, 1, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 2, "Plasma Bite", 38, 84, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 3, "Enhanced Jaw Crush", 40, 80, SKILL_ENHANCED_JAW_CRUSH);
    }


    enemy->hp = enemy->maxHP;
}
