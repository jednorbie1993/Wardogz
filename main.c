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

    while (1) {
        printf("\n===== WARDOGZ MENU =====\n");
        printf("1. View Stats\n");
        printf("2. Train Dog\n");
        printf("3. Battle\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printDog(player);
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
        }
        else if (choice == 4) {
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