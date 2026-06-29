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
#include "intro.h"
#include <string.h>
#include <stdarg.h>
#include "save.h"
#include "console.h"

void showMainMenu(GameData *game, Dog *player)
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("WARDOGZ MENU");
    printBlankLine();

    printMenuItem(1, "Wardogz");
    printMenuItem(2, "Train Dog");
    printMenuItem(3, "Battle");
    printMenuItemFormat(4, "Rest (%d/%d)", game->restCount, player->maxRest);
    printMenuItem(5, "Options");

    if (player->campaignCompleted)
    {
        printMenuItem(6, "Credits");
        printMenuItem(7, "Exit");
    }
    else
    {
        printMenuItem(6, "Exit");
    }

    printBlankLine();
    printf("%35sEnter choice: ", "");
}

void showWardogzSubMenu()
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("WARDOGZ");
    printBlankLine();

    printMenuItem(1, "View Stats");
    printMenuItem(2, "Skills");
    printMenuItem(3, "Back");

    printBlankLine();
    printf("%35sChoice: ", "");
}

void showTrainMenu()
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("TRAIN DOG");
    printBlankLine();

    printMenuItem(1, "Power Training");
    printMenuItem(2, "Speed Training");
    printMenuItem(3, "Balance Training");
    printMenuItem(4, "Sparring Training");
    printMenuItem(5, "Return");

    printBlankLine();
    printf("%35sChoice: ", "");
}

void showBattleMenu()
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("BATTLE");
    printBlankLine();

    printMenuItem(1, "Campaign");
    printMenuItem(2, "Arena");
    printMenuItem(3, "Back");

    printBlankLine();
    printf("%35sChoice: ", "");
}

void showOptionsMenu()
{
    system("cls");

    printBorder();
    printBlankLine();
    printCentered("OPTIONS");
    printBlankLine();

    printMenuItemFormat(1, "System Log (%s)", systemLog ? "ON" : "OFF");
    printMenuItemFormat(2, "Animation (%s)", animationOn ? "ON" : "OFF");
    printMenuItem(3, "Back");

    printBlankLine();
    printf("%35sEnter choice: ", "");
}

