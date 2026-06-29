#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "dog.h"
#include "enemies/enemy.h"
#include "skill.h"
#include "sparring/sparring.h"
#include "dog_utils.h"
#include "cinematic.h"
#include "battle.h"
#include "enemies/enemy_stage3.h"
#include "stages/stage4.h"
#include "dialogue/battle_dialogue.h"
#include "replay_system.h"
#include "enemies/enemy_stage5.h"
#include "console.h"

// extern globals from dog.c
extern int animationOn;
void setCriticalUserIntelligence(Dog *user);

int cinematicMode = 1;


static void printBattleInputPrompt(const char *text)
{
    printf("%35s%s", "", text);
}

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

static void printCenteredHPLine(const char *label, int hp, int maxHp)
{
    char line[120];
    int bars = (hp * 10) / maxHp;
    char bar[11];

    for (int i = 0; i < 10; i++)
        bar[i] = (i < bars) ? '#' : '-';

    bar[10] = '\0';

    sprintf(line, "%-6s: [%s] (%d/%d)", label, bar, hp, maxHp);
    printCenteredNoNewline(line);
}

static void printCenteredHPLineAnimated(const char *label, int hp, int maxHp)
{
    char line[120];
    int bars = (hp * 10) / maxHp;
    char bar[11];

    for (int i = 0; i < 10; i++)
        bar[i] = (i < bars) ? '#' : '-';

    bar[10] = '\0';

    sprintf(line, "%-6s: [%s] (%d/%d)   ", label, bar, hp, maxHp);

    int len = strlen(line);
    int spaces = (CONSOLE_WIDTH - len) / 2;

    if (spaces < 0)
        spaces = 0;

    printf("\r%*s%s", spaces, "", line);
}

void cinematicPause(int ms)
{
    if (cinematicMode)
        Sleep(ms);
}

void cinematicDots(const char *text)
{
    printBlankLine();
    printCenteredNoNewline(text);

    if (!cinematicMode)
    {
        printf("...\n");
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(180);
    }

    printf("\n");
}

void battleDivider()
{
    printBorder();
}

