#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "intro.h"
#include "dog.h"
#include <windows.h>

static void clearScreen()
{
    system("cls");
}

static void pressEnterIntro()
{
    printf("\nPress ENTER to continue...");
    fflush(stdout);

    char temp[20];
    fgets(temp, sizeof(temp), stdin);
}

static void introTypeText(const char *text, int delay)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout);

        if (animationOn)
            Sleep(delay);
    }
}

static void introLine(const char *text)
{
    introTypeText(text, 18);
    introTypeText("\n", 0);
}

static void introBlank()
{
    printf("\n");
}

static void slowDots(const char *text)
{
    introTypeText(text, 18);

    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);

        if (animationOn)
            Sleep(250);
    }

    printf("\n");
}

static void titleScreen()
{
    clearScreen();

    printf("========================================================\n");
    printf("                     WARDOGZ\n");
    printf("========================================================\n");
    printf("                 Press ENTER to Start\n");
    printf("========================================================\n");

    char temp[20];
    fgets(temp, sizeof(temp), stdin);
    
    Beep(800, 150);
}

static char getYesNo()
{
    char input[20];

    while (1)
    {
        printf("Choice (Y/N): ");
        fgets(input, sizeof(input), stdin);

        if (toupper(input[0]) == 'Y')
            return 'Y';

        if (toupper(input[0]) == 'N')
            return 'N';

        printf("Invalid input! Please enter Y or N.\n");
    }
}

static int choosePartner()
{
    char input[20];
    int choice;

    while (1)
    {
        clearScreen();
        printf("========================\n");
        printf("CHOOSE YOUR PARTNER\n");
        printf("========================\n\n");
        printf("1. Jamber  (Power Type)\n");
        printf("2. Kane    (Speed Type)\n\n");
        printf("Choice: ");

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1 || choice == 2)
            return choice;

        printf("Invalid choice!\n");
        pressEnterIntro();
    }
}

static void showJamberInfo()
{
    clearScreen();

    introLine("--------------------------------------------------------");
    introBlank();
    introLine("Jamber");
    introBlank();
    introLine("Type : Power");
    introBlank();
    introLine("Jamber is a fearless warrior");
    introLine("known for overwhelming enemies");
    introLine("with incredible strength.");
    introBlank();
    introLine("His powerful body allows him");
    introLine("to gain Attack and Endurance");
    introLine("more efficiently than most dogs.");
    introBlank();
    introLine("If you enjoy heavy damage");
    introLine("and aggressive battles,");
    introBlank();
    introLine("Jamber is the perfect partner.");
    introBlank();
    introLine("Do you want to train Jamber?");
    introBlank();
}

static void showKaneInfo()
{
    clearScreen();

    introLine("--------------------------------------------------------");
    introBlank();
    introLine("Kane");
    introBlank();
    introLine("Type : Speed");
    introBlank();
    introLine("Kane is a swift and brave warrior");
    introLine("with sharp instincts and quick movement.");
    introBlank();
    introLine("His natural agility allows him");
    introLine("to gain Speed and Accuracy");
    introLine("more efficiently than most dogs.");
    introBlank();
    introLine("If you enjoy fast movement,");
    introLine("precise attacks, and tactical battles,");
    introBlank();
    introLine("Kane is the perfect partner.");
    introBlank();
    introLine("Do you want to train Kane?");
    introBlank();
}

