#ifndef DOG_H
#define DOG_H

#define MAX_SKILLS 10
#define MAX_STAT 999
#define MIN_STAT 0

extern int systemLog;
extern int animationOn;

// 🔥 SKILL STRUCT
typedef struct {
    char name[30];
    int power;
    int cost;
} Skill;

// 🔥 FINAL DOG STRUCT (WITH SKILLS NA)
typedef struct {
    char name[50];

    int hp, maxHP;
    int attack, defense, speed;
    int accuracy, intelligence;
    int fatigue;
    int maxFatigue;

    Skill skills[MAX_SKILLS];
    int skillCount;

    int equipped[4]; // 4 slots only
} Dog;

// ================= CORE =================
void createDog(Dog *d);
void printDog(Dog d);
int battle(Dog *player, int zoneIndex, int progress[]);
void displayBattleStatus(Dog player, Dog enemy);
void waitForEnter();
void pauseAndClear();
void loseSequence(Dog *player, Dog *enemy);

// ================= PLAYER SYSTEM =================
int playerTurn(Dog *player, Dog *enemy, int *defending);
void playerAttack(Dog *player, Dog *enemy);
void skillMenu(Dog *d);

// ================= UI =================
void showHPBarPlayer(int hp, int maxHp);

// ================= SYSTEM =================
void applyBattleStatGain(Dog *d);
void trainDog(Dog *d, int type);
void preBattleScene();

// ================= ENEMY =================
void createEnemy(Dog *e);
int enemyAttack(Dog *player, Dog *enemy, int *defending);
void enemyQuickAttack(Dog *player, Dog *enemy);
void setEnemyByZone(Dog *enemy, int zoneIndex, int i);
void enemyTurn(Dog *player, Dog *enemy, int *defending);

// ================= UTIL =================
int clamp(int value);
int clampFatigue(int value);
int getFatiguePenalty(int fatigue);
int isCritical(int hp, int maxHP);

#endif