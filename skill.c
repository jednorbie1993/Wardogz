#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dog.h"
#include <windows.h>
#include "skill.h"

int computeBaseDamage(Dog *player, Dog *enemy, Skill s)
{
    int penalty = getFatiguePenalty(player->fatigue);

    float atkRatio = (float)(player->attack - penalty) / 999.0f;
    if (atkRatio < 0.1f)
        atkRatio = 0.1f;

    int dmg = (int)(atkRatio * 80) + 20 + s.power;

    float defRatio = (float)enemy->defense / 999.0f;
    dmg -= (int)(defRatio * 30);

    if (isCritical(player->hp, player->maxHP))
    {
        dmg += 10;
        printf("CRITICAL HIT!\n");
    }

    dmg += (rand() % 11) - 5;

    if (dmg < 1) dmg = 1;
    if (dmg > 120) dmg = 120;

    return dmg;
}

void applyAttackSkill(Dog *player, Dog *enemy, Skill s, int *damage)
{
    printf("You used %s!\n", s.name);

    *damage = computeBaseDamage(player, enemy, s);
}

void applyBuffSkill(Dog *player, Dog *enemy, Skill s)
{
    printf("You used %s!\n", s.name);

    if (strcmp(s.name, "Titan Aegis") == 0)
    {
        player->defense += 40;
        player->hp += 15;
        if (player->hp > player->maxHP) player->hp = player->maxHP;

        player->fatigue -= 10;
        if (player->fatigue < 0) player->fatigue = 0;
    }
    else if (strcmp(s.name, "Iron Guard") == 0)
    {
        player->defense = clamp(player->defense + 5);
    }
    else if (strcmp(s.name, "Steel Wall") == 0)
    {
        player->defense += 20;
        if (player->defense > MAX_STAT) player->defense = MAX_STAT;

        player->fatigue += 5;
        if (player->fatigue > player->maxFatigue) player->fatigue = player->maxFatigue;
    }
    else if (strcmp(s.name, "Fortress Stance") == 0)
    {
        player->defense += 40;
        if (player->defense > MAX_STAT) player->defense = MAX_STAT;

        player->speed -= 20;
        if (player->speed < MIN_STAT) player->speed = MIN_STAT;

        player->fatigue += 10;
        if (player->fatigue > player->maxFatigue) player->fatigue = player->maxFatigue;
    }
}

void applyHealSkill(Dog *player, Skill s)
{
    printf("You used %s!\n", s.name);

    if (strcmp(s.name, "Last Stand") == 0)
    {
        player->hp = player->maxHP;
        printf("FULL RECOVERY!\n");
    }
    else
    {
        player->hp += 25;
        if (player->hp > player->maxHP)
            player->hp = player->maxHP;

        printf("Healed +25 HP!\n");
    }
}

