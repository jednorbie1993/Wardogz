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

// ================= CLASS B =================
// Class B scale:
// Normal strong stat: 500-620
// Small abnormal/specialty stat: 650-720
// Weak stat: 120-220
// Mid stat: 250-450
//
// Monster Rancher style:
// - Hindi lahat ng stat mataas.
// - Bawat enemy may specialty.
// - May weakness pa rin para hindi pang S/SS agad.
// - 10 enemies total for random arena fights.

void loadArenaClassBEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->arenaRank = 'B';
    enemy->zoneType = ZONE_MUTANT;
    enemy->personalityType = PERSONALITY_NORMAL;
    enemy->numSkills = 4;

    if (enemyIndex == 0)
    {
        // Power striker: sobrang lakas ng attack, pero manipis depensa.
        strcpy(enemy->name, "Ruinjaw");

        enemy->maxHP = 520;
        enemy->attack = 690;
        enemy->defense = 180;
        enemy->speed = 310;
        enemy->accuracy = 330;
        enemy->intelligence = 160;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Enhanced Jaw Crush", 46, 80, SKILL_ENHANCED_JAW_CRUSH);
        setArenaSkill(enemy, 1, "Razor Slash", 42, 84, SKILL_RAZOR_SLASH);
        setArenaSkill(enemy, 2, "Fang Storm", 37, 78, SKILL_FANG_STORM);
        setArenaSkill(enemy, 3, "Bite", 30, 92, SKILL_BITE);
    }
    else if (enemyIndex == 1)
    {
        // Heavy tank: makunat sobra, pero mabagal at hindi sobrang lakas tumama.
        strcpy(enemy->name, "Fortress Fang");

        enemy->maxHP = 680;
        enemy->attack = 330;
        enemy->defense = 700;
        enemy->speed = 135;
        enemy->accuracy = 260;
        enemy->intelligence = 280;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Bio Shield", 0, 100, SKILL_BIO_SHIELD);
        setArenaSkill(enemy, 1, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 2, "Reinforced Bite", 35, 84, SKILL_REINFORCED_BITE);
        setArenaSkill(enemy, 3, "Bite", 28, 92, SKILL_BITE);
    }
    else if (enemyIndex == 2)
    {
        // Speed killer: napakabilis at accurate, pero hindi matibay.
        strcpy(enemy->name, "Veloclaw");

        enemy->maxHP = 455;
        enemy->attack = 500;
        enemy->defense = 190;
        enemy->speed = 710;
        enemy->accuracy = 560;
        enemy->intelligence = 260;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Combat Rush", 39, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 1, "Thunder Surge", 41, 84, SKILL_THUNDER_SURGE);
        setArenaSkill(enemy, 2, "Plasma Bite", 43, 82, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 3, "Scratch", 27, 96, SKILL_SCRATCH);
    }
    else if (enemyIndex == 3)
    {
        // Status / int specialist: delikado sa toxin/control skills, pero mahina katawan.
        strcpy(enemy->name, "Mindmaw");

        enemy->maxHP = 430;
        enemy->attack = 310;
        enemy->defense = 210;
        enemy->speed = 440;
        enemy->accuracy = 620;
        enemy->intelligence = 715;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Neuro Toxin", 31, 90, SKILL_NEURO_TOXIN);
        setArenaSkill(enemy, 1, "Cryo Lock", 28, 88, SKILL_CRYO_LOCK);
        setArenaSkill(enemy, 2, "Acid Spit", 34, 86, SKILL_ACID_SPIT);
        setArenaSkill(enemy, 3, "Bite", 26, 94, SKILL_BITE);
    }
    else if (enemyIndex == 4)
    {
        // Mutant bruiser: malakas at makunat, pero hindi accurate at hindi matalino.
        strcpy(enemy->name, "Brutemane");

        enemy->maxHP = 610;
        enemy->attack = 620;
        enemy->defense = 510;
        enemy->speed = 260;
        enemy->accuracy = 210;
        enemy->intelligence = 150;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Mutation Surge", 0, 100, SKILL_MUTATION_SURGE);
        setArenaSkill(enemy, 1, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 2, "Reinforced Bite", 42, 80, SKILL_REINFORCED_BITE);
        setArenaSkill(enemy, 3, "Bite", 31, 90, SKILL_BITE);
    }
    else if (enemyIndex == 5)
    {
        // Glass cannon evo: attack at accuracy mataas, pero low HP/DEF.
        strcpy(enemy->name, "Splinter Rex");

        enemy->maxHP = 400;
        enemy->attack = 720;
        enemy->defense = 150;
        enemy->speed = 390;
        enemy->accuracy = 590;
        enemy->intelligence = 230;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Razor Slash", 48, 84, SKILL_RAZOR_SLASH);
        setArenaSkill(enemy, 1, "Fang Storm", 44, 78, SKILL_FANG_STORM);
        setArenaSkill(enemy, 2, "Blood Frenzy", 0, 100, SKILL_BLOOD_FRENZY);
        setArenaSkill(enemy, 3, "Scratch", 28, 96, SKILL_SCRATCH);
    }
    else if (enemyIndex == 6)
    {
        // Bio regen type: HP/INT/DEF mataas, pero hindi malakas ang attack.
        strcpy(enemy->name, "Mirehound");

        enemy->maxHP = 705;
        enemy->attack = 280;
        enemy->defense = 560;
        enemy->speed = 210;
        enemy->accuracy = 300;
        enemy->intelligence = 610;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 1, "Acid Spit", 34, 86, SKILL_ACID_SPIT);
        setArenaSkill(enemy, 2, "Bio Shield", 0, 100, SKILL_BIO_SHIELD);
        setArenaSkill(enemy, 3, "Bite", 27, 92, SKILL_BITE);
    }
    else if (enemyIndex == 7)
    {
        // Electric burst type: speed/attack mataas, pero low defense.
        strcpy(enemy->name, "Voltbreaker");

        enemy->maxHP = 500;
        enemy->attack = 585;
        enemy->defense = 205;
        enemy->speed = 650;
        enemy->accuracy = 455;
        enemy->intelligence = 310;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Thunder Surge", 45, 84, SKILL_THUNDER_SURGE);
        setArenaSkill(enemy, 1, "Plasma Bite", 43, 82, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 2, "Combat Rush", 39, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 3, "Bite", 30, 92, SKILL_BITE);
    }
    else if (enemyIndex == 8)
    {
        // Balanced elite: walang sobrang hina, pero walang 700 stat.
        strcpy(enemy->name, "Argent Howl");

        enemy->maxHP = 590;
        enemy->attack = 545;
        enemy->defense = 500;
        enemy->speed = 520;
        enemy->accuracy = 430;
        enemy->intelligence = 390;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Apex Overdrive", 0, 100, SKILL_APEX_OVERDRIVE);
        setArenaSkill(enemy, 1, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 2, "Enhanced Jaw Crush", 43, 82, SKILL_ENHANCED_JAW_CRUSH);
        setArenaSkill(enemy, 3, "Bite", 31, 92, SKILL_BITE);
    }
    else
    {
        // Class B boss: malakas all-around, pero hindi pa pang Class A/S.
        strcpy(enemy->name, "Royal Cerberus");

        enemy->maxHP = 725;
        enemy->attack = 680;
        enemy->defense = 610;
        enemy->speed = 560;
        enemy->accuracy = 520;
        enemy->intelligence = 475;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Apex Overdrive", 0, 100, SKILL_APEX_OVERDRIVE);
        setArenaSkill(enemy, 1, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 2, "Plasma Bite", 48, 82, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 3, "Enhanced Jaw Crush", 50, 80, SKILL_ENHANCED_JAW_CRUSH);
    }

    enemy->hp = enemy->maxHP;
}
