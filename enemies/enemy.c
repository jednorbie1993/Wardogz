#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../dog.h"
#include <windows.h>
#include "enemy.h"
#include "../cinematic.h"
#include "../console.h"
#include "enemy_stage5.h"

extern int systemLog;

static void typeTextCentered(const char *text, int delay)
{
    int len = strlen(text);
    int spaces = (CONSOLE_WIDTH - len) / 2;

    if (spaces < 0)
        spaces = 0;

    for (int i = 0; i < spaces; i++)
        printf(" ");

    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(delay);
    }
}


// =========================
// DEFEND COUNTER HELPERS
// =========================
static int tryDefendCounter(Dog *player, Dog *enemy)
{
    /*
        Return values:
        0 = counter failed, enemy skill continues but damage is reduced later
        1 = counter succeeded, enemy skill is blocked
        2 = counter succeeded and enemy died
    */
    int counterChance = 25 + (player->intelligence / 20);

    if (player->fatigue <= 20)
        counterChance = 0;

    if (counterChance > 45)
        counterChance = 45;

    if (rand() % 100 < counterChance)
    {
        int counterDmg = (player->attack * 2) + (player->intelligence / 2);

        counterDmg += rand() % 16;

        if (counterDmg < 210)
            counterDmg = 210;

        if (counterDmg > 300)
            counterDmg = 300;

        if (counterDmg > enemy->hp)
            counterDmg = enemy->hp;

        printCentered("DEFEND COUNTER!");
        printCenteredFormat("Counter dealt %d damage!", counterDmg);

        enemy->hp -= counterDmg;
        enemy->hp = clamp(enemy->hp);

        if (enemy->hp <= 0)
        {
            printCentered("Enemy defeated by DEFEND COUNTER!");
            return 2;
        }

        printCentered("Enemy skill was blocked!");
        return 1;
    }

    printCentered("Defend counter failed!");
    return 0;
}

static void reduceSkillDamageAfterFailedDefend(Dog *player, int hpBefore)
{
    int rawDamage = hpBefore - player->hp;

    if (rawDamage <= 0)
        return;

    int reducedDamage = (rawDamage * 60) / 100;

    if (reducedDamage < 1)
        reducedDamage = 1;

    player->hp = hpBefore - reducedDamage;
    player->hp = clamp(player->hp);

    printCenteredFormat("Defended! Took %d damage", reducedDamage);
}


// =========================
// CREATE ENEMY
// =========================
void createEnemy(Dog *e)
{
    strcpy(e->name, "Wild Dog");

    e->hp = 100;
    e->maxHP = 100;
    e->attack = 10;
    e->defense = 65;

    e->speed = 90;
    e->accuracy = 95;
    e->intelligence = 55;

    e->isConfused = 0;
    e->confuseTurns = 0;

    e->isBleeding = 0;
    e->bleedTurns = 0;
    e->bleedDamage = 0;
    e->isStunned = 0;
    e->stunTurns = 0;

    e->accuracyModifier = 0;
    e->numSkills = 0;

    e->isConfused = 0;
    e->confuseTurns = 0;
    e->mutationTriggered = 0;

    // NEW DEFAULTS
    e->zoneType = ZONE_NORMAL;
    e->personalityType = PERSONALITY_NORMAL;
}

// =========================
// QUICK ATTACK
// =========================
void enemyQuickAttack(Dog *player, Dog *enemy)
{
    int dmg = (enemy->attack / 8) + 3;

    if (dmg < 1)
        dmg = 1;

    player->hp -= dmg;
    player->hp = clamp(player->hp);

    printCenteredFormat("Enemy quickly attacks! You took %d damage!", dmg);
}

