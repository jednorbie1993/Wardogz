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

// extern globals from dog.c
extern int animationOn;

int cinematicMode = 1;

void cinematicPause(int ms)
{
    if (cinematicMode)
        Sleep(ms);
}

void cinematicDots(const char *text)
{
    printf("\n%s", text);

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
    printf("====================================\n");
}

void showEnemyEntrance(Dog *enemy, int zoneIndex)
{
    printf("\n");
    if (strcmp(enemy->name, "Grimfang") == 0)
    {
        typeText("\"The streets belong to the strongest.\"", 25);

        printf("\n\n");

        typeText("Grimfang emerged!", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (strcmp(enemy->name, "Diremaw") == 0)
    {
        typeText("\"The wild doesn't care who you are. It only decides who remains.\"", 25);

        printf("\n\n");

        typeText("Diremaw emerged!", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (strcmp(enemy->name, "Blackclaw") == 0)
    {
        typeText("\"We were weapons... until we learned who the real enemy was.\"", 25);

        printf("\n\n");

        typeText("Blackclaw emerged!", 25);

        printf("\n");
        waitForEnter();

        return;
    }
    if (strcmp(enemy->name, "Omega Prime") == 0)
    {
        typeText("\"The experiment is complete... and you are the final test.\"", 25);

        printf("\n\n");

        typeText("Omega Prime emerged!", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (strcmp(enemy->name, "Commander Cerberus") == 0)
    {
        typeText("\"Prototype command unit online. Target acquired.\"", 25);

        printf("\n\n");

        typeText("Commander Cerberus deployed!", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (strcmp(enemy->name, "Project Cerberus") == 0)
    {
        typeText("\"The final subject is awake.\"", 25);

        printf("\n\n");

        typeText("[FINAL CONTAINMENT BREACH]", 25);
        printf("\n");
        typeText("Project Cerberus steps out of the chamber.", 25);
        printf("\n");
        typeText("Its body looks more humanoid than dog.", 25);
        printf("\n");
        typeText("Mutation veins pulse across its frame.", 25);

        printf("\n");
        waitForEnter();

        return;
    }

    if (zoneIndex >= 16 && zoneIndex <= 20)
    {
        typeText(enemy->name, 25);
        typeText(" deployed!", 20);
    }
    else if (zoneIndex >= 8 && zoneIndex <= 11)
    {
        typeText(enemy->name, 25);
        typeText(" arrived!", 20);
    }
    else if (zoneIndex >= 3 && zoneIndex <= 7)
    {
        typeText(enemy->name, 25);
        typeText(" emerged!", 20);
    }
    else
    {
        typeText(enemy->name, 25);
        typeText(" appeared!", 20);
    }

    printf("\n");
    waitForEnter();
}


void showHPBarPlayer(int hp, int maxHp)
{
    static int lastHP = -1;

    // 🔥 RESET SIGNAL (for new battle)
    if (hp == -1)
    {
        lastHP = -1;
        return;
    }

    // 👉 Clamp safety
    if (hp < 0)
        hp = 0;
    if (hp > maxHp)
        hp = maxHp;

    // 👉 FIRST DRAW (instant, no animation)
    if (lastHP == -1)
    {
        lastHP = hp;

        int bars = (hp * 10) / maxHp;

        printf("\rPLAYER: [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)\n", hp, maxHp);
        return;
    }

    // 👉 NO ANIMATION MODE
    if (!animationOn)
    {
        int bars = (hp * 10) / maxHp;

        printf("\rPLAYER: [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)\n", hp, maxHp);

        lastHP = hp;
        return;
    }

    // 👉 ANIMATION MODE
    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        int bars = (current * 10) / maxHp;

        printf("\rPLAYER: [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)   ", current, maxHp);

        fflush(stdout);
        Sleep(20);
    }

    // 👉 FINAL EXACT VALUE
    int bars = (hp * 10) / maxHp;

    printf("\rPLAYER: [");
    for (int i = 0; i < 10; i++)
        printf(i < bars ? "#" : "-");

    printf("] (%d/%d)\n", hp, maxHp);

    lastHP = hp;
}

// ================= HP BAR ENEMY =================
void showHPBarEnemy(int hp, int maxHp)
{
    static int lastHP = -1;

    // 🔥 RESET SIGNAL (para sa new battle)
    if (hp == -1)
    {
        lastHP = -1;
        return;
    }

    // 👉 Clamp safety
    if (hp < 0)
        hp = 0;
    if (hp > maxHp)
        hp = maxHp;

    // 👉 FIRST DRAW (no animation, instant)
    if (lastHP == -1)
    {
        lastHP = hp;

        int bars = (hp * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)\n", hp, maxHp);
        return;
    }

    // 👉 NO ANIMATION MODE
    if (!animationOn)
    {
        int bars = (hp * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)\n", hp, maxHp);

        lastHP = hp;
        return;
    }

    // 👉 ANIMATION
    int step = (hp > lastHP) ? 1 : -1;

    for (int current = lastHP; current != hp; current += step)
    {
        int bars = (current * 10) / maxHp;

        printf("\rENEMY : [");
        for (int i = 0; i < 10; i++)
            printf(i < bars ? "#" : "-");

        printf("] (%d/%d)   ", current, maxHp);

        fflush(stdout);
        Sleep(20);
    }

    // 👉 FINAL EXACT VALUE
    int bars = (hp * 10) / maxHp;

    printf("\rENEMY : [");
    for (int i = 0; i < 10; i++)
        printf(i < bars ? "#" : "-");

    printf("] (%d/%d)\n", hp, maxHp);

    lastHP = hp;
}

// ================= DISPLAY =================
void displayBattleStatus(Dog player, Dog enemy)
{
    printf("====================================\n");
    showHPBarPlayer(player.hp, player.maxHP);
    showHPBarEnemy(enemy.hp, enemy.maxHP);
    printf("====================================\n");
}

void criticalHPScene(Dog *player)
{
    if (player->hp > 20)
        return;

    int msg = rand() % 3;

    if (msg == 0)
        printf("%s is barely standing...\n", player->name);
    else if (msg == 1)
        printf("Blood drips onto the ground...\n");
    else
        printf("%s struggles to keep fighting...\n", player->name);

}
// ================= LOSE =================

void loseSequence(Dog *player, Dog *enemy)
{
    printf("\nYOU LOST...\n");
    Sleep(500);

    printf("Recovering");
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        Sleep(150);
    }

    player->hp = player->maxHP;
    enemy->hp = enemy->maxHP;

    printf("\nYou are back to full HP!\n");
}

int handlePlayerDefeat(Dog *player, Dog *enemy, int baseDef, int baseSpd)
{
    player->hp = 0;

    system("cls");
    displayBattleStatus(*player, *enemy);

    int loseMsg = rand() % 3;

    if (loseMsg == 0)
        printf("\nYou collapse from exhaustion...\n");
    else if (loseMsg == 1)
        printf("\nYour vision starts to fade...\n");
    else
        printf("\nYou can no longer continue fighting...\n");

    Sleep(900);

    printf("\n YOU LOSE \n");

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
        printf("\nFinishing blow!\n");
    else if (defeatMsg == 1)
        printf("\n%s can no longer fight...\n", enemy->name);
    else
        printf("\n%s collapsed...\n", enemy->name);

    Sleep(700);

    if (strcmp(enemy->name, "Blackclaw") == 0)
    {
        typeText("Blackclaw lowers his head.", 25);
        printf("\n");

        waitForEnter();
        printf("\n");

        typeText("\"The battlefield... belongs to no one.\"", 25);
        printf("\n");
        waitForEnter();
    }

    printf("\n YOU WIN! \n");


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
        printf("You must rest before you battle again!\n");
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
            int remaining = 120 - (int)(elapsed / 1000);

            if (remaining < 0)
                remaining = 0;

            printf("[SELF DESTRUCT TIMER] %02d:%02d\n", remaining / 60, remaining % 60);
        }

        if (player->hp <= 20)
        {
            printf("\n [DANGER] Critical HP!\n");
        }

        printf("\n--- YOUR TURN ---\n");
        if (player->fatigue <= 20)
            printf("Exhausted!\n");

        printf("1. Attack  2. Defend  3. Heal  4. Surrender\n");
        printf("Choice: ");

        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &choice) != 1 || choice < 1 || choice > 4)
        {
            printf("Invalid!\n");
            waitForEnter();
            continue;
        }

        // 🔥 PLAYER ACTIONS
        if (choice == 1) // Attack
        {

            system("cls");
            displayBattleStatus(*player, enemy);

            printf("Skills:\n");

            for (int j = 0; j < 4; j++)
            {
                if (player->equipped[j] != -1)
                {
                    int idx = player->equipped[j];
                    printf("%d. %s (P:%d C:%d)\n", j + 1,
                           player->skills[idx].name,
                           player->skills[idx].power,
                           player->skills[idx].cost);
                }
                else
                    printf("%d. ---\n", j + 1);
            }

            fgets(buffer, sizeof(buffer), stdin);
            if (sscanf(buffer, "%d", &move) != 1 || move < 1 || move > 4)
            {
                printf("Invalid skill!\n");
                waitForEnter();
                continue;
            }
            system("cls");
            displayBattleStatus(*player, enemy);

            int skillIdx = player->equipped[move - 1];
            if (skillIdx == -1)
            {
                printf("No skill!\n");
                waitForEnter();
                continue;
            }

            Skill s = player->skills[skillIdx];

            if (player->fatigue < s.cost)
            {
                printf("\nLow energy! Weak attack!\n");
                cinematicPause(500);

                system("cls");
                displayBattleStatus(*player, enemy);

                cinematicDots("Player attacking");

                useSkill(player, &enemy, s);

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

                useSkill(player, &enemy, s);

                waitForEnter();

                if (enemy.hp < 0)
                    enemy.hp = 0;

                system("cls");
                displayBattleStatus(*player, enemy);

                printf("\n");

                playEnemyBattleDialogue(zoneIndex, enemy.name);
                printf("\n");

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
            printf("Defending!\n");
            waitForEnter();
        }
        else if (choice == 3) // Heal
        {
            player->hp += 20;
            if (player->hp > player->maxHP)
                player->hp = player->maxHP;

            printf("Healed +20 HP!\n");
            waitForEnter();
        }
        else if (choice == 4) // Surrender
        {
            printf("\nSurrendered...\n");
            waitForEnter();

            player->defense = baseDef;
            player->speed = baseSpd;
            return 2;
        }

        // 🔥 ENEMY TURN
        if (player->hp > 0 && enemy.hp > 0)
        {
            Sleep(500);
            int result = enemyAttack(player, &enemy, &defending);
            if (result == 0)
                player->hp = 0;
            if (result == 1)
                enemy.hp = 0;

            defending = 0;
        }
        // 👉 RESET DEFENSE AFTER TURN
        // 🔥 FATIGUE REGEN
        player->fatigue += 2;
        if (player->fatigue > player->maxFatigue)
            player->fatigue = player->maxFatigue;

        battleTurn++;

        if (strcmp(enemy.name, "Project Cerberus") == 0)
        {
            if (!enemy.regenerationUsed &&
                battleTurn >= enemy.regenerationTurn)
            {
                system("cls");
                displayBattleStatus(*player, enemy);

                typeText("\n[MUTATION OVERDRIVE]\n", 25);
                typeText("Project Cerberus fully regenerates!\n", 25);

                enemy.hp = enemy.maxHP;
                enemy.regenerationUsed = 1;

                waitForEnter();
            }
        }    

        if (cerberusTimerActive)
        {
            DWORD elapsed = GetTickCount() - cerberusStartTime;

            if (elapsed >= 120000)
            {
                system("cls");
                typeText("[BLACKSITE SELF-DESTRUCT]\n\n", 25);
                typeText("The final chamber overloads.\n", 25);
                typeText("You failed to stop Project Cerberus in time.\n", 25);
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