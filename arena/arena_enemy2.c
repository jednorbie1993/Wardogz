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
// Class E scale:
// Normal high stat: 150-200
// Boss/specialty can slightly pass 200
// Weak stat: 45-90
// Skill power usually: 12-22
void loadArenaClassEEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->zoneType = ZONE_CITY;
    enemy->personalityType = PERSONALITY_NORMAL;
    enemy->numSkills = 4;

    if (enemyIndex == 0)
    {
        // Tank beginner
        strcpy(enemy->name, "Bruiser");
        enemy->maxHP = 185;
        enemy->attack = 95;
        enemy->defense = 155;
        enemy->speed = 78;
        enemy->accuracy = 92;
        enemy->intelligence = 65;

        setArenaSkill(enemy, 0, "Heavy Bite", 15, 88, SKILL_HEAVY_BITE);
        setArenaSkill(enemy, 1, "Lock Jaw", 14, 84, SKILL_LOCK_JAW);
        setArenaSkill(enemy, 2, "Pack Attack", 13, 90, SKILL_PACK_ATTACK);
        setArenaSkill(enemy, 3, "Iron Guard", 0, 100, SKILL_IRON_GUARD);
    }
    else if (enemyIndex == 1)
    {
        // Fast attacker
        strcpy(enemy->name, "Spike");
        enemy->maxHP = 165;
        enemy->attack = 120;
        enemy->defense = 85;
        enemy->speed = 175;
        enemy->accuracy = 110;
        enemy->intelligence = 70;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Savage Fang", 17, 86, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 1, "Ambush", 14, 90, SKILL_AMBUSH);
        setArenaSkill(enemy, 2, "Dirty Scratch", 12, 95, SKILL_DIRTY_SCRATCH);
        setArenaSkill(enemy, 3, "Combat Rush", 16, 88, SKILL_COMBAT_RUSH);
    }
    else if (enemyIndex == 2)
    {
        // Desperate attacker
        strcpy(enemy->name, "Fang");
        enemy->maxHP = 195;
        enemy->attack = 145;
        enemy->defense = 100;
        enemy->speed = 125;
        enemy->accuracy = 100;
        enemy->intelligence = 78;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Bone Breaker", 18, 82, SKILL_BONE_BREAKER);
        setArenaSkill(enemy, 1, "Feral Rush", 15, 88, SKILL_FERAL_RUSH);
        setArenaSkill(enemy, 2, "Blood Scent", 0, 100, SKILL_BLOOD_SCENT);
        setArenaSkill(enemy, 3, "Alpha Rage", 17, 84, SKILL_ALPHA_RAGE);
    }
    else if (enemyIndex == 3)
    {
        // Heavy tank
        strcpy(enemy->name, "Crusher");
        enemy->maxHP = 215;
        enemy->attack = 110;
        enemy->defense = 190;
        enemy->speed = 60;
        enemy->accuracy = 88;
        enemy->intelligence = 62;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Tactical Guard", 0, 100, SKILL_TACTICAL_GUARD);
        setArenaSkill(enemy, 1, "Armor Break", 18, 82, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 2, "Heavy Bite", 17, 86, SKILL_HEAVY_BITE);
        setArenaSkill(enemy, 3, "Lock Jaw", 16, 80, SKILL_LOCK_JAW);
    }
    else if (enemyIndex == 4)
    {
        // High defense but weak speed
        strcpy(enemy->name, "Twister");
        enemy->maxHP = 190;
        enemy->attack = 125;
        enemy->defense = 200;
        enemy->speed = 75;
        enemy->accuracy = 105;
        enemy->intelligence = 85;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Heavy Bite", 18, 88, SKILL_HEAVY_BITE);
        setArenaSkill(enemy, 1, "Savage Fang", 20, 80, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 2, "Last Stand", 0, 100, SKILL_LAST_STAND);
        setArenaSkill(enemy, 3, "Lock Jaw", 17, 82, SKILL_LOCK_JAW);
    }
    else
    {
        // Class E boss
        strcpy(enemy->name, "Pit King");
        enemy->maxHP = 235;
        enemy->attack = 165;
        enemy->defense = 145;
        enemy->speed = 135;
        enemy->accuracy = 110;
        enemy->intelligence = 90;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Savage Fang", 20, 86, SKILL_SAVAGE_FANG);
        setArenaSkill(enemy, 1, "Combat Rush", 18, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 2, "Bone Breaker", 21, 80, SKILL_BONE_BREAKER);
        setArenaSkill(enemy, 3, "Alpha Rage", 22, 82, SKILL_ALPHA_RAGE);
    }

    enemy->hp = enemy->maxHP;
}
