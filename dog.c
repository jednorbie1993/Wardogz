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

int clampFatigue(int value)
{
    if (value > 100)
        return 100;
    if (value < 0)
        return 0;
    return value;
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

    // 🔻 FATIGUE CHECK (fail chance)
    if (d->fatigue < 20)
    {
        printf("Too exhausted... Training failed!\n");
        d->fatigue = clampFatigue(d->fatigue - 5);
        return;
    }

    int greatChance = rand() % 100;

    // ⭐ GREAT TRAINING
    if (greatChance < 10)
    {
        int bonus = 10;

        printf("GREAT TRAINING!\n");

        if (type == 1) // POWER
        {
            int g1 = getGrowthGain(d->maxHP);
            int g2 = getGrowthGain(d->attack);
            int g3 = getGrowthGain(d->defense);

            int t1 = g1 + bonus;
            int t2 = g2 + bonus;
            int t3 = g3 + bonus;

            d->maxHP = clamp(d->maxHP + t1);
            d->attack = clamp(d->attack + t2);
            d->defense = clamp(d->defense + t3);

            printf("HP +%d | ATK +%d | DEF +%d\n", t1, t2, t3);
        }
        else if (type == 2) // SPEED
        {
            int g1 = getGrowthGain(d->speed);
            int g2 = getGrowthGain(d->accuracy);
            int g3 = getGrowthGain(d->intelligence);

            int t1 = g1 + bonus;
            int t2 = g2 + bonus;
            int t3 = g3 + bonus;

            d->speed = clamp(d->speed + t1);
            d->accuracy = clamp(d->accuracy + t2);
            d->intelligence = clamp(d->intelligence + t3);

            printf("SPD +%d | ACC +%d | INT +%d\n", t1, t2, t3);
        }
        else // BALANCE
        {
            int g1 = getGrowthGain(d->maxHP);
            int g2 = getGrowthGain(d->attack);
            int g3 = getGrowthGain(d->defense);
            int g4 = getGrowthGain(d->speed);
            int g5 = getGrowthGain(d->intelligence);

            int t1 = g1 + bonus;
            int t2 = g2 + bonus;
            int t3 = g3 + bonus;
            int t4 = g4 + bonus;
            int t5 = g5 + bonus;

            d->maxHP = clamp(d->maxHP + t1);
            d->attack = clamp(d->attack + t2);
            d->defense = clamp(d->defense + t3);
            d->speed = clamp(d->speed + t4);
            d->intelligence = clamp(d->intelligence + t5);

            printf("HP +%d ATK +%d DEF +%d SPD +%d INT +%d\n",
                   t1, t2, t3, t4, t5);
        }

        d->hp = d->maxHP;
    }
    else
    {
        // ⭐ NORMAL TRAINING

        int g1, g2, g3;

        if (type == 1) // POWER
        {
            g1 = getGrowthGain(d->maxHP);
            g2 = getGrowthGain(d->attack);
            g3 = getGrowthGain(d->defense);

            d->maxHP = clamp(d->maxHP + g1);
            d->attack = clamp(d->attack + g2);
            d->defense = clamp(d->defense + g3);

            printf("HP +%d | ATK +%d | DEF +%d\n", g1, g2, g3);
        }
        else if (type == 2) // SPEED
        {
            g1 = getGrowthGain(d->speed);
            g2 = getGrowthGain(d->accuracy);
            g3 = getGrowthGain(d->intelligence);

            d->speed = clamp(d->speed + g1);
            d->accuracy = clamp(d->accuracy + g2);
            d->intelligence = clamp(d->intelligence + g3);

            printf("SPD +%d | ACC +%d | INT +%d\n", g1, g2, g3);
        }
        else // BALANCE
        {
            g1 = getGrowthGain(d->maxHP);
            g2 = getGrowthGain(d->attack);
            g3 = getGrowthGain(d->defense);

            int g4 = getGrowthGain(d->speed);
            int g5 = getGrowthGain(d->intelligence);

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

    // 🔻 FATIGUE COST
    d->fatigue = clampFatigue(d->fatigue - randRange(8, 15));
}

void createDog(Dog *d)
{
    printf("Enter your dog's name: ");

    fgets(d->name, 50, stdin);
    d->name[strcspn(d->name, "\n")] = 0;

    d->hp = 100;
    d->maxHP = 100;
    d->attack = 920;
    d->speed = 100;

    d->defense = 115;
    d->accuracy = 918; // 80% hit chance
    d->intelligence = 120;

    d->fatigue = 100; // full energy
}

void createEnemy(Dog *e)
{
    strcpy(e->name, "Wild Dog");

    e->hp = 100;
    e->maxHP = 100;
    e->attack = 80;
    e->defense = 65;

    e->speed = 90;    // dagdag mo rin para kumpleto
    e->accuracy = 95; // important sa hit system
    e->intelligence = 55;
}



void enemyQuickAttack(Dog *player, Dog *enemy)
{
    int dmg = (enemy->attack / 8) + 3;

    if (dmg < 1) dmg = 1;

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
    printf("\n--- Dog Info ---\n");
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
    if (!animationOn)
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

void battle(Dog *player)
{
    int invalidCount = 0;

    char input[10];
    Dog enemy;

    createEnemy(&enemy);

    int choice;
    int defending = 0;

    printf("\n=== BATTLE START ===\n");

    while (player->hp > 0 && enemy.hp > 0)
    {
        system("cls");

        displayBattleStatus(*player, enemy);

        printf("\n--- YOUR TURN ---\n");

        if (player->fatigue <= 20)
        {
            printf("Your dog is exhausted!\n");
        }

        printf("1. Attack\n2. Defend\n3. Item (Heal)\n4. Surrender\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);

        // Enter lang
        if (input[0] == '\n')
        {
            printf("Please select a number.\n");
            waitForEnter();
            continue;
        }

        choice = atoi(input);

        // invalid range
        if (choice < 1 || choice > 4)
        {
            printf("Invalid choice! Select 1-4 only.\n");
            waitForEnter();
            continue;
        }

        // ================= PLAYER TURN =================
        if (choice == 1) // ================= ATTACK =================
        {
            system("cls");
            displayBattleStatus(*player, enemy);

            printf("\nChoose Attack:\n");
            printf("1. Bite\n2. Scratch\n3. Growl\n4. Lock Jaw\n");

            fgets(input, sizeof(input), stdin);

            // ❗ INVALID INPUT HANDLER
            if (input[0] == '\n' || !isdigit((unsigned char)input[0]))
            {
                invalidCount++;

                system("cls");
                displayBattleStatus(*player, enemy);

                if (invalidCount == 1)
                    printf("\nHey, focus on your battle!\n");
                else if (invalidCount == 2)
                    printf("\nHey! Hey! I told you to focus!\n");
                else
                    printf("\nCome on! Wake up! What's wrong with you?\n");

                waitForEnter();

                printf("\nEnemy takes advantage of your hesitation!\n");
                enemyQuickAttack(player, &enemy);

                waitForEnter();
                continue;
            }

            int move = atoi(input);

            if (move < 1 || move > 4)
            {
                invalidCount++;

                system("cls");
                displayBattleStatus(*player, enemy);

                printf("\nInvalid move!\n");
                waitForEnter();

                printf("\nEnemy takes advantage!\n");
                enemyAttack(player, &enemy, &defending);

                waitForEnter();
                continue;
            }

            // ✅ VALID MOVE
            invalidCount = 0;

            int penalty = getFatiguePenalty(player->fatigue);
            int effectiveAttack = player->attack - penalty;
            if (effectiveAttack < 1) effectiveAttack = 1;
            if (effectiveAttack > 999) effectiveAttack = 999;

            char *moveName = "Unknown";

            if (move == 1) moveName = "Bite";
            else if (move == 2) moveName = "Scratch";
            else if (move == 3) moveName = "Growl";
            else if (move == 4) moveName = "Lock Jaw";

            printf("\nYou used %s...\n", moveName);

            printf("Attacking");
            for (int i = 0; i < 3; i++)
            {
                printf(".");
                fflush(stdout);
                Sleep(200);
            }
            printf("\n");

            // 🎯 ACCURACY
            int dodgeChance = enemy.speed * 2;
            int finalAccuracy = player->accuracy - dodgeChance;

            if (finalAccuracy < 70) finalAccuracy = 70;
            if (finalAccuracy > 95) finalAccuracy = 95;

            int roll = rand() % 100;

            if (roll < finalAccuracy)
            {
                if (move == 3) // GROWL
                {
                    enemy.attack -= 2;
                    if (enemy.attack < 1) enemy.attack = 1;

                    printf("Enemy attack reduced!\n");
                }
                else
                {
                    int baseDamage = (effectiveAttack / 6) + 5;

                    // 🎲 randomness (balanced range)
                    baseDamage += (rand() % 11) - 5; // -5 to +5

                    // ⚔️ move bonus
                    if (move == 1) baseDamage += 5;  // Bite
                    else if (move == 2) baseDamage += 3;  // Scratch
                    else if (move == 4) baseDamage += 8;  // Lock Jaw

                    // 🛡️ defense reduction (light lang)
                    baseDamage -= enemy.defense / 20;

                    // 💥 critical (optional pero maganda feel)
                    if (isCritical(player->hp, player->maxHP))
                    {
                        baseDamage += 10;
                        printf("CRITICAL HIT!\n");
                    }

                    // 😴 fatigue
                    float fatigueFactor = 1.0 - (player->fatigue / 200.0);
                    if (fatigueFactor < 0.6) fatigueFactor = 0.6;

                    int finalDamage = (int)(baseDamage * fatigueFactor);

                    // minimum safety
                    if (finalDamage < 1)
                        finalDamage = 1;

                    enemy.hp -= finalDamage;
                    enemy.hp = clamp(enemy.hp);

                    printf("You dealt %d damage!\n", finalDamage);
                }
            }
            else
            {
                printf("You missed!\n");
            }

            waitForEnter();
        }
        else if (choice == 2) // ================= DEFEND =================
        {
            defending = 1;
            printf("You are defending!\n");
            waitForEnter();
        }
        else if (choice == 3) // ================= HEAL =================
        {
            player->hp += 20;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;

            printf("You healed +20 HP!\n");
            waitForEnter();
        }
        else if (choice == 4) // ================= SURRENDER =================
        {
            printf("You surrendered...\n");
            pauseAndClear();
            break;
        }

        // ================= WIN CHECK =================
        if (enemy.hp <= 0)
        {
            system("cls");
            printf("\nYOU WIN!\n");
            applyBattleStatGain(player);
            pauseAndClear();
            break;
        }
        // ================= ENEMY TURN =================
        system("cls");
        displayBattleStatus(*player, enemy);

        enemyAttack(player, &enemy, &defending);
        printf("\nPress Enter to continue...");
        fflush(stdout);
        getchar();

        // ================= LOSE CHECK =================
        if (player->hp <= 0)
        {
            loseSequence(player, &enemy);
            pauseAndClear();
            break;
            }
        }
    }