#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dog.h"
#include <windows.h>

int main() {

    srand(time(NULL));

    Dog player;
    int choice;

    createDog(&player);

    int restCount = 0;

    while (1) {
        printf("\n===== WARDOGZ MENU =====\n");
        printf("1. View Stats\n");
        printf("2. Train Dog\n");
        printf("3. Battle\n");
        printf("4. Rest (%d/3)\n", restCount);
        printf("5. Exit\n");
        printf("Enter choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1) {
            system("cls");
            printDog(player);
            pauseAndClear(); // 👈 eto na kapalit
        }
        else if (choice == 2) {
            player.attack += 5;
            player.hp += 10;
            if (player.hp > player.maxHP) player.hp = player.maxHP;
            printf("You trained your dog!\n");
        }
        else if (choice == 3) {
            system("cls");
            battle(&player);

            restCount = 0; //  RESET AFTER BATTLE
        }
        else if (choice == 4) { // REST

            system("cls");
            
            if (player.hp == player.maxHP) {
                printf("You're already at full HP!\n");
            } else {

                // 🔥 DITO ILAGAY (before heal)
                printf("%s is resting", player.name);
                for (int i = 0; i < 3; i++) {
                    printf(".");
                    Sleep(300);
                }
                printf("\n");

                int heal = 20;
                player.hp += heal;

                if (player.hp > player.maxHP)
                    player.hp = player.maxHP;

                restCount++; // 🔥 IMPORTANT    

                printf("You recovered +%d HP!\n", heal);

                // 🔥 then show updated HP
                showHPBarPlayer(player.hp, player.maxHP);
            }

            waitForEnter();
            system("cls");
        }
        else if (choice == 5) {
            printf("Exiting game...\n");
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

/*

gcc main.c dog.c -o wardogz
.\wardogz.exe

*/