int main()
{
    setupConsole();
    srand(time(NULL));
    setbuf(stdout, NULL);

    GameData game;
    Dog *player = &game.player;
    int choice;

    if (!loadGame(&game))
    {
        introStory(player);
        player->campaignCompleted = 0;
        game.restCount = 0;

        for (int i = 0; i < 19; i++)
            game.progress[i] = 0;

        saveGame(&game);
    }
    else
    {
        system("cls");

        printBorder();
        printBlankLine();
        printCentered("AUTOLOAD COMPLETE!");
        printBlankLine();
        printCenteredFormat("Welcome back, %s & %s!", player->trainerName, player->name);
        printBlankLine();
        printBorder();
        waitForEnter();
    }

    int running = 1;

    while (running)
    {
        showMainMenu(&game, player);

        char input[10];
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        // ================= WARDOGZ MENU =================
        if (choice == 1)
        {
            int sub;

            while (1)
            {
                showWardogzSubMenu();

                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;

                if (input[0] == '\0')
                {
                    printCentered("Invalid choice!");
                    waitForEnter();
                    continue;
                }

                sub = atoi(input);

                if (sub == 1)
                {
                    system("cls");
                    printDog(*player);
                    waitForEnter();
                }
                else if (sub == 2)
                {
                    skillMenu(player);
                }
                else if (sub == 3)
                {
                    break;
                }
                else
                {
                    printCentered("Invalid choice!");
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
                showTrainMenu();

                char input[10];
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;

                // ================= EMPTY INPUT =================
                if (input[0] == '\0')
                {
                    printCentered("Invalid input!");
                    printCentered("Please enter a number.");
                    waitForEnter();
                    continue;
                }

                // ================= NOT A NUMBER =================
                if (!isdigit(input[0]))
                {
                    printCentered("Invalid input!");
                    printCentered("Numbers only.");
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
                    sparringMenu(player);
                    game.restCount = 0;
                    continue;
                }

                // ================= TRAINING VALIDATION =================
                if (t < 1 || t > 3)
                {
                    printCentered("Invalid choice!");
                    waitForEnter();
                    continue;
                }

                trainDog(player, t);
            }
        }

        // ================= BATTLE =================
        else if (choice == 3)
        {
            int battleChoice;
            char battleInput[10];

            while (1)
            {
                showBattleMenu();

                fgets(battleInput, sizeof(battleInput), stdin);
                battleChoice = atoi(battleInput);

                if (battleChoice == 1)
                {
                    system("cls");
                    startStage(player, game.progress);
                    game.restCount = 0;
                    player->fatigue = clampFatigue(player->fatigue - 2, player->maxFatigue);
                }
                else if (battleChoice == 2)
                {
                    arenaMenu(player);
                    game.restCount = 0;
                    player->fatigue = clampFatigue(player->fatigue - 2, player->maxFatigue);
                }
                else if (battleChoice == 3)
                {
                    break;
                }
                else
                {
                    printCentered("Invalid choice!");
                    waitForEnter();
                }
            }
        }

        // ================= REST =================
        else if (choice == 4)
        {
            if (game.restCount >= player->maxRest)
            {
                printCentered("You're too tired to rest anymore!");
                waitForEnter();
            }
            else if (player->fatigue >= 100 && player->hp >= player->maxHP)
            {
                printCentered("You're already fully rested!");
                waitForEnter();
            }
            else
            {
                system("cls");
                printBorder();
                printBlankLine();
                printCentered("RESTING");
                printBlankLine();

                printCenteredFormat("%s is resting...", player->name);
                Sleep(150);
                printBlankLine();

                // ================= HP RECOVERY =================
                int hpGain;

                if (game.restCount == 0)
                {
                    // first rest = recover half missing HP
                    int missingHP = player->maxHP - player->hp;
                    hpGain = missingHP / 2;

                    if (hpGain < 1)
                        hpGain = 1;
                }
                else
                {
                    // second & third rest
                    hpGain = 20 + ((player->maxHP / 100) * 5);
                    hpGain += rand() % 6;
                }

                if (player->hp < player->maxHP)
                {
                    player->hp += hpGain;

                    if (player->hp > player->maxHP)
                        player->hp = player->maxHP;

                    printCenteredFormat("Recovered +%d HP!", hpGain);
                }

                // ================= FATIGUE RECOVERY =================
                int fatigueGain = 20 + (player->stageClearBonus * 50) + (rand() % 6);

                if (fatigueGain > 300)
                    fatigueGain = 300;

                if (player->fatigue < player->maxFatigue)
                {
                    player->fatigue = clampFatigue(
                        player->fatigue + fatigueGain,
                        player->maxFatigue);

                    printCenteredFormat("Recovered +%d Fatigue!", fatigueGain);
                }

                printCentered("You feel refreshed!");

                game.restCount++;
                waitForEnter();
            }
        }

        // ================= OPTIONS =================
        else if (choice == 5)
        {
            int optChoice;

            while (1)
            {
                showOptionsMenu();

                fgets(input, sizeof(input), stdin);
                optChoice = atoi(input);

                if (optChoice == 1)
                {
                    systemLog = !systemLog;
                    printCenteredFormat("System Log is now %s", systemLog ? "ON" : "OFF");
                    waitForEnter();
                }
                else if (optChoice == 2)
                {
                    animationOn = !animationOn;
                    printCenteredFormat("Animation is now %s", animationOn ? "ON" : "OFF");
                    waitForEnter();
                }
                else if (optChoice == 3)
                {
                    break;
                }
                else
                {
                    printCentered("Invalid choice!");
                    waitForEnter();
                }
            }
        }

        // ================= CREDITS / EXIT =================
        else if (player->campaignCompleted && choice == 6)
        {
            showCredits();
        }
        else if
        (
            (player->campaignCompleted && choice == 7) ||
            (!player->campaignCompleted && choice == 6)
        )
        {
            printCentered("Exiting game...");
            saveGame(&game);
            running = 0;
        }
        else
        {
            printCentered("Invalid choice!");
            waitForEnter();
        }

        saveGame(&game);
    }
}
