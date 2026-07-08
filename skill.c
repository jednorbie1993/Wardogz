#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dog.h"
#include <windows.h>
#include "stat.h"
#include "skill.h"
#include "cinematic.h"
#include "console.h"

// ================= DAMAGE TIERS =================
// Hindi na kailangan magdagdag sa dog.h.
// Dito lang muna naka-classify ang attack skills.

int getSkillTier(Skill s)
{
    // Ultimate skills
    if (strcmp(s.name, "Ragnarok Fang") == 0 ||
        strcmp(s.name, "Judgement Eye") == 0 ||
        strcmp(s.name, "Zero Phantom") == 0)
    {
        return TIER_ULTIMATE;
    }
    // Strong / late-game / secret attack skills
    if (strcmp(s.name, "Shadow Bite") == 0 ||
        strcmp(s.name, "Dire Bite") == 0 ||
        strcmp(s.name, "Ambush Strike") == 0 ||
        strcmp(s.name, "Omega Bite") == 0 ||
        strcmp(s.name, "X Fang") == 0 ||
        strcmp(s.name, "Blood Frenzy") == 0 ||
        strcmp(s.name, "Phantom Rush") == 0 ||
        strcmp(s.name, "Shadow Blitz") == 0 ||
        strcmp(s.name, "Fatal Aim") == 0 ||
        strcmp(s.name, "Snoop Phantom") == 0 ||
        strcmp(s.name, "Tiny Blitz") == 0 ||
        strcmp(s.name, "Chubby Bulldozer") == 0 ||
        strcmp(s.name, "Jeward Precision") == 0 ||
        strcmp(s.name, "Rolling Tackle") == 0 ||
        strcmp(s.name, "Rival Breaker") == 0)
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
        dmg = randRange(180, 360);
    }
    else if (tier == TIER_STRONG)
    {
        dmg = randRange(120, 210);
    }
    else
    {
        dmg = randRange(80, 160);
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
    printBlankLine();
    printCenteredFormat("You used %s!", s.name);

    cinematicPause(250);

    *damage = computeBaseDamage(player, enemy, s);

    printCenteredFormat("Damage: -%d HP", *damage);

    cinematicPause(400);
}

void applyBuffSkill(Dog *player, Dog *enemy, Skill s)
{
    printCenteredFormat("You used %s!", s.name);

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
    printCenteredFormat("You used %s!", s.name);

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

        printCentered("LAST STAND RECOVERY!");
        printCenteredFormat("Healed +%d HP!", healAmount);
    }
}

int isRankAtLeastB(char rank)
{
    switch (rank)
    {
    case 'B':
    case 'A':
    case 'S':
    case 'X':
    case 'Z':
        return 1;
    }

    return 0;
}

