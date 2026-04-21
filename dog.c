#include <stdio.h>
#include "dog.h"
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h> // para sa strcspn

int systemLog = 0;
int animationOn = 1; //  NEW (default ON)

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

void createDog(Dog *d)
{
    printf("Enter your dog's name: ");

    fgets(d->name, 50, stdin);
    d->name[strcspn(d->name, "\n")] = 0;

    d->hp = 100;
    d->maxHP = 100;
    d->attack = 20;
    d->speed = 10;

    d->defense = 5;
    d->accuracy = 80; // 80% hit chance
    d->intelligence = 10;

    d->fatigue = 100; // full energy
}

void createEnemy(Dog *e)
{
    strcpy(e->name, "Wild Dog");

    e->hp = 100;
    e->maxHP = 100;
    e->attack = 10;
    e->defense = 5;

    e->speed = 10;    // dagdag mo rin para kumpleto
    e->accuracy = 90; // important sa hit system
    e->intelligence = 5;
}

void applyStatGain(Dog *d, int atk, int hp, int def, int spd, int acc, int intel)
{
    d->attack = clamp(d->attack + atk);
    d->hp = clamp(d->hp + hp);
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
                d->hp = clamp(d->hp + gain);
                if (d->hp > d->maxHP)
                    d->hp = d->maxHP;
                printf("HP +%d\n", gain);
                break;
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
    getchar(); // works perfectly kapag fgets na lahat
}

void pauseAndClear()
{
    printf("\nPress Enter to continue...");

    getchar(); // no loop, no fflush, simple lang

    system("cls");
}

void battle(Dog *player)
{
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
        choice = atoi(input);

        // ================= PLAYER TURN =================
        if (choice == 1)
        {
            system("cls");
            displayBattleStatus(*player, enemy);

            printf("\nChoose Attack:\n");
            printf("1. Bite\n2. Scratch\n3. Growl\n4. Lock Jaw\n");

            fgets(input, sizeof(input), stdin);
            int move = atoi(input);

            if (move < 1 || move > 4)
            {
                printf("Invalid move!\n");
                waitForEnter();
                continue;
            }

            int damage = 0;
            char *moveName = "Unknown";

            int penalty = getFatiguePenalty(player->fatigue);
            int effectiveAttack = player->attack - penalty;
            if (effectiveAttack < 1) effectiveAttack = 1;

            if (move == 1) { damage = effectiveAttack + 5; moveName = "Bite"; }
            else if (move == 2) { damage = effectiveAttack + 3; moveName = "Scratch"; }
            else if (move == 3) { moveName = "Growl"; }
            else if (move == 4) { damage = effectiveAttack + 8; moveName = "Lock Jaw"; }

            printf("\nYou used %s...\n", moveName);

            printf("Attacking");
            for (int i = 0; i < 3; i++)
            {
                printf(".");
                fflush(stdout);
                Sleep(200);
            }
            printf("\n");

            int dodgeChance = enemy.speed * 2;
            int finalAccuracy = player->accuracy - dodgeChance;

            if (finalAccuracy < 70) finalAccuracy = 70;
            if (finalAccuracy > 95) finalAccuracy = 95;

            int roll = rand() % 100;

            if (systemLog)
                printf("[HIT  ] Roll: %-3d | Acc : %-3d\n", roll, finalAccuracy);

            if (roll < finalAccuracy)
            {
                if (move == 3)
                {
                    enemy.attack -= 2;
                    printf("Enemy attack reduced!\n");
                }
                else
                {
                    damage += rand() % 6;

                    if (isCritical(player->hp, player->maxHP))
                    {
                        damage *= 2;
                        printf("CRITICAL HIT!\n");
                    }

                    damage -= enemy.defense;
                    if (damage < 1) damage = 1;

                    enemy.hp -= damage;
                    enemy.hp = clamp(enemy.hp);

                    printf("You dealt %d damage!\n", damage);
                }
            }
            else
            {
                printf("But it missed!\n");
            }

            waitForEnter();
        }
        else if (choice == 2)
        {
            defending = 1;
            printf("You are defending!\n");
            waitForEnter();
        }
        else if (choice == 3)
        {
            player->hp += 20;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;

            printf("You healed +20 HP!\n");
            waitForEnter();
        }
        else if (choice == 4)
        {
            printf("You surrendered...\n");
            pauseAndClear();
            break;
        }

        // ================= WIN CHECK =================
        if (enemy.hp <= 0)
        {
            printf("\nYOU WIN!\n");
            applyBattleStatGain(player);
            pauseAndClear();
            break;
        }

        // ================= ENEMY TURN =================
        system("cls");
        displayBattleStatus(*player, enemy);

        printf("\n--- ENEMY TURN ---\n");

        int action = rand() % 100;
        int enemyDamage = enemy.attack + (rand() % 6);

        if (enemy.hp <= 30 && action < 20)
        {
            enemy.hp += 15;
            if (enemy.hp > enemy.maxHP)
                enemy.hp = enemy.maxHP;

            printf("Enemy used Heal! (+15 HP)\n");
        }
        else
        {
            int move = rand() % 3;
            char *moveName;

            if (move == 0) { enemyDamage += 5; moveName = "Bite"; }
            else if (move == 1) { enemyDamage += 3; moveName = "Scratch"; }
            else { enemyDamage += 8; moveName = "Lock Jaw"; }

            if (defending)
            {
                enemyDamage /= 2;
                defending = 0;
                printf("You defended! Damage reduced!\n");
            }

            printf("Enemy used %s...\n", moveName);

            printf("Attacking");
            for (int i = 0; i < 3; i++)
            {
                printf(".");
                fflush(stdout);
                Sleep(150);
            }
            printf("\n");

            int dodgeChance = player->speed * 2;
            int finalAccuracy = enemy.accuracy - dodgeChance;

            if (finalAccuracy < 70) finalAccuracy = 70;
            if (finalAccuracy > 95) finalAccuracy = 95;

            int roll = rand() % 100;

            if (systemLog)
                printf("[HIT  ] Roll: %-3d | Acc : %-3d\n", roll, finalAccuracy);

            if (roll < finalAccuracy)
            {
                if (isCritical(enemy.hp, enemy.maxHP))
                {
                    enemyDamage *= 2;
                    printf("Enemy CRITICAL HIT!\n");
                }

                player->hp -= enemyDamage;
                player->hp = clamp(player->hp);

                printf("Enemy dealt %d damage!\n", enemyDamage);
            }
            else
            {
                printf("Enemy missed!\n");
            }
        }

        // 🔥 CRITICAL FIX: ALWAYS WAIT (kahit walang systemLog)
        waitForEnter();

        // ================= LOSE CHECK =================
        if (player->hp <= 0)
        {
            loseSequence(player, &enemy);
            pauseAndClear();
            break;
        }
    }
}