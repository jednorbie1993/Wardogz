#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "arena_enemy9.h"
#include "arena_enemy8.h"
#include "arena_enemy7.h"
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

// ================= CLASS SSS =================
// Class SSS scale:
// Normal strong stat: 920-970
// Specialty stat: 970-999
// Final boss specialty: 999 only
// Weak stat: 650-780
// Mid stat: 800-910
//
// Notes:
// - SSS is final arena class.
// - 4 enemies total.
// - Bawat enemy may 6 skills.
// - Mas malakas sa SS, pero may weakness pa rin bawat build.
// - enemy->arenaRank uses 'Z' because your arena code uses Z for SSS.

// Helper para sa skills na wala sa dog.h SkillID.
// Gumagana ito sa skill.c kapag ang skill ay naka-check gamit strcmp(s.name, "...").
static void setNameBasedEnemySkill(Dog *enemy, int slot, const char *name, int power, int cost, SkillType type)
{
    if (slot < 0 || slot >= MAX_SKILLS)
        return;

    strcpy(enemy->skills[slot].name, name);
    enemy->skills[slot].power = power;
    enemy->skills[slot].cost = cost;
    enemy->skills[slot].type = type;
    enemy->skills[slot].accuracy = 100;
    enemy->skills[slot].id = SKILL_NONE;
    enemy->skills[slot].cooldown = 0;
    enemy->skills[slot].cdLeft = 0;
    enemy->skills[slot].aiScore = 0;
}

void loadArenaClassSSSEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->arenaRank = 'Z'; // SSS
    enemy->zoneType = ZONE_MUTANT;
    enemy->personalityType = PERSONALITY_ALPHA;
    enemy->numSkills = 6;

    if (enemyIndex == 0)
    {
        // SSS execution type: sobrang taas attack, pero hindi tanky.
        strcpy(enemy->name, "Abyss Ragnarok");

        enemy->maxHP = 940;
        enemy->attack = 990;
        enemy->defense = 760;
        enemy->speed = 910;
        enemy->accuracy = 940;
        enemy->intelligence = 850;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Blacksite Execution", 78, 78, SKILL_BLACKSITE_EXECUTION);
        setArenaSkill(enemy, 1, "Humanoid Jaw Crush", 76, 80, SKILL_HUMANOID_JAW_CRUSH);
        setArenaSkill(enemy, 2, "Apex Overdrive", 74, 78, SKILL_APEX_OVERDRIVE);
        setArenaSkill(enemy, 3, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setNameBasedEnemySkill(enemy, 4, "Ragnarok Fang", 30, 16, SKILL_ATTACK);
        setArenaSkill(enemy, 5, "Armor Break", 64, 86, SKILL_ARMOR_BREAK);
    }
    else if (enemyIndex == 1)
    {
        // SSS fortress type: pinakamakunat, pero mabagal para may opening player.
        strcpy(enemy->name, "Titan Omega Core");

        enemy->maxHP = 999;
        enemy->attack = 850;
        enemy->defense = 999;
        enemy->speed = 650;
        enemy->accuracy = 820;
        enemy->intelligence = 930;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Bio Shield", 0, 100, SKILL_BIO_SHIELD);
        setArenaSkill(enemy, 1, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 2, "Mutation Overdrive", 0, 100, SKILL_MUTATION_OVERDRIVE);
        setArenaSkill(enemy, 3, "Suppression Howl", 0, 100, SKILL_SUPPRESSION_HOWL);
        setNameBasedEnemySkill(enemy, 4, "Titan Aegis", 0, 15, SKILL_BUFF);
        setArenaSkill(enemy, 5, "Reinforced Bite", 66, 84, SKILL_REINFORCED_BITE);
    }
    else if (enemyIndex == 2)
    {
        // SSS speed/control type: mabilis at accurate, pero mas manipis HP/defense.
        strcpy(enemy->name, "Zero Eclipse Phantom");

        enemy->maxHP = 900;
        enemy->attack = 930;
        enemy->defense = 720;
        enemy->speed = 999;
        enemy->accuracy = 980;
        enemy->intelligence = 940;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Combat Rush", 70, 90, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 1, "Timeline Maul", 72, 80, SKILL_TIMELINE_MAUL);
        setArenaSkill(enemy, 2, "Cryo Lock", 64, 90, SKILL_CRYO_LOCK);
        setArenaSkill(enemy, 3, "Thunder Surge", 0, 100, SKILL_THUNDER_SURGE);
        setNameBasedEnemySkill(enemy, 4, "Zero Phantom", 30, 15, SKILL_ATTACK);
        setNameBasedEnemySkill(enemy, 5, "Snoop Phantom", 32, 16, SKILL_ATTACK);
    }
    else if (enemyIndex == 3)
    {
        // Final SSS champion: all-around monster, pero final 1v1 lang dapat ito.
        strcpy(enemy->name, "Godfang Fenrir");

        enemy->maxHP = 999;
        enemy->attack = 999;
        enemy->defense = 970;
        enemy->speed = 960;
        enemy->accuracy = 970;
        enemy->intelligence = 980;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Mutation Overdrive", 0, 100, SKILL_MUTATION_OVERDRIVE);
        setArenaSkill(enemy, 1, "Blacksite Execution", 82, 78, SKILL_BLACKSITE_EXECUTION);
        setArenaSkill(enemy, 2, "Humanoid Jaw Crush", 80, 80, SKILL_HUMANOID_JAW_CRUSH);
        setArenaSkill(enemy, 3, "Timeline Maul", 78, 80, SKILL_TIMELINE_MAUL);
        setArenaSkill(enemy, 4, "Cursed Instinct", 0, 100, SKILL_CURSED_INSTINCT);
        setNameBasedEnemySkill(enemy, 5, "Judgement Eye", 32, 15, SKILL_ATTACK);
    }
    else
    {
        // Safety fallback kapag mali ang enemyIndex.
        loadArenaClassSSSEnemy(enemy, 3);
        return;
    }

    enemy->hp = enemy->maxHP;
}