// =========================
// MAIN ENEMY ATTACK
// =========================
int enemyAttack(Dog *player, Dog *enemy, int *defending)
{
    // =========================
    // STUN CHECK
    // =========================
    if (enemy->isStunned && enemy->stunTurns > 0)
    {
        system("cls");
        displayBattleStatus(*player, *enemy);

        printBlankLine();
        printCentered("--- ENEMY TURN ---");
        printCenteredFormat("%s is STUNNED and cannot move!", enemy->name);

        enemy->stunTurns--;

        if (enemy->stunTurns <= 0)
            enemy->isStunned = 0;

        waitForEnter();
        return -1;
    }

    // =========================
    // WILD SKILLS SYSTEM
    // =========================
    if (enemy->numSkills >= 3 && enemy->zoneType != ZONE_CITY)
    {
        if (enemy->zoneType == ZONE_RAVINE && rand() % 100 < 15)
        {
            printCentered("Ambush bonus! Speed increased!");
            enemy->speed += 3;
        }

        if (enemy->zoneType == ZONE_TRIAL && enemy->hp < enemy->maxHP / 2)
        {
            printCentered("Trial Rage activated!");
            enemy->attack += 3;
        }

        int skillChoice = 0;

        // =========================
        // ZONE: RAVINE
        // =========================
        if (enemy->zoneType == ZONE_RAVINE)
        {
            int pool[] = {0, 1};
            skillChoice = pool[rand() % 2];
        }

        // =========================
        // ZONE: TRIAL
        // =========================
        else if (enemy->zoneType == ZONE_TRIAL)
        {
            if (enemy->hp < enemy->maxHP / 2)
                skillChoice = 1;
            else
            {
                int pool[] = {0, 1, 2};
                skillChoice = pool[rand() % 3];
            }
        }

        // =========================
        // ZONE: MILITARY (FIXED PROPERLY)
        // =========================
        else if (enemy->zoneType == ZONE_MILITARY)
        {
            int r = rand() % 100;

            if (enemy->hp < enemy->maxHP * 0.2)
                skillChoice = 3; // Self Destruct
            else if (r < 25)
                skillChoice = 0; // Precision Shot
            else if (r < 45)
                skillChoice = 1; // Tactical Guard
            else if (r < 60)
                skillChoice = 2; // Reinforcement
            else if (r < 80)
                skillChoice = 4; // Barrage Fire
            else
                skillChoice = 5; // Military Charge
        }

        // =========================
        // Bio-Lab zone
        // =========================
        else if (enemy->zoneType == ZONE_BIOLAB)
        {
            int r = rand() % 100;

            if (enemy->hp < enemy->maxHP * 0.25)
                skillChoice = 3;
            else if (r < 20)
                skillChoice = 0;
            else if (r < 35)
                skillChoice = 1;
            else if (r < 50)
                skillChoice = 2;
            else if (r < 70)
                skillChoice = 4;
            else
                skillChoice = 5;
        }
        else if (enemy->zoneType == ZONE_MUTANT)
        {
            int r = rand() % 100;

            /*
                STAGE 5 / BLACKSITE LABORATORY
                Most Stage 5 enemies only have 4 skills:
                index 0, 1, 2, 3

                Zone 5 final boss: Project Cerberus
                - Uses the same existing skill IDs from enemy_stage5.c
                - No new dog.h enum needed here
                - Regen/timer should be handled in battle.c
            */
            if (strcmp(enemy->name, "Project Cerberus") == 0)
            {
                if (enemy->hp < enemy->maxHP * 0.35)
                    skillChoice = 0; // Mutation Overdrive / Apex Overdrive effect
                else if (r < 30)
                    skillChoice = 1; // Humanoid Jaw Crush
                else if (r < 55)
                    skillChoice = 2; // Timeline Maul
                else if (r < 80)
                    skillChoice = 3; // Cursed Instinct
                else
                    skillChoice = 0;
            }
            else if (enemy->hp < enemy->maxHP * 0.30)
                skillChoice = 3;
            else if (r < 30)
                skillChoice = 0;
            else if (r < 55)
                skillChoice = 1;
            else if (r < 80)
                skillChoice = 2;
            else
                skillChoice = rand() % enemy->numSkills;
        }
        else
        {
            skillChoice = rand() % enemy->numSkills;
        }

        char *bioLabLines[] = {"Mutation active.", "Target acquired.", "Bio weapon online."};
        char *mutantLines[] = {"Perfect mutation.", "No weaknesses.", "Adapting..."};
        char *wildLines[] = {"Grrrr...", "The beast attacks.", "Predator mode."};

        int randomLine = rand() % 3;

        if (enemy->zoneType == ZONE_BIOLAB)
            printCentered(bioLabLines[randomLine]);
        else if (enemy->zoneType == ZONE_MUTANT)
        {
            if (strcmp(enemy->name, "Project Cerberus") == 0)
            {
                char *cerberusLines[] =
                {
                    "Regeneration cells unstable.",
                    "Humanoid mutation adapting.",
                    "Timeline curse resonating."
                };

                printCentered(cerberusLines[randomLine]);
            }
            else
            {
                printCentered(mutantLines[randomLine]);
            }
        }
        else
            printCentered(wildLines[randomLine]);

        /*if (enemy->zoneType == ZONE_BIOLAB)
            printf("%s mutates violently...\n", enemy->name);
        else if (enemy->zoneType == ZONE_MUTANT)
            printf("%s activates perfect mutation...\n", enemy->name);
        else
            printf("%s snarls viciously...\n", enemy->name);*/

        // SAFETY CHECK (IMPORTANT)
        if (skillChoice < 0 || skillChoice >= MAX_SKILLS)
        {
            printCenteredFormat("%s hesitates...", enemy->name);
            skillChoice = 0;
        }

        // =========================
        // OSSAS COUNTER CHECK VS SKILL
        // =========================
        if (player->isCountering && player->counterDamage > 0)
        {
            int triggerChance = 65 + (player->intelligence / 20);

            if (triggerChance > 85)
                triggerChance = 85;

            if (rand() % 100 < triggerChance)
            {
                int reflect = (player->attack * 2) + player->intelligence;
                reflect += rand() % 16;

                if (reflect < 180)
                    reflect = 180;

                if (reflect > 300)
                    reflect = 300;

                if (reflect < 1)
                    reflect = 1;

                if (reflect > enemy->hp)
                    reflect = enemy->hp;

                printCentered("OSSAS COUNTER TRIGGERS!");
                printCenteredFormat("Reflected %d damage!", reflect);

                enemy->hp -= reflect;
                enemy->hp = clamp(enemy->hp);

                if (enemy->hp <= 0)
                {
                    player->isCountering = 0;
                    player->counterDamage = 0;

                    printCentered("Enemy defeated by OSSAS COUNTER!");
                    waitForEnter();
                    return 1;
                }
            }
            else
            {
                printCentered("Ossas Counter failed!");
            }

            player->isCountering = 0;
            player->counterDamage = 0;
        }

        int hpBeforeSkill = player->hp;
        int defendWasActive = 0;
        int defendCounterResult = 0;

        if (*defending)
        {
            defendWasActive = 1;
            defendCounterResult = tryDefendCounter(player, enemy);
            *defending = 0;

            if (defendCounterResult == 2)
            {
                waitForEnter();
                return 1;
            }

            if (defendCounterResult == 1)
            {
                waitForEnter();
                return -1;
            }
        }

        SkillID skillId = enemy->skills[skillChoice].id;

        switch (skillId)
        {
        case SKILL_PACK_ATTACK:
            usePackAttack(enemy, player);
            break;

        case SKILL_AMBUSH:
            useAmbush(enemy, player);
            break;

        case SKILL_HOWL_DEBUFF:
            useHowlDebuff(enemy, player);
            break;

        case SKILL_FERAL_RUSH:
            useFeralRush(enemy, player);
            break;
        // diremaw
        case SKILL_MAULING_BITE:
            useMaulingBite(enemy, player);
            break;

        case SKILL_RABID_CLAW:
            useRabidClaw(enemy, player);
            break;

        case SKILL_BLOOD_SCENT:
            useBloodScent(enemy, player);
            break;

        case SKILL_WILD_POUNCE:
            useWildPounce(enemy, player);
            break;

        case SKILL_BONE_BREAKER:
            useBoneBreaker(enemy, player);
            break;

        case SKILL_PREDATOR_FRENZY:
            usePredatorFrenzy(enemy, player);
            break;

        // =========================
        // MILITARY SKILLS
        // =========================
        case SKILL_PRECISION_SHOT:
            usePrecisionShot(enemy, player);
            break;

        case SKILL_TACTICAL_GUARD:
            useTacticalGuard(enemy, player);
            break;

        case SKILL_REINFORCEMENT:
            useReinforcement(enemy, player);
            break;

        case SKILL_SELF_DESTRUCT:
            useSelfDestruct(enemy, player);
            break;

        case SKILL_BARRAGE_FIRE:
            useBarrageFire(enemy, player);
            break;

        case SKILL_MILITARY_CHARGE:
            useMilitaryCharge(enemy, player);
            break;
        case SKILL_AMBUSH_STRIKE:
            useAmbushStrike(enemy, player);
            break;
        // =========================
        // Bio-Lab skills
        // =========================
        case SKILL_MUTATION_SURGE:
            useMutationSurge(enemy, player);
            break;

        case SKILL_BIO_SHIELD:
            useBioShield(enemy, player);
            break;

        case SKILL_CELL_REGEN:
            useCellRegen(enemy, player);
            break;

        case SKILL_CONTAINED_EXPLOSION:
            useContainedExplosion(enemy, player);
            break;

        case SKILL_ACID_SPIT:
            useAcidSpit(enemy, player);
            break;

        case SKILL_NEURO_TOXIN:
            useNeuroToxin(enemy, player);
            break;
        //secret lab skills 
        case SKILL_REINFORCED_BITE:
            useReinforcedBite(enemy, player);
            break;

        case SKILL_COMBAT_RUSH:
            useCombatRush(enemy, player);
            break;

        case SKILL_PREDATOR_INSTINCT:
            usePredatorInstinct(enemy, player);
            break;

        case SKILL_ENHANCED_JAW_CRUSH:
            useEnhancedJawCrush(enemy, player);
            break;

        case SKILL_RAZOR_SLASH:
            useRazorSlash(enemy, player);
            break;

        case SKILL_BLOOD_FRENZY:
            useBloodFrenzy(enemy, player);
            break;

        case SKILL_FANG_STORM:
            useFangStorm(enemy, player);
            break;    

        case SKILL_TACTICAL_BITE:
            useTacticalBite(enemy, player);
            break;

        case SKILL_ARMOR_BREAK:
            useArmorBreak(enemy, player);
            break;

        case SKILL_SUPPRESSION_HOWL:
            useSuppressionHowl(enemy, player);
            break;

        case SKILL_BLACKSITE_EXECUTION:
            useBlacksiteExecution(enemy, player);
            break;

        case SKILL_PLASMA_BITE:
            usePlasmaBite(enemy, player);
            break;

        case SKILL_CRYO_LOCK:
            useCryoLock(enemy, player);
            break;

        case SKILL_THUNDER_SURGE:
            useThunderSurge(enemy, player);
            break;

        case SKILL_APEX_OVERDRIVE:
            useApexOverdrive(enemy, player);
            break;

        case SKILL_MUTATION_OVERDRIVE:
            useMutationOverdrive(enemy, player);
            break;

        case SKILL_HUMANOID_JAW_CRUSH:
            useHumanoidJawCrush(enemy, player);
            break;

        case SKILL_TIMELINE_MAUL:
            useTimelineMaul(enemy, player);
            break;

        case SKILL_CURSED_INSTINCT:
            useCursedInstinct(enemy, player);
            break;
            
        default:
            {
                char *mutantActions[] =
                {
                    "launches a savage assault!",
                    "tears through the battlefield!",
                    "unleashes a violent mutation strike!"
                };

                char *militaryActions[] =
                {
                    "executes a combat maneuver!",
                    "launches a tactical offensive!",
                    "performs a precision assault!"
                };

                char *bioActions[] =
                {
                    "releases unstable bio-energy!",
                    "lashes out with a mutated strike!",
                    "fires an experimental attack!"
                };

                int dmg = (enemy->attack / 4) + 8 + (rand() % 8);

                dmg -= player->defense / 45;

                if (dmg < 5)
                    dmg = 5;

                player->hp -= dmg;
                player->hp = clamp(player->hp);

                int r = rand() % 3;

                if (enemy->zoneType == ZONE_MUTANT)
                    printCenteredFormat("%s %s", enemy->name, mutantActions[r]);
                else if (enemy->zoneType == ZONE_BIOLAB)
                    printCenteredFormat("%s %s", enemy->name, bioActions[r]);
                else if (enemy->zoneType == ZONE_MILITARY)
                    printCenteredFormat("%s %s", enemy->name, militaryActions[r]);
                else
                    printCenteredFormat("%s attacks fiercely!", enemy->name);

                printCenteredFormat("You took %d damage!", dmg);

                break;
            }
        }
        if (defendWasActive && defendCounterResult == 0 && hpBeforeSkill > player->hp)
            reduceSkillDamageAfterFailedDefend(player, hpBeforeSkill);

        if (enemy->zoneType == ZONE_MUTANT &&
            enemy->hp < enemy->maxHP * 0.70 &&
            !enemy->mutationTriggered)
        {
            char *mutationLines[] =
            {
                "Experimental genes activated!",
                "Prototype limiters released!",
                "Predatory instincts unleashed!",
                "Mutation level rising!",
                "Combat adaptation detected!"
            };

            char *cerberusMutationLines[] =
            {
                "Regeneration cells awakened!",
                "Humanoid frame adapting!",
                "Black serum reacting!",
                "Timeline curse detected!",
                "Final containment failing!"
            };

            int randomLine = rand() % 5;

            printBlankLine();

            {
                char mutationText[120];
                sprintf(mutationText, "%s is mutating!", enemy->name);
                typeTextCentered(mutationText, 30);
                printBlankLine();
            }

            if (strcmp(enemy->name, "Project Cerberus") == 0)
                typeTextCentered(cerberusMutationLines[randomLine], 30);
            else
                typeTextCentered(mutationLines[randomLine], 30);

            printBlankLine();

            typeTextCentered("Attack increased!", 30);
            printBlankLine();

            if (strcmp(enemy->name, "Project Cerberus") == 0)
                enemy->attack += 5;
            else
                enemy->attack += 3;

            enemy->mutationTriggered = 1;

            waitForEnter();
            system("cls");
            displayBattleStatus(*player, *enemy);
        }

        if (player->accuracyModifier < 0)
        {
            player->accuracy += 20;
            player->accuracyModifier = 0;
            printCentered("Accuracy recovering...");
        }

        if (player->bleedTurns > 0)
        {
            player->hp -= player->bleedDamage;
            player->hp = clamp(player->hp);

            printCenteredFormat("Bleed: -%d HP", player->bleedDamage);

            player->bleedTurns--;

            if (player->bleedTurns <= 0)
            {
                player->bleedDamage = 0;
                printCentered("Bleeding stopped.");
            }
        }

        waitForEnter();
        return -1;
    }

    // =========================
    // CINEMATIC ENEMY TURN
    // =========================
    system("cls");

    displayBattleStatus(*player, *enemy);

    printBlankLine();
    printCentered("--- ENEMY TURN ---");

    int enemyDamage = (enemy->attack / 6) + 4;

    handleStage1EnemyBehavior(player, enemy, &enemyDamage);

    enemyDamage += rand() % 5;
    enemyDamage -= player->defense / 40;

    if (enemyDamage < 3)
        enemyDamage = 3;

    int dodgeChance = player->speed * 2;
    int hitChance = enemy->accuracy - dodgeChance;

    hitChance = (hitChance < 70) ? 70 : (hitChance > 95 ? 95 : hitChance);

    // =========================
    // BLEED CHECK
    // =========================
    if (enemy->isBleeding && enemy->bleedTurns > 0)
    {
        int bleedDmg = (rand() % 5) + 3;

        printCenteredFormat("Enemy BLEEDING: -%d HP", bleedDmg);

        enemy->hp -= bleedDmg;
        enemy->hp = clamp(enemy->hp);

        enemy->bleedTurns--;

        if (enemy->bleedTurns <= 0)
        {
            enemy->isBleeding = 0;
            printCentered("Bleeding stopped.");
        }

        waitForEnter();

        if (enemy->hp <= 0)
        {
            printCentered("Enemy DIED from bleeding!");
            return 1;
        }
    }

    // =========================
    // CONFUSION CHECK
    // =========================
    
    if (enemy->isConfused && enemy->confuseTurns > 0)
    {
        printCenteredFormat("%s is CONFUSED!", enemy->name);

        if (rand() % 100 < 50)
        {
            printCentered("Confused enemy MISSED!");

            enemy->confuseTurns--;

            if (enemy->confuseTurns <= 0)
                enemy->isConfused = 0;

            waitForEnter();
            return -1;
        }

        enemy->confuseTurns--;

        if (enemy->confuseTurns <= 0)
            enemy->isConfused = 0;
    }

    // =========================
    // HIT CHECK
    // =========================
    int roll = rand() % 100;

    if (roll >= hitChance)
    {
        printCentered("Enemy MISSED!");
        waitForEnter();
        return -1;
    }

    // =========================
    // DEFEND SYSTEM - STAGE 1
    // =========================
    if (*defending)
    {
        int counterChance = 25 + (player->intelligence / 20);

        if (player->fatigue <= 20)
            counterChance = 0;

        if (counterChance > 45)
            counterChance = 45;

        // Defend always reduces incoming Stage 1 damage.
        enemyDamage = (enemyDamage * 60) / 100;

        if (enemyDamage < 1)
            enemyDamage = 1;

        printCenteredFormat("Defended! Took %d damage", enemyDamage);

        // Counter is a bonus while defending, not a replacement for damage reduction.
        if (rand() % 100 < counterChance)
        {
            int counterDmg = (player->attack * 2) + (player->intelligence / 2);

            counterDmg += rand() % 16;

            if (counterDmg < 210)
                counterDmg = 210;

            if (counterDmg > 300)
                counterDmg = 300;

            printCentered("DEFEND COUNTER!");
            printCenteredFormat("Counter dealt %d damage!", counterDmg);

            enemy->hp -= counterDmg;
            enemy->hp = clamp(enemy->hp);

            if (enemy->hp <= 0)
            {
                printCentered("Enemy defeated by DEFEND COUNTER!");
                waitForEnter();
                return 1;
            }
        }

        player->hp -= enemyDamage;
        player->hp = clamp(player->hp);

        *defending = 0;
    }
    else
    {
        if (player->isCountering && player->counterDamage > 0)
        {
            int triggerChance = 65 + (player->intelligence / 20);

            if (triggerChance > 85)
                triggerChance = 85;

            if (rand() % 100 < triggerChance)
            {
                printCentered("OSSAS COUNTER TRIGGERS!");

                int reflect = player->counterDamage;

                if (reflect > enemy->hp)
                    reflect = enemy->hp;

                enemy->hp -= reflect;
                enemy->hp = clamp(enemy->hp);

                printCenteredFormat("Reflected %d damage!", reflect);

                enemyDamage /= 2;
            }
            else
            {
                printCentered("Ossas Counter failed!");
            }

            player->isCountering = 0;
            player->counterDamage = 0;
        }

        player->hp -= enemyDamage;
        player->hp = clamp(player->hp);

        printCenteredFormat("%s dealt %d damage!", enemy->name, enemyDamage);
    }

    // =========================
    // END CHECK
    // =========================
    if (player->hp <= 0)
    {
        printCentered("You were defeated...");
        waitForEnter();
        return 0;
    }

    waitForEnter();
    return -1;
}