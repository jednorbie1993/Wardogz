#include <stdio.h>
#include "dog.h"
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h> // para sa strcspn
#include <ctype.h>

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
void sparringDog(Dog *player, int type)
{
    Dog spar;

    // create sparring partner
    createSparPartner(&spar, type);

    printf("\n🔥 Sparring Match Started!\n");
    printf("Opponent: %s\n", spar.name);

    int playerHP = player->maxHP;
    int sparHP = spar.maxHP;

    while (playerHP > 0 && sparHP > 0)
    {
        // PLAYER TURN
        int dmg = (player->attack / 10) + rand() % 3;
        sparHP -= dmg;

        printf("You dealt %d damage!\n", dmg);

        if (sparHP <= 0) break;

        // SPAR TURN
        int enemyDmg = (spar.attack / 10) + rand() % 3;
        playerHP -= enemyDmg;

        printf("%s dealt %d damage!\n", spar.name, enemyDmg);
    }

    // RESULT
    if (playerHP > 0)
    {
        printf("\nYou won sparring!\n");

        // small stat gain ONLY
        if (type == 1) player->attack += rand() % 3 + 1;
        if (type == 2) player->defense += rand() % 3 + 1;
        if (type == 3) player->accuracy += rand() % 3 + 1;
        if (type == 4) player->intelligence += rand() % 3 + 1;
        if (type == 5) player->speed += rand() % 3 + 1;
    }
    else
    {
        printf("\nYou lost sparring...\n");
    }

    waitForEnter();
}
void createSparPartner(Dog *e, int type)
{
    // reset basic stats first
    memset(e, 0, sizeof(Dog));

    e->maxHP = 80 + rand() % 30;
    e->hp = e->maxHP;

    e->fatigue = 100;
    e->maxFatigue = 100;

    e->isConfused = 0;
    e->confuseTurns = 0;
    e->isBleeding = 0;
    e->bleedTurns = 0;

    e->skillCount = 0;

    // ================= OSSAS (ATTACK) =================
    if (type == 1)
    {
        strcpy(e->name, "Ossas");

        e->attack = 120 + rand() % 30;
        e->defense = 60 + rand() % 20;
        e->speed = 70 + rand() % 20;
        e->accuracy = 80 + rand() % 10;
        e->intelligence = 50;

        printf("⚔️ Ossas appears! Aggressive attacker!\n");
    }

    // ================= CHUBBY (DEFENSE) =================
    else if (type == 2)
    {
        strcpy(e->name, "Chubby");

        e->attack = 60 + rand() % 20;
        e->defense = 130 + rand() % 40;
        e->speed = 50 + rand() % 15;
        e->accuracy = 70 + rand() % 10;
        e->intelligence = 60;

        printf("🛡️ Chubby appears! Defensive tank!\n");
    }

    // ================= JWEAR (ACCURACY) =================
    else if (type == 3)
    {
        strcpy(e->name, "Jewar");

        e->attack = 80 + rand() % 20;
        e->defense = 70 + rand() % 20;
        e->speed = 80 + rand() % 20;
        e->accuracy = 140 + rand() % 30;
        e->intelligence = 80;

        printf("🎯 Jewar appears! Precision striker!\n");
    }

    // ================= TINY (INTELLIGENCE) =================
    else if (type == 4)
    {
        strcpy(e->name, "Tiny");

        e->attack = 70 + rand() % 20;
        e->defense = 60 + rand() % 20;
        e->speed = 60 + rand() % 20;
        e->accuracy = 80 + rand() % 15;
        e->intelligence = 150 + rand() % 40;

        printf("🧠 Tiny appears! Smart strategist!\n");
    }

    // ================= SNOOPY (SPEED) =================
    else if (type == 5)
    {
        strcpy(e->name, "Snoopy");

        e->attack = 70 + rand() % 20;
        e->defense = 60 + rand() % 20;
        e->speed = 150 + rand() % 40;
        e->accuracy = 85 + rand() % 15;
        e->intelligence = 70;

        printf("⚡ Snoopy appears! Speed demon!\n");
    }

    // fallback safety
    else
    {
        strcpy(e->name, "Unknown");
    }
}
void sparringMenu(Dog *player)
{
    int t;

    while (1)
    {
        system("cls");

        printf("==== SPARRING TRAINING ====\n");
        printf("1. Ossas (Attack Training)\n");
        printf("2. Chubby (Defense Training)\n");
        printf("3. Jewar (Accuracy Training)\n");
        printf("4. Tiny (Intelligence Training)\n");
        printf("5. Snoopy (Speed Training)\n");
        printf("6. Return\n");
        printf("Choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        // ================= EMPTY INPUT =================
        if (input[0] == '\0')
        {
            printf("Invalid input! Please enter a number.\n");
            waitForEnter();
            continue;
        }

        // ================= NOT A NUMBER =================
        if (!isdigit(input[0]))
        {
            printf("Invalid input! Numbers only.\n");
            waitForEnter();
            continue;
        }

        t = atoi(input);

        if (t == 6)
        {
            system("cls");
            break;
        }

        if (t < 1 || t > 5)
        {
            printf("Invalid choice!\n");
            waitForEnter();
            continue;
        }

        // 🥊 START SPARRING BATTLE
        sparringBattle(player, t);
    }
}
int sparringBattle(Dog *player, int type)
{
    Dog enemy;
    createSparPartner(&enemy, type);

    int playerHP = player->maxHP;
    int enemyHP = enemy.maxHP;

    printf("\n🔥 SPARRING START!\n");
    printf("Opponent: %s\n\n", enemy.name);

    while (playerHP > 0 && enemyHP > 0)
    {
        // ================= PLAYER TURN =================
        int playerDmg = (player->attack / 12) + rand() % 4;
        enemyHP -= playerDmg;

        printf("You hit %s for %d damage!\n", enemy.name, playerDmg);

        if (enemyHP <= 0) break;

        // ================= ENEMY TURN =================
        int enemyDmg = (enemy.attack / 12) + rand() % 4;
        playerHP -= enemyDmg;

        printf("%s hits you for %d damage!\n", enemy.name, enemyDmg);
    }

    // ================= RESULT =================
    if (playerHP > 0)
    {
        printf("\n🏆 You won sparring!\n");

        // small stat gain based on type
        if (type == 1) player->attack += 1;
        if (type == 2) player->defense += 1;
        if (type == 3) player->accuracy += 1;
        if (type == 4) player->intelligence += 1;
        if (type == 5) player->speed += 1;

        return 1;
    }
    else
    {
        printf("\n💀 You lost sparring...\n");
        return 0;
    }
}
void createDog(Dog *d)
{
    printf("Enter your dog's name: ");

    fgets(d->name, 50, stdin);
    d->name[strcspn(d->name, "\n")] = 0;

    d->hp = 100;
    d->maxHP = 100;
    d->attack = 320;
    d->speed = 300;

    d->defense = 315;
    d->accuracy = 918; // 80% hit chance
    d->intelligence = 920;

    d->fatigue = 100; // full energy
    d->maxFatigue = 100;

    d->skillCount = 2;

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

        // 🔥 SPECIAL EFFECTS (dito lang dapat lahat)
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
        // 🩸 Savage Fang effect
        else if (strcmp(s.name, "Savage Fang") == 0)
        {
            printf("A vicious tearing attack!\n");

            if (rand() % 100 < 40) // 40% bleed chance
            {
                enemy->isBleeding = 1;
                enemy->bleedTurns = 3; // fixed turns

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

            *damage += 5; // optional bonus

            // 🔥 FORCE HIT SYSTEM
            enemy->accuracy = 1000; // para siguradong tatama logic mo
        }
        else if (strcmp(s.name, "Blood Frenzy") == 0)
        {
            printf("You enter a BLOOD FRENZY!\n");

            // extra damage boost
            *damage += 15;

            // guaranteed bleed
            enemy->isBleeding = 1;
            enemy->bleedTurns = 4;

            printf("Enemy is BLEEDING heavily!\n");

            // downside (self damage)
            int recoil = 10;
            player->hp -= recoil;

            printf("You hurt yourself for %d recoil!\n", recoil);
        }
        else if (strcmp(s.name, "Phantom Rush") == 0)
        {
            printf("You vanish and strike multiple times!\n");

            // 🔥 2-hit burst
            int hit1 = (*damage);
            int hit2 = (*damage) / 2;

            int totalDamage = hit1 + hit2;

            // small randomness (speed chaos)
            totalDamage += (rand() % 6); // +0 to +5

            *damage = totalDamage;

            printf("First strike: %d\n", hit1);
            printf("Second strike: %d\n", hit2);

            // 🌀 evasion bonus chance (flavor effect)
            if (rand() % 100 < 25)
            {
                printf("You became untouchable during Phantom Rush!\n");
                // optional: could reduce enemy counter damage later
            }
        }
        else if (strcmp(s.name, "Shadow Blitz") == 0)
        {
            printf("You melt into the shadows and strike instantly!\n");

            // 🔥 base burst (stronger than Phantom Rush)
            int base = *damage;

            // 3-hit chain
            int hit1 = base;
            int hit2 = (int)(base * 0.7);
            int hit3 = (int)(base * 0.5);

            int total = hit1 + hit2 + hit3;

            // ⚡ speed bonus damage
            total += 10 + (rand() % 11); // 10–20 extra

            // 🎯 crit chance boost
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

            // 🎯 precise strike (remove randomness feel)
            int preciseDamage = *damage + 15;

            // 🔥 bonus crit chance
            if (rand() % 100 < 35)
            {
                printf("CRITICAL DEAD EYE SHOT!\n");
                preciseDamage += 20;
            }

            // 🧠 accuracy mastery bonus
            preciseDamage += (player->accuracy / 50);

            *damage = preciseDamage;

            printf("Dead Eye hits cleanly!\n");
        }
        else if (strcmp(s.name, "Fatal Aim") == 0)
        {
            printf("You lock in a fatal trajectory...\n");

            // 🎯 strong precision hit
            int dmg = *damage + 20;

            // 💥 armor break effect
            int defBreak = 15;
            enemy->defense -= defBreak;

            if (enemy->defense < 0)
                enemy->defense = 0;

            printf("Enemy DEF reduced by %d!\n", defBreak);

            // 💀 execute bonus if low HP
            if (enemy->hp < enemy->maxHP * 0.3)
            {
                dmg += 25;
                printf("EXECUTION BONUS!\n");
            }

            // ⚡ crit chance
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

            // 🔥 base destruction boost
            int base = *damage + 30;

            // ⚔️ multi-hit annihilation
            int hit1 = base;
            int hit2 = (int)(base * 0.8);
            int hit3 = (int)(base * 0.6);

            int total = hit1 + hit2 + hit3;

            printf("Hit 1: %d\n", hit1);
            printf("Hit 2: %d\n", hit2);
            printf("Hit 3: %d\n", hit3);

            // 🩸 guaranteed bleed (endgame pressure)
            enemy->isBleeding = 1;
            enemy->bleedTurns = 4;

            printf("Enemy is BLEEDING from destruction!\n");

            // 💀 execute bonus
            if (enemy->hp < enemy->maxHP * 0.4)
            {
                total += 30;
                printf("RAGNAROK EXECUTION BONUS!\n");
            }

            // ⚡ raw chaos modifier
            total += rand() % 15;

            // 🔥 recoil (power has cost)
            int recoil = 12;
            player->hp -= recoil;
            player->hp = clamp(player->hp);

            printf("You suffer %d recoil from Ragnarok power!\n", recoil);

            *damage = total;
        }
        else if (strcmp(s.name, "Judgement Eye") == 0)
        {
            printf("You gaze into the enemy's fate...\n");

            // 🎯 precise execution hit
            int dmg = *damage + 25;

            // 🛡️ DEF BREAK (judgement cracks armor)
            int defBreak = 20;
            enemy->defense -= defBreak;

            if (enemy->defense < 0)
                enemy->defense = 0;

            printf("Enemy DEF shattered by %d!\n", defBreak);

            // 🧠 CONFUSION (mental collapse)
            if (rand() % 100 < 35)
            {
                enemy->isConfused = 1;
                enemy->confuseTurns = 2 + rand() % 2;

                printf("Enemy's mind breaks under JUDGEMENT!\n");
            }

            // 💀 execute pressure
            if (enemy->hp < enemy->maxHP * 0.4)
            {
                dmg += 30;
                printf("JUDGEMENT EXECUTION BONUS!\n");
            }

            // ⚡ crit chance
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

            // ⚡ speed scaling damage
            int base = *damage + (player->speed / 20);

            // 👤 multi-hit phantom strikes
            int hit1 = base;
            int hit2 = (int)(base * 0.7);
            int hit3 = (int)(base * 0.5);
            int hit4 = (rand() % 10); // extra chaos hit

            int total = hit1 + hit2 + hit3 + hit4;

            printf("Phantom Hit 1: %d\n", hit1);
            printf("Phantom Hit 2: %d\n", hit2);
            printf("Phantom Hit 3: %d\n", hit3);
            printf("Phantom Hit 4: %d\n", hit4);

            // 🛡️ partial defense ignore
            int ignoreDef = enemy->defense / 3;
            enemy->defense -= ignoreDef;

            if (enemy->defense < 0)
                enemy->defense = 0;

            printf("Enemy DEF partially bypassed!\n");

            // 💀 assassin bonus if low HP
            if (enemy->hp < enemy->maxHP * 0.4)
            {
                total += 25;
                printf("ZERO PHANTOM EXECUTION BONUS!\n");
            }

            // ⚡ burnout cost (balance)
            int fatigueCost = 15;
            player->fatigue -= fatigueCost;

            if (player->fatigue < 0)
                player->fatigue = 0;

            printf("Fatigue drained by %d!\n", fatigueCost);

            *damage = total;
        }
        else if (s.type == SKILL_BUFF)
        {
            printf("You used %s!\n", s.name);

            if (strcmp(s.name, "Titan Aegis") == 0)
            {
                printf("🛡️ Titan Aegis activated!\n");

                // 🔥 Massive defense boost
                player->defense += 40;

                // ❤️ small heal sustain
                player->hp += 15;
                if (player->hp > player->maxHP)
                    player->hp = player->maxHP;

                // 🧱 optional: reduce fatigue cost pressure
                player->fatigue -= 10;
                if (player->fatigue < 0)
                    player->fatigue = 0;

                printf("DEF increased massively! Damage reduced for next hits!\n");
            }

            *damage = 0;
        }
    }

    // ================= BUFF =================
    else if (s.type == SKILL_BUFF)
    {
        printf("You used %s!\n", s.name);

        if (strcmp(s.name, "Iron Guard") == 0)
        {
            player->defense = clamp(player->defense + 5);
            printf("DEF +5!\n");
        }
        if (strcmp(s.name, "Steel Wall") == 0)
        {
            printf("You brace your body like unbreakable steel!\n");

            // 🔥 big defense boost (temporary style)
            player->defense += 20;
            if (player->defense > MAX_STAT)
                player->defense = MAX_STAT;

            printf("DEF +20!\n");

            // 🛡️ optional: reduce fatigue slightly (tank recovery feel)
            player->fatigue += 5;
            if (player->fatigue > player->maxFatigue)
                player->fatigue = player->maxFatigue;

            printf("You stabilized your stance!\n");
        }
        else if (strcmp(s.name, "Fortress Stance") == 0)
        {
            printf("You become an unbreakable fortress!\n");

            // 🛡️ massive defense boost
            player->defense += 40;
            if (player->defense > MAX_STAT)
                player->defense = MAX_STAT;

            printf("DEF +40!\n");

            // 🐢 trade-off: slower movement (heavy stance)
            player->speed -= 20;
            if (player->speed < MIN_STAT)
                player->speed = MIN_STAT;

            printf("Speed reduced due to heavy stance!\n");

            // 🔥 optional sustain
            player->fatigue += 10;
            if (player->fatigue > player->maxFatigue)
                player->fatigue = player->maxFatigue;

            printf("You are in FORTRESS MODE!\n");

        }

        *damage = 0; // importante para hindi pumasok sa hit system
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
    e->defense = 965;

    e->speed = 90;    // dagdag mo rin para kumpleto
    e->accuracy = 95; // important sa hit system
    e->intelligence = 55;

    e->isConfused = 0;
    e->confuseTurns = 0;

    e->isBleeding = 0;
    e->bleedTurns = 0;
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

    if (zoneIndex == 0)
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
    else if (zoneIndex == 1)
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
    else if (zoneIndex == 2)
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

    int choice;
    int defending = 0;
    int move;

    int baseDef = player->defense;
    int baseSpd = player->speed;

    Dog enemy;
    createEnemy(&enemy);
    setEnemyByZone(&enemy, zoneIndex, progress[zoneIndex]);

    system("cls");
    preBattleScene();

    // ================= MAIN BATTLE LOOP =================
    while (player->hp > 0 && enemy.hp > 0)
    {
        system("cls");
        displayBattleStatus(*player, enemy);

        printf("\n--- YOUR TURN ---\n");

        if (player->fatigue <= 20)
            printf("Your dog is exhausted!\n");

        printf("1. Attack\n2. Defend\n3. Heal\n4. Surrender\n");
        printf("Choice: ");

        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &choice) != 1 || choice < 1 || choice > 4)
        {
            printf("Invalid choice!\n");
            waitForEnter();
            continue;
        }

        // ================= ATTACK =================
        if (choice == 1)
        {
            system("cls");
            displayBattleStatus(*player, enemy);

            printf("Choose Skill:\n");

            for (int i = 0; i < 4; i++)
            {
                if (player->equipped[i] != -1)
                {
                    int idx = player->equipped[i];
                    printf("%d. %s (P:%d C:%d)\n",
                           i + 1,
                           player->skills[idx].name,
                           player->skills[idx].power,
                           player->skills[idx].cost);
                }
                else
                {
                    printf("%d. ---\n", i + 1);
                }
            }

            fgets(buffer, sizeof(buffer), stdin);

            if (sscanf(buffer, "%d", &move) != 1 || move < 1 || move > 4)
            {
                printf("Invalid skill!\n");
                waitForEnter();
                continue;
            }

            int skillIndex = player->equipped[move - 1];

            if (skillIndex == -1)
            {
                printf("No skill equipped!\n");
                waitForEnter();
                continue;
            }

            Skill s = player->skills[skillIndex];
            int damage = 0;

            // ================= FATIGUE CHECK =================
            if (player->fatigue < s.cost)
            {
                printf("Not enough energy! Weak action...\n");

                applySkillEffect(player, &enemy, s, &damage);
                damage /= 2; // hina pag kulang energy

                player->fatigue = 0;
            }
            else
            {
                applySkillEffect(player, &enemy, s, &damage);

                player->fatigue -= s.cost;
                player->fatigue = clampFatigue(player->fatigue, player->maxFatigue);
            }

            // ================= HIT SYSTEM =================
            if (damage > 0) // attack lang may hit/miss
            {
                if ((rand() % 100) < player->accuracy)
                {
                    enemy.hp -= damage;
                    enemy.hp = clamp(enemy.hp);

                    printf("You dealt %d damage!\n", damage);
                }
                else
                {
                    printf("You missed!\n");
                }
            }

            waitForEnter();
        }

        // ================= DEFEND =================
        else if (choice == 2)
        {
            defending = 1;
            printf("You are defending!\n");
            waitForEnter();
        }

        // ================= HEAL (basic) =================
        else if (choice == 3)
        {
            player->hp += 20;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;

            printf("You healed +20 HP!\n");
            waitForEnter();
        }

        // ================= SURRENDER =================
        else if (choice == 4)
        {
            printf("You surrendered...\n");
            waitForEnter();
            
            player->defense = baseDef;
            player->speed   = baseSpd;

            return 2;
        }

        // ================= ENEMY TURN =================
        if (player->hp > 0 && enemy.hp > 0)
        {
            int result = enemyAttack(player, &enemy, &defending);

            if (result == 0)
                player->hp = 0;
            if (result == 1)
                enemy.hp = 0;
        }

        // ================= FATIGUE REGEN =================
        player->fatigue += 2;
        if (player->fatigue > player->maxFatigue)
            player->fatigue = player->maxFatigue;

        // ================= RESULT CHECK =================
        if (player->hp <= 0)
        {
            printf("\n=== YOU LOSE ===\n");

            player->fatigue += 20;
            if (player->fatigue > player->maxFatigue)
                player->fatigue = player->maxFatigue;

                player->defense = baseDef;
                player->speed   = baseSpd;

            waitForEnter();
            return 0;
        }

        if (enemy.hp <= 0)
        {
            printf("\nYOU WIN!\n");

            applyBattleStatGain(player);
            checkSkillUnlock(player);

            player->fatigue += 20;
            if (player->fatigue > player->maxFatigue)
                player->fatigue = player->maxFatigue;

            if (progress[zoneIndex] < 3)
                progress[zoneIndex]++;

                player->defense = baseDef;
                player->speed   = baseSpd;

            waitForEnter();
            return 1;
        }
    }

    return -1;
}