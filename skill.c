#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dog.h"
#include <windows.h>
#include "stat.h"
#include "skill.h"
#include "cinematic.h"

// ================= DAMAGE TIERS =================
// Hindi na kailangan magdagdag sa dog.h.
// Dito lang muna naka-classify ang attack skills.
#define TIER_NORMAL   1
#define TIER_STRONG   2
#define TIER_ULTIMATE 3

int getSkillTier(Skill s)
{
    // Ultimate skills
    if (strcmp(s.name, "Ragnarok Fang") == 0)
        return TIER_ULTIMATE;

    // Strong / late-game / secret attack skills
    if (strcmp(s.name, "Shadow Bite") == 0 ||
        strcmp(s.name, "Dire Bite") == 0 ||
        strcmp(s.name, "Ambush Strike") == 0 ||
        strcmp(s.name, "Omega Bite") == 0 ||
        strcmp(s.name, "X Fang") == 0 ||
        strcmp(s.name, "Blood Frenzy") == 0 ||
        strcmp(s.name, "Phantom Rush") == 0 ||
        strcmp(s.name, "Shadow Blitz") == 0 ||
        strcmp(s.name, "Zero Phantom") == 0 ||
        strcmp(s.name, "Fatal Aim") == 0 ||
        strcmp(s.name, "Judgement Eye") == 0 ||
        strcmp(s.name, "Snoop Phantom") == 0 ||
        strcmp(s.name, "Tiny Blitz") == 0 ||
        strcmp(s.name, "Chubby Bulldozer") == 0 ||
        strcmp(s.name, "Jeward Precision") == 0)
    {
        return TIER_STRONG;
    }

    // Default attack skills
    return TIER_NORMAL;
}

int computeBaseDamage(Dog *player, Dog *enemy, Skill s)
{
    int tier = getSkillTier(s);
    int dmg;

    if (tier == TIER_ULTIMATE)
    {
        dmg = randRange(180, 250);
    }
    else if (tier == TIER_STRONG)
    {
        dmg = randRange(120, 180);
    }
    else
    {
        dmg = randRange(80, 140);
    }

    // Small stat influence only, para hindi sobrang laki kapag 999 stats.
    int penalty = getFatiguePenalty(player->fatigue);
    int atk = player->attack - penalty;
    if (atk < 1)
        atk = 1;

    int statBonus = (atk - enemy->defense) / 40;

    if (statBonus > 20)
        statBonus = 20;
    if (statBonus < -20)
        statBonus = -20;

    dmg += statBonus;

    if (dmg < 1)
        dmg = 1;

    return dmg;
}

void applyAttackSkill(Dog *player, Dog *enemy, Skill s, int *damage)
{
    printf("\nYou used %s!\n", s.name);

    cinematicPause(250);

    *damage = computeBaseDamage(player, enemy, s);

    printf("Damage: -%d HP\n", *damage);

    cinematicPause(400);
}

void applyBuffSkill(Dog *player, Dog *enemy, Skill s)
{
    printf("You used %s!\n", s.name);

    if (strcmp(s.name, "Titan Aegis") == 0)
    {
        player->defense += 40;
        player->hp += 15;
        if (player->hp > player->maxHP)
            player->hp = player->maxHP;

        player->fatigue -= 10;
        if (player->fatigue < 0)
            player->fatigue = 0;
    }
    else if (strcmp(s.name, "Iron Guard") == 0)
    {
        player->defense = clamp(player->defense + 5);
    }
    else if (strcmp(s.name, "Steel Wall") == 0)
    {
        player->defense += 20;
        if (player->defense > MAX_STAT)
            player->defense = MAX_STAT;

        player->fatigue += 5;
        if (player->fatigue > player->maxFatigue)
            player->fatigue = player->maxFatigue;
    }
    else if (strcmp(s.name, "Fortress Stance") == 0)
    {
        player->defense += 40;
        if (player->defense > MAX_STAT)
            player->defense = MAX_STAT;

        player->speed -= 20;
        if (player->speed < MIN_STAT)
            player->speed = MIN_STAT;

        player->fatigue += 10;
        if (player->fatigue > player->maxFatigue)
            player->fatigue = player->maxFatigue;
    }
}

