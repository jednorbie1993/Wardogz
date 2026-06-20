#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "arena_enemy2.h"
#include "arena_enemy.h"
#include "arena.h"
#include "../skill.h"
#include "../cinematic.h"
#include "../enemies/enemy.h"


// ================= CLASS E =================
void loadArenaClassEEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->zoneType = ZONE_CITY;
    enemy->personalityType = PERSONALITY_NORMAL;
    enemy->numSkills = 4;

    if (enemyIndex == 0)
    {
        strcpy(enemy->name, "Bruiser");
        enemy->maxHP = 180;
        enemy->attack = 28;
        enemy->defense = 80;
        enemy->speed = 82;
        enemy->accuracy = 88;
        enemy->intelligence = 60;

        setArenaSkill(enemy, 0, "Heavy Bite", 15, 88, SKILL_HEAVY_BITE);
        setArenaSkill(enemy, 1, "Lock Jaw", 14, 84, SKILL_LOCK_JAW);
        setArenaSkill(enemy, 2, "Pack Attack", 13, 90, SKILL_PACK_ATTACK);
        setArenaSkill(enemy, 3, "Iron Guard", 0, 100, SKILL_IRON_GUARD);
    }
    else if (enemyIndex == 1)
    {
        strcpy(enemy->name, "Spike");
        enemy->maxHP = 170;
        enemy->attack = 30;
        enemy->defense = 72;
        enemy->speed = 110;
        enemy->accuracy = 90;
        enemy->intelligence = 62;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Savage Fang", 17, 86, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 1, "Ambush", 14, 90, SKILL_AMBUSH);
        setArenaSkill(enemy, 2, "Dirty Scratch", 12, 95, SKILL_DIRTY_SCRATCH);
        setArenaSkill(enemy, 3, "Combat Rush", 16, 88, SKILL_COMBAT_RUSH);
    }
    else if (enemyIndex == 2)
    {
        strcpy(enemy->name, "Fang");
        enemy->maxHP = 195;
        enemy->attack = 32;
        enemy->defense = 85;
        enemy->speed = 96;
        enemy->accuracy = 88;
        enemy->intelligence = 70;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Bone Breaker", 18, 82, SKILL_BONE_BREAKER);
        setArenaSkill(enemy, 1, "Feral Rush", 15, 88, SKILL_FERAL_RUSH);
        setArenaSkill(enemy, 2, "Blood Scent", 0, 100, SKILL_BLOOD_SCENT);
        setArenaSkill(enemy, 3, "Alpha Rage", 17, 84, SKILL_ALPHA_RAGE);
    }
    else if (enemyIndex == 3)
    {
        strcpy(enemy->name, "Crusher");
        enemy->maxHP = 220;
        enemy->attack = 34;
        enemy->defense = 105;
        enemy->speed = 70;
        enemy->accuracy = 84;
        enemy->intelligence = 58;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Tactical Guard", 0, 100, SKILL_TACTICAL_GUARD);
        setArenaSkill(enemy, 1, "Armor Break", 18, 82, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 2, "Heavy Bite", 17, 86, SKILL_HEAVY_BITE);
        setArenaSkill(enemy, 3, "Lock Jaw", 16, 80, SKILL_LOCK_JAW);
    }
    else
    {
        strcpy(enemy->name, "Pit King");
        enemy->maxHP = 250;
        enemy->attack = 40;
        enemy->defense = 95;
        enemy->speed = 100;
        enemy->accuracy = 90;
        enemy->intelligence = 78;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Savage Fang", 20, 86, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 1, "Combat Rush", 18, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 2, "Bone Breaker", 21, 80, SKILL_BONE_BREAKER);
        setArenaSkill(enemy, 3, "Alpha Rage", 22, 82, SKILL_ALPHA_RAGE);
    }

    enemy->hp = enemy->maxHP;
}