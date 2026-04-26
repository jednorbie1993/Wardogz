#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dog.h"
#include <windows.h>
#include <ctype.h>

void playerTurn(Dog *player, Dog *enemy, int *defending)
{
    char input[10];
    int choice;

    printf("\n--- YOUR TURN ---\n");

    if (player->fatigue <= 20)
        printf("Your dog is exhausted!\n");

    printf("1. Attack\n2. Defend\n3. Item (Heal)\n4. Surrender\n");
    printf("Choice: ");

    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    if (input[0] == '\n')
    {
        printf("Please select a number.\n");
        waitForEnter();
        return;
    }

    if (choice < 1 || choice > 4)
    {
        printf("Invalid choice!\n");
        waitForEnter();
        return;
    }

    if (choice == 1)
    {
        playerAttack(player, enemy);
    }
    else if (choice == 2)
    {
        *defending = 1;
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
        player->hp = 0;
        pauseAndClear();
    }
}

void playerAttack(Dog *player, Dog *enemy)
{
    char input[10];
    int move;
    static int invalidCount = 0;

    system("cls");
    displayBattleStatus(*player, *enemy);

    printf("\nChoose Attack:\n");
    printf("1. Bite\n2. Scratch\n3. Growl\n4. Lock Jaw\n");

    fgets(input, sizeof(input), stdin);

    // ❗ INVALID INPUT HANDLER
    if (input[0] == '\n' || !isdigit((unsigned char)input[0]))
    {
        invalidCount++;

        system("cls");
        displayBattleStatus(*player, *enemy);

        if (invalidCount == 1)
            printf("\nHey, focus on your battle!\n");
        else if (invalidCount == 2)
            printf("\nHey! Hey! I told you to focus!\n");
        else
            printf("\nCome on! Wake up! What's wrong with you?\n");

        waitForEnter();

        printf("\nEnemy takes advantage of your hesitation!\n");
        enemyQuickAttack(player, enemy);

        waitForEnter();
        return;
    }

    move = atoi(input);

    if (move < 1 || move > 4)
    {
        invalidCount++;

        system("cls");
        displayBattleStatus(*player, *enemy);

        printf("\nInvalid move!\n");
        waitForEnter();

        printf("\nEnemy takes advantage!\n");
        enemyAttack(player, enemy, NULL);

        waitForEnter();
        return;
    }

    // ================= VALID MOVE =================
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

    // ================= ACCURACY =================
    int dodgeChance = enemy->speed * 2;
    int finalAccuracy = player->accuracy - dodgeChance;

    if (finalAccuracy < 70) finalAccuracy = 70;
    if (finalAccuracy > 95) finalAccuracy = 95;

    int roll = rand() % 100;

    if (roll < finalAccuracy)
    {
        if (move == 3) // GROWL
        {
            enemy->attack -= 2;
            if (enemy->attack < 1) enemy->attack = 1;

            printf("Enemy attack reduced!\n");
        }
        else
        {
            int baseDamage = (effectiveAttack / 6) + 5;

            baseDamage += (rand() % 11) - 5;

            if (move == 1) baseDamage += 5;
            else if (move == 2) baseDamage += 3;
            else if (move == 4) baseDamage += 8;

            baseDamage -= enemy->defense / 20;

            if (isCritical(player->hp, player->maxHP))
            {
                baseDamage += 10;
                printf("CRITICAL HIT!\n");
            }

            float fatigueFactor = 1.0 - (player->fatigue / 200.0);
            if (fatigueFactor < 0.6) fatigueFactor = 0.6;

            int finalDamage = (int)(baseDamage * fatigueFactor);

            if (finalDamage < 1)
                finalDamage = 1;

            enemy->hp -= finalDamage;
            enemy->hp = clamp(enemy->hp);

            printf("You dealt %d damage!\n", finalDamage);
        }
    }
    else
    {
        printf("You missed!\n");
    }

    waitForEnter();
}

