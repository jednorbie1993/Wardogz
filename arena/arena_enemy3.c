#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "arena_enemy3.h"
#include "arena_enemy2.h"
#include "arena_enemy.h"
#include "arena.h"
#include "../skill.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"

// ================= CLASS D =================
// Class D scale:
// Normal strong stat: 240-300
// Small abnormal/specialty stat: 310-330
// Weak stat: 80-150
// Mid stat: 160-230

void loadArenaClassDEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->arenaRank = 'D';
    enemy->zoneType = ZONE_CITY;
    enemy->personalityType = PERSONALITY_NORMAL;
    enemy->numSkills = 4;

    if (enemyIndex == 0)
    {
        // Tank type: mataas HP/DEF, mahina ATK
        strcpy(enemy->name, "Gravel");
        enemy->maxHP = 285;
        enemy->attack = 145;
        enemy->defense = 275;
        enemy->speed = 150;
        enemy->accuracy = 165;
        enemy->intelligence = 125;

        setArenaSkill(enemy, 0, "Heavy Bite", 20, 88, SKILL_HEAVY_BITE);
        setArenaSkill(enemy, 1, "Lock Jaw", 18, 84, SKILL_LOCK_JAW);
        setArenaSkill(enemy, 2, "Pack Attack", 17, 90, SKILL_PACK_ATTACK);
        setArenaSkill(enemy, 3, "Iron Guard", 0, 100, SKILL_IRON_GUARD);
    }
    else if (enemyIndex == 1)
    {
        // Speed type: mabilis pero manipis defense
        strcpy(enemy->name, "Slash");
        enemy->maxHP = 245;
        enemy->attack = 230;
        enemy->defense = 115;
        enemy->speed = 305;
        enemy->accuracy = 245;
        enemy->intelligence = 140;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Savage Fang", 22, 86, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 1, "Ambush Strike", 20, 88, SKILL_AMBUSH_STRIKE);
        setArenaSkill(enemy, 2, "Dirty Scratch", 17, 95, SKILL_DIRTY_SCRATCH);
        setArenaSkill(enemy, 3, "Combat Rush", 21, 88, SKILL_COMBAT_RUSH);
    }
    else if (enemyIndex == 2)
    {
        // Heavy bruiser: makapal at may decent power, mabagal
        strcpy(enemy->name, "Brutus");
        enemy->maxHP = 320;
        enemy->attack = 255;
        enemy->defense = 300;
        enemy->speed = 95;
        enemy->accuracy = 170;
        enemy->intelligence = 115;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Tactical Guard", 0, 100, SKILL_TACTICAL_GUARD);
        setArenaSkill(enemy, 1, "Armor Break", 23, 82, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 2, "Heavy Bite", 21, 86, SKILL_HEAVY_BITE);
        setArenaSkill(enemy, 3, "Bone Breaker", 24, 80, SKILL_BONE_BREAKER);
    }
    else if (enemyIndex == 3)
    {
        // Berserker: mataas ATK, mid speed, mahina INT
        strcpy(enemy->name, "Ravager");
        enemy->maxHP = 275;
        enemy->attack = 315;
        enemy->defense = 170;
        enemy->speed = 225;
        enemy->accuracy = 190;
        enemy->intelligence = 90;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Feral Rush", 22, 88, SKILL_FERAL_RUSH);
        setArenaSkill(enemy, 1, "Blood Scent", 0, 100, SKILL_BLOOD_SCENT);
        setArenaSkill(enemy, 2, "Savage Fang", 24, 84, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 3, "Alpha Rage", 25, 82, SKILL_ALPHA_RAGE);
    }
    else if (enemyIndex == 4)
    {
        // Wall type: abnormal DEF for Class D, pero mabagal at hindi malakas
        strcpy(enemy->name, "Ironhide");
        enemy->maxHP = 335;
        enemy->attack = 175;
        enemy->defense = 330;
        enemy->speed = 80;
        enemy->accuracy = 150;
        enemy->intelligence = 130;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Iron Guard", 0, 100, SKILL_IRON_GUARD);
        setArenaSkill(enemy, 1, "Tactical Guard", 0, 100, SKILL_TACTICAL_GUARD);
        setArenaSkill(enemy, 2, "Armor Break", 25, 80, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 3, "Lock Jaw", 22, 82, SKILL_LOCK_JAW);
    }
    else if (enemyIndex == 5)
    {
        // Fast attacker: high SPD/ACC, average HP/DEF
        strcpy(enemy->name, "Blitz");
        enemy->maxHP = 255;
        enemy->attack = 260;
        enemy->defense = 135;
        enemy->speed = 325;
        enemy->accuracy = 285;
        enemy->intelligence = 155;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Combat Rush", 25, 90, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 1, "Ambush Strike", 24, 86, SKILL_AMBUSH_STRIKE);
        setArenaSkill(enemy, 2, "Feral Rush", 23, 88, SKILL_FERAL_RUSH);
        setArenaSkill(enemy, 3, "Savage Fang", 26, 84, SKILL_SAVAGE_FANG);
    }
    else if (enemyIndex == 6)
    {
        // Power type: highest damage sa normal D enemy, pero accuracy/speed not perfect
        strcpy(enemy->name, "Mangler");
        enemy->maxHP = 305;
        enemy->attack = 325;
        enemy->defense = 215;
        enemy->speed = 140;
        enemy->accuracy = 165;
        enemy->intelligence = 110;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Bone Breaker", 28, 78, SKILL_BONE_BREAKER);
        setArenaSkill(enemy, 1, "Alpha Rage", 27, 82, SKILL_ALPHA_RAGE);
        setArenaSkill(enemy, 2, "Blood Scent", 0, 100, SKILL_BLOOD_SCENT);
        setArenaSkill(enemy, 3, "Heavy Bite", 25, 86, SKILL_HEAVY_BITE);
    }
    else
    {
        // Class D boss: high stats pero hindi pa Class C level
        strcpy(enemy->name, "Junkyard Baron");
        enemy->maxHP = 350;
        enemy->attack = 335;
        enemy->defense = 285;
        enemy->speed = 230;
        enemy->accuracy = 235;
        enemy->intelligence = 180;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Alpha Rage", 32, 82, SKILL_ALPHA_RAGE);
        setArenaSkill(enemy, 1, "Savage Fang", 30, 84, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 2, "Bone Breaker", 31, 78, SKILL_BONE_BREAKER);
        setArenaSkill(enemy, 3, "Combat Rush", 28, 88, SKILL_COMBAT_RUSH);
    }

    enemy->hp = enemy->maxHP;
}
