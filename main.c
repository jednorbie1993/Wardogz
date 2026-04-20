#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dog.h"
#include <windows.h>

int main()
{
    srand(time(NULL));

    Dog player;
    int choice;

    createDog(&player);

    int restCount = 0;

    while (1)
    {
        printf("\n===== WARDOGZ MENU =====\n");
        printf("1. View Stats\n");
        printf("2. Train Dog\n");
        printf("3. Battle\n");
        printf("4. Rest (%d/3)\n", restCount);
        printf("5. Options\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1)
        {
            system("cls");
            printDog(player);
            pauseAndClear();
        }
        else if (choice == 2)
        {
            system("cls");

            player.attack += 5;
            player.hp += 10;
            player.defense += 2;
            player.speed += 1;
            player.accuracy += 2;
            player.intelligence += 2;

            if (player.hp > player.maxHP)
                player.hp = player.maxHP;

            printf("You trained your dog!\n");
            pauseAndClear();
        }
        else if (choice == 3)
        {
            system("cls");
            battle(&player);
            restCount = 0;
        }
        else if (choice == 4)
        {
            if (restCount >= 3)
            {
                printf("You're too tired to rest anymore!\n");
                waitForEnter();
                system("cls");
            }
            else if (player.hp == player.maxHP)
            {
                printf("You're already at full HP!\n");
                waitForEnter();
                system("cls");
            }
            else
            {
                printf("%s is resting", player.name);
                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    Sleep(300);
                }
                printf("\n");

                int heal = 20;
                player.hp += heal;

                if (player.hp > player.maxHP)
                    player.hp = player.maxHP;

                restCount++;

                printf("You recovered +%d HP!\n", heal);
                showHPBarPlayer(player.hp, player.maxHP);
                waitForEnter();
                system("cls");
            }
        }
        else if (choice == 5)
        {
            int optChoice;

            while (1)
            {
                system("cls");
                printf("\n===== OPTIONS =====\n");
                printf("1. System Log (%s)\n", systemLog ? "ON" : "OFF");
                printf("2. Animation (%s)\n", animationOn ? "ON" : "OFF");
                printf("3. Back\n");
                printf("Enter choice: ");

                char input[10];
                fgets(input, sizeof(input), stdin);
                optChoice = atoi(input);

                if (optChoice == 1)
                {
                    systemLog = !systemLog;
                    printf("System Log is now %s\n", systemLog ? "ON" : "OFF");
                    waitForEnter();
                }
                else if (optChoice == 2)
                {
                    animationOn = !animationOn;
                    printf("Animation is now %s\n", animationOn ? "ON" : "OFF");
                    waitForEnter();
                }
                else if (optChoice == 3)
                {
                    system("cls");
                    break;
                }
                else
                {
                    printf("Invalid choice!\n");
                    waitForEnter();
                }
            }
        }
        else if (choice == 6)
        {
            printf("Exiting game...\n");
            break;
        }
        else
        {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
// gcc main.c dog.c -o wardogz
//.\wardogz.exe