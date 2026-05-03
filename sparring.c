#include "dog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int enemyAI(Dog *enemy, Dog *player, int type)
{
    int move = rand() % 4;

    if (type == 1) // Ossas aggressive
        return (enemy->attack / 10) + rand() % 6;

    if (type == 2) // Chubby tank
        return (enemy->attack / 14) + rand() % 3;

    if (type == 5) // Snoopy speed
        return (enemy->attack / 11) + rand() % 5;

    // default
    return (enemy->attack / 12) + rand() % 4;
}

void applySparReward(Dog *player, int type)
{
    if (type == 1)
        player->attack += 1;
    if (type == 2)
        player->defense += 1;
    if (type == 3)
        player->accuracy += 1;
    if (type == 4)
        player->intelligence += 1;
    if (type == 5)
        player->speed += 1;

    printf("Spar reward applied!\n");
    waitForEnter();
}

void sparringDog(Dog *player, int type)
{
    Dog spar;

    // create sparring partner
    createSparPartner(&spar, type);

    printf("\n Sparring Match Started!\n");
    printf("Opponent: %s\n", spar.name);

    int playerHP = player->maxHP;
    int sparHP = spar.maxHP;

    while (playerHP > 0 && sparHP > 0)
    {
        // PLAYER TURN
        int dmg = (player->attack / 10) + rand() % 3;
        sparHP -= dmg;

        printf("You dealt %d damage!\n", dmg);

        if (sparHP <= 0)
            break;

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
        if (type == 1)
            player->attack += rand() % 3 + 1;
        if (type == 2)
            player->defense += rand() % 3 + 1;
        if (type == 3)
            player->accuracy += rand() % 3 + 1;
        if (type == 4)
            player->intelligence += rand() % 3 + 1;
        if (type == 5)
            player->speed += rand() % 3 + 1;
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

        printf("Ossas appears! Aggressive attacker!\n");
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

        printf("Chubby appears! Defensive tank!\n");
    }

    // ================= JWEAR (ACCURACY) =================
    else if (type == 3)
    {
        strcpy(e->name, "Jeward");

        e->attack = 80 + rand() % 20;
        e->defense = 70 + rand() % 20;
        e->speed = 80 + rand() % 20;
        e->accuracy = 140 + rand() % 30;
        e->intelligence = 80;

        printf("Jeward appears! Precision striker!\n");
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

        printf("Tiny appears! Smart strategist!\n");
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

        printf("Snoopy appears! Speed demon!\n");
    }

    // fallback safety
    else
    {
        strcpy(e->name, "Unknown");
    }
    pauseAndClear();
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

    int pHP = player->maxHP;
    int eHP = enemy.maxHP;

    int pMax = player->maxHP;
    int eMax = enemy.maxHP;

    printf("\n SPARRING START: %s\n\n", enemy.name);
    pauseAndClear();

    while (pHP > 0 && eHP > 0)
    {
        // ================= HP BAR =================
        printf("\nYOU:    [%d/%d]\n", pHP, pMax);
        printf("ENEMY:  [%d/%d]\n\n", eHP, eMax);

        // ================= PLAYER MOVE =================
        int move;
        int dmg = 0;

        printf("\nChoose Move:\n");
        printf("1. Gum Bite\n");
        printf("2. Light Charge\n");
        printf("3. Hip Check\n");
        printf("4. Paw Hug\n");
        printf("Choice: ");

        scanf("%d", &move);
        getchar();

        if (move == 1)
        {
            printf("You used Gum Bite!\n");
            dmg = (player->attack / 12) + rand() % 4;
        }
        else if (move == 2)
        {
            printf("Light Charge!\n");
            dmg = (player->attack / 10) + rand() % 6;
        }
        else if (move == 3)
        {
            printf("Hip Check!\n");
            dmg = (player->attack / 11) + rand() % 5;
        }
        else if (move == 4)
        {
            printf("Paw Hug!\n");
            dmg = (player->attack / 20);

            player->hp += 3;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;
        }

        eHP -= dmg;
        printf("You dealt %d damage!\n", dmg);

        if (eHP <= 0)
            break;

        // ================= ENEMY MOVE =================
        int enemyMove = rand() % 3 + 1;
        int enemyDmg = 0;

        if (enemyMove == 1)
        {
            printf("%s used Bite!\n", enemy.name);
            enemyDmg = (enemy.attack / 12) + rand() % 4;
        }
        else if (enemyMove == 2)
        {
            printf("%s used Charge!\n", enemy.name);
            enemyDmg = (enemy.attack / 10) + rand() % 5;
        }
        else
        {
            printf("%s used Tackle!\n", enemy.name);
            enemyDmg = (enemy.attack / 11) + rand() % 4;
        }

        pHP -= enemyDmg;
        printf("%s dealt %d damage!\n", enemy.name, enemyDmg);

        // ================= CUT FEEL =================
        printf("\nPress Enter to continue...");
        getchar();

        system("cls");
    }

    // ================= RESULT =================
    if (pHP > 0)
    {
        printf("\n YOU WIN SPARRING!\n");
        applySparReward(player, type);
        return 1;
    }
    else
    {
        printf("\n YOU LOST SPARRING...\n");
        return 0;
    }
}
