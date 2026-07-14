#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stage.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"
#include "stage5.h"
#include "../dog.h"
#include "../cinematic.h"
#include "../console.h"

void startStage(Dog *player, int progress[])
{
    int stageChoice;

    while (1)
    {
        system("cls");

        int urbanComplete =
            (progress[0] >= 3) +
            (progress[1] >= 3) +
            (progress[2] >= 3);

        int wildComplete =
            (progress[3] >= 3) +
            (progress[4] >= 3) +
            (progress[5] >= 2) +
            (progress[6] >= 4) +
            (progress[7] >= 4);

        int militaryComplete =
            (progress[8] >= 2) +
            (progress[9] >= 4) +
            (progress[10] >= 4) +
            (progress[11] >= 3);

        int bioLabComplete =
            (progress[12] >= 2) +
            (progress[13] >= 4) +
            (progress[14] >= 4) +
            (progress[15] >= 3);

        int blacksiteComplete =
            (progress[16] >= 4) +
            (progress[17] >= 4) +
            (progress[18] >= 4) +
            (progress[19] >= 4) +
            (progress[20] >= 1);

        player->stageClearBonus = 0;

        if (urbanComplete >= 3)
            player->stageClearBonus++;

        if (wildComplete >= 5)
            player->stageClearBonus++;

        if (militaryComplete >= 4)
            player->stageClearBonus++;

        if (bioLabComplete >= 4)
            player->stageClearBonus++;

        if (blacksiteComplete >= 5)
            player->stageClearBonus++;

        printBorder();
        printBlankLine();
        printCentered("SELECT STAGE");
        printBlankLine();

        printMenuItemFormat(1, "Urban Strays (%d/3)", urbanComplete);

        if (urbanComplete >= 3)
            printMenuItemFormat(2, "Wild Territory (%d/5)", wildComplete);
        else
            printMenuItem(2, "Wild Territory (Locked)");

        if (wildComplete >= 5)
            printMenuItemFormat(3, "Military Zone (%d/4)", militaryComplete);
        else
            printMenuItem(3, "Military Zone (Locked)");

        if (militaryComplete >= 4)
            printMenuItemFormat(4, "Bio-Containment Zone (%d/4)", bioLabComplete);
        else
            printMenuItem(4, "Bio-Containment Zone (Locked)");

        if (bioLabComplete >= 4)
            printMenuItemFormat(5, "Blacksite Laboratory (%d/5)", blacksiteComplete);
        else
            printMenuItem(5, "Blacksite Laboratory (Locked)");

        printMenuItem(6, "Back");
        printBlankLine();
        printf("%35sChoice: ", "");

        char input[10];
        fgets(input, sizeof(input), stdin);

        if (input[0] == '\n')
        {
            printCentered("Please select a number.");
            waitForEnter();
            continue;
        }

        stageChoice = atoi(input);

        if (stageChoice < 1 || stageChoice > 6)
        {
            printCentered("Invalid choice! Select 1-6 only.");
            waitForEnter();
            continue;
        }

        if (stageChoice == 6)
            return;

        if (stageChoice == 1)
        {
            runStage1(player, progress);
        }
        else if (stageChoice == 2)
        {
            if (urbanComplete < 3)
            {
                printCentered("Complete Urban Strays first!");
                waitForEnter();
                continue;
            }

            runStage2(player, progress);
        }
        else if (stageChoice == 3)
        {
            if (wildComplete < 5)
            {
                printCentered("Complete Wild Territory first!");
                waitForEnter();
                continue;
            }

            runStage3(player, progress);
        }
        else if (stageChoice == 4)
        {
            if (militaryComplete < 4)
            {
                printCentered("Complete Military Zone first!");
                waitForEnter();
                continue;
            }

            runStage4(player, progress);
        }
        else if (stageChoice == 5)
        {
            if (bioLabComplete < 4)
            {
                printCentered("Complete Bio-Containment Zone first!");
                waitForEnter();
                continue;
            }

            runStage5(player, progress);
        }
    }
}
