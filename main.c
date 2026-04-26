#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dog.h"
#include <windows.h>
#include "stage.h"

int main()
{
    srand(time(NULL));
    setbuf(stdout, NULL);

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
            while (1) // 🔁 loop para hindi umalis agad
            {
                system("cls");

                printf("1. Power Training\n");
                printf("2. Speed Training\n");
                printf("3. Balance Training\n");
                printf("4. Return\n");
                printf("Choice: ");

                char input[10];
                fgets(input, sizeof(input), stdin);
                int t = atoi(input);

                // 👉 RETURN OPTION
                if (t == 4)
                {
                    system("cls");
                    break; // ⬅️ EXIT training menu, balik sa main menu
                }

                if (t < 1 || t > 3)
                {
                    printf("Invalid choice!\n");
                    waitForEnter();
                    continue; // stay sa training menu
                }

                trainDog(&player, t);

                printf("\nTraining complete!\n");
                waitForEnter(); // mas safe kaysa pauseAndClear
            }
        }
        else if (choice == 3)
        {
            system("cls");
            startStage(&player);
            restCount = 0;
            player.fatigue = clampFatigue(player.fatigue - 10);
        }
        else if (choice == 4)
        {
            if (restCount >= 3)
            {
                printf("You're too tired to rest anymore!\n");
                waitForEnter();
                system("cls");
            }
            else if (player.fatigue >= 100)
            {
                printf("You're already fully rested!\n");
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

                // 👉 heal HP (optional nalang)
                if (player.hp < player.maxHP)
                {
                    player.hp += heal;
                    if (player.hp > player.maxHP)
                        player.hp = player.maxHP;
                }

                // ⭐ MAIN PURPOSE: fatigue recovery
                player.fatigue = clampFatigue(player.fatigue + 20);

                restCount++;

                printf("Recovered +20 Fatigue!\n");

                if (player.hp < player.maxHP)
                    printf("Recovered +%d HP!\n", heal);

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
/*

gcc main.c dog.c stage.c -o wardogz
.\wardogz.exe

gcc *.c -o wardogz
.\wardogz.exe

gcc *.c -o wardo -Wall -Wextra

gcc *.c -o wardogz.exe; .\wardogz.exe

played 4/25
*/