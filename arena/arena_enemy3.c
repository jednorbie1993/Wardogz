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
void loadArenaClassDEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->zoneType = ZONE_CITY;
    enemy->personalityType = PERSONALITY_NORMAL;
    enemy->numSkills = 4;

    if (enemyIndex == 0)
    {
        strcpy(enemy->name, "Gravel");
        enemy->maxHP = 270;
        enemy->attack = 45;
        enemy->defense = 105;
        enemy->speed = 90;
        enemy->accuracy = 88;
        enemy->intelligence = 68;

        setArenaSkill(enemy, 0, "Heavy Bite", 20, 88, SKILL_HEAVY_BITE);
        setArenaSkill(enemy, 1, "Lock Jaw", 18, 84, SKILL_LOCK_JAW);
        setArenaSkill(enemy, 2, "Pack Attack", 17, 90, SKILL_PACK_ATTACK);
        setArenaSkill(enemy, 3, "Iron Guard", 0, 100, SKILL_IRON_GUARD);
    }
    else if (enemyIndex == 1)
    {
        strcpy(enemy->name, "Slash");
        enemy->maxHP = 285;
        enemy->attack = 50;
        enemy->defense = 100;
        enemy->speed = 125;
        enemy->accuracy = 90;
        enemy->intelligence = 72;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Savage Fang", 22, 86, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 1, "Ambush Strike", 20, 88, SKILL_AMBUSH_STRIKE);
        setArenaSkill(enemy, 2, "Dirty Scratch", 17, 95, SKILL_DIRTY_SCRATCH);
        setArenaSkill(enemy, 3, "Combat Rush", 21, 88, SKILL_COMBAT_RUSH);
    }
    else if (enemyIndex == 2)
    {
        strcpy(enemy->name, "Brutus");
        enemy->maxHP = 320;
        enemy->attack = 52;
        enemy->defense = 125;
        enemy->speed = 80;
        enemy->accuracy = 84;
        enemy->intelligence = 65;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Tactical Guard", 0, 100, SKILL_TACTICAL_GUARD);
        setArenaSkill(enemy, 1, "Armor Break", 23, 82, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 2, "Heavy Bite", 21, 86, SKILL_HEAVY_BITE);
        setArenaSkill(enemy, 3, "Bone Breaker", 24, 80, SKILL_BONE_BREAKER);
    }
    else if (enemyIndex == 3)
    {
        strcpy(enemy->name, "Ravager");
        enemy->maxHP = 310;
        enemy->attack = 56;
        enemy->defense = 112;
        enemy->speed = 105;
        enemy->accuracy = 88;
        enemy->intelligence = 74;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Feral Rush", 22, 88, SKILL_FERAL_RUSH);
        setArenaSkill(enemy, 1, "Blood Scent", 0, 100, SKILL_BLOOD_SCENT);
        setArenaSkill(enemy, 2, "Savage Fang", 24, 84, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 3, "Alpha Rage", 25, 82, SKILL_ALPHA_RAGE);
    }
    else if (enemyIndex == 4)
    {
        strcpy(enemy->name, "Ironhide");
        enemy->maxHP = 360;
        enemy->attack = 54;
        enemy->defense = 145;
        enemy->speed = 75;
        enemy->accuracy = 82;
        enemy->intelligence = 70;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Iron Guard", 0, 100, SKILL_IRON_GUARD);
        setArenaSkill(enemy, 1, "Tactical Guard", 0, 100, SKILL_TACTICAL_GUARD);
        setArenaSkill(enemy, 2, "Armor Break", 25, 80, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 3, "Lock Jaw", 22, 82, SKILL_LOCK_JAW);
    }
    else if (enemyIndex == 5)
    {
        strcpy(enemy->name, "Blitz");
        enemy->maxHP = 300;
        enemy->attack = 58;
        enemy->defense = 108;
        enemy->speed = 135;
        enemy->accuracy = 92;
        enemy->intelligence = 78;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Combat Rush", 25, 90, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 1, "Ambush Strike", 24, 86, SKILL_AMBUSH_STRIKE);
        setArenaSkill(enemy, 2, "Feral Rush", 23, 88, SKILL_FERAL_RUSH);
        setArenaSkill(enemy, 3, "Savage Fang", 26, 84, SKILL_SAVAGE_FANG);
    }
    else if (enemyIndex == 6)
    {
        strcpy(enemy->name, "Mangler");
        enemy->maxHP = 380;
        enemy->attack = 62;
        enemy->defense = 130;
        enemy->speed = 95;
        enemy->accuracy = 86;
        enemy->intelligence = 76;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Bone Breaker", 28, 78, SKILL_BONE_BREAKER);
        setArenaSkill(enemy, 1, "Alpha Rage", 27, 82, SKILL_ALPHA_RAGE);
        setArenaSkill(enemy, 2, "Blood Scent", 0, 100, SKILL_BLOOD_SCENT);
        setArenaSkill(enemy, 3, "Heavy Bite", 25, 86, SKILL_HEAVY_BITE);
    }
    else
    {
        strcpy(enemy->name, "Junkyard Baron");
        enemy->maxHP = 430;
        enemy->attack = 68;
        enemy->defense = 140;
        enemy->speed = 115;
        enemy->accuracy = 90;
        enemy->intelligence = 85;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Alpha Rage", 32, 82, SKILL_ALPHA_RAGE);
        setArenaSkill(enemy, 1, "Savage Fang", 30, 84, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 2, "Bone Breaker", 31, 78, SKILL_BONE_BREAKER);
        setArenaSkill(enemy, 3, "Combat Rush", 28, 88, SKILL_COMBAT_RUSH);
    }

    enemy->hp = enemy->maxHP;
}