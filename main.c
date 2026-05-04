#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dog.h"
#include <windows.h>
#include "stage.h"
#include <ctype.h>
#include "sparring.h"

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
        system("cls");
        printf("===== WARDOGZ MENU =====\n");
        printf("1. Wardogz\n");
        printf("2. Train Dog\n");
        printf("3. Battle\n");
        printf("4. Rest (%d/3)\n", restCount);
        printf("5. Options\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        // ================= WARDOGZ MENU =================
        if (choice == 1)
        {
            int sub;

            while (1)
            {
                system("cls");

                printf("===== WARDOGZ =====\n");
                printf("1. View Stats\n");
                printf("2. Skills\n");
                printf("3. Back\n");
                printf("Choice: ");

                fgets(input, sizeof(input), stdin);

                input[strcspn(input, "\n")] = 0;
                

                if (input[0] == '\0')
                {
                    printf("Invalid choice!\n");
                    waitForEnter();
                    continue;
                }

                sub = atoi(input);

                if (sub == 1)
                {
                    system("cls");
                    printDog(player);
                    waitForEnter();
                }
                else if (sub == 2)
                {
                    skillMenu(&player);
                }
                else if (sub == 3)
                {
                    break;
                }
                else
                {
                    printf("Invalid choice!\n");
                    waitForEnter();
                }
            }
        }

        // ================= TRAIN =================
        else if (choice == 2)
        {
            int t;

            while (1)
            {
                system("cls");

                printf("1. Power Training\n");
                printf("2. Speed Training\n");
                printf("3. Balance Training\n");
                printf("4. Sparring Training\n");
                printf("5. Return\n");
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

                // ================= RETURN =================
                if (t == 5)
                {
                    system("cls");
                    break;
                }

                // ================= SPARRING =================
                if (t == 4)
                {
                    sparringMenu(&player);  // or sparringBattle loop menu mo
                    continue;
                }

                // ================= TRAINING VALIDATION =================
                if (t < 1 || t > 3)
                {
                    printf("Invalid choice!\n");
                    waitForEnter();
                    continue;
                }

                trainDog(&player, t);
            }
        }

        // ================= BATTLE =================
        else if (choice == 3)
        {
            system("cls");
            startStage(&player);
            restCount = 0;
            player.fatigue = clampFatigue(player.fatigue - 10, player.maxFatigue);
        }

        // ================= REST =================
        else if (choice == 4)
        {
            if (restCount >= 3)
            {
                printf("You're too tired to rest anymore!\n");
                waitForEnter();
            }
            else if (player.fatigue >= 100 && player.hp >= player.maxHP)
            {
                printf("You're already fully rested!\n");
                waitForEnter();
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

                int hpGain = (rand() % 11) + 15;
                int fatigueGain = (rand() % 11) + 15;

                if (player.hp < player.maxHP)
                {
                    player.hp += hpGain;
                    if (player.hp > player.maxHP)
                        player.hp = player.maxHP;

                    printf("Recovered +%d HP!\n", hpGain);
                }

                if (player.fatigue < 100)
                {
                    player.fatigue = clampFatigue(player.fatigue + fatigueGain, player.maxFatigue);
                    printf("Recovered +%d Fatigue!\n", fatigueGain);
                }

                printf("You feel refreshed!\n");

                restCount++;
                waitForEnter();
            }
        }

        // ================= OPTIONS =================
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
                    break;
                }
                else
                {
                    printf("Invalid choice!\n");
                    waitForEnter();
                }
            }
        }

        // ================= EXIT =================
        else if (choice == 6)
        {
            printf("Exiting game...\n");
            break;
        }

        else
        {
            printf("Invalid choice!\n");
            waitForEnter();
        }
    }
}    
    /*

    gcc main.c dog.c stage.c enemy.c -o wardogz
    .\wardogz.exe

    gcc *.c -o wardogz
    .\wardogz.exe

    gcc *.c -o wardo -Wall -Wextra

    gcc *.c -o wardogz.exe; .\wardogz.exe

    gcc main.c dog.c sparring.c enemy.c stage.c -o wardogz.exe

    played 4/25

                   9111

    */
