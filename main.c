#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dog.h"
#include <windows.h>
#include "stages/stage.h"
#include <ctype.h>
#include "sparring/sparring.h"
#include "cinematic.h"
#include "sparring/sparring_system.h"
#include "credit.h"
#include "arena/arena.h"

int main()
{
    srand(time(NULL));
    setbuf(stdout, NULL);

    Dog player;
    int choice;

    createDog(&player);
    player.campaignCompleted = 0;

    int restCount = 0;
    int maxRest = 3;
    //int progress[19] = {0};

    int progress[21] =
    {
        3,3,3,
        3,3,2,4,4,
        2,4,4,3,
        2,4,4,3,
        4,4,4,4,0
    };

    while (1)
    {


        system("cls");
        printf("===== WARDOGZ MENU =====\n");
        printf("1. Wardogz\n");
        printf("2. Train Dog\n");
        printf("3. Battle\n");
        printf("4. Rest (%d/%d)\n", restCount, player.maxRest);
        printf("5. Options\n");

        if (player.campaignCompleted)
        {
            printf("6. Credits\n");
            printf("7. Exit\n");
        }
        else
        {
            printf("6. Exit\n");
        }
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
            int battleChoice;
            char battleInput[10];

            while (1)
            {
                system("cls");

                printf("===== BATTLE =====\n");
                printf("1. Campaign\n");
                printf("2. Arena\n");
                printf("3. Back\n");
                printf("Choice: ");

                fgets(battleInput, sizeof(battleInput), stdin);
                battleChoice = atoi(battleInput);

                if (battleChoice == 1)
                {
                    system("cls");
                    startStage(&player, progress);
                    restCount = 0;
                    player.fatigue = clampFatigue(player.fatigue - 10, player.maxFatigue);
                }
                else if (battleChoice == 2)
                {
                    arenaMenu(&player);
                }
                else if (battleChoice == 3)
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

        // ================= REST =================
        else if (choice == 4)
        {
            if (restCount >= player.maxRest)
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
                    Sleep(50);
                }

                printf("\n");

                // ================= HP RECOVERY =================
                int hpGain;

                if (restCount == 0)
                {
                    // first rest = recover half missing HP
                    int missingHP = player.maxHP - player.hp;
                    hpGain = missingHP / 2;

                    if (hpGain < 1)
                        hpGain = 1;
                }
                else
                {
                    // second & third rest
                    hpGain = 20 + ((player.maxHP / 100) * 5);
                    hpGain += rand() % 6;
                }

                if (player.hp < player.maxHP)
                {
                    player.hp += hpGain;

                    if (player.hp > player.maxHP)
                        player.hp = player.maxHP;

                    printf("Recovered +%d HP!\n", hpGain);
                }

                // ================= FATIGUE RECOVERY =================
                int fatigueGain = 20 + (player.stageClearBonus * 50) + (rand() % 6);

                if (fatigueGain > 300)
                    fatigueGain = 300;
                

                if (player.fatigue < player.maxFatigue)
                {
                    player.fatigue = clampFatigue(
                        player.fatigue + fatigueGain,
                        player.maxFatigue);

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
        else if (player.campaignCompleted && choice == 6)
        {
            showCredits();
        }
        else if
        (
            (player.campaignCompleted && choice == 7) ||
            (!player.campaignCompleted && choice == 6)
        )
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
    