#include <stdio.h>
#include "dog.h"
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h> // para sa strcspn
#include <ctype.h>
#include "sparring.h"

int systemLog = 0;
int animationOn = 1; //  NEW (default ON)


int randRange(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

// growth curve (higher stat = lower gain)
int getGrowthGain(int stat)
{
    int base = randRange(3, 5); // 3–5

    if (stat > 200)
        base -= 1;
    if (stat > 400)
        base -= 1;
    if (stat > 700)
        base -= 1;

    if (base < 1)
        base = 1;

    return base;
}

int clamp(int value)
{
    if (value > MAX_STAT)
        return MAX_STAT;
    if (value < MIN_STAT)
        return MIN_STAT;
    return value;
}

int clampFatigue(int f, int max)
{
    if (max <= 0)
        return 0; // safety: kung wala pang maxFatigue

    if (f < 0)
        return 0;

    if (f > max)
        return max;

    return f;
}

int getFatiguePenalty(int fatigue)
{
    if (fatigue >= 80)
        return 0;
    else if (fatigue >= 60)
        return 2;
    else if (fatigue >= 40)
        return 6;
    else if (fatigue >= 20)
        return 12;
    else if (fatigue > 0)
        return 24;
    else
        return 50;
}

int isCritical(int currentHP, int maxHP)
{
    int critChance;

    if (currentHP <= maxHP * 0.2)
    {
        // LOW HP → clutch mode
        critChance = (rand() % 16) + 20; // 20–35%
    }
    else
    {
        // NORMAL
        critChance = (rand() % 8) + 8; // 8–15%
    }

    int roll = rand() % 100;

    if (systemLog)
    {
        printf("[CRIT ] Roll: %-3d | Chance : %-3d\n", roll, critChance);
    }

    return roll < critChance;
}
void preBattleScene()
{
    const char *messages[] = {
        "Stay focused...",
        "You hear footsteps nearby...",
        "A sudden noise echoes...",
        "Something is watching you...",
        "Car passing... be careful!",
        "The air feels tense..."};

    int count = sizeof(messages) / sizeof(messages[0]);

    system("cls");

    // 🔥 random message
    int r = rand() % count;

    printf("\n");
    for (int i = 0; messages[r][i] != '\0'; i++)
    {
        printf("%c", messages[r][i]);
        fflush(stdout);
        Sleep(40); // animation speed
    }

    printf("\n\nPress Enter to continue...");
    getchar();
}
void trainDog(Dog *d, int type)
{
    printf("\nTraining");

    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(200);
    }
    printf("\n");

    // ================= HARD BLOCK: NO ENERGY =================
    if (d->fatigue <= 0)
    {
        printf("Your dog is completely exhausted!\n");
        printf("You must REST before training again.\n");

        d->fatigue = 0;
        waitForEnter();
        return;
    }

    // ================= FATIGUE FAILURE SYSTEM =================
    int failChance;

    if (d->fatigue <= 30)
        failChance = 25;
    else if (d->fatigue <= 50)
        failChance = 15;
    else
        failChance = 5;

    int rollFail = rand() % 100;

    if (rollFail < failChance)
    {
        printf("Too exhausted... Training failed!\n");

        d->fatigue = clampFatigue(d->fatigue - 5, d->maxFatigue);

        waitForEnter();
        return;
    }

    int greatChance = rand() % 100;

    // ================= TRAINING SUCCESS =================
    if (greatChance < 10)
    {
        printf("GREAT TRAINING!\n");

        if (type == 1)
        {
            int g1 = randRange(11, 20);
            int g2 = randRange(11, 20);
            int g3 = randRange(11, 20);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);

            printf("HP +%d | ATK +%d | DEF +%d\n", g1, g2, g3);
        }
        else if (type == 2)
        {
            int g1 = randRange(11, 20);
            int g2 = randRange(11, 20);
            int g3 = randRange(11, 20);

            d->speed = clamp(d->speed + g1);
            d->accuracy = clamp(d->accuracy + g2);
            d->intelligence = clamp(d->intelligence + g3);

            printf("SPD +%d | ACC +%d | INT +%d\n", g1, g2, g3);
        }
        else
        {
            int g1 = randRange(11, 20);
            int g2 = randRange(11, 20);
            int g3 = randRange(11, 20);
            int g4 = randRange(11, 20);
            int g5 = randRange(11, 20);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);
            d->speed = clamp(d->speed + g4);
            d->intelligence = clamp(d->intelligence + g5);

            printf("HP +%d ATK +%d DEF +%d SPD +%d INT +%d\n",
                   g1, g2, g3, g4, g5);
        }

        d->hp = d->maxHP;
    }
    else
    {
        printf("Training successful!\n");

        int minGain, maxGain;

        if (d->fatigue <= 30)
        {
            minGain = 1;
            maxGain = 10;
        }
        else
        {
            minGain = 5;
            maxGain = 10;
        }

        if (type == 1)
        {
            int g1 = randRange(minGain, maxGain);
            int g2 = randRange(minGain, maxGain);
            int g3 = randRange(minGain, maxGain);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);

            printf("HP +%d | ATK +%d | DEF +%d\n", g1, g2, g3);
        }
        else if (type == 2)
        {
            int g1 = randRange(minGain, maxGain);
            int g2 = randRange(minGain, maxGain);
            int g3 = randRange(minGain, maxGain);

            d->speed = clamp(d->speed + g1);
            d->accuracy = clamp(d->accuracy + g2);
            d->intelligence = clamp(d->intelligence + g3);

            printf("SPD +%d | ACC +%d | INT +%d\n", g1, g2, g3);
        }
        else
        {
            int g1 = randRange(minGain, maxGain);
            int g2 = randRange(minGain, maxGain);
            int g3 = randRange(minGain, maxGain);
            int g4 = randRange(minGain, maxGain);
            int g5 = randRange(minGain, maxGain);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);
            d->speed = clamp(d->speed + g4);
            d->intelligence = clamp(d->intelligence + g5);

            printf("HP +%d ATK +%d DEF +%d SPD +%d INT +%d\n",
                   g1, g2, g3, g4, g5);
        }

        d->hp = d->maxHP;
    }

    // ================= FATIGUE COST =================
    d->fatigue = clampFatigue(d->fatigue - randRange(5, 12), d->maxFatigue);

    waitForEnter();
}

