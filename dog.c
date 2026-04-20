#include <stdio.h>
#include "dog.h"
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h> // para sa strcspn

int systemLog = 0;

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

void printDog(Dog d)
{
    printf("\n--- Dog Info ---\n");
    printf("Name: %s\n", d.name);
    printf("HP: %d\n", d.hp);
    printf("Attack: %d\n", d.attack);
    printf("Speed: %d\n", d.speed);
}

void typeText(char *text, int speed)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        Sleep(speed); //  dynamic na
    }
}

void showHPBarPlayer(int hp, int maxHp)
{
    static int lastHP = 100;

    if (hp < lastHP)
    {
        for (int current = lastHP; current >= hp; current--)
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

            printf("] (%d/%d)", current, maxHp);
            Sleep(30);
        }
    }
    else
    {
        for (int current = lastHP; current <= hp; current++)
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

            printf("] (%d/%d)", current, maxHp);
            Sleep(30);
        }
    }

    printf("\n");
    lastHP = hp;
}

void showHPBarEnemy(int hp, int maxHp)
{
    static int lastHP = -1;

    if (lastHP == -1)
    {
        lastHP = hp;
    }

    if (hp < lastHP)
    {
        for (int current = lastHP; current >= hp; current--)
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

            printf("] (%d/%d)", current, maxHp);
            Sleep(30);
        }
    }
    else
    {
        for (int current = lastHP; current <= hp; current++)
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

            printf("] (%d/%d)", current, maxHp);
            Sleep(30);
        }
    }

    printf("\n");
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

    getchar();   // no loop, no fflush, simple lang

    system("cls");
}

void battle(Dog *player)
{
    char input[10];
    Dog enemy;

    createEnemy(&enemy); // dito na manggagaling stats

    int choice;
    int defending = 0;

    printf("\n=== BATTLE START ===\n");

    while (player->hp > 0 && enemy.hp > 0)
    {
        system("cls");

        printf("\n--- BATTLE STATUS ---\n");
        showHPBarPlayer(player->hp, player->maxHP);
        showHPBarEnemy(enemy.hp, enemy.maxHP);

        printf("\n--- YOUR TURN ---\n");
        printf("1. Attack\n2. Defend\n3. Item (Heal)\n4. Surrender\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        // ================= ATTACK =================
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

            if (move == 1)
            {
                damage = player->attack + 5;
                moveName = "Bite";
            }
            else if (move == 2)
            {
                damage = player->attack + 3;
                moveName = "Scratch";
            }
            else if (move == 3)
            {
                moveName = "Growl";
            }
            else if (move == 4)
            {
                damage = player->attack + 8;
                moveName = "Lock Jaw";
            }

            //  animation
            system("cls");
            displayBattleStatus(*player, enemy);

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

            if (finalAccuracy < 70)
                finalAccuracy = 70;
            if (finalAccuracy > 95)
                finalAccuracy = 95;

            int roll = rand() % 100;

            // =====================
            // ANIMATION ONLY IF ON
            // =====================
            if (systemLog)
            {
                printf("\nCalculating...\n");

                for (int i = 0; i < 10; i++)
                {
                    int tempRoll = rand() % 100;
                    int tempAcc = rand() % 100;

                    printf("\rRoll: %d | Accuracy: %d   ", tempRoll, tempAcc);
                    fflush(stdout);

                    Sleep(80);
                }

                printf("\n");
            }

            // FINAL RESULT (always show once)
            if (systemLog)
            {
                printf("\rRoll: %d | Accuracy: %d\n", roll, finalAccuracy);
            }
            else
            {
                printf("\r"); // just clean line, no spam
            }

            if (roll < finalAccuracy)
            {
                if (move == 3)
                {
                    printf("Enemy attack reduced!\n");
                    enemy.attack -= 2;
                }
                else
                {
                    int variance = rand() % 6;
                    damage += variance;

                    damage -= enemy.defense;
                    if (damage < 1)
                        damage = 1;

                    enemy.hp -= damage;
                    if (enemy.hp < 0)
                        enemy.hp = 0;

                    printf("It hit! You dealt %d damage!\n", damage);
                }
            }
            else
            {
                printf("But it missed!\n");
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

        // ================= HEAL =================
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
            pauseAndClear();
            break;
        }

        // ================= WIN CHECK =================
        if (enemy.hp <= 0)
        {
            printf("\nYOU WIN!\n");
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

            if (move == 0)
            {
                enemyDamage += 5;
                moveName = "Bite";
            }
            else if (move == 1)
            {
                enemyDamage += 3;
                moveName = "Scratch";
            }
            else
            {
                enemyDamage += 8;
                moveName = "Lock Jaw";
            }

            if (defending)
            {
                enemyDamage /= 2;
                defending = 0;
                printf("You defended! Damage reduced!\n");
            }

            printf("Enemy used %s...\n", moveName);

            int dodgeChance = player->speed * 2;
            int finalAccuracy = enemy.accuracy - dodgeChance;

            if (finalAccuracy < 70)
                finalAccuracy = 70;
            if (finalAccuracy > 95)
                finalAccuracy = 95;

            int roll = rand() % 100;

            if (systemLog)
            {
                printf("\n[DEBUG] Roll: %d | Accuracy: %d\n", roll, finalAccuracy);
            }

            if (roll < finalAccuracy)
            {
                printf("Attacking");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    Sleep(150);
                }

                player->hp -= enemyDamage;
                if (player->hp < 0)
                    player->hp = 0;

                printf("\nEnemy dealt %d damage!\n", enemyDamage);
            }
            else
            {
                printf("Enemy attacking");
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    fflush(stdout);
                    Sleep(150);
                }

                printf("\nEnemy missed! You dodged!\n");
            }

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
}
