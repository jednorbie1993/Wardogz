#include <stdio.h>
#include <string.h>
#include <windows.h>

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

// ================= CLASS S =================
// Class S scale:
// Normal strong stat: 700-800
// Specialty / boss stat: 820-890 only
// Weak stat: 260-430
// Mid stat: 500-720
//
// Monster Rancher style:
// - Hindi lahat 999 para hindi unfair.
// - Bawat enemy may sariling specialty at weakness.
// - Gumamit ng konting Secret Lab skills kasi Class S na.
// - 11 enemies total for random arena fights.

void loadArenaClassSEnemy(Dog *enemy, int enemyIndex)
{
    createEnemy(enemy);

    enemy->arenaRank = 'S';
    enemy->zoneType = ZONE_MUTANT;
    enemy->personalityType = PERSONALITY_ALPHA;
    enemy->numSkills = 4;

    if (enemyIndex == 0)
    {
        // Pure power type: sobrang lakas bumitaw, pero medyo mabagal at mahina INT.
        strcpy(enemy->name, "Titanjaw");

        enemy->maxHP = 760;
        enemy->attack = 820;
        enemy->defense = 480;
        enemy->speed = 280;
        enemy->accuracy = 620;
        enemy->intelligence = 260;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Enhanced Jaw Crush", 58, 80, SKILL_ENHANCED_JAW_CRUSH);
        setArenaSkill(enemy, 1, "Blacksite Execution", 62, 76, SKILL_BLACKSITE_EXECUTION);
        setArenaSkill(enemy, 2, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 3, "Bite", 38, 92, SKILL_BITE);
    }
    else if (enemyIndex == 1)
    {
        // Defense wall: halos fortress, pero mabagal at hindi masyado accurate.
        strcpy(enemy->name, "Iron Bastion");

        enemy->maxHP = 820;
        enemy->attack = 500;
        enemy->defense = 850;
        enemy->speed = 260;
        enemy->accuracy = 420;
        enemy->intelligence = 600;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Bio Shield", 0, 100, SKILL_BIO_SHIELD);
        setArenaSkill(enemy, 1, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 2, "Suppression Howl", 0, 100, SKILL_SUPPRESSION_HOWL);
        setArenaSkill(enemy, 3, "Reinforced Bite", 48, 84, SKILL_REINFORCED_BITE);
    }
    else if (enemyIndex == 2)
    {
        // Speed assassin: mabilis at accurate, pero manipis depensa.
        strcpy(enemy->name, "Flashfang");

        enemy->maxHP = 620;
        enemy->attack = 760;
        enemy->defense = 300;
        enemy->speed = 850;
        enemy->accuracy = 820;
        enemy->intelligence = 500;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Combat Rush", 52, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 1, "Thunder Surge", 0, 100, SKILL_THUNDER_SURGE);
        setArenaSkill(enemy, 2, "Tactical Bite", 50, 86, SKILL_TACTICAL_BITE);
        setArenaSkill(enemy, 3, "Scratch", 36, 96, SKILL_SCRATCH);
    }
    else if (enemyIndex == 3)
    {
        // Lab control type: INT/accuracy mataas, status/debuff focus, pero low HP.
        strcpy(enemy->name, "Neuroshade");

        enemy->maxHP = 580;
        enemy->attack = 460;
        enemy->defense = 340;
        enemy->speed = 650;
        enemy->accuracy = 820;
        enemy->intelligence = 850;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Neuro Toxin", 42, 90, SKILL_NEURO_TOXIN);
        setArenaSkill(enemy, 1, "Cryo Lock", 45, 88, SKILL_CRYO_LOCK);
        setArenaSkill(enemy, 2, "Cursed Instinct", 0, 100, SKILL_CURSED_INSTINCT);
        setArenaSkill(enemy, 3, "Acid Spit", 44, 86, SKILL_ACID_SPIT);
    }
    else if (enemyIndex == 4)
    {
        // Berserker mutant: attack/speed mataas, pero low defense at low accuracy.
        strcpy(enemy->name, "Blood Apex");

        enemy->maxHP = 680;
        enemy->attack = 840;
        enemy->defense = 320;
        enemy->speed = 760;
        enemy->accuracy = 450;
        enemy->intelligence = 280;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Blood Frenzy", 0, 100, SKILL_BLOOD_FRENZY);
        setArenaSkill(enemy, 1, "Fang Storm", 54, 78, SKILL_FANG_STORM);
        setArenaSkill(enemy, 2, "Razor Slash", 57, 84, SKILL_RAZOR_SLASH);
        setArenaSkill(enemy, 3, "Mutation Overdrive", 0, 100, SKILL_MUTATION_OVERDRIVE);
    }
    else if (enemyIndex == 5)
    {
        // Elemental plasma attacker: balanced offense, defense breaker.
        strcpy(enemy->name, "Plasma Rex");

        enemy->maxHP = 720;
        enemy->attack = 780;
        enemy->defense = 580;
        enemy->speed = 660;
        enemy->accuracy = 700;
        enemy->intelligence = 620;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Plasma Bite", 56, 82, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 1, "Thunder Surge", 0, 100, SKILL_THUNDER_SURGE);
        setArenaSkill(enemy, 2, "Armor Break", 50, 86, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 3, "Bite", 40, 92, SKILL_BITE);
    }
    else if (enemyIndex == 6)
    {
        // Regeneration type: makunat, matalino, pero kulang burst damage.
        strcpy(enemy->name, "Mire Omega");

        enemy->maxHP = 850;
        enemy->attack = 520;
        enemy->defense = 720;
        enemy->speed = 400;
        enemy->accuracy = 540;
        enemy->intelligence = 780;
        enemy->personalityType = PERSONALITY_TANK;

        setArenaSkill(enemy, 0, "Cell Regeneration", 0, 100, SKILL_CELL_REGEN);
        setArenaSkill(enemy, 1, "Bio Shield", 0, 100, SKILL_BIO_SHIELD);
        setArenaSkill(enemy, 2, "Acid Spit", 46, 86, SKILL_ACID_SPIT);
        setArenaSkill(enemy, 3, "Reinforced Bite", 47, 84, SKILL_REINFORCED_BITE);
    }
    else if (enemyIndex == 7)
    {
        // Military prototype: trained, tactical, all-around pero hindi highest stat.
        strcpy(enemy->name, "K-9 Phantom Unit");

        enemy->maxHP = 720;
        enemy->attack = 740;
        enemy->defense = 680;
        enemy->speed = 720;
        enemy->accuracy = 780;
        enemy->intelligence = 700;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Tactical Bite", 52, 86, SKILL_TACTICAL_BITE);
        setArenaSkill(enemy, 1, "Armor Break", 50, 86, SKILL_ARMOR_BREAK);
        setArenaSkill(enemy, 2, "Suppression Howl", 0, 100, SKILL_SUPPRESSION_HOWL);
        setArenaSkill(enemy, 3, "Blacksite Execution", 58, 78, SKILL_BLACKSITE_EXECUTION);
    }
    else if (enemyIndex == 8)
    {
        // Timeline multi-hit type: delikado pag tumagal, pero low defense.
        strcpy(enemy->name, "Chrono Mauler");

        enemy->maxHP = 690;
        enemy->attack = 790;
        enemy->defense = 380;
        enemy->speed = 740;
        enemy->accuracy = 720;
        enemy->intelligence = 760;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Timeline Maul", 55, 80, SKILL_TIMELINE_MAUL);
        setArenaSkill(enemy, 1, "Combat Rush", 50, 88, SKILL_COMBAT_RUSH);
        setArenaSkill(enemy, 2, "Cursed Instinct", 0, 100, SKILL_CURSED_INSTINCT);
        setArenaSkill(enemy, 3, "Fang Storm", 50, 78, SKILL_FANG_STORM);
    }
    else if (enemyIndex == 9)
    {
        // Balanced Class S elite: walang obvious weakness, pero walang 970 specialty.
        strcpy(enemy->name, "Silver Chimera");

        enemy->maxHP = 760;
        enemy->attack = 780;
        enemy->defense = 740;
        enemy->speed = 720;
        enemy->accuracy = 700;
        enemy->intelligence = 680;
        enemy->personalityType = PERSONALITY_ALPHA;

        setArenaSkill(enemy, 0, "Apex Overdrive", 60, 78, SKILL_APEX_OVERDRIVE);
        setArenaSkill(enemy, 1, "Predator Instinct", 0, 100, SKILL_PREDATOR_INSTINCT);
        setArenaSkill(enemy, 2, "Plasma Bite", 54, 82, SKILL_PLASMA_BITE);
        setArenaSkill(enemy, 3, "Enhanced Jaw Crush", 56, 80, SKILL_ENHANCED_JAW_CRUSH);
    }
    else
    {
        // Class S boss: malakas all-around, pero hindi pa final SS/SSS level.
        strcpy(enemy->name, "Sovereign Cerberus");

        enemy->maxHP = 880;
        enemy->attack = 890;
        enemy->defense = 840;
        enemy->speed = 800;
        enemy->accuracy = 780;
        enemy->intelligence = 820;
        enemy->personalityType = PERSONALITY_DESPERATE;

        setArenaSkill(enemy, 0, "Mutation Overdrive", 0, 100, SKILL_MUTATION_OVERDRIVE);
        setArenaSkill(enemy, 1, "Humanoid Jaw Crush", 62, 80, SKILL_HUMANOID_JAW_CRUSH);
        setArenaSkill(enemy, 2, "Timeline Maul", 58, 78, SKILL_TIMELINE_MAUL);
        setArenaSkill(enemy, 3, "Apex Overdrive", 66, 76, SKILL_APEX_OVERDRIVE);
    }

    enemy->hp = enemy->maxHP;
}