void createDog(Dog *d)
{
    printf("Enter your dog's name: ");

    fgets(d->name, 50, stdin);
    d->name[strcspn(d->name, "\n")] = 0;

    d->hp = 100;
    d->maxHP = 100;
    d->attack = 920;
    d->speed = 300;

    d->defense = 315;
    d->accuracy = 918; // 80% hit chance
    d->intelligence = 920;

    d->fatigue = 100; // full energy
    d->maxFatigue = 100;

    d->skillCount = 2;

    d->isCountering = 0;
    d->counterDamage = 0;

    d->isBleeding = 0;
    d->bleedTurns = 0;
    d->bleedDamage = 0;  // 🔥 ADD THIS
    d->accuracyModifier = 0;  // 🔥 ADD THIS

    strcpy(d->skills[0].name, "Bite");
    d->skills[0].power = 5;
    d->skills[0].cost = 5;
    d->skills[0].type = SKILL_ATTACK;

    strcpy(d->skills[1].name, "Scratch");
    d->skills[1].power = 3;
    d->skills[1].cost = 3;
    d->skills[1].type = SKILL_ATTACK;

    d->equipped[0] = 0;
    d->equipped[1] = 1;
    d->equipped[2] = -1;
    d->equipped[3] = -1;


    initSparringProgress(d);
}
void applySkillEffect(Dog *player, Dog *enemy, Skill s, int *damage)
{
    // ================= ATTACK =================
    if (s.type == SKILL_ATTACK)
    {
        printf("You used %s!\n", s.name);

        int penalty = getFatiguePenalty(player->fatigue);

        float atkRatio = (float)(player->attack - penalty) / 999.0f;
        if (atkRatio < 0.1f)
            atkRatio = 0.1f;

        *damage = (int)(atkRatio * 80) + 20 + s.power;

        float defRatio = (float)enemy->defense / 999.0f;
        *damage -= (int)(defRatio * 30);

        if (isCritical(player->hp, player->maxHP))
        {
            *damage += 10;
            printf("CRITICAL HIT!\n");
        }

        *damage += (rand() % 11) - 5;

        if (*damage < 1)
            *damage = 1;
        if (*damage > 120)
            *damage = 120;

        // 🔥 ALL SPECIAL EFFECTS HERE (single block)
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
        else if (strcmp(s.name, "Quick Dash") == 0)
        {
            printf("A fast strike!\n");
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
            enemy->accuracy = 1000; // force hit
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
            int hit1 = (*damage);
            int hit2 = (*damage) / 2;
            int totalDamage = hit1 + hit2;
            totalDamage += (rand() % 6);
            *damage = totalDamage;
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
            int defBreak = 15;
            enemy->defense -= defBreak;
            if (enemy->defense < 0)
                enemy->defense = 0;
            printf("Enemy DEF reduced by %d!\n", defBreak);
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
        else if (strcmp(s.name, "Ragnarok Fang") == 0)
        {
            printf("THE WORLD TREMBLES UNDER RAGNAROK FANG!\n");
            int base = *damage + 30;
            int hit1 = base;
            int hit2 = (int)(base * 0.8);
            int hit3 = (int)(base * 0.6);
            int total = hit1 + hit2 + hit3;
            printf("Hit 1: %d\n", hit1);
            printf("Hit 2: %d\n", hit2);
            printf("Hit 3: %d\n", hit3);
            enemy->isBleeding = 1;
            enemy->bleedTurns = 4;
            printf("Enemy is BLEEDING from destruction!\n");
            if (enemy->hp < enemy->maxHP * 0.4)
            {
                total += 30;
                printf("RAGNAROK EXECUTION BONUS!\n");
            }
            total += rand() % 15;
            int recoil = 12;
            player->hp -= recoil;
            player->hp = clamp(player->hp);
            printf("You suffer %d recoil from Ragnarok power!\n", recoil);
            *damage = total;
        }
        else if (strcmp(s.name, "Judgement Eye") == 0)
        {
            printf("You gaze into the enemy's fate...\n");
            int dmg = *damage + 25;
            int defBreak = 20;
            enemy->defense -= defBreak;
            if (enemy->defense < 0)
                enemy->defense = 0;
            printf("Enemy DEF shattered by %d!\n", defBreak);
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
            printf("You disappear from existence...\n");
            printf("ZERO PHANTOM ACTIVATED!\n");
            int base = *damage + (player->speed / 20);
            int hit1 = base;
            int hit2 = (int)(base * 0.7);
            int hit3 = (int)(base * 0.5);
            int hit4 = (rand() % 10);
            int total = hit1 + hit2 + hit3 + hit4;
            printf("Phantom Hit 1: %d\n", hit1);
            printf("Phantom Hit 2: %d\n", hit2);
            printf("Phantom Hit 3: %d\n", hit3);
            printf("Phantom Hit 4: %d\n", hit4);
            int ignoreDef = enemy->defense / 3;
            enemy->defense -= ignoreDef;
            if (enemy->defense < 0)
                enemy->defense = 0;
            printf("Enemy DEF partially bypassed!\n");
            if (enemy->hp < enemy->maxHP * 0.4)
            {
                total += 25;
                printf("ZERO PHANTOM EXECUTION BONUS!\n");
            }
            int fatigueCost = 15;
            player->fatigue -= fatigueCost;
            if (player->fatigue < 0)
                player->fatigue = 0;
            printf("Fatigue drained by %d!\n", fatigueCost);
            *damage = total;
        }
        // ================= SPARRING TECHNIQUES =================
        else if (strcmp(s.name, "Ossas Counter") == 0) 
        {
            printf("🔄 OSSAS COUNTER STANCE!\n");
            *damage = 0;  // NO DAMAGE - pure setup
            
            player->isCountering = 1;
            player->counterDamage = (player->attack / 3) + 10;
            if (player->counterDamage > 40) player->counterDamage = 40;
            
            printf("✅ Counter trap set! (65-85% trigger)\n");
        }
        else if (strcmp(s.name, "Chubby Bulldozer") == 0) 
        {
            printf("CHUBBY BULLDOZER!\n");
            *damage += 22;
            enemy->defense -= 15;
            if (enemy->defense < 0) enemy->defense = 0;
            printf("Enemy DEF crushed -15!\n");
        }
        else if (strcmp(s.name, "Tiny Blitz") == 0) 
        {
            printf("TINY BLITZ!\n");
            int hit1 = *damage;
            int hit2 = (*damage * 7) / 10;
            int hit3 = (*damage * 5) / 10;
            *damage = hit1 + hit2 + hit3;
            printf("Triple blitz hits!\n");
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
        else if (strcmp(s.name, "Snoop Phantom") == 0) 
        {
            printf("SNOOP PHANTOM TECHNIQUE!\n");
            int base = *damage + 20;
            *damage = base * 2;
            enemy->isConfused = 1;
            enemy->confuseTurns = 4;
            enemy->isBleeding = 1;
            enemy->bleedTurns = 3;
            printf("DOUBLE PHANTOM + FULL STATUS!\n");
        }
    }
    // ================= BUFF =================
    else if (s.type == SKILL_BUFF)
    {
        printf("You used %s!\n", s.name);

        if (strcmp(s.name, "Titan Aegis") == 0)
        {
            printf("🛡️ Titan Aegis activated!\n");
            player->defense += 40;
            player->hp += 15;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;
            player->fatigue -= 10;
            if (player->fatigue < 0)
                player->fatigue = 0;
            printf("DEF increased massively! Damage reduced for next hits!\n");
        }
        else if (strcmp(s.name, "Iron Guard") == 0)
        {
            player->defense = clamp(player->defense + 5);
            printf("DEF +5!\n");
        }
        else if (strcmp(s.name, "Steel Wall") == 0)
        {
            printf("You brace your body like unbreakable steel!\n");
            player->defense += 20;
            if (player->defense > MAX_STAT)
                player->defense = MAX_STAT;
            printf("DEF +20!\n");
            player->fatigue += 5;
            if (player->fatigue > player->maxFatigue)
                player->fatigue = player->maxFatigue;
            printf("You stabilized your stance!\n");
        }
        else if (strcmp(s.name, "Fortress Stance") == 0)
        {
            printf("You become an unbreakable fortress!\n");
            player->defense += 40;
            if (player->defense > MAX_STAT)
                player->defense = MAX_STAT;
            printf("DEF +40!\n");
            player->speed -= 20;
            if (player->speed < MIN_STAT)
                player->speed = MIN_STAT;
            printf("Speed reduced due to heavy stance!\n");
            player->fatigue += 10;
            if (player->fatigue > player->maxFatigue)
                player->fatigue = player->maxFatigue;
            printf("You are in FORTRESS MODE!\n");
        }

        *damage = 0;
    }
    // ================= HEAL =================
    else if (s.type == SKILL_HEAL)
    {
        printf("You used %s!\n", s.name);

        if (strcmp(s.name, "Last Stand") == 0)
        {
            printf("You refuse to fall!\n");
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

        *damage = 0;
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


// 🔥 WILD SKILL FUNCTIONS - ADD TO dog.c
void setEnemySkillsWild(Dog *enemy, int zoneIndex, int enemyLevel) {
    enemy->skills[0].id = SKILL_PACK_ATTACK;
    strcpy(enemy->skills[0].name, "Pack Attack");
    enemy->skills[0].power = 25;
    
    enemy->skills[1].id = SKILL_AMBUSH;
    strcpy(enemy->skills[1].name, "Ambush");
    enemy->skills[1].power = 35;
    
    if (zoneIndex == 3 || zoneIndex == 5) {
        enemy->skills[2].id = SKILL_HOWL_DEBUFF;
        strcpy(enemy->skills[2].name, "Howl");
    } else {
        enemy->skills[2].id = SKILL_FERAL_RUSH;
        strcpy(enemy->skills[2].name, "Feral Rush");
    }
    enemy->skills[2].power = 28;
    
    enemy->numSkills = 3;
    enemy->attack = (int)(enemy->attack * 1.2);
    enemy->speed = (int)(enemy->speed * 1.1);
}

int usePackAttack(Dog *user, Dog *target) {
    int hits = 2 + (rand() % 2);
    int total = 0;
    printf("%s calls pack! ", user->name);
    
    for (int i = 0; i < hits; i++) {
        int dmg = (user->attack * 0.7) + (rand() % 15);
        target->hp -= dmg;
        total += dmg;
        printf("Hit%d:-%d ", i+1, dmg);
    }
    printf("\n");
    return total;
}

int useAmbush(Dog *user, Dog *target) {
    int dmg = user->attack * 2 + (rand() % 20);
    target->hp -= dmg;
    printf("%s ambushes from shadows! CRIT! -%d\n", user->name, dmg);
    user->speed += 8;
    return dmg;
}

int useHowlDebuff(Dog *user, Dog *target) {
    target->accuracyModifier -= 25;
    target->accDebuffTurns = 3;
    int dmg = user->attack / 4;
    target->hp -= dmg;
    printf("%s HOWLS! Accuracy DOWN! Echo:-%d\n", user->name, dmg);
    return dmg;
}

int useFeralRush(Dog *user, Dog *target) {
    int dmg = (user->attack * 1.6) + (rand() % 15);
    target->hp -= dmg;
    target->bleedTurns += 2;
    target->bleedDamage = 10;
    printf("%s FERAL RUSH! -%d +BLEED!\n", user->name, dmg);
    return dmg;
}

int hasSkill(Dog *d, char name[])
{
    for (int i = 0; i < d->skillCount; i++)
    {
        if (strcmp(d->skills[i].name, name) == 0)
        {
            return 1; // meron na
        }
    }
    return 0; // wala pa
}

void skillMenu(Dog *d)
{
    int choice;

    while (1)
    {
        system("cls");

        printf("===== SKILL MENU =====\n");
        printf("1. View All Skills\n");
        printf("2. Current Skills\n");
        printf("3. Equip Skills\n");
        printf("4. Back\n");
        printf("Choice: ");

        char input[20];
        int choice;

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (input[0] == '\0')
        {
            printf("Invalid choice!\n");
            waitForEnter();
            continue;
        }

        choice = atoi(input);

        // ================= VIEW ALL =================
        if (choice == 1)
        {
            system("cls");
            printf("--- ALL SKILLS ---\n");

            for (int i = 0; i < d->skillCount; i++)
            {
                printf("%d. %s (Power:%d Cost:%d)\n",
                       i + 1,
                       d->skills[i].name,
                       d->skills[i].power,
                       d->skills[i].cost);
            }

            waitForEnter();
        }

        // ================= CURRENT EQUIPPED =================
        else if (choice == 2)
        {
            system("cls");
            printf("--- CURRENT SKILLS ---\n");

            for (int i = 0; i < 4; i++)
            {
                if (d->equipped[i] != -1)
                {
                    int idx = d->equipped[i];
                    printf("Slot %d: %s (P:%d C:%d)\n",
                           i + 1,
                           d->skills[idx].name,
                           d->skills[idx].power,
                           d->skills[idx].cost);
                }
                else
                {
                    printf("Slot %d: [EMPTY]\n", i + 1);
                }
            }

            waitForEnter();
        }

        // ================= EQUIP =================
        else if (choice == 3)
        {
            int slot, pick;

            system("cls");

            // 👉 show current first (very important UX)
            printf("--- CURRENT SKILLS ---\n");
            for (int i = 0; i < 4; i++)
            {
                if (d->equipped[i] != -1)
                {
                    int idx = d->equipped[i];
                    printf("Slot %d: %s\n", i + 1, d->skills[idx].name);
                }
                else
                {
                    printf("Slot %d: [EMPTY]\n", i + 1);
                }
            }

            printf("\nChoose slot (1-4): ");
            scanf("%d", &slot);
            while (getchar() != '\n')
                ;

            if (slot < 1 || slot > 4)
            {
                printf("Invalid slot!\n");
                waitForEnter();
                continue;
            }

            system("cls");
            printf("\n--- AVAILABLE SKILLS ---\n");

            for (int i = 0; i < d->skillCount; i++)
            {
                printf("%d. %s (P:%d C:%d)\n",
                       i + 1,
                       d->skills[i].name,
                       d->skills[i].power,
                       d->skills[i].cost);
            }

            printf("Choice: ");
            scanf("%d", &pick);
            while (getchar() != '\n')
                ;

            if (pick < 1 || pick > d->skillCount)
            {
                printf("Invalid skill!\n");
                waitForEnter();
                continue;
            }

            d->equipped[slot - 1] = pick - 1;

            printf("Skill equipped to Slot %d!\n", slot);
            waitForEnter();
        }

        // ================= BACK =================
        else if (choice == 4)
        {
            break;
        }

        else
        {
            printf("Invalid choice!\n");
            waitForEnter();
        }
    }
}

void createEnemy(Dog *e)
{
    strcpy(e->name, "Wild Dog");

    e->hp = 100;
    e->maxHP = 100;
    e->attack = 10;
    e->defense = 65;

    e->speed = 90;    // dagdag mo rin para kumpleto
    e->accuracy = 95; // important sa hit system
    e->intelligence = 55;

    e->isConfused = 0;
    e->confuseTurns = 0;

    e->isBleeding = 0; e->bleedTurns = 0; e->bleedDamage = 0;
    e->accuracyModifier = 0; e->numSkills = 0;
    
    e->isConfused = 0; e->confuseTurns = 0;
}

void enemyQuickAttack(Dog *player, Dog *enemy)
{
    int dmg = (enemy->attack / 8) + 3;

    if (dmg < 1)
        dmg = 1;

    player->hp -= dmg;
    player->hp = clamp(player->hp);

    printf("Enemy quickly attacks! You took %d damage!\n", dmg);
}

void setEnemyByZone(Dog *enemy, int zoneIndex, int i)
{
    // reset base stats muna (important!)
    createEnemy(enemy);

    if (zoneIndex == 0) // 🔥 STAGE 1: Back Alley
    {
        if (i == 0)
            strcpy(enemy->name, "Skinny Stray");
        else if (i == 1)
        {
            strcpy(enemy->name, "Scrap Fighter");
            enemy->attack += 3;
            enemy->defense += 2;
        }
        else
        {
            strcpy(enemy->name, "Alley Alpha");
            enemy->attack += 6;
            enemy->defense += 4;
            enemy->maxHP += 20;
        }
    }
    else if (zoneIndex == 1) // 🔥 STAGE 1: Junkyard
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Rust Hound");
            enemy->defense += 3;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Guard Dog");
            enemy->defense += 5;
        }
        else
        {
            strcpy(enemy->name, "Iron Jaw");
            enemy->defense += 8;
            enemy->maxHP += 25;
        }
    }
    else if (zoneIndex == 2) // 🔥 STAGE 1: Abandoned Block
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Night Stray");
            enemy->speed += 3;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Sneak Biter");
            enemy->accuracy += 5;
        }
        else
        {
            strcpy(enemy->name, "Street King");
            enemy->speed += 5;
            enemy->attack += 5;
        }
    }
    // 🔥 STAGE 2: Wild Territory - NEW!
    else if (zoneIndex == 3) // River Pack Hideout
    {
        if (i == 0)
        {
            strcpy(enemy->name, "River Scout");
            enemy->attack += 8;
            enemy->speed += 4;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Pack Hunter");
            enemy->attack += 12;
            enemy->speed += 6;
            enemy->maxHP += 15;
        }
        else
        {
            strcpy(enemy->name, "River Alpha");
            enemy->attack += 18;
            enemy->speed += 10;
            enemy->maxHP += 30;
            enemy->defense += 5;
        }
    }
    else if (zoneIndex == 4) // Forest Ambush Grounds
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Forest Stalker");
            enemy->speed += 8;
            enemy->accuracy += 10;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Ambush Leader");
            enemy->speed += 12;
            enemy->accuracy += 15;
            enemy->attack += 5;
        }
        else
        {
            strcpy(enemy->name, "Shadow Pack");
            enemy->speed += 18;
            enemy->accuracy += 25;
            enemy->attack += 10;
            enemy->maxHP += 20;
        }
    }
    else if (zoneIndex == 5) // Mountain Pack Den (HARDER - max 4)
    {
        if (i == 0)
        {
            strcpy(enemy->name, "Mountain Guard");
            enemy->defense += 10;
            enemy->maxHP += 25;
        }
        else if (i == 1)
        {
            strcpy(enemy->name, "Peak Warrior");
            enemy->defense += 15;
            enemy->maxHP += 35;
            enemy->attack += 8;
        }
        else if (i == 2)
        {
            strcpy(enemy->name, "Summit Enforcer");
            enemy->defense += 22;
            enemy->maxHP += 50;
            enemy->attack += 12;
            enemy->speed += 5;
        }
        else // i == 3 (replay)
        {
            strcpy(enemy->name, "Mountain King");
            enemy->defense += 30;
            enemy->maxHP += 70;
            enemy->attack += 20;
            enemy->speed += 10;
        }
    }

    // sync HP
    enemy->hp = enemy->maxHP;
}

