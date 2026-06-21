#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "arena_enemy6.h"
#include "arena_enemy5.h"
#include "arena_enemy4.h"
#include "arena_enemy3.h"
#include "arena_enemy2.h"
#include "arena_enemy.h"
#include "arena.h"
#include "../skill.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"

// ================= CLASS A =================
// Class A scale:
// Normal strong stat: 520-600
// Specialty stat: 610-640 only for special builds / boss style
// Weak stat: 180-300
// Mid stat: 350-500
//
// Reminder scale:
// F  = max around 150
// E  = max around 200
// D  = max around 300
// C  = max around 400, abnormal can reach 450-480
// B  = max around 500, abnormal can reach 550
// A  = max around 600
// S  = 700-800 depende build
// SS = around 900
// SSS = 900-999
//
// Monster Rancher style:
// - Mas malakas sa Class B pero hindi pa pang S.
// - Bawat enemy may specialty at weakness.
// - 10 enemies total for random arena fights.

void loadArenaClassAEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->arenaRank = 'A';
    enemy->zoneType = ZONE_MUTANT;
    enemy->personalityType = PERSONALITY_NORMAL;
    enemy->numSkills = 4;

    if (enemyIndex == 0)
    {
        // Clean striker: mataas attack/accuracy, pero average defense.
        strcpy(enemy->name, "Crimson Veyron");

        enemy->maxHP = 560;
        enemy->attack = 600;
        enemy->defense = 360;
        enemy->speed = 470;
        enemy->accuracy = 575;
        enemy->intelligence = 330;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Tactical Bite", 49, 86, SKILL_TACTICAL_BITE);
        setArenaSkill(enemy, 1, "Razor Slash", 47, 84, SKILL_RAZOR_SLASH);
        setArenaSkill(enemy, 2, "Armor Break", 42, 82, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 3, "Bite", 32, 92, SKILL_BITE);
    }
    else if (enemyIndex == 1)
    {
        // Iron wall: mataas HP/DEF, pero mabagal.
        strcpy(enemy->name, "Granite Maw");

        enemy->maxHP = 625;
        enemy->attack = 430;
        enemy->defense = 620;
        enemy->speed = 220;
        enemy->accuracy = 360;
        enemy->intelligence = 420;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Bio Shield", 0, 100, SKILL_BIO_SHIELD);
        setArenaSkill(enemy, 1, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 2, "Reinforced Bite", 42, 84, SKILL_REINFORCED_BITE);
        setArenaSkill(enemy, 3, "Armor Break", 38, 82, SKILL_ARMOR_BREAK);
    }
    else if (enemyIndex == 2)
    {
        // Speed assassin: mabilis at accurate, pero hindi makunat.
        strcpy(enemy->name, "Silver Dashfang");

        enemy->maxHP = 500;
        enemy->attack = 540;
        enemy->defense = 285;
        enemy->speed = 630;
        enemy->accuracy = 590;
        enemy->intelligence = 360;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Combat Rush", 45, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 1, "Thunder Surge", 48, 84, SKILL_THUNDER_SURGE);
        setArenaSkill(enemy, 2, "Fang Storm", 43, 78, SKILL_FANG_STORM);
        setArenaSkill(enemy, 3, "Scratch", 30, 96, SKILL_SCRATCH);
    }
    else if (enemyIndex == 3)
    {
        // Control specialist: intelligence/accuracy mataas, pero low HP.
        strcpy(enemy->name, "Null Howler");

        enemy->maxHP = 480;
        enemy->attack = 390;
        enemy->defense = 300;
        enemy->speed = 455;
        enemy->accuracy = 600;
        enemy->intelligence = 625;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Suppression Howl", 0, 100, SKILL_SUPPRESSION_HOWL);
        setArenaSkill(enemy, 1, "Cryo Lock", 34, 88, SKILL_CRYO_LOCK);
        setArenaSkill(enemy, 2, "Neuro Toxin", 35, 90, SKILL_NEURO_TOXIN);
        setArenaSkill(enemy, 3, "Acid Spit", 38, 86, SKILL_ACID_SPIT);
    }
    else if (enemyIndex == 4)
    {
        // Berserker: matinding attack, pero may accuracy/defense weakness.
        strcpy(enemy->name, "Warspike Rex");

        enemy->maxHP = 585;
        enemy->attack = 635;
        enemy->defense = 335;
        enemy->speed = 420;
        enemy->accuracy = 305;
        enemy->intelligence = 250;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Blood Frenzy", 0, 100, SKILL_BLOOD_FRENZY);
        setArenaSkill(enemy, 1, "Enhanced Jaw Crush", 52, 80, SKILL_ENHANCED_JAW_CRUSH);
        setArenaSkill(enemy, 2, "Razor Slash", 48, 84, SKILL_RAZOR_SLASH);
        setArenaSkill(enemy, 3, "Bite", 34, 90, SKILL_BITE);
    }
    else if (enemyIndex == 5)
    {
        // Plasma hunter: balanced damage with good speed, pero hindi tanky.
        strcpy(enemy->name, "Plasma Jackal");

        enemy->maxHP = 530;
        enemy->attack = 560;
        enemy->defense = 340;
        enemy->speed = 545;
        enemy->accuracy = 510;
        enemy->intelligence = 445;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Plasma Bite", 51, 82, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 1, "Thunder Surge", 47, 84, SKILL_THUNDER_SURGE);
        setArenaSkill(enemy, 2, "Combat Rush", 44, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 3, "Tactical Bite", 43, 86, SKILL_TACTICAL_BITE);
    }
    else if (enemyIndex == 6)
    {
        // Tactical tank-breaker: good intelligence/accuracy, pang basag depensa.
        strcpy(enemy->name, "Breakfang Atlas");

        enemy->maxHP = 570;
        enemy->attack = 525;
        enemy->defense = 470;
        enemy->speed = 390;
        enemy->accuracy = 555;
        enemy->intelligence = 570;
        enemy->personalityType = PERSONALITY_NORMAL;

        setArenaSkill(enemy, 0, "Armor Break", 48, 84, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 1, "Tactical Bite", 47, 86, SKILL_TACTICAL_BITE);
        setArenaSkill(enemy, 2, "Suppression Howl", 0, 100, SKILL_SUPPRESSION_HOWL);
        setArenaSkill(enemy, 3, "Reinforced Bite", 41, 84, SKILL_REINFORCED_BITE);
    }
    else if (enemyIndex == 7)
    {
        // Regen bruiser: makunat at stable, pero hindi super bilis.
        strcpy(enemy->name, "Vita Cerber");

        enemy->maxHP = 640;
        enemy->attack = 470;
        enemy->defense = 555;
        enemy->speed = 315;
        enemy->accuracy = 410;
        enemy->intelligence = 520;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 1, "Bio Shield", 0, 100, SKILL_BIO_SHIELD);
        setArenaSkill(enemy, 2, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 3, "Reinforced Bite", 43, 84, SKILL_REINFORCED_BITE);
    }
    else if (enemyIndex == 8)
    {
        // Balanced elite: walang sobrang hina, solid lahat pero hindi pang S.
        strcpy(enemy->name, "Aurum Fenrir");

        enemy->maxHP = 600;
        enemy->attack = 575;
        enemy->defense = 535;
        enemy->speed = 520;
        enemy->accuracy = 500;
        enemy->intelligence = 490;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Apex Overdrive", 0, 100, SKILL_APEX_OVERDRIVE);
        setArenaSkill(enemy, 1, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 2, "Plasma Bite", 50, 82, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 3, "Enhanced Jaw Crush", 49, 80, SKILL_ENHANCED_JAW_CRUSH);
    }
    else
    {
        // Class A boss: peak A class, pero hindi pa S class.
        strcpy(enemy->name, "King Ragnarok");

        enemy->maxHP = 650;
        enemy->attack = 640;
        enemy->defense = 600;
        enemy->speed = 555;
        enemy->accuracy = 560;
        enemy->intelligence = 540;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Apex Overdrive", 0, 100, SKILL_APEX_OVERDRIVE);
        setArenaSkill(enemy, 1, "Blacksite Execution", 56, 78, SKILL_BLACKSITE_EXECUTION);
        setArenaSkill(enemy, 2, "Plasma Bite", 53, 82, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 3, "Enhanced Jaw Crush", 52, 80, SKILL_ENHANCED_JAW_CRUSH);
    }

    enemy->hp = enemy->maxHP;
}