void applyHealSkill(Dog *player, Skill s)
{
    printf("You used %s!\n", s.name);

    if (strcmp(s.name, "Last Stand") == 0)
    {
        int minHeal = 196;
        int maxHeal = 220;

        if (player->maxHP >= 600)
            maxHeal = 270;

        if (player->maxHP >= 800)
            maxHeal = 320;

        if (player->maxHP >= 900)
            maxHeal = 350;

        if (player->maxHP >= 999)
        {
            minHeal = 210;
            maxHeal = 400;
        }

        int healAmount = minHeal + rand() % (maxHeal - minHeal + 1);

        player->hp += healAmount;

        if (player->hp > player->maxHP)
            player->hp = player->maxHP;

        printf("LAST STAND RECOVERY!\n");
        printf("Healed +%d HP!\n", healAmount);
    }
}

void checkSkillUnlock(Dog *d)
{
    // ================= SECRET ENEMY SKILLS =================
    if (d->defeatedGrimfangX && d->skillCount < MAX_SKILLS && !hasSkill(d, "X Fang"))
    {
        strcpy(d->skills[d->skillCount].name, "X Fang");
        d->skills[d->skillCount].power = 32;
        d->skills[d->skillCount].cost = 15;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_X_FANG;

        printf("NEW SECRET SKILL UNLOCKED: X Fang!\n");
        d->skillCount++;
    }
    if (d->defeatedGrimfang && d->skillCount < MAX_SKILLS && !hasSkill(d, "Shadow Bite"))
    {
        strcpy(d->skills[d->skillCount].name, "Shadow Bite");
        d->skills[d->skillCount].power = 18;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_SHADOW_BITE;

        printf("NEW SECRET SKILL UNLOCKED: Shadow Bite!\n");
        d->skillCount++;
    }

    if (d->defeatedDiremaw && d->skillCount < MAX_SKILLS && !hasSkill(d, "Dire Bite"))
    {
        strcpy(d->skills[d->skillCount].name, "Dire Bite");
        d->skills[d->skillCount].power = 22;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_DIRE_BITE;

        printf("NEW SECRET SKILL UNLOCKED: Dire Bite!\n");
        d->skillCount++;
    }
    if (d->defeatedBlackclaw && d->skillCount < MAX_SKILLS && !hasSkill(d, "Ambush Strike"))
    {
        strcpy(d->skills[d->skillCount].name, "Ambush Strike");
        d->skills[d->skillCount].power = 24;
        d->skills[d->skillCount].cost = 11;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_AMBUSH_STRIKE;

        printf("NEW SECRET SKILL UNLOCKED: Ambush Strike!\n");
        d->skillCount++;
    }
    if (d->defeatedOmega && d->skillCount < MAX_SKILLS && !hasSkill(d, "Omega Bite"))
    {
        strcpy(d->skills[d->skillCount].name, "Omega Bite");
        d->skills[d->skillCount].power = 28;
        d->skills[d->skillCount].cost = 13;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_OMEGA_BITE;

        printf("NEW SECRET SKILL UNLOCKED: Omega Bite!\n");
        d->skillCount++;
    }
    // ================= SPEED =================
    if (d->speed >= 100 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Quick Dash"))
    {
        strcpy(d->skills[d->skillCount].name, "Quick Dash");
        d->skills[d->skillCount].power = 7;
        d->skills[d->skillCount].cost = 6;
        d->skills[d->skillCount].type = SKILL_DAMAGE; // ✅ FIX

        printf("NEW SKILL UNLOCKED: Quick Dash!\n");
        d->skillCount++;
    }

    if (d->speed >= 180 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Flash Step"))
    {
        strcpy(d->skills[d->skillCount].name, "Flash Step");
        d->skills[d->skillCount].power = 9;
        d->skills[d->skillCount].cost = 7;
        d->skills[d->skillCount].type = SKILL_DAMAGE; // ✅ FIX

        printf("NEW SKILL UNLOCKED: Flash Step!\n");
        d->skillCount++;
    }
    // ================= SPEED (MID GAME) =================
    if (d->speed >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Phantom Rush"))
    {
        strcpy(d->skills[d->skillCount].name, "Phantom Rush");
        d->skills[d->skillCount].power = 12;
        d->skills[d->skillCount].cost = 9;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Phantom Rush!\n");
        d->skillCount++;
    }

    if (d->speed >= 350 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Shadow Blitz"))
    {
        strcpy(d->skills[d->skillCount].name, "Shadow Blitz");
        d->skills[d->skillCount].power = 15;
        d->skills[d->skillCount].cost = 11;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Shadow Blitz!\n");
        d->skillCount++;
    }
    if (d->speed >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Zero Phantom"))
    {
        strcpy(d->skills[d->skillCount].name, "Zero Phantom");
        d->skills[d->skillCount].power = 24;
        d->skills[d->skillCount].cost = 14;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Zero Phantom!\n");
        d->skillCount++;
    }

    // ================= ATTACK =================
    if (d->attack >= 150 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Heavy Bite"))
    {
        strcpy(d->skills[d->skillCount].name, "Heavy Bite");
        d->skills[d->skillCount].power = 10;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Heavy Bite!\n");
        d->skillCount++;
    }

    if (d->attack >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Savage Fang"))
    {
        strcpy(d->skills[d->skillCount].name, "Savage Fang");
        d->skills[d->skillCount].power = 14;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Savage Fang!\n");
        d->skillCount++;
    }

    if (d->attack >= 320 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Blood Frenzy"))
    {
        strcpy(d->skills[d->skillCount].name, "Blood Frenzy");
        d->skills[d->skillCount].power = 18;
        d->skills[d->skillCount].cost = 12;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Blood Frenzy!\n");
        d->skillCount++;
    }
    if (d->attack >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Ragnarok Fang"))
    {
        strcpy(d->skills[d->skillCount].name, "Ragnarok Fang");
        d->skills[d->skillCount].power = 25;
        d->skills[d->skillCount].cost = 15;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Ragnarok Fang!\n");
        d->skillCount++;
    }

    // ================= DEFENSE =================
    if (d->defense >= 120 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Iron Guard"))
    {
        strcpy(d->skills[d->skillCount].name, "Iron Guard");
        d->skills[d->skillCount].power = 0;
        d->skills[d->skillCount].cost = 5;
        d->skills[d->skillCount].type = SKILL_BUFF;

        printf("NEW SKILL UNLOCKED: Iron Guard!\n");
        d->skillCount++;
    }
    // ================= DEFENSE (MID GAME) =================
    if (d->defense >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Steel Wall"))
    {
        strcpy(d->skills[d->skillCount].name, "Steel Wall");
        d->skills[d->skillCount].power = 0;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_BUFF;

        printf("NEW SKILL UNLOCKED: Steel Wall!\n");
        d->skillCount++;
    }

    if (d->defense >= 350 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Fortress Stance"))
    {
        strcpy(d->skills[d->skillCount].name, "Fortress Stance");
        d->skills[d->skillCount].power = 0;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_BUFF;

        printf("NEW SKILL UNLOCKED: Fortress Stance!\n");
        d->skillCount++;
    }
    if (d->defense >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Titan Aegis"))
    {
        strcpy(d->skills[d->skillCount].name, "Titan Aegis");
        d->skills[d->skillCount].power = 0;
        d->skills[d->skillCount].cost = 15;
        d->skills[d->skillCount].type = SKILL_BUFF;

        printf("NEW SKILL UNLOCKED: Titan Aegis!\n");
        d->skillCount++;
    }

    // ================= ACCURACY =================
    if (d->accuracy >= 130 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Sure Strike"))
    {
        strcpy(d->skills[d->skillCount].name, "Sure Strike");
        d->skills[d->skillCount].power = 8;
        d->skills[d->skillCount].cost = 6;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Sure Strike!\n");
        d->skillCount++;
    }
    // ================= ACCURACY (MID GAME) =================
    if (d->accuracy >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Dead Eye"))
    {
        strcpy(d->skills[d->skillCount].name, "Dead Eye");
        d->skills[d->skillCount].power = 11;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Dead Eye!\n");
        d->skillCount++;
    }

    if (d->accuracy >= 350 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Fatal Aim"))
    {
        strcpy(d->skills[d->skillCount].name, "Fatal Aim");
        d->skills[d->skillCount].power = 14;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Fatal Aim!\n");
        d->skillCount++;
    }
    if (d->accuracy >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Judgement Eye"))
    {
        strcpy(d->skills[d->skillCount].name, "Judgement Eye");
        d->skills[d->skillCount].power = 22;
        d->skills[d->skillCount].cost = 14;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printf("NEW SKILL UNLOCKED: Judgement Eye!\n");
        d->skillCount++;
    }

    // ================= HP =================
    if (d->maxHP >= 200 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Last Stand"))
    {
        strcpy(d->skills[d->skillCount].name, "Last Stand");
        d->skills[d->skillCount].power = 12;
        d->skills[d->skillCount].cost = 9;
        d->skills[d->skillCount].type = SKILL_HEAL;

        printf("NEW SKILL UNLOCKED: Last Stand!\n");
        d->skillCount++;
    }
}

void applySkillEffect(Dog *player, Dog *enemy, Skill s, int *damage)
{
    if (s.type == SKILL_DAMAGE)
    {
        applyAttackSkill(player, enemy, s, damage);
    }
    else if (s.type == SKILL_BUFF)
    {
        applyBuffSkill(player, enemy, s);
        *damage = 0;
    }
    else if (s.type == SKILL_HEAL)
    {
        applyHealSkill(player, s);
        *damage = 0;
    }
}

int hasEquippedSkill(Dog *d, const char *skillName)
{
    for (int i = 0; i < d->maxSkillSlots; i++)
    {
        int idx = d->equipped[i];

        if (idx != -1 && strcmp(d->skills[idx].name, skillName) == 0)
            return 1;
    }

    return 0;
}

int hasSecretComboSet(Dog *d)
{
    return hasEquippedSkill(d, "X Fang") &&
           hasEquippedSkill(d, "Shadow Bite") &&
           hasEquippedSkill(d, "Dire Bite") &&
           hasEquippedSkill(d, "Ambush Strike") &&
           hasEquippedSkill(d, "Omega Bite");
}

void applySpecialEffects(Dog *player, Dog *enemy, Skill s, int *damage)
{
    //  ALL SPECIAL EFFECTS HERE
    if (strcmp(s.name, "Shadow Bite") == 0)
    {
        printf("SHADOW BITE!\n");

        *damage += 10;

        enemy->isBleeding = 1;
        enemy->bleedTurns = 3;

        enemy->accuracy -= 10;
        if (enemy->accuracy < 1)
            enemy->accuracy = 1;

        printf("Enemy is BLEEDING!\n");
        printf("Enemy Accuracy -10!\n");
    }

    else if (strcmp(s.name, "Dire Bite") == 0)
    {
        printf("DIRE BITE!\n");

        int hit1 = *damage;
        int hit2 = *damage / 2;

        *damage = hit1 + hit2;

        enemy->isBleeding = 1;
        enemy->bleedTurns = 4;

        printf("Double bite!\n");
        printf("Enemy is BLEEDING!\n");
    }

    else if (strcmp(s.name, "Ambush Strike") == 0)
    {
        printf("AMBUSH STRIKE!\n");

        *damage += 18;

        if (player->speed > enemy->speed)
        {
            *damage += 25;
            printf("Speed advantage bonus!\n");
        }

        if (rand() % 100 < 35)
        {
            enemy->isConfused = 1;
            enemy->confuseTurns = 2;
            printf("Enemy is CONFUSED!\n");
        }
    }

    else if (strcmp(s.name, "Omega Bite") == 0)
    {
        printf("OMEGA BITE!\n");

        *damage += 25;

        enemy->defense -= 20;
        if (enemy->defense < 0)
            enemy->defense = 0;

        enemy->attack -= 10;
        if (enemy->attack < 1)
            enemy->attack = 1;

        printf("Enemy DEF -20!\n");
        printf("Enemy ATK -10!\n");
    }

    else if (strcmp(s.name, "X Fang") == 0)
    {
        printf("X FANG!\n");

        int base = *damage + 20;

        int hit1 = base;
        int hit2 = base * 7 / 10;
        int hit3 = base * 5 / 10;

        *damage = hit1 + hit2 + hit3;

        enemy->defense -= 18;
        if (enemy->defense < 0)
            enemy->defense = 0;

        if (rand() % 100 < 30)
        {
            enemy->isConfused = 1;
            enemy->confuseTurns = 2;
            printf("Enemy is CONFUSED!\n");
        }

        printf("Triple X combo!\n");
        printf("Enemy DEF -18!\n");
    }

    else if (strcmp(s.name, "Flash Step") == 0)
    {
        printf("A blinding strike!\n");
        if (rand() % 100 < 30)
        {
            enemy->isConfused = 1;
            enemy->confuseTurns = 2 + rand() % 2;
            printf("Enemy is CONFUSED!\n");
        }
    }

    else if (strcmp(s.name, "Savage Fang") == 0)
    {
        printf("A vicious tearing attack!\n");
        if (rand() % 100 < 40)
        {
            enemy->isBleeding = 1;
            enemy->bleedTurns = 3;
            printf("Enemy is BLEEDING!\n");
        }
    }

    else if (strcmp(s.name, "Ragnarok Fang") == 0)
    {
        printf("THE WORLD TREMBLES UNDER RAGNAROK FANG!\n");

        // Random hit display only: 1-3 hits
        int hits = 1 + rand() % 3;
        printf("%d HIT DESTRUCTION!\n", hits);

        // Damage range is already handled by computeBaseDamage(): 180-250.
        // Critical stays in battle.c para hindi doble critical.

        // DEF down chance 60%
        if (rand() % 100 < 60)
        {
            int defReduce = 19 + rand() % 12; // 19-30

            enemy->defense -= defReduce;

            if (enemy->defense < 0)
                enemy->defense = 0;

            printf("Enemy DEF -%d!\n", defReduce);
        }

        // Bleed chance 30%
        if (rand() % 100 < 30)
        {
            enemy->isBleeding = 1;
            enemy->bleedTurns = 3;

            printf("Enemy is BLEEDING!\n");
        }
    }

    // ================= SPARRING TECHNIQUES =================
    else if (strcmp(s.name, "Ossas Counter") == 0)
    {
        printf("OSSAS COUNTER STANCE!\n");

        *damage = 0;

        player->isCountering = 1;
        player->counterDamage = (player->attack / 3) + 10;

        if (player->counterDamage > 40)
            player->counterDamage = 40;

        printf("Counter trap set!\n");
    }

    else if (strcmp(s.name, "Tiny Blitz") == 0)
    {
        int hit1 = *damage;
        int hit2 = (*damage * 7) / 10;
        int hit3 = (*damage * 5) / 10;

        *damage = hit1 + hit2 + hit3;

        printf("Triple Blitz!\n");
    }

    else if (strcmp(s.name, "Snoop Phantom") == 0)
    {
        *damage *= 2;

        enemy->isConfused = 1;
        enemy->confuseTurns = 4;

        enemy->isBleeding = 1;
        enemy->bleedTurns = 3;

        printf("DOUBLE PHANTOM + STATUS!\n");
    }

    // ================= NORMAL ATTACK EFFECTS =================
    else if (strcmp(s.name, "Quick Dash") == 0)
    {
        printf("A fast strike!\n");
    }

    else if (strcmp(s.name, "Heavy Bite") == 0)
    {
        printf("Armor breaking bite!\n");
        enemy->defense -= 5;
        if (enemy->defense < 0)
            enemy->defense = 0;
        printf("Enemy DEF reduced!\n");
    }

    else if (strcmp(s.name, "Sure Strike") == 0)
    {
        printf("An unavoidable attack!\n");
        *damage += 5;
        enemy->accuracy = 1000;
    }

    else if (strcmp(s.name, "Blood Frenzy") == 0)
    {
        printf("You enter a BLOOD FRENZY!\n");
        *damage += 15;

        enemy->isBleeding = 1;
        enemy->bleedTurns = 4;

        printf("Enemy is BLEEDING heavily!\n");

        int recoil = 10;
        player->hp -= recoil;

        printf("You hurt yourself for %d recoil!\n", recoil);
    }

    else if (strcmp(s.name, "Phantom Rush") == 0)
    {
        printf("You vanish and strike multiple times!\n");

        int hit1 = *damage;
        int hit2 = *damage / 2;

        *damage = hit1 + hit2 + (rand() % 6);

        printf("First strike: %d\n", hit1);
        printf("Second strike: %d\n", hit2);
    }

    else if (strcmp(s.name, "Shadow Blitz") == 0)
    {
        printf("You melt into the shadows and strike instantly!\n");

        int base = *damage;

        int hit1 = base;
        int hit2 = (int)(base * 0.7);
        int hit3 = (int)(base * 0.5);

        int total = hit1 + hit2 + hit3;

        total += 10 + (rand() % 11);

        if (rand() % 100 < 50)
        {
            printf("SHADOW CRITICAL STRIKE!\n");
            total += 20;
        }

        *damage = total;

        printf("Hit 1: %d\n", hit1);
        printf("Hit 2: %d\n", hit2);
        printf("Hit 3: %d\n", hit3);
    }

    else if (strcmp(s.name, "Dead Eye") == 0)
    {
        printf("You focus and lock onto the target...\n");

        int preciseDamage = *damage + 15;

        if (rand() % 100 < 35)
        {
            printf("CRITICAL DEAD EYE SHOT!\n");
            preciseDamage += 20;
        }

        preciseDamage += (player->accuracy / 50);

        *damage = preciseDamage;

        printf("Dead Eye hits cleanly!\n");
    }

    else if (strcmp(s.name, "Fatal Aim") == 0)
    {
        printf("You lock in a fatal trajectory...\n");

        int dmg = *damage + 20;

        enemy->defense -= 15;
        if (enemy->defense < 0)
            enemy->defense = 0;

        if (enemy->hp < enemy->maxHP * 0.3)
        {
            dmg += 25;
            printf("EXECUTION BONUS!\n");
        }

        if (rand() % 100 < 40)
        {
            printf("FATAL CRITICAL HIT!\n");
            dmg += 20;
        }

        *damage = dmg;

        printf("Fatal Aim strikes deep!\n");
    }

    else if (strcmp(s.name, "Judgement Eye") == 0)
    {
        printf("You gaze into the enemy's fate...\n");

        int dmg = *damage + 25;

        enemy->defense -= 20;
        if (enemy->defense < 0)
            enemy->defense = 0;

        if (rand() % 100 < 35)
        {
            enemy->isConfused = 1;
            enemy->confuseTurns = 2 + rand() % 2;
            printf("Enemy's mind breaks under JUDGEMENT!\n");
        }

        if (enemy->hp < enemy->maxHP * 0.4)
        {
            dmg += 30;
            printf("JUDGEMENT EXECUTION BONUS!\n");
        }

        if (rand() % 100 < 45)
        {
            dmg += 20;
            printf("CRITICAL JUDGEMENT STRIKE!\n");
        }

        *damage = dmg;

        printf("Judgement Eye pierces the soul!\n");
    }

    else if (strcmp(s.name, "Zero Phantom") == 0)
    {
        printf("ZERO PHANTOM ACTIVATED!\n");

        int base = *damage + (player->speed / 15);

        int hit1 = base;
        int hit2 = base * 7 / 10;
        int hit3 = base * 5 / 10;

        *damage = hit1 + hit2 + hit3;

        enemy->defense -= enemy->defense / 3;

        if (rand() % 100 < 40)
        {
            enemy->isConfused = 1;
            enemy->confuseTurns = 2;
            printf("Enemy is CONFUSED!\n");
        }

        printf("Enemy DEF reduced by 1/3!\n");
    }

    else if (strcmp(s.name, "Chubby Bulldozer") == 0)
    {
        printf("CHUBBY BULLDOZER!\n");

        *damage += 22;

        enemy->defense -= 15;
        if (enemy->defense < 0)
            enemy->defense = 0;

        printf("Enemy DEF crushed -15!\n");
    }

    else if (strcmp(s.name, "Jeward Precision") == 0)
    {
        printf("JEWARD PRECISION!\n");

        *damage += 25;

        int defIgnore = enemy->defense / 2;
        *damage += defIgnore;

        player->accuracy += 30;

        printf("DEFENSE PENETRATED!\n");
    }
    // ================= SECRET SET BONUS =================
    if (
        hasSecretComboSet(player) &&
        (
            strcmp(s.name, "Shadow Bite") == 0 ||
            strcmp(s.name, "Dire Bite") == 0 ||
            strcmp(s.name, "Ambush Strike") == 0 ||
            strcmp(s.name, "Omega Bite") == 0 ||
            strcmp(s.name, "X Fang") == 0
        )
    )
    {
        printf("\n[SECRET PACK COMBO ACTIVATED]\n");

        *damage += 30;

        enemy->defense -= 10;
        if (enemy->defense < 0)
            enemy->defense = 0;

        enemy->attack -= 5;
        if (enemy->attack < 1)
            enemy->attack = 1;

        printf("Combo bonus: +30 damage, Enemy DEF -10, Enemy ATK -5!\n");
    }
}
