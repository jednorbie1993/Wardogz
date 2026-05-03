#ifndef DOG_H
#define DOG_H

#define MAX_SKILLS 10
#define MAX_STAT 999
#define MIN_STAT 0

#define SKILL_ATTACK 1
#define SKILL_BUFF 2
#define SKILL_HEAL 3

extern int systemLog;
extern int animationOn;

// 🔥 ADD THIS (Skill IDs)
typedef enum {
    SKILL_NONE = -1,
    SKILL_BITE,
    SKILL_SCRATCH,
    SKILL_QUICK_DASH,
    SKILL_FLASH_STEP,
    SKILL_HEAVY_BITE,
    SKILL_SAVAGE_FANG,
    SKILL_IRON_GUARD,
    SKILL_SURE_STRIKE,
    SKILL_LAST_STAND
} SkillID;

// 🔥 SKILL STRUCT (ADD id ONLY — no structure change)
typedef struct {
    char name[30];
    int power;
    int cost;
    int type;
    int id;   // ✅ NEW (safe addition)
} Skill;

// 🔥 FINAL DOG STRUCT (UNCHANGED)
typedef struct {
    char name[50];

    int hp, maxHP;
    int attack, defense, speed;
    int accuracy, intelligence;
    int fatigue;
    int maxFatigue;
    int isConfused;
    int confuseTurns;
    int isBleeding;
    int bleedTurns;

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
void checkSkillUnlock(Dog *d);
int hasSkill(Dog *d, char name[]);
int clampFatigue(int f, int max);
void applySkillEffect(Dog *player, Dog *enemy, Skill s, int *damage);

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
int getFatiguePenalty(int fatigue);
int isCritical(int hp, int maxHP);

int sparringBattle(Dog *player, int type);
void createSparPartner(Dog *e, int type);
void sparringDog(Dog *player, int type);
void sparringMenu(Dog *player);
#endif