void showEnemyEntrance(Dog *enemy, int zoneIndex)
{
    printf("\n");
    if (strcmp(enemy->name, "Grimfang") == 0)
    {
        typeTextCentered("\"The streets belong to the strongest.\"", 25);

        printf("\n\n");

        typeTextCentered("Grimfang emerged!", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (strcmp(enemy->name, "Diremaw") == 0)
    {
        typeTextCentered("\"The wild doesn't care who you are. It only decides who remains.\"", 25);

        printf("\n\n");

        typeTextCentered("Diremaw emerged!", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (strcmp(enemy->name, "Blackclaw") == 0)
    {
        typeTextCentered("\"We were weapons... until we learned who the real enemy was.\"", 25);

        printf("\n\n");

        typeTextCentered("Blackclaw emerged!", 25);

        printf("\n");
        waitForEnter();

        return;
    }
    if (strcmp(enemy->name, "Omega Prime") == 0)
    {
        typeTextCentered("\"The experiment is complete... and you are the final test.\"", 25);

        printf("\n\n");

        typeTextCentered("Omega Prime emerged!", 25);

        printf("\n");
        waitForEnter();

        return;
    }
    if (strcmp(enemy->name, "Grimfang-X") == 0)
    {
        typeTextCentered("\"They rebuilt my bones... but not my loyalty.\"", 25);

        printf("\n\n");

        typeTextCentered("[BLACKSITE SECRET SUBJECT DETECTED]", 25);
        printf("\n");

        typeTextCentered("Grimfang-X emerged!", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (strcmp(enemy->name, "Commander Cerberus") == 0)
    {
        typeTextCentered("\"Prototype command unit online. Target acquired.\"", 25);

        printf("\n\n");

        typeTextCentered("Commander Cerberus deployed!", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (strcmp(enemy->name, "Project Cerberus") == 0)
    {
        typeTextCentered("\"The final subject is awake.\"", 25);

        printf("\n\n");

        typeTextCentered("[FINAL CONTAINMENT BREACH]", 25);
        printf("\n");
        typeTextCentered("Project Cerberus steps out of the chamber.", 25);
        printf("\n");
        typeTextCentered("Its body looks more humanoid than dog.", 25);
        printf("\n");
        typeTextCentered("Mutation veins pulse across its frame.", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (zoneIndex >= 16 && zoneIndex <= 20)
    {
        typeText(enemy->name, 25);
        typeTextCentered(" deployed!", 20);
    }
    else if (zoneIndex >= 8 && zoneIndex <= 11)
    {
        typeText(enemy->name, 25);
        typeTextCentered(" arrived!", 20);
    }
    else if (zoneIndex >= 3 && zoneIndex <= 7)
    {
        typeText(enemy->name, 25);
        typeTextCentered(" emerged!", 20);
    }
    else
    {
        typeText(enemy->name, 25);
        typeTextCentered(" appeared!", 20);
    }

    printf("\n");
    waitForEnter();
}


void showHPBarPlayer(int hp, int maxHp)
{
    static int lastHP = -1;

    if (hp == -1)
    {
        lastHP = -1;
        return;
    }

    if (hp < 0)
        hp = 0;
    if (hp > maxHp)
        hp = maxHp;

    if (lastHP == -1 || !animationOn)
    {
        printCenteredHPLine("PLAYER", hp, maxHp);
        lastHP = hp;
        return;
    }

    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        printCenteredHPLineAnimated("PLAYER", current, maxHp);
        fflush(stdout);
        Sleep(1);
    }

    printCenteredHPLineAnimated("PLAYER", hp, maxHp);
    lastHP = hp;
}

// ================= HP BAR ENEMY =================
void showHPBarEnemy(int hp, int maxHp)
{
    static int lastHP = -1;

    if (hp == -1)
    {
        lastHP = -1;
        return;
    }

    if (hp < 0)
        hp = 0;
    if (hp > maxHp)
        hp = maxHp;

    if (lastHP == -1 || !animationOn)
    {
        printCenteredHPLine("ENEMY", hp, maxHp);
        lastHP = hp;
        return;
    }

    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        printCenteredHPLineAnimated("ENEMY", current, maxHp);
        fflush(stdout);
        Sleep(1);
    }

    printCenteredHPLineAnimated("ENEMY", hp, maxHp);
    lastHP = hp;
}

// ================= DISPLAY =================
void displayBattleStatus(Dog player, Dog enemy)
{
    printBorder();

    showHPBarPlayer(player.hp, player.maxHP);

    if (player.isStunned && player.stunTurns > 0)
        printf(" (STUN %d)", player.stunTurns);

    printf("\n");

    showHPBarEnemy(enemy.hp, enemy.maxHP);

    if (enemy.isStunned && enemy.stunTurns > 0)
        printf(" (STUN %d)", enemy.stunTurns);

    printf("\n");
    printBorder();
}

void criticalHPScene(Dog *player)
{
    if (player->hp > 20)
        return;

    int msg = rand() % 3;

    if (msg == 0)
        printCenteredFormat("%s is barely standing...", player->name);
    else if (msg == 1)
        printCentered("Blood drips onto the ground...");
    else
        printCenteredFormat("%s struggles to keep fighting...", player->name);

}
// ================= LOSE =================

void loseSequence(Dog *player, Dog *enemy)
{
    printBlankLine();
    printCentered("YOU LOST...");
    Sleep(500);

    printCenteredNoNewline("Recovering");
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(150);
    }

    player->hp = player->maxHP;
    enemy->hp = enemy->maxHP;

    printBlankLine();
    printCentered("You are back to full HP!");
}

int handlePlayerDefeat(Dog *player, Dog *enemy, int baseDef, int baseSpd)
{
    player->hp = 0;

    system("cls");
    displayBattleStatus(*player, *enemy);

    int loseMsg = rand() % 3;

    if (loseMsg == 0)
    {
        printBlankLine();
        printCentered("You collapse from exhaustion...");
    }
    else if (loseMsg == 1)
    {
        printBlankLine();
        printCentered("Your vision starts to fade...");
    }
    else
    {
        printBlankLine();
        printCentered("You can no longer continue fighting...");
    }

    Sleep(900);

    printBlankLine();
    printCentered("YOU LOSE");

    player->fatigue = clampFatigue(player->fatigue + 20, player->maxFatigue);

    player->defense = baseDef;
    player->speed = baseSpd;

    waitForEnter();

    return 0;
}



int handleEnemyDefeat(Dog *player, Dog *enemy, int zoneIndex, int progress[], int baseDef, int baseSpd)
{
    enemy->hp = 0;

    system("cls");
    displayBattleStatus(*player, *enemy);

    int defeatMsg = rand() % 3;

    if (defeatMsg == 0)
    {
        printBlankLine();
        printCentered("Finishing blow!");
    }
    else if (defeatMsg == 1)
    {
        printBlankLine();
        printCenteredFormat("%s can no longer fight...", enemy->name);
    }
    else
    {
        printBlankLine();
        printCenteredFormat("%s collapsed...", enemy->name);
    }

    Sleep(700);

    if (strcmp(enemy->name, "Blackclaw") == 0)
    {
        typeTextCentered("Blackclaw lowers his head.", 25);
        printf("\n");

        waitForEnter();
        printf("\n");

        typeTextCentered("\"The battlefield... belongs to no one.\"", 25);
        printf("\n");
        waitForEnter();
    }

    printBlankLine();
    printCentered("--- VICTORY! ---");


    if (strcmp(enemy->name, "Grimfang") == 0)
    {
        player->defeatedGrimfang = 1;
    }

    if (strcmp(enemy->name, "Diremaw") == 0)
    {
        player->defeatedDiremaw = 1;
    }
    if (strcmp(enemy->name, "Blackclaw") == 0)
    {
        player->defeatedBlackclaw = 1;
    }
    if (strcmp(enemy->name, "Omega Prime") == 0)
    {
        player->defeatedOmega = 1;
    }
    if (strcmp(enemy->name, "Grimfang-X") == 0)
    {
        player->defeatedGrimfangX = 1;
    }

    applyBattleStatGain(player);
    checkSkillUnlock(player);

    int maxEnemies[21] =
    {
        3,3,3,
        3,3,2,4,4,
        2,4,4,3,
        2,4,4,3,
        4,4,4,4,
        1
    };

    if (zoneIndex >= 0 && zoneIndex < 21 && progress[zoneIndex] < maxEnemies[zoneIndex])
    {
        progress[zoneIndex]++;
    }

    player->fatigue = clampFatigue(player->fatigue + 20, player->maxFatigue);

    player->defense = baseDef;
    player->speed = baseSpd;

    waitForEnter();

    return 1;
}

int getBattleMaxEnemies(int zoneIndex)
{
    int maxEnemies[21] =
    {
        3,3,3,
        3,3,2,4,4,
        2,4,4,3,
        2,4,4,3,
        4,4,4,4,
        1
    };

    if (zoneIndex < 0 || zoneIndex >= 21)
        return 3;

    return maxEnemies[zoneIndex];
}



int battle(Dog *player, int zoneIndex, int progress[])
{
    return battleWithEnemyIndex(player, zoneIndex, progress, -1);
}

int battleWithEnemyIndex(Dog *player, int zoneIndex, int progress[], int enemyIndex)
{

    if (player->hp <= 0)
    {
        printCentered("You must rest before you battle again!");
        return -1;
    }

    int choice, move, defending = 0;
    int baseDef = player->defense;
    int baseSpd = player->speed;

    Dog enemy;
    createEnemy(&enemy);

    enemy.bleedDamage = 0;
    enemy.accuracyModifier = 0;
    player->bleedDamage = 0;
    player->accuracyModifier = 0;

    int i = (enemyIndex >= 0) ? enemyIndex : chooseReplayEnemyIndex(zoneIndex, progress, 0);

    // =========================
    // STAGE LOADER SYSTEM
    // =========================
    if (zoneIndex >= 16 && zoneIndex <= 20)
    {
        loadStage5Enemies(&enemy, zoneIndex, i);
    }
    else if (zoneIndex >= 12 && zoneIndex <= 15)  // Stage 4: Bio-Containment
    {
        loadStage4Enemies(&enemy, zoneIndex, i);
    }
    else if (zoneIndex >= 8 && zoneIndex <= 11)  // Stage 3: Military
    {
        loadStage3Enemies(&enemy, zoneIndex, i);
    }
    else if (zoneIndex >= 3 && zoneIndex <= 7)  // Stage 2: Wild
    {
        loadStage2Enemies(&enemy, zoneIndex, i);
    }
    else  // Stage 1: Urban
    {
        loadStage1Enemies(&enemy, zoneIndex, i);
    }

    applyReplayEliteBonus(&enemy, zoneIndex, i);

    showEnemyEntrance(&enemy, zoneIndex);

    system("cls");
    zoneStoryIntro(zoneIndex, progress[zoneIndex]);
    preBattleScene(zoneIndex);

    // 🔥 RESET HP BAR STATES (DITO MO ILALAGAY)
    showHPBarPlayer(-1, 1);
    showHPBarEnemy(-1, 1);

    int battleTurn = 0;
    int cerberusTimerActive = (strcmp(enemy.name, "Project Cerberus") == 0);
    DWORD cerberusStartTime = GetTickCount();

    // 🔥 MAIN BATTLE LOOP
    while (player->hp > 0 && enemy.hp > 0)
    {
        system("cls");
        displayBattleStatus(*player, enemy);

        if (cerberusTimerActive)
        {
            DWORD elapsed = GetTickCount() - cerberusStartTime;
            int remaining = 300 - (int)(elapsed / 1000); // 5 minutes

            if (remaining < 0)
                remaining = 0;

            printCenteredFormat("[SELF DESTRUCT TIMER] %02d:%02d", remaining / 60, remaining % 60);
        }

        if (player->hp <= 20)
        {
            printBlankLine();
            printCentered("[DANGER] Critical HP!");
        }

        printBlankLine();
        printCentered("--- YOUR TURN ---");
        if (player->fatigue <= 20)
            printCentered("Exhausted!");

        printCentered("1. Attack  2. Defend  3. Heal  4. Surrender");
        printBattleInputPrompt("Choice: ");

        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &choice) != 1 || choice < 1 || choice > 4)
        {
            printCentered("Invalid!");
            waitForEnter();
            continue;
        }

        // PLAYER ACTIONS
        if (choice == 1) // Attack
        {

            system("cls");
            displayBattleStatus(*player, enemy);

            printCentered("SKILLS");
            printBlankLine();

            int half = (player->maxSkillSlots + 1) / 2;

            for (int i = 0; i < half; i++)
            {
                int left = i;
                int right = i + half;
                char leftName[30];
                char rightName[30];
                char line[120];

                if (player->equipped[left] != -1)
                {
                    int idx = player->equipped[left];
                    strcpy(leftName, player->skills[idx].name);
                }
                else
                {
                    strcpy(leftName, "---");
                }

                if (right < player->maxSkillSlots)
                {
                    if (player->equipped[right] != -1)
                    {
                        int idx = player->equipped[right];
                        strcpy(rightName, player->skills[idx].name);
                    }
                    else
                    {
                        strcpy(rightName, "---");
                    }

                    sprintf(line, "%2d. %-20s   %2d. %-20s",
                            left + 1,
                            leftName,
                            right + 1,
                            rightName);
                }
                else
                {
                    sprintf(line, "%2d. %-20s", left + 1, leftName);
                }

                printCentered(line);
            }

            printBlankLine();
            printBattleInputPrompt("Choice: ");

            fgets(buffer, sizeof(buffer), stdin);
            if (sscanf(buffer, "%d", &move) != 1 || move < 1 || move > player->maxSkillSlots)
            {
                printCentered("Invalid skill!");
                waitForEnter();
                continue;
            }
            system("cls");
            displayBattleStatus(*player, enemy);

            int skillIdx = player->equipped[move - 1];
            if (skillIdx == -1)
            {
                printCentered("No skill!");
                waitForEnter();
                continue;
            }

            // =========================
            // SKILL COOLDOWN CHECK
            // Name-based fallback para gumana kahit old save / cooldown = 0
            // =========================
            if (strcmp(player->skills[skillIdx].name, "Hip Check") == 0 &&
                player->skills[skillIdx].cdLeft > 0)
            {
                printCentered("Hip Check is on cooldown! Use another move this turn.");
                waitForEnter();
                continue;
            }

            if (strcmp(player->skills[skillIdx].name, "Rolling Tackle") == 0 &&
                player->skills[skillIdx].cdLeft > 0)
            {
                printCentered("Rolling Tackle is on cooldown! Use another move this turn.");
                waitForEnter();
                continue;
            }

            Skill s = player->skills[skillIdx];

            if (player->fatigue < s.cost)
            {
                printBlankLine();
                printCentered("Low energy! Weak attack!");
                cinematicPause(500);

                system("cls");
                displayBattleStatus(*player, enemy);

                cinematicDots("Player attacking");

                setCriticalUserIntelligence(player);
                useSkill(player, &enemy, s);

                // =========================
                // SET COOLDOWN AFTER USING SPECIAL SKILLS
                // cdLeft = 2 means: next player turn blocked once,
                // then after using another move it becomes usable again.
                // =========================
                if (strcmp(player->skills[skillIdx].name, "Hip Check") == 0)
                    player->skills[skillIdx].cdLeft = 2;
                else if (strcmp(player->skills[skillIdx].name, "Rolling Tackle") == 0)
                    player->skills[skillIdx].cdLeft = 3;

                waitForEnter();

                if (enemy.hp < 0)
                    enemy.hp = 0;

                criticalHPScene(player);
                criticalHPScene(&enemy);

                waitForEnter();

                player->fatigue = 0;
            }
            else
            {
                system("cls");
                displayBattleStatus(*player, enemy);

                cinematicDots("Player attacking");

                setCriticalUserIntelligence(player);
                useSkill(player, &enemy, s);

                // =========================
                // SET COOLDOWN AFTER USING SPECIAL SKILLS
                // cdLeft = 2 means: next player turn blocked once,
                // then after using another move it becomes usable again.
                // =========================
                if (strcmp(player->skills[skillIdx].name, "Hip Check") == 0)
                    player->skills[skillIdx].cdLeft = 2;
                else if (strcmp(player->skills[skillIdx].name, "Rolling Tackle") == 0)
                    player->skills[skillIdx].cdLeft = 3;

                waitForEnter();

                if (enemy.hp < 0)
                    enemy.hp = 0;

                system("cls");
                displayBattleStatus(*player, enemy);

                printBlankLine();

                playEnemyBattleDialogue(zoneIndex, enemy.name);
                printBlankLine();

                criticalHPScene(player);
                criticalHPScene(&enemy);

                waitForEnter();

                player->fatigue -= s.cost;
                player->fatigue =
                    clampFatigue(player->fatigue,
                                 player->maxFatigue);
            }

        } // ✅ IMPORTANT: ito yung kulang mo

        else if (choice == 2) // Defend
        {
            defending = 1;
            printCentered("Defending!");
            waitForEnter();
        }
        else if (choice == 3) // Heal
        {
            int tier = player->maxHP / 100;

            if (tier < 1)
                tier = 1;

            int minHeal = 15 * tier;
            int maxHeal = minHeal + 15;

            int healAmount = minHeal + rand() % (maxHeal - minHeal + 1);

            player->hp += healAmount;

            if (player->hp > player->maxHP)
                player->hp = player->maxHP;

            printCenteredFormat("Healed +%d HP!", healAmount);
            waitForEnter();
        }
        else if (choice == 4) // Surrender
        {
            printBlankLine();
            printCentered("Surrendered...");
            waitForEnter();

            player->defense = baseDef;
            player->speed = baseSpd;
            return 2;
        }

        // 🔥 ENEMY TURN
        if (player->hp > 0 && enemy.hp > 0)
        {
            Sleep(500);

            // Arena backup stun check.
            // Kahit may stun check na sa enemyAttack(), dito muna natin hinaharang
            // para siguradong hindi na makakapasok sa enemy skill/attack logic.
            if (enemy.isStunned && enemy.stunTurns > 0)
            {
                system("cls");
                displayBattleStatus(*player, enemy);

                printBlankLine();
                printCentered("--- ENEMY TURN ---");
                printCenteredFormat("%s is STUNNED and cannot move!", enemy.name);

                enemy.stunTurns--;

                if (enemy.stunTurns <= 0)
                    enemy.isStunned = 0;

                waitForEnter();
            }
            else
            {
                setCriticalUserIntelligence(&enemy);
                int result = enemyAttack(player, &enemy, &defending);

                if (result == 0)
                    player->hp = 0;
                if (result == 1)
                    enemy.hp = 0;
            }

            defending = 0;
        }
        // 👉 RESET DEFENSE AFTER TURN
        // 🔥 FATIGUE REGEN
        player->fatigue += 2;
        if (player->fatigue > player->maxFatigue)
            player->fatigue = player->maxFatigue;

        battleTurn++;
        for (int i = 0; i < player->skillCount; i++)
        {
            if (player->skills[i].cdLeft > 0)
                player->skills[i].cdLeft--;
        }

        if (strcmp(enemy.name, "Project Cerberus") == 0)
        {
            if (!enemy.regenerationUsed &&
                battleTurn >= enemy.regenerationTurn)
            {
                system("cls");
                displayBattleStatus(*player, enemy);

                typeTextCentered("\n[MUTATION OVERDRIVE]\n", 25);
                typeTextCentered("Project Cerberus fully regenerates!\n", 25);

                enemy.hp = enemy.maxHP;
                enemy.regenerationUsed = 1;

                waitForEnter();
            }
        }    

        if (cerberusTimerActive)
        {
            DWORD elapsed = GetTickCount() - cerberusStartTime;

            if (elapsed >= 300000)
            {
                system("cls");
                typeTextCentered("[BLACKSITE SELF-DESTRUCT]\n\n", 25);
                typeTextCentered("The final chamber overloads.\n", 25);
                typeTextCentered("You failed to stop Project Cerberus in time.\n", 25);
                waitForEnter();

                player->hp = 0;
            }
        }

        // 🔥 WIN/LOSE CHECK
        if (player->hp <= 0)
        {
            return handlePlayerDefeat(player, &enemy, baseDef, baseSpd);
        }

        if (enemy.hp <= 0)
        {
            return handleEnemyDefeat(player, &enemy, zoneIndex, progress, baseDef, baseSpd);
        }
        
    }

    player->defense = baseDef;
    player->speed = baseSpd;
    return -1;
}