void applyStatGain(Dog *d, int atk, int hp, int def, int spd, int acc, int intel)
{
    d->attack = clamp(d->attack + atk);
    float ratio = (float)d->hp / d->maxHP;

    d->maxHP = clamp(d->maxHP + hp);
    d->hp = (int)(d->maxHP * ratio);
    d->defense = clamp(d->defense + def);
    d->speed = clamp(d->speed + spd);
    d->accuracy = clamp(d->accuracy + acc);
    d->intelligence = clamp(d->intelligence + intel);
}

void applyBattleStatGain(Dog *d)
{
    int chosen[6] = {0}; // track kung alin na napili
    int count = 0;

    while (count < 3)
    {
        int stat = rand() % 6;

        if (chosen[stat] == 0)
        {
            chosen[stat] = 1;
            count++;

            int gain = (rand() % 5) + 1; // +1 to +5

            switch (stat)
            {
            case 0:
                d->attack = clamp(d->attack + gain);
                printf("ATK +%d\n", gain);
                break;
            case 1:
            {
                float ratio = (float)d->hp / d->maxHP;

                d->maxHP = clamp(d->maxHP + gain);
                d->hp = (int)(d->maxHP * ratio);

                printf("HP +%d\n", gain);
                break;
            }
            case 2:
                d->defense = clamp(d->defense + gain);
                printf("DEF +%d\n", gain);
                break;
            case 3:
                d->speed = clamp(d->speed + gain);
                printf("SPD +%d\n", gain);
                break;
            case 4:
                d->accuracy = clamp(d->accuracy + gain);
                printf("ACC +%d\n", gain);
                break;
            case 5:
                d->intelligence = clamp(d->intelligence + gain);
                printf("INT +%d\n", gain);
                break;
            }
        }
    }
}

