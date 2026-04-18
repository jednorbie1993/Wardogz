#include <stdio.h>
#include "dog.h"
#include <stdlib.h>
#include <windows.h>

void createDog(Dog *d) {
    printf("Enter your dog's name: ");
    scanf("%s", d->name);

    d->hp = 100;
    d->maxHP = 100;  
    d->attack = 20;
    d->speed = 10;
}

void printDog(Dog d) {
    printf("\n--- Dog Info ---\n");
    printf("Name: %s\n", d.name);
    printf("HP: %d\n", d.hp);
    printf("Attack: %d\n", d.attack);
    printf("Speed: %d\n", d.speed);
}

void typeText(char *text, int speed) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        Sleep(speed); //  dynamic na
    }
}

void showHPBarPlayer(int hp, int maxHp) {
    static int lastHP = 100;

    if (hp < lastHP) {
        for (int current = lastHP; current >= hp; current--) {
            int bars = (current * 10) / maxHp;

            printf("\rPLAYER: [");
            for (int i = 0; i < 10; i++) {
                if (i < bars) printf("#");
                else printf("-");
            }

            printf("] (%d/%d)", current, maxHp);
            Sleep(30);
        }
    } else {
        for (int current = lastHP; current <= hp; current++) {
            int bars = (current * 10) / maxHp;

            printf("\rPLAYER: [");
            for (int i = 0; i < 10; i++) {
                if (i < bars) printf("#");
                else printf("-");
            }

            printf("] (%d/%d)", current, maxHp);
            Sleep(30);
        }
    }

    printf("\n");
    lastHP = hp;
}

void showHPBarEnemy(int hp, int maxHp) {
    static int lastHP = -1;

    if (lastHP == -1) {
        lastHP = hp;
    }

    if (hp < lastHP) {
        for (int current = lastHP; current >= hp; current--) {
            int bars = (current * 10) / maxHp;

            printf("\rENEMY : [");
            for (int i = 0; i < 10; i++) {
                if (i < bars) printf("#");
                else printf("-");
            }

            printf("] (%d/%d)", current, maxHp);
            Sleep(30);
        }
    } else {
        for (int current = lastHP; current <= hp; current++) {
            int bars = (current * 10) / maxHp;

            printf("\rENEMY : [");
            for (int i = 0; i < 10; i++) {
                if (i < bars) printf("#");
                else printf("-");
            }

            printf("] (%d/%d)", current, maxHp);
            Sleep(30);
        }
    }

    printf("\n");
    lastHP = hp;
}

void displayBattleStatus(Dog player, Dog enemy) {
    printf("\n--- BATTLE STATUS ---\n");

    printf("PLAYER: ");
    showHPBarPlayer(player.hp, player.maxHP);

    printf("ENEMY : ");
    showHPBarEnemy(enemy.hp, enemy.maxHP);
}

void waitForEnter() {
    printf("\nPress Enter to continue...");
    getchar(); // wait for enter
}

void battle(Dog *player) {
    Dog enemy;
    enemy.hp = 100;
    enemy.maxHP = 100;
    enemy.attack = 10;

    int choice;
    int defending = 0;

    printf("\n=== BATTLE START ===\n");

    while (player->hp > 0 && enemy.hp > 0) {

        system("cls"); //  CLEAR SCREEN EVERY TURN

        // ================= STATUS =================
        printf("\n--- BATTLE STATUS ---\n");
        showHPBarPlayer(player->hp, 100);
        showHPBarEnemy(enemy.hp, 100);

        // ================= PLAYER TURN =================
        printf("\n--- YOUR TURN ---\n");
        printf("1. Attack\n");
        printf("2. Defend\n");
        printf("3. Item (Heal)\n");
        printf("4. Surrender\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // clear buffer

        if (choice == 1) {

            system("cls");
            displayBattleStatus(*player, enemy);

            int move;
            printf("\nChoose Attack:\n");
            printf("1. Bite\n2. Scratch\n3. Growl\n4. Lock Jaw\n");
            scanf("%d", &move);
            while (getchar() != '\n');

            if (move < 1 || move > 4) {
            printf("Invalid move!\n");
            waitForEnter();
            continue; // balik sa next loop (your turn ulit)
            }

            int damage = player->attack;

            char *moveName = "Unknown"; // default

            if (move == 1) {
                damage += 5;
                moveName = "Bite";
            }
            else if (move == 2) {
                damage += 3;
                moveName = "Scratch";
            }
            else if (move == 3) {
                damage += 1;
                moveName = "Growl";
            }
            else if (move == 4) {
                damage += 8;
                moveName = "Lock Jaw";
            }
            
            system("cls");
            displayBattleStatus(*player, enemy);
            printf("\n");

            char buffer[50];
            sprintf(buffer, "You used %s...\n", moveName);
            typeText(buffer, 20);

            printf("Attacking");
            for (int i = 0; i < 3; i++) {
                printf(".");
                Sleep(300);
            }
            printf("\n");

            enemy.hp -= damage;
            if (enemy.hp < 0) enemy.hp = 0;

            int variance = rand() % 6; // 0–5
            damage += variance;

            printf("You dealt %d damage! (+%d random)\n", damage, variance);
            waitForEnter();
        }

        else if (choice == 2) {
            defending = 1;
            printf("You are defending!\n");
        }
        else if (choice == 3) {
            player->hp += 20;
            if (player->hp > 100) player->hp = 100;
            printf("You healed +20 HP!\n");
        }
        else if (choice == 4) {
            printf("You surrendered...\n");
            break;
        }

        if (enemy.hp <= 0) {
            printf("\n YOU WIN!\n");
            break;
        }

        system("cls");
        displayBattleStatus(*player, enemy);

        // ================= ENEMY TURN =================
        printf("\n--- ENEMY TURN ---\n");

        int action = rand() % 100;
        int enemyDamage = enemy.attack;
        int variance = rand() % 6;
        enemyDamage += variance;

        if (enemy.hp <= 30 && action == 40) {
            // HEAL
            enemy.hp += 15;
            if (enemy.hp > 100) enemy.hp = 100;
            printf("Enemy used Heal! (+15 HP)\n");
            waitForEnter();
        }
        else if (action == 75) {
            // DEFEND (simple)
            printf("Enemy is defending!\n");
            waitForEnter();
            enemyDamage = enemyDamage / 2; // weaker next attack
            
        }
        else {
            // ATTACK
            int move = rand() % 3;

            char *moveName;

            if (move == 0) {
                enemyDamage += 5;
                moveName = "Bite";
            }
            else if (move == 1) {
                enemyDamage += 3;
                moveName = "Scratch";
            }
            else {
                enemyDamage += 8;
                moveName = "Lock Jaw";
            }

            if (defending) {
                enemyDamage /= 2;
                defending = 0;
            }

            char buffer[50];
            sprintf(buffer, "Enemy used %s...\n", moveName);
            typeText(buffer, 25);

            // 🔥 attack animation
            printf("Attacking");
            for (int i = 0; i < 3; i++) {
                printf(".");
                Sleep(300);
            }
            printf("\n");

            system("cls");
            displayBattleStatus(*player, enemy);
            printf("\n");

            player->hp -= enemyDamage;
            if (player->hp < 0) player->hp = 0;

            printf("\n");
            printf("Enemy dealt %d damage!\n", enemyDamage);
            waitForEnter();
        }

        if (player->hp <= 0) {
            printf("\n YOU LOST!\n");
            break;
        }

    }   //  CLOSES while loop

}   //  CLOSES battle function


// =========================================
// OUTSIDE NA DAPAT ITO
// =========================================

