#include <stdio.h>
#include <stdlib.h>

#include "../cinematic.h"
#include "battle_dialogue.h"

void playEnemyBattleDialogue(int zoneIndex, char enemyName[])
{
    char *backAlleyLines[] =
    {
        "Not bad...",
        "You're tougher than I expected.",
        "That attack almost got me.",
        "Heh... this is getting fun.",
        "You fight pretty well.",
        "Let's end this.",
        "I won't hold back anymore.",
        "You're still standing?",
        "Tch... annoying.",
        "This fight is mine."
    };

    char *wildLines[] =
    {
        "GRRRR...",
        "The wild shows no mercy.",
        "You entered the wrong territory.",
        "Only the strong survive here.",
        "I'll tear you apart.",
        "You can smell the blood in the air.",
        "This land belongs to us.",
        "Your fear is showing.",
        "Run while you still can.",
        "You're prey now."
    };

    char *militaryLines[] =
    {
        "Target acquired. Recalculating...",
        "Discipline will prevail!",
        "Your resistance is futile.",
        "Tactical retreat denied.",
        "Engaging counter-protocols!",
        "Military precision activated.",
        "You cannot defeat ORDER!",
        "Reinforcements en route.",
        "Error: Target still operational.",
        "Commander protocol: ELIMINATE!"
    };

    char *bioLabLines[] =
    {
        "Subject containment failing...",
        "ERROR: Target still operational.",
        "Bio-signature detected. Engaging.",
        "Containment protocol: ACTIVATE!",
        "Sample analysis complete. ELIMINATE.",
        "Experiment success rate: 99%...",
        "Hybrid systems online.",
        "PROJECT Omega engaging.",
        "Mutation surge: IMPUTING!",
        "BREACH IMMINENT!"
    };

    int randomLine = rand() % 10;

    typeText(enemyName, 25);
    printf(": ");

    if (zoneIndex >= 12)
    {
        typeText(bioLabLines[randomLine], 22);
    }
    else if (zoneIndex >= 8)
    {
        typeText(militaryLines[randomLine], 22);
    }
    else if (zoneIndex >= 3)
    {
        typeText(wildLines[randomLine], 20);
    }
    else
    {
        typeText(backAlleyLines[randomLine], 20);
    }

}