void checkSkillUnlock(Dog *d)
{
    // ================= SPEED =================
    if (d->speed >= 100 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Quick Dash"))
    {
        strcpy(d->skills[d->skillCount].name, "Quick Dash");
        d->skills[d->skillCount].power = 7;
        d->skills[d->skillCount].cost = 6;
        d->skills[d->skillCount].type = SKILL_ATTACK; // ✅ FIX

        printf("NEW SKILL UNLOCKED: Quick Dash!\n");
        d->skillCount++;
    }

    if (d->speed >= 180 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Flash Step"))
    {
        strcpy(d->skills[d->skillCount].name, "Flash Step");
        d->skills[d->skillCount].power = 9;
        d->skills[d->skillCount].cost = 7;
        d->skills[d->skillCount].type = SKILL_ATTACK; // ✅ FIX

        printf("NEW SKILL UNLOCKED: Flash Step!\n");
        d->skillCount++;
    }
    // ================= SPEED (MID GAME) =================
    if (d->speed >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Phantom Rush"))
    {
        strcpy(d->skills[d->skillCount].name, "Phantom Rush");
        d->skills[d->skillCount].power = 12;
        d->skills[d->skillCount].cost = 9;
        d->skills[d->skillCount].type = SKILL_ATTACK;

        printf("NEW SKILL UNLOCKED: Phantom Rush!\n");
        d->skillCount++;
    }

    if (d->speed >= 350 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Shadow Blitz"))
    {
        strcpy(d->skills[d->skillCount].name, "Shadow Blitz");
        d->skills[d->skillCount].power = 15;
        d->skills[d->skillCount].cost = 11;
        d->skills[d->skillCount].type = SKILL_ATTACK;

        printf("NEW SKILL UNLOCKED: Shadow Blitz!\n");
        d->skillCount++;
    }
    if (d->speed >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Zero Phantom"))
    {
        strcpy(d->skills[d->skillCount].name, "Zero Phantom");
        d->skills[d->skillCount].power = 24;
        d->skills[d->skillCount].cost = 14;
        d->skills[d->skillCount].type = SKILL_ATTACK;

        printf("NEW SKILL UNLOCKED: Zero Phantom!\n");
        d->skillCount++;
    }

    // ================= ATTACK =================
    if (d->attack >= 150 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Heavy Bite"))
    {
        strcpy(d->skills[d->skillCount].name, "Heavy Bite");
        d->skills[d->skillCount].power = 10;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_ATTACK;

        printf("NEW SKILL UNLOCKED: Heavy Bite!\n");
        d->skillCount++;
    }

    if (d->attack >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Savage Fang"))
    {
        strcpy(d->skills[d->skillCount].name, "Savage Fang");
        d->skills[d->skillCount].power = 14;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_ATTACK;

        printf("NEW SKILL UNLOCKED: Savage Fang!\n");
        d->skillCount++;
    }

    if (d->attack >= 320 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Blood Frenzy"))
    {
        strcpy(d->skills[d->skillCount].name, "Blood Frenzy");
        d->skills[d->skillCount].power = 18;
        d->skills[d->skillCount].cost = 12;
        d->skills[d->skillCount].type = SKILL_ATTACK;

        printf("NEW SKILL UNLOCKED: Blood Frenzy!\n");
        d->skillCount++;
    }
    if (d->attack >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Ragnarok Fang"))
    {
        strcpy(d->skills[d->skillCount].name, "Ragnarok Fang");
        d->skills[d->skillCount].power = 25;
        d->skills[d->skillCount].cost = 15;
        d->skills[d->skillCount].type = SKILL_ATTACK;

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
        d->skills[d->skillCount].type = SKILL_ATTACK;

        printf("NEW SKILL UNLOCKED: Sure Strike!\n");
        d->skillCount++;
    }
    // ================= ACCURACY (MID GAME) =================
    if (d->accuracy >= 250 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Dead Eye"))
    {
        strcpy(d->skills[d->skillCount].name, "Dead Eye");
        d->skills[d->skillCount].power = 11;
        d->skills[d->skillCount].cost = 8;
        d->skills[d->skillCount].type = SKILL_ATTACK;

        printf("NEW SKILL UNLOCKED: Dead Eye!\n");
        d->skillCount++;
    }

    if (d->accuracy >= 350 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Fatal Aim"))
    {
        strcpy(d->skills[d->skillCount].name, "Fatal Aim");
        d->skills[d->skillCount].power = 14;
        d->skills[d->skillCount].cost = 10;
        d->skills[d->skillCount].type = SKILL_ATTACK;

        printf("NEW SKILL UNLOCKED: Fatal Aim!\n");
        d->skillCount++;
    }
    if (d->accuracy >= 500 && d->skillCount < MAX_SKILLS && !hasSkill(d, "Judgement Eye"))
    {
        strcpy(d->skills[d->skillCount].name, "Judgement Eye");
        d->skills[d->skillCount].power = 22;
        d->skills[d->skillCount].cost = 14;
        d->skills[d->skillCount].type = SKILL_ATTACK;

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
    if (s.type == SKILL_ATTACK)
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

void applySpecialEffects(Dog *player, Dog *enemy, Skill s, int *damage)
{
    // 🔥 ALL SPECIAL EFFECTS HERE

    if (strcmp(s.name, "Flash Step") == 0)
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

        int base = *damage + 30;
        int hit1 = base;
        int hit2 = (int)(base * 0.8);
        int hit3 = (int)(base * 0.6);

        *damage = hit1 + hit2 + hit3;

        enemy->isBleeding = 1;
        enemy->bleedTurns = 4;

        printf("MULTI HIT DESTRUCTION!\n");

        player->hp -= 12;
        player->hp = clamp(player->hp);
    }

    // ================= 🔥 SPARRING TECHNIQUES =================
    else if (strcmp(s.name, "Ossas Counter") == 0)
    {
        printf("🔄 OSSAS COUNTER STANCE!\n");

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

        int base = *damage + (player->speed / 20);

        int hit1 = base;
        int hit2 = (int)(base * 0.7);
        int hit3 = (int)(base * 0.5);
        int hit4 = rand() % 10;

        int total = hit1 + hit2 + hit3 + hit4;

        enemy->defense -= enemy->defense / 3;
        if (enemy->defense < 0)
            enemy->defense = 0;

        if (enemy->hp < enemy->maxHP * 0.4)
        {
            total += 25;
            printf("ZERO PHANTOM EXECUTION BONUS!\n");
        }

        player->fatigue -= 15;
        if (player->fatigue < 0)
            player->fatigue = 0;

        *damage = total;
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
}
