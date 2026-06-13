#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    char *grimfangLines[] =
    {
        "The streets belong to the strongest.",
        "You're standing on my turf.",
        "No one survives here for free.",
        "Strength decides everything.",
        "Show me what you've got.",
        "You're tougher than you look.",
        "Keep fighting.",
        "This city made me.",
        "Not bad.",
        "Let's finish this."
    };

    char *diremawLines[] =
    {
        "Only the strong survive here.",
        "The wild shows no mercy.",
        "You entered the wrong territory.",
        "Your fear is showing.",
        "This land belongs to us.",
        "Run while you still can.",
        "I can smell your weakness.",
        "The hunt has begun.",
        "You're prey now.",
        "Survival is earned."
    };

    char *blackclawLines[] =
    {
        "Stay focused.",
        "Your stance is improving.",
        "Hesitation gets warriors killed.",
        "I've seen battles far worse than this.",
        "Discipline wins fights.",
        "Show me your resolve.",
        "A soldier fights with purpose.",
        "You're adapting quickly.",
        "Not bad... but keep pushing.",
        "Let's see what you're really capable of."
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

    char *blacksiteLines[] =
    {
        "We were once abandoned. Now we are perfected.",
        "The alley was only the beginning.",
        "Every subject here survived the impossible.",
        "The laboratory rewards those who endure.",
        "You recognize us. We remember you too.",
        "Former strays. Current weapons.",
        "Pain created monsters. Training created soldiers.",
        "You fought us before. Try again.",
        "Evolution never stops.",
        "Welcome to the Blacksite."
    };

    int randomLine = rand() % 10;

    typeText(enemyName, 25);
    printf(": ");

    if (strcmp(enemyName, "Grimfang") == 0)
    {
        typeText(grimfangLines[randomLine], 22);
    }
    else if (strcmp(enemyName, "Diremaw") == 0)
    {
        typeText(diremawLines[randomLine], 22);
    }
    else if (strcmp(enemyName, "Blackclaw") == 0)
    {
        typeText(blackclawLines[randomLine], 22);
    }
        else if (zoneIndex >= 16)
    {
        typeText(blacksiteLines[randomLine], 22);
    }
        else if (zoneIndex >= 12)
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