void printDog(Dog d)
{
    printf("--- Dog Info ---\n");
    printf("Name: %s\n", d.name);
    printf("HP: %d\n", d.hp);
    printf("Attack: %d\n", d.attack);
    printf("Speed: %d\n", d.speed);

    printf("Defense: %d\n", d.defense);
    printf("Accuracy: %d\n", d.accuracy);
    printf("Intelligence: %d\n", d.intelligence);

    printf("Fatigue: %d/100\n", d.fatigue); // ✅ DITO LANG
}

void typeText(char *text, int speed)
{
    if (!animationOn)
    {
        printf("%s", text);
        return;
    }

    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout); // 👉 para real-time output
        Sleep(speed);
    }
}

void showHPBarPlayer(int hp, int maxHp)
{
    static int lastHP = -1;

    if (lastHP == -1)
        lastHP = hp;

    // 👉 Clamp safety (para di sumobra)
    if (hp < 0)
        hp = 0;
    if (hp > maxHp)
        hp = maxHp;

    if (!animationOn)
    {
        int bars = (hp * 10) / maxHp;

        printf("\rPLAYER: [");

        for (int i = 0; i < 10; i++)
        {
            if (i < bars)
                printf("#");
            else
                printf("-");
        }

        // 👉 IMPORTANT: clear leftover characters
        printf("] (%d/%d)        ", hp, maxHp);

        fflush(stdout);

        printf("\n"); // final line break so di sumunod ang next print

        lastHP = hp;
        return;
    }

    // 👉 determine direction
    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        int bars = (current * 10) / maxHp;

        printf("\rPLAYER: [");
        for (int i = 0; i < 10; i++)
        {
            if (i < bars)
                printf("#");
            else
                printf("-");
        }
        printf("] (%d/%d)   ", current, maxHp);

        fflush(stdout); // 🔥 IMPORTANT para smooth overwrite
        Sleep(25);
    }

    // 👉 final state (para exact hp)
    int bars = (hp * 10) / maxHp;

    printf("\rPLAYER: [");
    for (int i = 0; i < 10; i++)
    {
        if (i < bars)
            printf("#");
        else
            printf("-");
    }
    printf("] (%d/%d)   \n", hp, maxHp);

    lastHP = hp;
}

