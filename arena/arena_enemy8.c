#include <stdio.h>
#include <string.h>
#include <windows.h>

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

// ================= CLASS SS =================
// Class SS scale:
// Normal strong stat: 830-900
// Specialty stat: 900-940
// Boss specialty: 940-960 only
// Weak stat: 400-600
// Mid stat: 650-820
//
// Notes:
// - SS is stronger than S, pero hindi pa SSS.
// - 7 enemies total.
// - Bawat enemy may 6 skills.
// - Gumamit ng Secret Lab / late-game arena skills.
// - enemy->arenaRank uses 'X' because your arena code uses X for SS.

// Helper para sa skills na wala sa dog.h SkillID.
// Gumagana ito sa skill.c dahil karamihan ng player/sparring skills
// ay naka-check gamit strcmp(s.name, "...").
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

void loadArenaClassSSEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->arenaRank = 'X'; // SS
    enemy->zoneType = ZONE_MUTANT;
    enemy->personalityType = PERSONALITY_ALPHA;
    enemy->numSkills = 6;

    if (enemyIndex == 0)
    {
        // Power execution type: sobrang lakas ng bite damage, pero hindi pinakamabilis.
        strcpy(enemy->name, "Ragnarok Tyrant");

        enemy->maxHP = 900;
        enemy->attack = 940;
        enemy->defense = 760;
        enemy->speed = 620;
        enemy->accuracy = 780;
        enemy->intelligence = 640;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Blacksite Execution", 70, 78, SKILL_BLACKSITE_EXECUTION);
        setArenaSkill(enemy, 1, "Humanoid Jaw Crush", 68, 80, SKILL_HUMANOID_JAW_CRUSH);
        setArenaSkill(enemy, 2, "Enhanced Jaw Crush", 62, 84, SKILL_ENHANCED_JAW_CRUSH);
        setArenaSkill(enemy, 3, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 4, "Armor Break", 56, 86, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 5, "Bite", 45, 92, SKILL_BITE);
    }
    else if (enemyIndex == 1)
    {
        // SS tank: makunat, nagre-regen, pero mabagal.
        strcpy(enemy->name, "Fortress Omega");

        enemy->maxHP = 960;
        enemy->attack = 700;
        enemy->defense = 940;
        enemy->speed = 430;
        enemy->accuracy = 650;
        enemy->intelligence = 820;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Bio Shield", 0, 100, SKILL_BIO_SHIELD);
        setArenaSkill(enemy, 1, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 2, "Suppression Howl", 0, 100, SKILL_SUPPRESSION_HOWL);
        setArenaSkill(enemy, 3, "Mutation Overdrive", 0, 100, SKILL_MUTATION_OVERDRIVE);
        setArenaSkill(enemy, 4, "Reinforced Bite", 58, 84, SKILL_REINFORCED_BITE);
        setArenaSkill(enemy, 5, "Acid Spit", 52, 86, SKILL_ACID_SPIT);
    }
    else if (enemyIndex == 2)
    {
        // Speed killer: halos SS speed cap, pero medyo manipis depensa.
        strcpy(enemy->name, "Zero Flashhound");

        enemy->maxHP = 820;
        enemy->attack = 860;
        enemy->defense = 560;
        enemy->speed = 940;
        enemy->accuracy = 900;
        enemy->intelligence = 720;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Combat Rush", 62, 90, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 1, "Fang Storm", 60, 82, SKILL_FANG_STORM);
        setArenaSkill(enemy, 2, "Timeline Maul", 64, 80, SKILL_TIMELINE_MAUL);
        setArenaSkill(enemy, 3, "Thunder Surge", 0, 100, SKILL_THUNDER_SURGE);
        setArenaSkill(enemy, 4, "Tactical Bite", 58, 88, SKILL_TACTICAL_BITE);
        setArenaSkill(enemy, 5, "Scratch", 42, 96, SKILL_SCRATCH);
    }
    else if (enemyIndex == 3)
    {
        // Control / debuff type: mataas INT at accuracy, maraming status style skills.
        strcpy(enemy->name, "Mindbreak Cerberus");

        enemy->maxHP = 840;
        enemy->attack = 720;
        enemy->defense = 650;
        enemy->speed = 790;
        enemy->accuracy = 930;
        enemy->intelligence = 940;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Neuro Toxin", 56, 92, SKILL_NEURO_TOXIN);
        setArenaSkill(enemy, 1, "Cryo Lock", 56, 90, SKILL_CRYO_LOCK);
        setArenaSkill(enemy, 2, "Cursed Instinct", 0, 100, SKILL_CURSED_INSTINCT);
        setArenaSkill(enemy, 3, "Suppression Howl", 0, 100, SKILL_SUPPRESSION_HOWL);
        setArenaSkill(enemy, 4, "Thunder Surge", 0, 100, SKILL_THUNDER_SURGE);
        setArenaSkill(enemy, 5, "Plasma Bite", 58, 84, SKILL_PLASMA_BITE);
    }
    else if (enemyIndex == 4)
    {
        // Hybrid elite: walang sobrang hina, pang gatekeeper bago boss.
        strcpy(enemy->name, "Eclipse Warbeast");

        enemy->maxHP = 900;
        enemy->attack = 890;
        enemy->defense = 850;
        enemy->speed = 860;
        enemy->accuracy = 840;
        enemy->intelligence = 800;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Apex Overdrive", 68, 80, SKILL_APEX_OVERDRIVE);
        setArenaSkill(enemy, 1, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 2, "Plasma Bite", 62, 84, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 3, "Razor Slash", 62, 86, SKILL_RAZOR_SLASH);
        setArenaSkill(enemy, 4, "Blood Frenzy", 0, 100, SKILL_BLOOD_FRENZY);
        setArenaSkill(enemy, 5, "Armor Break", 58, 86, SKILL_ARMOR_BREAK);
    }
    else if (enemyIndex == 5)
    {
        // Hybrid elite: walang sobrang hina, pang gatekeeper bago boss.
        strcpy(enemy->name, "Ragnarok Phantom");

        enemy->maxHP = 920;
        enemy->attack = 940;       // main specialty
        enemy->defense = 760;
        enemy->speed = 910;        // fast SS
        enemy->accuracy = 890;
        enemy->intelligence = 820;
        enemy->personalityType = PERSONALITY_DESPERATE;

        // ===== Skills from skill.c =====
        setNameBasedEnemySkill(enemy, 0, "Ragnarok Fang", 25, 15, SKILL_ATTACK);
        setNameBasedEnemySkill(enemy, 1, "Zero Phantom", 24, 14, SKILL_ATTACK);
        setNameBasedEnemySkill(enemy, 2, "Judgement Eye", 22, 14, SKILL_ATTACK);
        setNameBasedEnemySkill(enemy, 3, "Titan Aegis", 0, 15, SKILL_BUFF);

        // ===== Skills from sparring_unlocks.c =====
        setNameBasedEnemySkill(enemy, 4, "Tiny Blitz", 20, 13, SKILL_ATTACK);
        setNameBasedEnemySkill(enemy, 5, "Snoop Phantom", 28, 16, SKILL_ATTACK);
    }
    else if (enemyIndex == 6)
    {
        // SS boss: malakas all-around, pero hindi pa 999 SSS final monster.
        strcpy(enemy->name, "Imperial Fenrir");

        enemy->maxHP = 980;
        enemy->attack = 960;
        enemy->defense = 920;
        enemy->speed = 900;
        enemy->accuracy = 890;
        enemy->intelligence = 900;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Mutation Overdrive", 0, 100, SKILL_MUTATION_OVERDRIVE);
        setArenaSkill(enemy, 1, "Blacksite Execution", 74, 78, SKILL_BLACKSITE_EXECUTION);
        setArenaSkill(enemy, 2, "Humanoid Jaw Crush", 72, 80, SKILL_HUMANOID_JAW_CRUSH);
        setArenaSkill(enemy, 3, "Timeline Maul", 70, 80, SKILL_TIMELINE_MAUL);
        setArenaSkill(enemy, 4, "Apex Overdrive", 72, 78, SKILL_APEX_OVERDRIVE);
        setArenaSkill(enemy, 5, "Cursed Instinct", 0, 100, SKILL_CURSED_INSTINCT);
    }
    else
    {
        // Safety fallback kapag mali ang enemyIndex.
        loadArenaClassSSEnemy(enemy, 6);
        return;
    }

    enemy->hp = enemy->maxHP;
}