void introStory(Dog *player)
{
    char trainerName[50];
    int partnerChoice;
    char confirm;

    titleScreen();
    clearScreen();

    printf("========================================================\n");
    printf("                     WARDOGZ\n");
    printf("                 Planet Kepler-22b\n");
    printf("                     Year 2207\n");
    printf("========================================================\n\n");

    slowDots("Initializing system");
    slowDots("Connecting to WARDOGZ Academy");
    introLine("Connection established.");

    pressEnterIntro();
    clearScreen();

    introLine("Greetings, Trainer.");
    introBlank();
    introLine("Welcome to the WARDOGZ Academy.");
    introBlank();
    introLine("For over a century, this academy has trained");
    introLine("elite warrior dogs to protect cities,");
    introLine("territories, and survivors across");
    introLine("Planet Kepler-22b.");
    introBlank();
    introLine("Every legendary trainer started");
    introLine("exactly where you are today.");
    introBlank();
    introLine("Perhaps...");
    introBlank();
    introLine("The next legend will be you.");

    pressEnterIntro();
    clearScreen();

    introLine("Before we begin...");
    introBlank();
    introLine("May I know your name?");
    introBlank();
    printf("Enter your name: ");

    fgets(trainerName, sizeof(trainerName), stdin);
    trainerName[strcspn(trainerName, "\n")] = 0;

    if (trainerName[0] == '\0')
        strcpy(trainerName, "Trainer");

    clearScreen();

    introTypeText("Ah... ", 18);
    introTypeText(trainerName, 18);
    introTypeText(".\n\n", 18);

    introLine("It's a pleasure to meet you.");
    introBlank();
    introLine("From this day forward,");
    introLine("you are officially recognized");
    introLine("as a WARDOGZ Academy trainee.");
    introBlank();
    introLine("Every trainer needs a loyal partner.");
    introBlank();
    introLine("Today, you will choose");
    introLine("the warrior dog that will");
    introLine("fight beside you throughout");
    introLine("your journey.");
    introBlank();
    introLine("Choose carefully.");
    introBlank();
    introLine("This decision cannot be changed.");

    pressEnterIntro();

    while (1)
    {
        partnerChoice = choosePartner();

        if (partnerChoice == 1)
            showJamberInfo();
        else
            showKaneInfo();

        confirm = getYesNo();

        if (confirm == 'Y')
            break;
    }

    /*
       This initializes all default stats, skills, fatigue, arena data,
       unlock flags, and sparring progress.

       IMPORTANT:
       Remove the dog-name question inside createDog() in dog.c.
       The intro now sets the fixed partner name: Jamber or Kane.
    */
    createDog(player);
    strcpy(player->trainerName, trainerName);

    if (partnerChoice == 1)
    {
        strcpy(player->name, "Jamber");

        /* Power Type starter bonus */
        player->attack += 10;
        player->maxHP += 20;
        player->hp = player->maxHP;

        clearScreen();
        introLine("Excellent choice.");
        introBlank();
        introLine("Jamber proudly stands by your side.");
        introBlank();
        introLine("Together, both of you will become");
        introLine("strong enough to overcome");
        introLine("any challenge.");
    }
    else
    {
        strcpy(player->name, "Kane");

        /* Speed Type starter bonus */
        player->speed += 10;
        player->accuracy += 10;

        clearScreen();
        introLine("Excellent choice.");
        introBlank();
        introLine("Kane happily accepts you");
        introLine("as his trainer.");
        introBlank();
        introLine("Together, both of you will");
        introLine("race toward victory.");
    }

    pressEnterIntro();
    clearScreen();

    introLine("--------------------------------------------------------");
    introBlank();
    introLine("Your journey begins today.");
    introBlank();
    introLine("Train hard.");
    introBlank();
    introLine("Win battles.");
    introBlank();
    introLine("Master new skills.");
    introBlank();
    introLine("Build an unbreakable bond");
    introLine("with your partner.");
    introBlank();
    introLine("Many powerful opponents await you...");
    introBlank();
    introLine("Only those with determination");
    introLine("can reach the top.");
    introBlank();
    introTypeText("Good luck, ", 18);
    introTypeText(trainerName, 18);
    introTypeText(".\n\n", 18);
    introLine("May you and your partner");
    introLine("become the greatest team");
    introLine("the WARDOGZ Academy");
    introLine("has ever seen.");

    pressEnterIntro();
    clearScreen();

    introLine("DAY 1");
    introBlank();
    introLine("WARDOGZ Academy");
    introLine("Training Grounds");

    pressEnterIntro();
}