void showHPBarEnemy(int hp, int maxHp)
{
    static int lastHP = -1;

    if (lastHP == -1)
        lastHP = hp;

    if (hp < 0)
        hp = 0;
    if (hp > maxHp)
        hp = maxHp;

    // 👉 OFF animation (clean single print)
    if (!animationOn || hp == 0)
    {
        int bars = (hp * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
        {
            if (i < bars)
                printf("#");
            else
                printf("-");
        }

        printf("] (%d/%d)        \n", hp, maxHp);

        lastHP = hp;
        return;
    }

    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        int bars = (current * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
        {
            if (i < bars)
                printf("#");
            else
                printf("-");
        }

        printf("] (%d/%d)   ", current, maxHp);

        fflush(stdout);
        Sleep(25);
    }

    // 👉 final exact state
    int bars = (hp * 10) / maxHp;

    printf("\rENEMY : [");
    for (int i = 0; i < 10; i++)
    {
        if (i < bars)
            printf("#");
        else
            printf("-");
    }

    printf("] (%d/%d)        \n", hp, maxHp);

    lastHP = hp;
}

void displayBattleStatus(Dog player, Dog enemy)
{
    printf("\n--- BATTLE STATUS ---\n");

    printf("PLAYER: ");
    showHPBarPlayer(player.hp, player.maxHP);

    printf("ENEMY : ");
    showHPBarEnemy(enemy.hp, enemy.maxHP);
}

void loseSequence(Dog *player, Dog *enemy)
{
    printf("\nYOU LOST...\n");
    Sleep(500);

    printf("Recovering");
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(150);
    }

    player->hp = player->maxHP;
    enemy->hp = enemy->maxHP;

    printf("\nYou are back to full HP!\n");
}