void checkSkillUnlock(Dog *d)
{
    // ================= COOLDOWN FIX FOR OLD SAVES =================
    // Kapag na-unlock na dati ang skill bago nilagyan ng cooldown,
    // dito natin inaayos para gumana pa rin kahit old save.
    for (int i = 0; i < d->skillCount; i++)
    {
        if (strcmp(d->skills[i].name, "Hip Check") == 0)
        {
            d->skills[i].cooldown = 1;
            if (d->skills[i].cdLeft < 0)
                d->skills[i].cdLeft = 0;
        }
        else if (strcmp(d->skills[i].name, "Rolling Tackle") == 0)
        {
            d->skills[i].cooldown = 2;
            if (d->skills[i].cdLeft < 0)
                d->skills[i].cdLeft = 0;
        }
    }
    // ================= SECRET ENEMY SKILLS =================
    if (d->defeatedGrimfangX && d->skillCount < MAX_SKILLS && !hasSkill(d, "X Fang"))
    {
        strcpy(d->skills[d->skillCount].name, "X Fang");
        d->skills[d->skillCount].power = 32;
        d->skills[d->skillCount].cost = 15;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_X_FANG;

        printCentered("NEW SECRET SKILL UNLOCKED: X Fang!");
        d->skillCount++;
    }
    if (d->defeatedGrimfang && d->skillCount < MAX_SKILLS && !hasSkill(d, "Shadow Bite"))
    {
        strcpy(d->skills[d->skillCount].name, "Shadow Bite");
        d->skills[d->skillCount].power = 18;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_SHADOW_BITE;

        printCentered("NEW SECRET SKILL UNLOCKED: Shadow Bite!");
        d->skillCount++;
    }

    if (d->defeatedDiremaw && d->skillCount < MAX_SKILLS && !hasSkill(d, "Dire Bite"))
    {
        strcpy(d->skills[d->skillCount].name, "Dire Bite");
        d->skills[d->skillCount].power = 22;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_DIRE_BITE;

        printCentered("NEW SECRET SKILL UNLOCKED: Dire Bite!");
        d->skillCount++;
    }
    if (d->defeatedBlackclaw && d->skillCount < MAX_SKILLS && !hasSkill(d, "Ambush Strike"))
    {
        strcpy(d->skills[d->skillCount].name, "Ambush Strike");
        d->skills[d->skillCount].power = 24;
        d->skills[d->skillCount].cost = 11;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_AMBUSH_STRIKE;

        printCentered("NEW SECRET SKILL UNLOCKED: Ambush Strike!");
        d->skillCount++;
    }
    if (d->defeatedOmega && d->skillCount < MAX_SKILLS && !hasSkill(d, "Omega Bite"))
    {
        strcpy(d->skills[d->skillCount].name, "Omega Bite");
        d->skills[d->skillCount].power = 28;
        d->skills[d->skillCount].cost = 13;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].id = SKILL_OMEGA_BITE;

        printCentered("NEW SECRET SKILL UNLOCKED: Omega Bite!");
        d->skillCount++;
    }
    // ================= SPEED =================
    if (d->speed >= 100 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Quick Dash"))
    {
        strcpy(d->skills[d->skillCount].name, "Quick Dash");
        d->skills[d->skillCount].power = 7;
        d->skills[d->skillCount].cost = 6;
        d->skills[d->skillCount].type = SKILL_DAMAGE; // ✅ FIX

        printCentered("NEW SKILL UNLOCKED: Quick Dash!");
        d->skillCount++;
    }

    if (d->speed >= 180 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Flash Step"))
    {
        strcpy(d->skills[d->skillCount].name, "Flash Step");
        d->skills[d->skillCount].power = 9;
        d->skills[d->skillCount].cost = 7;
        d->skills[d->skillCount].type = SKILL_DAMAGE; // ✅ FIX

        printCentered("NEW SKILL UNLOCKED: Flash Step!");
        d->skillCount++;
    }
    // ================= SPEED (MID GAME) =================
    if (d->speed >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Phantom Rush"))
    {
        strcpy(d->skills[d->skillCount].name, "Phantom Rush");
        d->skills[d->skillCount].power = 12;
        d->skills[d->skillCount].cost = 9;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Phantom Rush!");
        d->skillCount++;
    }

    if (d->speed >= 350 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Shadow Blitz"))
    {
        strcpy(d->skills[d->skillCount].name, "Shadow Blitz");
        d->skills[d->skillCount].power = 15;
        d->skills[d->skillCount].cost = 11;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Shadow Blitz!");
        d->skillCount++;
    }
    if (d->speed >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Zero Phantom"))
    {
        strcpy(d->skills[d->skillCount].name, "Zero Phantom");
        d->skills[d->skillCount].power = 24;
        d->skills[d->skillCount].cost = 14;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Zero Phantom!");
        d->skillCount++;
    }

    // ================= ATTACK =================
    if (d->attack >= 150 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Heavy Bite"))
    {
        strcpy(d->skills[d->skillCount].name, "Heavy Bite");
        d->skills[d->skillCount].power = 10;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Heavy Bite!");
        d->skillCount++;
    }

    if (d->attack >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Savage Fang"))
    {
        strcpy(d->skills[d->skillCount].name, "Savage Fang");
        d->skills[d->skillCount].power = 14;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Savage Fang!");
        d->skillCount++;
    }

    if (d->attack >= 320 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Blood Frenzy"))
    {
        strcpy(d->skills[d->skillCount].name, "Blood Frenzy");
        d->skills[d->skillCount].power = 18;
        d->skills[d->skillCount].cost = 12;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Blood Frenzy!");
        d->skillCount++;
    }
    if (d->attack >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Ragnarok Fang"))
    {
        strcpy(d->skills[d->skillCount].name, "Ragnarok Fang");
        d->skills[d->skillCount].power = 25;
        d->skills[d->skillCount].cost = 15;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Ragnarok Fang!");
        d->skillCount++;
    }

    // ================= DEFENSE =================
    if (d->defense >= 120 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Iron Guard"))
    {
        strcpy(d->skills[d->skillCount].name, "Iron Guard");
        d->skills[d->skillCount].power = 0;
        d->skills[d->skillCount].cost = 5;
        d->skills[d->skillCount].type = SKILL_BUFF;

        printCentered("NEW SKILL UNLOCKED: Iron Guard!");
        d->skillCount++;
    }
    // ================= DEFENSE (MID GAME) =================
    if (d->defense >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Steel Wall"))
    {
        strcpy(d->skills[d->skillCount].name, "Steel Wall");
        d->skills[d->skillCount].power = 0;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_BUFF;

        printCentered("NEW SKILL UNLOCKED: Steel Wall!");
        d->skillCount++;
    }

    if (d->defense >= 350 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Fortress Stance"))
    {
        strcpy(d->skills[d->skillCount].name, "Fortress Stance");
        d->skills[d->skillCount].power = 0;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_BUFF;

        printCentered("NEW SKILL UNLOCKED: Fortress Stance!");
        d->skillCount++;
    }
    if (d->defense >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Titan Aegis"))
    {
        strcpy(d->skills[d->skillCount].name, "Titan Aegis");
        d->skills[d->skillCount].power = 0;
        d->skills[d->skillCount].cost = 15;
        d->skills[d->skillCount].type = SKILL_BUFF;

        printCentered("NEW SKILL UNLOCKED: Titan Aegis!");
        d->skillCount++;
    }

    // ================= ACCURACY =================
    if (d->accuracy >= 130 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Sure Strike"))
    {
        strcpy(d->skills[d->skillCount].name, "Sure Strike");
        d->skills[d->skillCount].power = 8;
        d->skills[d->skillCount].cost = 6;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Sure Strike!");
        d->skillCount++;
    }
    // ================= ACCURACY (MID GAME) =================
    if (d->accuracy >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Dead Eye"))
    {
        strcpy(d->skills[d->skillCount].name, "Dead Eye");
        d->skills[d->skillCount].power = 11;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Dead Eye!");
        d->skillCount++;
    }

    if (d->accuracy >= 350 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Fatal Aim"))
    {
        strcpy(d->skills[d->skillCount].name, "Fatal Aim");
        d->skills[d->skillCount].power = 14;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Fatal Aim!");
        d->skillCount++;
    }
    if (d->accuracy >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Judgement Eye"))
    {
        strcpy(d->skills[d->skillCount].name, "Judgement Eye");
        d->skills[d->skillCount].power = 22;
        d->skills[d->skillCount].cost = 14;
        d->skills[d->skillCount].type = SKILL_DAMAGE;

        printCentered("NEW SKILL UNLOCKED: Judgement Eye!");
        d->skillCount++;
    }

    // ================= HP =================
    if (d->maxHP >= 200 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Last Stand"))
    {
        strcpy(d->skills[d->skillCount].name, "Last Stand");
        d->skills[d->skillCount].power = 12;
        d->skills[d->skillCount].cost = 9;
        d->skills[d->skillCount].type = SKILL_HEAL;

        printCentered("NEW SKILL UNLOCKED: Last Stand!");
        d->skillCount++;
    }
    // ================= COMBAT SKILLS =================
    if (isRankAtLeastB(d->arenaRank) &&
        d->maxHP >= 300 &&
        d->attack >= 300 &&
        d->defense >= 300 &&
        d->skillCount < MAX_SKILLS &&
        !hasSkill(d, "Hip Check"))
    {
        strcpy(d->skills[d->skillCount].name, "Hip Check");
        d->skills[d->skillCount].power = 9;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].cooldown = 1;
        d->skills[d->skillCount].cdLeft = 0;

        printCentered("NEW SKILL UNLOCKED: Hip Check!");
        d->skillCount++;
    }

    if (d->hipCheckUses >= 25 &&
        d->skillCount < MAX_SKILLS &&
        !hasSkill(d, "Rolling Tackle"))
    {
        strcpy(d->skills[d->skillCount].name, "Rolling Tackle");
        d->skills[d->skillCount].power = 18;
        d->skills[d->skillCount].cost = 14;
        d->skills[d->skillCount].type = SKILL_DAMAGE;
        d->skills[d->skillCount].cooldown = 2;
        d->skills[d->skillCount].cdLeft = 0;

        printCentered("NEW SKILL UNLOCKED: Rolling Tackle!");
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
        printCentered("SHADOW BITE!");

        *damage += 10;

        enemy->isBleeding = 1;
        enemy->bleedTurns = 3;

        enemy->accuracy -= 10;
        if (enemy->accuracy < 1)
            enemy->accuracy = 1;

        printCentered("Enemy is BLEEDING!");
        printCentered("Enemy Accuracy -10!");
    }

    else if (strcmp(s.name, "Dire Bite") == 0)
    {
        printCentered("DIRE BITE!");

        int hit1 = *damage;
        int hit2 = *damage / 2;

        *damage = hit1 + hit2;

        enemy->isBleeding = 1;
        enemy->bleedTurns = 4;

        printCentered("Double bite!");
        printCentered("Enemy is BLEEDING!");
    }

    else if (strcmp(s.name, "Ambush Strike") == 0)
    {
        printCentered("AMBUSH STRIKE!");

        *damage += 18;

        if (player->speed > enemy->speed)
        {
            *damage += 25;
            printCentered("Speed advantage bonus!");
        }

        if (rand() % 100 < 35)
        {
            enemy->isConfused = 1;
            enemy->confuseTurns = 2;
            printCentered("Enemy is CONFUSED!");
        }
    }

    else if (strcmp(s.name, "Omega Bite") == 0)
    {
        printCentered("OMEGA BITE!");

        *damage += 25;

        enemy->defense -= 20;
        if (enemy->defense < 0)
            enemy->defense = 0;

        enemy->attack -= 10;
        if (enemy->attack < 1)
            enemy->attack = 1;

        printCentered("Enemy DEF -20!");
        printCentered("Enemy ATK -10!");
    }

    else if (strcmp(s.name, "X Fang") == 0)
    {
        printCentered("X FANG!");

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
            printCentered("Enemy is CONFUSED!");
        }

        printCentered("Triple X combo!");
        printCentered("Enemy DEF -18!");
    }

    else if (strcmp(s.name, "Flash Step") == 0)
    {
        printCentered("A blinding strike!");
        if (rand() % 100 < 30)
        {
            enemy->isConfused = 1;
            enemy->confuseTurns = 2 + rand() % 2;
            printCentered("Enemy is CONFUSED!");
        }
    }

    else if (strcmp(s.name, "Savage Fang") == 0)
    {
        printCentered("A vicious tearing attack!");
        if (rand() % 100 < 40)
        {
            enemy->isBleeding = 1;
            enemy->bleedTurns = 3;
            printCentered("Enemy is BLEEDING!");
        }
    }

    else if (strcmp(s.name, "Ragnarok Fang") == 0)
    {
        printCentered("THE WORLD TREMBLES UNDER RAGNAROK FANG!");

        // Random hit display only: 1-3 hits
        int hits = 1 + rand() % 3;
        printCenteredFormat("%d HIT DESTRUCTION!", hits);

        // Damage range is already handled by computeBaseDamage(): 180-250.
        // Critical stays in battle.c para hindi doble critical.

        // DEF down chance 60%
        if (rand() % 100 < 60)
        {
            int defReduce = 19 + rand() % 12; // 19-30

            enemy->defense -= defReduce;

            if (enemy->defense < 0)
                enemy->defense = 0;

            printCenteredFormat("Enemy DEF -%d!", defReduce);
        }

        // Bleed chance 30%
        if (rand() % 100 < 30)
        {
            enemy->isBleeding = 1;
            enemy->bleedTurns = 3;

            printCentered("Enemy is BLEEDING!");
        }
    }

    // ================= SPARRING TECHNIQUES =================
    else if (strcmp(s.name, "Ossas Counter") == 0)
    {
        printCentered("OSSAS COUNTER STANCE!");

        *damage = 0;

        player->isCountering = 1;
        player->counterDamage = (player->attack / 3) + 10;

        if (player->counterDamage > 40)
            player->counterDamage = 40;

        printCentered("Counter trap set!");
    }

    else if (strcmp(s.name, "Tiny Blitz") == 0)
    {
        int hit1 = *damage;
        int hit2 = (*damage * 7) / 10;
        int hit3 = (*damage * 5) / 10;

        *damage = hit1 + hit2 + hit3;

        printCentered("Triple Blitz!");
    }

    else if (strcmp(s.name, "Snoop Phantom") == 0)
    {
        *damage *= 2;

        enemy->isConfused = 1;
        enemy->confuseTurns = 4;

        enemy->isBleeding = 1;
        enemy->bleedTurns = 3;

        printCentered("DOUBLE PHANTOM + STATUS!");
    }

    // ================= NORMAL ATTACK EFFECTS =================
    else if (strcmp(s.name, "Quick Dash") == 0)
    {
        printCentered("A fast strike!");
    }

    else if (strcmp(s.name, "Hip Check") == 0)
    {
        player->hipCheckUses++;

        if (rand() % 100 < 40)
        {
            enemy->isStunned = 1;
            enemy->stunTurns = 1 + rand() % 2;

            printCenteredFormat("%s is STUNNED!", enemy->name);
        }

        checkSkillUnlock(player);
    }

    else if (strcmp(s.name, "Rolling Tackle") == 0)
    {
        printCentered("ROLLING TACKLE!");

        player->hipCheckUses++;

        *damage += 20;

        if (rand() % 100 < 60)
        {
            enemy->isStunned = 1;
            enemy->stunTurns = 1;

            printCenteredFormat("%s is STUNNED!", enemy->name);
        }

        printCentered("Heavy rolling hit!");
    }

    else if (strcmp(s.name, "Rival Breaker") == 0)
    {
        printCentered("RIVAL BREAKER!");

        *damage += 25;

        enemy->defense -= 10;
        if (enemy->defense < 0)
            enemy->defense = 0;

        if (rand() % 100 < 45)
        {
            enemy->isStunned = 1;
            enemy->stunTurns = 1;

            printCenteredFormat("%s is STUNNED!", enemy->name);
        }

        printCentered("Enemy DEF reduced!");
    }

    else if (strcmp(s.name, "Heavy Bite") == 0)
    {
            printCentered("Armor breaking bite!");
            enemy->defense -= 5;
            if (enemy->defense < 0)
                enemy->defense = 0;
            printCentered("Enemy DEF reduced!");
        }

        else if (strcmp(s.name, "Sure Strike") == 0)
        {
            printCentered("An unavoidable attack!");
            *damage += 5;
            enemy->accuracy = 1000;
        }

        else if (strcmp(s.name, "Blood Frenzy") == 0)
        {
            printCentered("You enter a BLOOD FRENZY!");
            *damage += 15;

            enemy->isBleeding = 1;
            enemy->bleedTurns = 4;

            printCentered("Enemy is BLEEDING heavily!");

            int recoil = 10;
            player->hp -= recoil;

            printCenteredFormat("You hurt yourself for %d recoil!", recoil);
        }

        else if (strcmp(s.name, "Phantom Rush") == 0)
        {
            printCentered("You vanish and strike multiple times!");

            int hit1 = *damage;
            int hit2 = *damage / 2;

            *damage = hit1 + hit2 + (rand() % 6);

            printCenteredFormat("First strike: %d", hit1);
            printCenteredFormat("Second strike: %d", hit2);
        }

        else if (strcmp(s.name, "Shadow Blitz") == 0)
        {
            printCentered("You melt into the shadows and strike instantly!");

            int base = *damage;

            int hit1 = base;
            int hit2 = (int)(base * 0.7);
            int hit3 = (int)(base * 0.5);

            int total = hit1 + hit2 + hit3;

            total += 10 + (rand() % 11);

            if (rand() % 100 < 50)
            {
                printCentered("SHADOW CRITICAL STRIKE!");
                total += 20;
            }

            *damage = total;

            printCenteredFormat("Hit 1: %d", hit1);
            printCenteredFormat("Hit 2: %d", hit2);
            printCenteredFormat("Hit 3: %d", hit3);
        }

        else if (strcmp(s.name, "Dead Eye") == 0)
        {
            printCentered("You focus and lock onto the target...");

            int preciseDamage = *damage + 15;

            if (rand() % 100 < 35)
            {
                printCentered("CRITICAL DEAD EYE SHOT!");
                preciseDamage += 20;
            }

            preciseDamage += (player->accuracy / 50);

            *damage = preciseDamage;

            printCentered("Dead Eye hits cleanly!");
        }

        else if (strcmp(s.name, "Fatal Aim") == 0)
        {
            printCentered("You lock in a fatal trajectory...");

            int dmg = *damage + 20;

            enemy->defense -= 15;
            if (enemy->defense < 0)
                enemy->defense = 0;

            if (enemy->hp < enemy->maxHP * 0.3)
            {
                dmg += 25;
                printCentered("EXECUTION BONUS!");
            }

            if (rand() % 100 < 40)
            {
                printCentered("FATAL CRITICAL HIT!");
                dmg += 20;
            }

            *damage = dmg;

            printCentered("Fatal Aim strikes deep!");
        }

        else if (strcmp(s.name, "Judgement Eye") == 0)
        {
            printCentered("You gaze into the enemy's fate...");

            int dmg = *damage + 25;

            enemy->defense -= 20;
            if (enemy->defense < 0)
                enemy->defense = 0;

            if (rand() % 100 < 35)
            {
                enemy->isConfused = 1;
                enemy->confuseTurns = 2 + rand() % 2;
                printCentered("Enemy's mind breaks under JUDGEMENT!");
            }

            if (enemy->hp < enemy->maxHP * 0.4)
            {
                dmg += 30;
                printCentered("JUDGEMENT EXECUTION BONUS!");
            }

            if (rand() % 100 < 45)
            {
                dmg += 20;
                printCentered("CRITICAL JUDGEMENT STRIKE!");
            }

            *damage = dmg;

            printCentered("Judgement Eye pierces the soul!");
        }

        else if (strcmp(s.name, "Zero Phantom") == 0)
        {
            printCentered("ZERO PHANTOM ACTIVATED!");

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
                printCentered("Enemy is CONFUSED!");
            }

            printCentered("Enemy DEF reduced by 1/3!");
        }

        else if (strcmp(s.name, "Chubby Bulldozer") == 0)
        {
            printCentered("CHUBBY BULLDOZER!");

            *damage += 22;

            enemy->defense -= 15;
            if (enemy->defense < 0)
                enemy->defense = 0;

            printCentered("Enemy DEF crushed -15!");
        }

        else if (strcmp(s.name, "Jeward Precision") == 0)
        {
            printCentered("JEWARD PRECISION!");

            *damage += 25;

            int defIgnore = enemy->defense / 2;
            *damage += defIgnore;

            player->accuracy += 30;

            printCentered("DEFENSE PENETRATED!");
        }
    // ================= SECRET SET BONUS =================
    if (
        (
            strcmp(s.name, "Shadow Bite") == 0 ||
            strcmp(s.name, "Dire Bite") == 0 ||
            strcmp(s.name, "Ambush Strike") == 0 ||
            strcmp(s.name, "Omega Bite") == 0 ||
            strcmp(s.name, "X Fang") == 0) &&
        hasSecretComboSet(player))
    {
        printBlankLine();
        printCentered("[SECRET PACK COMBO ACTIVATED]");

        *damage += 30;

        enemy->defense -= 10;
        if (enemy->defense < 0)
            enemy->defense = 0;

        enemy->attack -= 5;
        if (enemy->attack < 1)
            enemy->attack = 1;

        printCentered("Combo bonus: +30 damage, Enemy DEF -10, Enemy ATK -5!");
    }
}
