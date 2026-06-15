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
        "Mutation surge: INPUTTING!",
        "BREACH IMMINENT!"
    };

    // STAGE 5 - ZONE 1: ENHANCED STRAYS
    char *enhancedStrayLines[] =
    {
        "Subject 014 escaped containment.",
        "Movement detected in Sector B.",
        "Bone density enhancement: 300%.",
        "Former stray unit entering combat mode.",
        "Pain tolerance test complete. Beginning attack.",
        "Urban instinct restored. Weapon training active.",
        "The alley was only the prototype.",
        "Containment collar signal lost.",
        "We survived the streets. We survived the lab.",
        "Enhanced subject responding with aggression."
    };

    // STAGE 5 - ZONE 2: FERAL MUTATION WARD
    char *feralMutationLines[] =
    {
        "Mutation ward breach detected.",
        "Feral strain exceeding safety limits.",
        "Predator response rising beyond control.",
        "Warning: Subject aggression cannot be stabilized.",
        "Muscle fibers tearing past normal limits.",
        "The ward doors were never meant to hold us.",
        "Heartbeat unstable. Combat output increasing.",
        "Blood sample corrupted. Mutation spreading.",
        "Containment team lost contact.",
        "The experiment is hungry."
    };

    // STAGE 5 - ZONE 3: BLACKSITE MILITARY PROTOTYPES
    char *blacksiteMilitaryLines[] =
    {
        "Prototype weapon system online.",
        "Target confirmed. No retreat authorized.",
        "Blacksite command has marked you hostile.",
        "Military enhancement protocol activated.",
        "Combat data uploaded. Weakness identified.",
        "You are facing the finished model.",
        "Tactical mutation sequence engaged.",
        "Prototype soldier entering kill-zone.",
        "Mission parameter: erase the intruder.",
        "Blacksite orders are absolute."
    };

    // STAGE 5 - ZONE 4: PERFECTED BIO WEAPONS
    char *perfectBioLines[] =
    {
        "Mutation stabilized.",
        "Combat efficiency: 100%.",
        "You are facing perfection.",
        "Biological limits removed.",
        "Adaptation complete.",
        "Target resistance irrelevant.",
        "Combat data accepted.",
        "Evolution successful.",
        "You cannot stop progress.",
        "Prototype superiority confirmed."
    };

    // STAGE 5 - ZONE 5: OMEGA PROJECT
    char *omegaLines[] =
    {
        "Project Omega online.",
        "Final protocol activated.",
        "All previous subjects were failures.",
        "You stand before the apex predator.",
        "Laboratory authority acknowledged.",
        "No further evolution required.",
        "Termination sequence initiated.",
        "Combat analysis complete.",
        "This experiment ends now.",
        "Witness the final result."
    };

    // STAGE 5 SECRET / REPLAY ENEMY
    char *grimfangXLines[] =
    {
        "Prototype deemed too aggressive.",
        "Termination failed.",
        "You defeated my old form. Try the perfected one.",
        "The streets made me strong. The lab made me worse.",
        "Containment was a mistake.",
        "Grimfang was only the beginning.",
        "Every scar became an upgrade.",
        "I remember the alley. I remember you.",
        "No leash. No cage. No mercy.",
        "This is what survival created."
    };

    int randomLine = rand() % 10;

    typeText(enemyName, 25);
    printf(": ");

    if (strcmp(enemyName, "Grimfang-X") == 0)
    {
        typeText(grimfangXLines[randomLine], 22);
    }
    else if (strcmp(enemyName, "Grimfang") == 0)
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
    else if (zoneIndex == 20)
    {
        typeText(omegaLines[randomLine], 22);
    }
    else if (zoneIndex == 19)
    {
        typeText(perfectBioLines[randomLine], 22);
    }
    else if (zoneIndex == 18)
    {
        typeText(blacksiteMilitaryLines[randomLine], 22);
    }
    else if (zoneIndex == 17)
    {
        typeText(feralMutationLines[randomLine], 22);
    }
    else if (zoneIndex == 16)
    {
        typeText(enhancedStrayLines[randomLine], 22);
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