void waitForEnter()
{
    printf("\nPress Enter to continue...");
    while (getchar() != '\n')
        ; // wait until Enter lang
}

void pauseAndClear()
{
    printf("\nPress Enter to continue...");

    getchar(); // no loop, no fflush, simple lang

    system("cls");
}
int battle(Dog *player, int zoneIndex, int progress[])
{
    if (player->hp <= 0)
    {
        printf("You must rest before you battle again!\n");
        return -1;
    }

    int choice, move, defending = 0;
    int baseDef = player->defense;
    int baseSpd = player->speed;

    Dog enemy;
    createEnemy(&enemy);

    enemy.bleedDamage = 0;
    enemy.accuracyModifier = 0;
    enemy.numSkills = 0;
    player->bleedDamage = 0;  // Player safety too
    player->accuracyModifier = 0;
    
    // 🔥 ENEMY SETUP - CLEAN & SIMPLE
    int i = progress[zoneIndex];
    if (zoneIndex >= 3) { // Stage 2: Wild Territory
        if (zoneIndex == 5) if (i >= 4) i = 3;
        else if (i >= 3) i = 2;
        
        setEnemyByZone(&enemy, zoneIndex, i);
        setEnemySkillsWild(&enemy, zoneIndex, i);
        
        system("cls");
        printf("\n🐺 [WILD TERRITORY ENEMY]\n");
        printf("Enemy: %s\n", enemy.name);
        printf("Skills: Pack Attack | Ambush | Howl/Feral\n");
        waitForEnter();
    } 
    else { // Stage 1: Urban Strays
        if (i >= 3) i = 2;
        setEnemyByZone(&enemy, zoneIndex, i);
        enemy.numSkills = 0; // No wild skills
    }

    system("cls");
    preBattleScene();

    // 🔥 MAIN BATTLE LOOP
    while (player->hp > 0 && enemy.hp > 0)
    {
        system("cls");
        displayBattleStatus(*player, enemy);

        printf("\n--- YOUR TURN ---\n");
        if (player->fatigue <= 20) printf("⚠️  Exhausted!\n");

        printf("1. Attack  2. Defend  3. Heal  4. Surrender\n");
        printf("Choice: ");

        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &choice) != 1 || choice < 1 || choice > 4)
        {
            printf("Invalid!\n"); waitForEnter(); continue;
        }

        // 🔥 PLAYER ACTIONS
        if (choice == 1) // Attack
        {
            system("cls"); displayBattleStatus(*player, enemy);
            printf("Skills:\n");

            for (int j = 0; j < 4; j++)
            {
                if (player->equipped[j] != -1)
                {
                    int idx = player->equipped[j];
                    printf("%d. %s (P:%d C:%d)\n", j+1, 
                           player->skills[idx].name, 
                           player->skills[idx].power, 
                           player->skills[idx].cost);
                }
                else printf("%d. ---\n", j+1);
            }

            fgets(buffer, sizeof(buffer), stdin);
            if (sscanf(buffer, "%d", &move) != 1 || move < 1 || move > 4)
            { printf("Invalid skill!\n"); waitForEnter(); continue; }

            int skillIdx = player->equipped[move - 1];
            if (skillIdx == -1) { printf("No skill!\n"); waitForEnter(); continue; }

            Skill s = player->skills[skillIdx];
            int damage = 0;

            if (player->fatigue < s.cost)
            {
                printf("Low energy! Weak attack...\n");
                applySkillEffect(player, &enemy, s, &damage);
                damage /= 2;
                player->fatigue = 0;
            }
            else
            {
                applySkillEffect(player, &enemy, s, &damage);
                player->fatigue -= s.cost;
                player->fatigue = clampFatigue(player->fatigue, player->maxFatigue);
            }

            if (damage > 0 && (rand() % 100) < player->accuracy)
            {
                enemy.hp -= damage; enemy.hp = clamp(enemy.hp);
                printf("Dealt %d damage!\n", damage);
            }
            else if (damage > 0) printf("Missed!\n");

            waitForEnter();
        }
        else if (choice == 2) // Defend
        {
            defending = 1;
            printf("Defending!\n"); waitForEnter();
        }
        else if (choice == 3) // Heal
        {
            player->hp += 20;
            if (player->hp > player->maxHP) player->hp = player->maxHP;
            printf("Healed +20 HP!\n"); waitForEnter();
        }
        else if (choice == 4) // Surrender
        {
            printf("Surrendered...\n"); waitForEnter();
            player->defense = baseDef; player->speed = baseSpd;
            return 2;
        }

        // 🔥 ENEMY TURN
        if (player->hp > 0 && enemy.hp > 0)
        {
            int result = enemyAttack(player, &enemy, &defending);
            if (result == 0) player->hp = 0;
            if (result == 1) enemy.hp = 0;
        }

        // 🔥 FATIGUE REGEN
        player->fatigue += 2;
        if (player->fatigue > player->maxFatigue) player->fatigue = player->maxFatigue;

        // 🔥 WIN/LOSE CHECK
        if (player->hp <= 0)
        {
            printf("\n💀 YOU LOSE 💀\n");
            player->fatigue = clampFatigue(player->fatigue + 20, player->maxFatigue);
            player->defense = baseDef; player->speed = baseSpd;
            waitForEnter(); return 0;
        }

        if (enemy.hp <= 0)
        {
            printf("\n🎉 YOU WIN! 🎉\n");
            applyBattleStatGain(player);
            checkSkillUnlock(player);
            
            /// 🔥 FIXED PROGRESS SYSTEM
            if (zoneIndex == 5) { // Mountain Den max 4
                if (progress[zoneIndex] < 4) progress[zoneIndex]++;
            } else { // All others max 3
                if (progress[zoneIndex] < 3) progress[zoneIndex]++;
            }

            player->fatigue = clampFatigue(player->fatigue + 20, player->maxFatigue);
            player->defense = baseDef; player->speed = baseSpd;
            waitForEnter(); return 1;
        }
    }

    player->defense = baseDef; player->speed = baseSpd;
    return -1;
}